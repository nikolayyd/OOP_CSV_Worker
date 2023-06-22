#include "../headers/TextColumn.h"

    // vector<string> textValues;

TextColumn::TextColumn() : BaseColumn("Text"), textValues() {}

void TextColumn::addValueInColumn(const string& value) {
    
    if (StringOperations::checkIsTextInQuotes(value)) {
        textValues.push_back(StringOperations::removeQuotesInText(value));
    } else {
        textValues.push_back(value);
    }
}

const string TextColumn::getValueAtIndex(unsigned index) const {
    if (index < textValues.size()) {
        return textValues.at(index);
    } else {
        throw std::out_of_range("Error while executing getValueOfIndex(TextValues)"); 
    }
}

const vector<string> TextColumn::getColumn() const {
    if (textValues.size() > 0) {
        return textValues;
    } else {
        throw std::runtime_error("Emty column!"); 
    }
}

const unsigned TextColumn::getSize() const {
    return textValues.size();
}

void TextColumn::removeValueAt(unsigned index) {
    textValues.erase(textValues.begin() + index);
}

const string TextColumn::getMinimalValue() const {
    return StringOperations::findMinimalString(textValues);
}

const string TextColumn::getMaximalValue() const {
    return StringOperations::findMaximalString(textValues);
}

const vector<unsigned> TextColumn::getIndexesOfSortedColumn(char s) const {  
    return StringOperations::getIndexesOfStringSorted(textValues, s);
}
