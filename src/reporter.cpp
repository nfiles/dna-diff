#include <iostream>
using std::endl;
#include <iomanip>
using std::setw;
using std::left;
using std::right;
using std::setprecision;
#include <sstream>
using std::stringstream;

#include "reporter.h"

namespace DnaDiff {

Reporter::Reporter() { }
Reporter::~Reporter() { }

string Reporter::GenerateReport(//const string &filename,
    const Result &diff_result)
{
    stringstream out;

    if (diff_result.filename.length() > 0) {
        out << "File: " << diff_result.filename << endl << endl;
    }

    unsigned int strand1_length = diff_result.strand1.length();
    unsigned int strand2_length = diff_result.strand2.length();

    bool invalid_bases_exist = (diff_result.invalid_strand1.size() > 0) ||
                               (diff_result.invalid_strand2.size() > 0);

    bool strand_lengths_are_different = (strand1_length != strand2_length);

    float percent;
    if (!invalid_bases_exist && !strand_lengths_are_different) {
        this->ListDifferences(out, diff_result);

        percent = (float)diff_result.diff_count /
                  (float)strand1_length * 100.0;

        out << left << setw(20) << "Length of sequence:"
            << right << setw(5) << strand1_length << endl
            << left << setw(20) << "Differences:"
            << right << setw(5) << diff_result.diff_count << endl
            << left << setw(20) << "Percent different:"
            << right << setw(5) << setprecision(4) << percent << "%" << endl;

    } else if (strand_lengths_are_different) { //different input line lengths

        out << "The strands are different lengths." << endl
            << "Line 1: " << strand1_length << endl
            << "Line 2: " << strand2_length << endl;

    } else { //invalid base codes

        char base;
        unsigned int invalid_index;
        unsigned int i, size;

        out << "Invalid base codes found" << endl;

        // valid base codes
        size = diff_result.valid_bases.size();
        if (size > 0) {
            out << "Valid base codes: ";
            for (i = 0; i < size - 1; ++i) {
                out << diff_result.valid_bases[i] << ", ";
            }
            out << diff_result.valid_bases[i] << endl;
        }

        // invalid codes from strand 1
        size = diff_result.invalid_strand1.size();
        if (size > 0) {
            out << endl
                << "Sequence 1: " << size << " invalid codes" << endl
                << "Index    Code" << endl;

            for (i = 0; i < size; ++i) {
                invalid_index = diff_result.invalid_strand1[i];
                base = diff_result.strand1[invalid_index];
                out << " " << setw(9) << left << invalid_index << base << endl;
            }
        }

        // invalid codes from strand 2
        size = diff_result.invalid_strand2.size();
        if (size > 0) {
            out << endl
                << "Sequence 2: " << size << " invalid codes" << endl
                << setw(9) << left << "Index" << "Code" << endl;

            for (i = 0; i < size; ++i) {
                invalid_index = diff_result.invalid_strand2[i];
                base = diff_result.strand2[invalid_index];
                out << " " << setw(9) << left << invalid_index << base << endl;
            }
        }
    }

    out.flush();

    return out.str();
}

}