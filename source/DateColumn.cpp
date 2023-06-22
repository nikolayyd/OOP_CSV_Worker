#include "../headers/DateColumn.h"

DateColumn::DateColumn () : BaseColumn("Date"), dateValues() {}

void DateColumn::addValueInColumn(const string& value) {
    dateValues.push_back(value);
}

const string DateColumn::getValueAtIndex(unsigned index) const {
    if (index < dateValues.size()) {
        return dateValues.at(index);
    } else {
        throw std::out_of_range("Error in method getValueAtIndex(DateColumn)"); 
    }
}

const vector<string> DateColumn::getColumn() const {
    if (dateValues.size() > 0) {
        return dateValues;
    } else {
        throw std::runtime_error("Empty column!");
    }
}

const unsigned DateColumn::getSize() const {
    return dateValues.size();
}

void DateColumn::removeValueAt(unsigned index) {
    dateValues.erase(dateValues.begin() + index);
} 

const string DateColumn::getMinimalValue() const {
    return StringOperations::findMinimalString(dateValues);
}

const string DateColumn::getMaximalValue() const {
    return StringOperations::findMaximalString(dateValues);
}

const vector<unsigned> DateColumn::getIndexesOfSortedColumn(char s) const {
    return StringOperations::getIndexesOfStringSorted(dateValues, s);
}
