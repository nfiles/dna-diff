#include <iostream>
using std::endl;
#include <iomanip>
using std::setw;
using std::left;

#include "column-reporter.h"

namespace DnaDiff {

ColumnReporter::ColumnReporter () { }

void ColumnReporter::ListDifferences(ostream &out,
                                     const Result &diff_result)
{
    string in1 = diff_result.strand1;
    out << "     -1-    -2-    Different?" << endl;
    char mark, base1, base2;
    for (unsigned int i = 0; i < in1.length(); ++i) {
        mark = diff_result.differences[i] ? 'X' : ' ';
        base1 = static_cast<char>(toupper(diff_result.strand1[i]));
        base2 = static_cast<char>(toupper(diff_result.strand2[i]));
        out << setw(6) << left << i + 1
            << setw(7) << left << base1
            << setw(8) << left << base2
            << mark << endl;
    }
    out << endl;
}

}
