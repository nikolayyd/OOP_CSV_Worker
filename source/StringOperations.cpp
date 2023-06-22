#include "../headers/StringOperations.h"

// Check if symbol is letter
bool StringOperations::isLetter(char symbol) {
    return (tolower(symbol) >= 'a' && 
        tolower(symbol) <= 'z');
}

// Swap two string values
void StringOperations::swapString(string& a, string& b) {
    string temp = a;
    a = b;
    b = temp;
}


// Swap two long double values
void StringOperations::swapLongDouble(long double& a, long double& b) {
    long double temp = a;
    a = b;
    b = temp;
}

// Swap two indexes (unsigned) 
void StringOperations::swapIndexes(unsigned& a, unsigned& b) {
    unsigned temp = a;
    a = b;
    b = temp;
}

// Getting the name of the file
const string StringOperations::getFileName(const string& path) {
    string copyPath = path;
    size_t indexOfSlash = copyPath.find_last_of('\\');
    
    if (indexOfSlash != string::npos) {
        copyPath = path.substr(indexOfSlash + 1, path.size());
    }


    if (copyPath.substr(copyPath.size() - 3, copyPath.size()) != "csv") {
        throw std::runtime_error("Invalid file format!");
    }
    return copyPath;
}


// Finding the minimal string of column
const string StringOperations::findMinimalString(const vector<string>& values) {
    string currentValue = values.front();

    for (const string& value : values)
    {
        if (value < currentValue) {
            currentValue = value;
        }
    }
    
    return currentValue;
}

// Finding the minimal number of column
const double StringOperations::findMinimalNum(const vector<long double>& values) {
    long double currentNum = values.front();

    for (long double num : values)
    {
        if (num < currentNum) {
            currentNum = num;
        }
    }

    return currentNum;
}

// Finding the maximal string of column
const string StringOperations::findMaximalString(const vector<string>& values) {
    string currentValue = values.front();

    for (const string& value : values)
    {
        if (value > currentValue) {
            currentValue = value;
        }
    }
    
    return currentValue;
}

// Finding the maximal number of column
const double StringOperations::findMaximalNum(const vector<long double>& values) {
    long double currentNum = values.front();

    for (long double num : values)
    {
        if (num > currentNum) {
            currentNum = num;
        }
    }
    
    return currentNum;
}

// Reworking the filePath from console for file works in the program
const string& StringOperations::makePathEscapeSym(string& path) {
    char s;
    for (unsigned i  = 0; i < path.size(); i++) {
        s = path.at(i);
        
        if (s == '\\') {
            path.insert(++i, "\\");
            ++i;
        }
    }

    return path;
    
}

// This method removes trailing nulls
void StringOperations::removeTrailingNulls(string& value) {
    char s;
    s = value.back();
    while (s == '0')
    {
        value.pop_back();
        s = value.back();
    }
        
        if (s == '.') {
            value.pop_back();
        } 
}

// Check if the value is title (or text) 
bool StringOperations::checkIsTitle(const string& title) {
    return isLetter(title[0]) ? true : false;
}

// Check if text is in the quotes
bool StringOperations::checkIsTextInQuotes(const string& value) {
    return (value[0] == '"' && value.back() == '"') ||
        (value[0] == '\'' && value.back() == '\''); 
}

// Check if value type is date
bool StringOperations::checkIsDate(const string& date) {
    string dateCopy = date;
    size_t indexSlash = 0;
    unsigned countOfSlashes = 0;

    while (dateCopy.size() != 0) {
        indexSlash = dateCopy.find_first_of('-');    
        if (indexSlash == string::npos) {
            return (countOfSlashes == 2) ? true : false;
        } 
        else {
            dateCopy = dateCopy.substr(indexSlash + 1, dateCopy.size());
            countOfSlashes++;
        }
    }

    return false;
}

// Splits the row
const string StringOperations::splitRow(size_t indexComma, string& rowCopy) {
    string currentTitle;

    indexComma = rowCopy.find_first_of(',');
    if (indexComma != string::npos) {
        currentTitle = rowCopy.substr(0, indexComma);
        rowCopy = rowCopy.substr(indexComma + 1, rowCopy.size());
    } 
    else {
        currentTitle = rowCopy;
        rowCopy.erase();
    }

    return currentTitle;
}

// Cast string to number
unsigned StringOperations::stringToNumber(const string& str) {
    unsigned number;
    try {
        number = std::stoi(str);
    }
    catch(...) {
        throw std::invalid_argument("Trying to cast value which is no number!");
    }

    return number;
}

// Count commas in row, used for syntax check of file 
const unsigned StringOperations::countCommas(const string& row) {
    unsigned count = 0;
    size_t indexComma;
    string rowCopy = row;

    while (rowCopy.size() != 0) {
        indexComma = rowCopy.find_first_of(',');
        if (indexComma == string::npos) {
            rowCopy.clear();
            break;
        }
        count++;
        rowCopy = rowCopy.substr(indexComma + 1, rowCopy.size());
    }

    return count;
}

// Remove quotes from values with type text when opening the file
const string StringOperations::removeQuotesInText(const string& value) {
    string valueWithoutQuotes = value;
    valueWithoutQuotes = valueWithoutQuotes.substr(1, valueWithoutQuotes.size());
    valueWithoutQuotes.pop_back();

    return valueWithoutQuotes;
}

