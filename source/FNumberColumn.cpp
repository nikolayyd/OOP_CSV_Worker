#include "../headers/FNumberColumn.h"

FNumberColumn::FNumberColumn() : BaseColumn("FacultyNumber"), facultyNumberValues() {}

void FNumberColumn::addValueInColumn(const string& value) {
    facultyNumberValues.push_back(value);
}

const string FNumberColumn::getValueAtIndex(unsigned index) const {
    if (index < facultyNumberValues.size()) {
        return facultyNumberValues.at(index);
    } else {
        throw std::out_of_range("Error in method getValue(FacultyNumberColumns)"); 
    }
}

const vector<string> FNumberColumn::getColumn() const {
    if (facultyNumberValues.size() > 0) {
        return facultyNumberValues;
    } else {
        throw std::runtime_error("Empty column!"); 
    }
}

const unsigned FNumberColumn::getSize() const {
    return facultyNumberValues.size();
}

void FNumberColumn::removeValueAt(unsigned index) {
    facultyNumberValues.erase(facultyNumberValues.begin() + index);
} 

const string FNumberColumn::getMinimalValue() const {
    return StringOperations::findMinimalString(facultyNumberValues);
}

const string FNumberColumn::getMaximalValue() const {
    return StringOperations::findMaximalString(facultyNumberValues);
}

const vector<unsigned> FNumberColumn::getIndexesOfSortedColumn(char s) const {
    return StringOperations::getIndexesOfStringSorted(facultyNumberValues, s);
}
