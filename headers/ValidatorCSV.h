#ifndef VALIDATOR_CSV_H
#define VALIDATOR_CSV_H

#include <string>
#include <vector>
#include <exception>
#include <stdexcept>
#include <fstream>
#include "StringOperations.h"

using std::string;
using std::vector;


// In this class there are validation functions
class ValidatorCSV {
private:
    static bool isOldFacultyNumber(const string& value);
    static bool isNewFacultyNumber(const string& value);

    static bool isCorrectDate(const vector<string>& splittedDate);

    static bool isValueTitle(const string& title);

    static bool isValidNumber(const string& value);

    static bool isValidDate(const string& value);

    static bool isValidFacultyNumber(const string& value);

    static bool isValidText(const string& value);
public:
    static void validateFileSyntax(std::fstream& in);
    static const string validateType(const string& value);
    static bool isFirstRowWithTitles(const string& row);
};
#endif //VALIDATOR_CSV_H