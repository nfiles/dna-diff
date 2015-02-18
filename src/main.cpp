#include <iostream>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;

#include "engine.h"
#include "reporter.h"
#include "column-reporter.h"
#include "blast-reporter.h"

enum REPORT_FORMAT {
    REPORT_BLAST,
    REPORT_COLUMNS
};
enum ARG_STATE {
    READ_DEFAULT,
    READ_FORMAT
};

const string NAME = "dna-diff";
const string USAGE = NAME + " [options]\n" +
                     "\t-f --format [format]: format of report\n" +
                     "\t\tblast, column\n" +
                     "\t-r --rna: accept RNA base (U: Uracil)";

int main (int argc, const char *args[])
{
    bool accept_rna = false;
    REPORT_FORMAT report_format = REPORT_BLAST;
    ARG_STATE arg_state = READ_DEFAULT;

    // read and interpret command-line arguments
    string arg;
    for (int i = 1; i < argc; ++i) {
        arg = string(args[i]);
        switch (arg_state) {
            case READ_FORMAT:
                if (arg == "blast") {
                    report_format = REPORT_BLAST;
                } else if (arg == "column") {
                    report_format = REPORT_COLUMNS;
                } else {
                    cerr << "Invalid format type: " << arg << endl
                         << USAGE << endl;
                    return 1;
                }

                arg_state = READ_DEFAULT;
                break;
            default:
                if (arg == "-f" || arg == "--format") {
                    arg_state = READ_FORMAT;
                } else if (arg == "-r" || arg == "--rna") {
                    accept_rna = true;
                } else {
                    cerr << USAGE << endl;
                    return 1;
                }
        }
    }

    // read strands
    string strand1, strand2;
    cin >> strand1 >> strand2;

    // compute differences
    DnaDiff::Engine engine(accept_rna);
    DnaDiff::Result result = engine.CompareDna(strand1, strand2);

    DnaDiff::Reporter *reporter;
    if (report_format == REPORT_BLAST) {
        reporter = new DnaDiff::BlastReporter();
    } else if (report_format == REPORT_COLUMNS) {
        reporter = new DnaDiff::ColumnReporter();
    } else {
        reporter = new DnaDiff::ColumnReporter();
    }

    cout << reporter->GenerateReport(result);

    delete reporter;

    return 0;
}
