#ifndef BLAST_REPORTER_H
#define BLAST_REPORTER_H

#include <string>
using std::string;
#include <iostream>
using std::ostream;

#include "result.h"
#include "reporter.h"

namespace DnaDiff {

class BlastReporter : public Reporter {
public:
    BlastReporter();

protected:
    virtual void ListDifferences (ostream &, const Result &);
};

}

#endif // BLAST_REPORTER_H
