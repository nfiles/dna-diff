#ifndef COLUMN_REPORTER_H
#define COLUMN_REPORTER_H

#include <string>
using std::string;
#include <iostream>
using std::ostream;

#include "result.h"
#include "reporter.h"

namespace DnaDiff {

class ColumnReporter : public Reporter {
public:
    ColumnReporter();

protected:
    virtual void ListDifferences (ostream &, const Result &);
};

}

#endif // COLUMN_REPORTER_H