// Adding quotes to values of type text while saving the file
const string StringOperations::addQuotes(const string& currentValue) {
    string copyValue = currentValue;
    // if it is 1 element, single quotes, else double.
    if (copyValue.size() == 1) {
        copyValue.insert(0, "'");
        copyValue.push_back('\'');
    } 
    else {
        copyValue.insert(0, "\"");
        copyValue.push_back('\"');
    }

    return copyValue;
}

// Splits date for validation
const vector<string> StringOperations::splitDate(const string& date) {
    string dateCopy = date;
    vector<string> buffer;
    size_t indexSlash = 0;

    for (unsigned i = 0; dateCopy.size() != 0; i++) {
        indexSlash = dateCopy.find_first_of('-');
        
        if (indexSlash == string::npos) {
            buffer.push_back(dateCopy);
            dateCopy.clear();
            break;
        } 
        else {
            buffer.push_back(dateCopy.substr(0,  indexSlash));
            dateCopy = dateCopy.substr(indexSlash + 1, dateCopy.size());
        }
    }

    return buffer;
}

// Finding the second part of command (after a space)
const string StringOperations::findArgument(const string& command) {
    string path = command.substr(command.find_first_of(' ') + 1, command.size());
    return path;
}

// Getting the first part of command (or text) (before space)
const string StringOperations::getFirstPart(const string& command) {
    string key = command.substr(0, command.find_first_of(' '));
    return key;
}

// Getting a vector of permutation from string
const vector<unsigned> StringOperations::getPermutation(const string& permutation) {
    vector<unsigned> finalPermutation;
    string permutationCopy = permutation;
    string currentNum;
    size_t indexSpace;

    while (permutationCopy.size() != 0) {
        indexSpace = permutationCopy.find_first_of(' ');

        if (indexSpace == string::npos) {
            currentNum = permutationCopy;
            finalPermutation.push_back(std::stoi(currentNum));
            return finalPermutation;
        } 
        else {
            currentNum = permutationCopy.substr(0, indexSpace);
            permutationCopy = permutationCopy.substr(indexSpace + 1, permutationCopy.size());
            finalPermutation.push_back(std::stoi(currentNum));
        }
    }

    return finalPermutation;   
}

// This method fills a vector with indexes of rows
void StringOperations::fillIndexes(vector<unsigned>& indexes, unsigned size) {
    for (unsigned i = 0; i < size; i++) {
        indexes.push_back(i);
    }
}

// Getting the new sorted indexes, used for sorting (sorting date,text,facultyNumbers)
vector<unsigned> StringOperations::getIndexesOfStringSorted(const vector<string>& stringValues, char s) {
    vector<unsigned> indexes;
    string currentValue;
    vector<string> valuesCopy = stringValues;
    fillIndexes(indexes, stringValues.size());

    for (unsigned i = 0; i < valuesCopy.size() - 1; i++) {
        for (unsigned j = 0; j < valuesCopy.size() - i - 1; j++)
        {
            if (s == 'i' && valuesCopy[j] > valuesCopy[j + 1]) {
                swapString(valuesCopy[j], valuesCopy[j + 1]);
                swapIndexes(indexes[j], indexes[j + 1]);
            }
            else if (s == 'd' && valuesCopy[j] < valuesCopy[j + 1]) {
                swapString(valuesCopy[j], valuesCopy[j + 1]);
                swapIndexes(indexes[j], indexes[j + 1]);
            }
        }
    }

    return indexes;
}

// Getting the new sorted indexes, used for sorting (sorting numbers)
vector<unsigned> StringOperations::getIndexesOfNumberSorted(const vector<long double>& numberValues, char s) {
    vector<unsigned> indexes;
    long double tempValue = 0;
    vector<long double> valuesCopy = numberValues;
    fillIndexes(indexes, numberValues.size());

    for (unsigned i = 0; i < valuesCopy.size() - 1; i++) {
        for (unsigned j = 0; j < valuesCopy.size() - i - 1; j++)
        {
            if (s == 'i' && valuesCopy[j] > valuesCopy[j + 1]) {
                swapLongDouble(valuesCopy[j], valuesCopy[j + 1]);
                swapIndexes(indexes[j], indexes[j + 1]);
            }
            else if (s == 'd' && valuesCopy[j] < valuesCopy[j + 1]) {
                swapLongDouble(valuesCopy[j], valuesCopy[j + 1]);
                swapIndexes(indexes[j], indexes[j + 1]);
            }
        }
    }

    return indexes;    
}

// This method distinguishes the way of filtering and returns key, which is used later
const unsigned StringOperations::getWayOfFiltering(const string& wayOfFiltering) {
    if (wayOfFiltering == "==") {
        return 1;
    }
    else if(wayOfFiltering == "!=") {
        return 2;
    }
    else if(wayOfFiltering == "<") {
        return 3;
    }
    else if(wayOfFiltering == "<=") {
        return 4;
    }
    else if(wayOfFiltering == ">") {
        return 5;
    }
    else if(wayOfFiltering == ">=") {
        return 6;
    }
    else {
        std::cout << "Invalid way of filtering!\n";
        return -1;
    }
}