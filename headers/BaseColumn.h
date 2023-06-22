#ifndef BASE_COLUMN_H
#define BASE_COLUMN_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include <stdexcept>
#include "StringOperations.h"

using std::string;
using std::vector;

// Base class of columns
class BaseColumn {
protected:
    string typeOfColumn;
public:
    BaseColumn() = default;
    BaseColumn(const string& value);

    // Returns the type of column
    const string& getTypeOfColumn() const;
    virtual ~BaseColumn() = default;

    // Pure virtual methods
    virtual void addValueInColumn(const string& value) = 0;
    virtual const string  getValueAtIndex(unsigned index) const = 0;

    virtual const vector<string> getColumn() const = 0;

    virtual void removeValueAt(unsigned index) = 0;

    virtual const unsigned getSize() const = 0;

    virtual const string getMinimalValue() const = 0;
    virtual const string getMaximalValue() const = 0;

    virtual const vector<unsigned> getIndexesOfSortedColumn(char s) const = 0; 
};

#endif //BASE_COLUMN_H