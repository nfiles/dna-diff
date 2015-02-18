#include "engine.h"

namespace DnaDiff {

Result Engine::CompareDna(const string &strand1, const string &strand2,
                          const string &filename)
{
    unsigned int strand1_length = strand1.length();
    unsigned int strand2_length = strand2.length();

    unsigned int min_strand_length = strand1_length < strand2_length
                                     ? strand1_length
                                     : strand2_length;

    Result result;
    result.filename = filename;
    result.strand1  = strand1;
    result.strand2  = strand2;

    //the bases to be compared
    char base1, base2;
    // compare the sequence of each genome
    for (unsigned int i = 0; i < min_strand_length; ++i) {
        base1 = tolower(strand1[i]);
        base2 = tolower(strand2[i]);

        // check for invalid base pairs
        switch (base1) {
            case 'a': case 't': case 'c': case 'g':
                break;

            case 'u':
                if (_rna)
                    break;

            default:
                result.invalid_strand1.push_back(i);
                break;
        }

        switch (base2) {
            case 'a': case 't': case 'c': case 'g':
                break;

            case 'u':
                if (_rna)
                    break;
            default:
                result.invalid_strand2.push_back(i);
                break;
        }

        //are the base codes different?
        if (base1 != base2) {
            result.differences.push_back(true);
            result.diff_count = result.diff_count + 1;
        } else {
            result.differences.push_back(false);
        }
    }

    // TODO: set the valid bases
    result.valid_bases = _rna ? RNA_BASES : DNA_BASES;

    return result;
}

}
