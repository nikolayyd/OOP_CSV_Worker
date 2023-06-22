#include "../headers/NumberColumn.h"

NumberColumn::NumberColumn() : BaseColumn("Number"), numberValues() {}

void NumberColumn::addValueInColumn(const string& value) {
    long double number;
    number = std::stold(value);
    numberValues.push_back(number);
}

const string NumberColumn::getValueAtIndex(unsigned index) const {
    string numberToString;
    if (index < numberValues.size()) {
        numberToString = std::to_string(numberValues.at(index));
        StringOperations::removeTrailingNulls(numberToString);
        return numberToString;
    } else {
        throw std::out_of_range("Error in method getValueAtIndex(NumberColumn)!"); 
    }

}

const vector<string> NumberColumn::getColumn() const {
    vector<string> numberValuesToString;
    string currentValue;

    if (numberValues.size() > 0) {
        for (long double num : numberValues)
        {
            currentValue = std::to_string(num);
            StringOperations::removeTrailingNulls(currentValue);
            numberValuesToString.push_back(currentValue);
        }
    } else {
        throw std::runtime_error("Empty column(NumberColumn)!"); 
    }

    return numberValuesToString;
}

const unsigned NumberColumn::getSize() const {
    return numberValues.size();
}

void NumberColumn::removeValueAt(unsigned index) {
    numberValues.erase(numberValues.begin() + index);
} 

const string NumberColumn::getMinimalValue() const {
    double minimalNum = StringOperations::findMinimalNum(numberValues);
    string minimalNumInString = std::to_string(minimalNum);
    return minimalNumInString;
}

const string NumberColumn::getMaximalValue() const {
    double maximalNum = StringOperations::findMaximalNum(numberValues);
    string maximalNumInString = std::to_string(maximalNum);

    return maximalNumInString;
}

const vector<unsigned> NumberColumn::getIndexesOfSortedColumn(char s) const {
    return StringOperations::getIndexesOfNumberSorted(numberValues, s);
}
