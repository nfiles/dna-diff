#ifndef RESULT_H
#define RESULT_H

#include <string>
using std::string;
#include <vector>
using std::vector;

namespace DnaDiff {

struct Result {
    Result(): diff_count(0) { }

    string filename;

    string strand1;
    string strand2;

    unsigned int diff_count;
    vector<bool> differences;

    vector<unsigned int> invalid_strand1;
    vector<unsigned int> invalid_strand2;

    vector<char> valid_bases;
};

}

#endif // RESULT_H
