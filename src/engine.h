#ifndef ENGINE_H
#define ENGINE_H

#include <string>
using std::string;
#include <vector>
using std::vector;

#include "result.h"

namespace DnaDiff {

class Engine {
public:
    Engine ( bool rna = false ): _rna(rna)
    {
        DNA_BASES.push_back('A');
        DNA_BASES.push_back('T');
        DNA_BASES.push_back('C');
        DNA_BASES.push_back('G');

        RNA_BASES.push_back('A');
        RNA_BASES.push_back('T');
        RNA_BASES.push_back('U');
        RNA_BASES.push_back('C');
        RNA_BASES.push_back('G');
    }

    // compare 2 strands of DNA
    Result CompareDna (const string &, const string &,
                       const string &filename = "");

private:
    bool _rna;

    vector<char> DNA_BASES;
    vector<char> RNA_BASES;
};

}

#endif // ENGINE_H
