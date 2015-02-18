#include <iostream>
using std::endl;
#include <iomanip>
using std::setw;
using std::left;
using std::right;

#include "blast-reporter.h"

namespace DnaDiff {

BlastReporter::BlastReporter () { }

void BlastReporter::ListDifferences(ostream &out,
                                    const Result &diff_result)
{
    unsigned int len = diff_result.differences.size();
    unsigned int row, col, head, index;
    unsigned int width = 60;
    unsigned int title_width = 8;
    unsigned int left_width = 5;
    unsigned int right_width = 5;

    string empty = "";

    for (row = 0; (head = row * width) < len; ++row) {
        // genome 1
        out << setw(title_width) << left << "Gen. 1"
            << setw(left_width) << left << head + 1;
        for (col = 0; col < width && (index = head + col) < len; ++col) {
            out << static_cast<char>(toupper(diff_result.strand1[index]));
        }
        out << setw(width - col + 1) << empty
            << setw(right_width) << right << head + col << endl;

        // differences
        out << setw(title_width + left_width) << empty;
        for (col = 0; col < width && (index = head + col) < len; ++col) {
            out << (diff_result.differences[index] ? empty : "|");
        }
        out << endl;

        // genome 2
        out << setw(title_width) << left << "Gen. 2"
            << setw(left_width) << left << head + 1;
        for (col = 0; col < width && (index = head + col) < len; ++col) {
            out << static_cast<char>(toupper(diff_result.strand2[index]));
        }
        out << setw(width - col + 1) << empty
            << setw(right_width) << right << head + col << endl;

        out << endl;
    }
}

}
