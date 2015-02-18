#ifndef REPORTER_H
#define REPORTER_H

#include <string>
using std::string;
#include <iostream>
using std::ostream;

#include "result.h"

namespace DnaDiff {

class Reporter {
public:
    Reporter();
    virtual ~Reporter();

    virtual string GenerateReport (const Result &);

protected:
    virtual void ListDifferences (ostream &, const Result &) = 0;
};

}

#endif // REPORTER_H
