#include "../headers/ValidatorCSV.h"

// checking for old faculty numbers in FMI
bool ValidatorCSV::isOldFacultyNumber(const string& value) {
    bool isCorrectBeg = (value.size() == 5) &&
                    (value[0] == '4' || value[0] == '7');

    bool flag = false;
    for (unsigned i = 1; i < value.size() && isCorrectBeg; i++)
    {
        flag = isdigit(value[i]) ? true : false;
    }
     
    return flag;
}

// checking for new faculty numbers in FMI
bool ValidatorCSV::isNewFacultyNumber(const string& value) {
    bool isCorrect = (value.size() == 10) &&
                    isdigit(value[0]) &&
                    value[1] == 'M' &&
                    value[2] == 'I' &&
                    value[3] == '0';
    
    bool flag = false;
    for (unsigned i = 4; i < value.size() && isCorrect; i++)
    {
        flag = isdigit(value[i]) ? true : false;
    }
    
    return flag;
}

// Check if date is correct
bool ValidatorCSV::isCorrectDate(const vector<string>& splittedDate) {
    unsigned year;
    unsigned month;
    unsigned day;

    bool isCorrectYear = false;
    bool isLeapYear = false;
    bool isCorrectMonth = false;
    bool isCorrectDay = false;
    
    try {
        year = std::stoi(splittedDate.at(0));
        month = std::stoi(splittedDate.at(1));
        day = std::stoi(splittedDate.at(2));
    }
    catch(...)
    {
        return false;
    }

    isCorrectYear = (year > 0) && (year <= 2030);
    isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    isCorrectMonth = (month > 0) && (month <= 12);
    switch (month)
    {
        case 1: case 3: case 5: case 7:
        case 8: case 10: case 12:
            isCorrectDay = day <= 31;   
            break;
        case 4: case 6: case 9: case 11:
            isCorrectDay = day <= 30;
            break;
        case 2: 
            isCorrectDay = (isLeapYear && day <= 29) || (!isLeapYear && day <= 28);
        default:
            break;
    }

    return isCorrectYear && isCorrectMonth && isCorrectDay;
}

// Check if value is title
bool ValidatorCSV::isValueTitle(const string& title) {
    return StringOperations::checkIsTitle(title);
}

// This method validates specific types of values and returns the value type
const string ValidatorCSV::validateType(const string& value) {
    string typeOfValue;
    if (isValidText(value)) {
        typeOfValue = "Text";
    } else if (isValidDate(value)) {
        typeOfValue = "Date";
    } else if (isValidFacultyNumber(value)) {
        typeOfValue = "FacultyNumber";
    } else if (isValidNumber(value)) {
        typeOfValue = "Number";
    } else {
        typeOfValue = "Text";
    }

    return typeOfValue;
}

// This method validates date
bool ValidatorCSV::isValidDate(const string& value) {
    if(!StringOperations::checkIsDate(value)) {
        return false;
    }

    vector<string> splittedDate = StringOperations::splitDate(value);

    return isCorrectDate(splittedDate);
}


// This method validates faculty numbers in FMI
bool ValidatorCSV::isValidFacultyNumber(const string& value) {
    return (isOldFacultyNumber(value) || isNewFacultyNumber(value)) ? 
        true : false;
}

// This method validates numbers
bool ValidatorCSV::isValidNumber(const string& value) {
    long double num;

    try
    {
        num = std::stold(value);
    }
    catch(...)
    {
        return false;
    }

    return true;
}

// This method validates Text in quotes
bool ValidatorCSV::isValidText(const string& value) {
    return StringOperations::checkIsTextInQuotes(value) ? true : false;
}

// Validation of CSV file syntax
void ValidatorCSV::validateFileSyntax(std::fstream& in) {
    unsigned currentRowCountOfCommas = 0;
    string row;
    std::getline(in, row, '\n');
    unsigned countOfCommaInRow = StringOperations::countCommas(row);

    while (!in.eof())
    {
        row.clear();
        std::getline(in, row, '\n');
        currentRowCountOfCommas = StringOperations::countCommas(row);
        if (countOfCommaInRow != currentRowCountOfCommas) {
            throw std::runtime_error("Invalid file syntax!");
        }
    }
}

// Check if first row is with titles or not
bool ValidatorCSV::isFirstRowWithTitles(const string& row) {
    size_t indexComma = 0;
    string rowCopy = row;
    string currentTitle;
    
    if (rowCopy.size() == 0) {
        return false;
    }

    while (rowCopy.size() != 0) {
        currentTitle = StringOperations::splitRow(indexComma, rowCopy);

        if(!isValueTitle(currentTitle)) {
            return false;
        }
    }
    
    return true;
}
