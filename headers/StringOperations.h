#ifndef STRING_OPERATIONS_H
#define STRING_OPERATIONS_H
#include <vector>
#include <string>
#include <iostream>
using std::string;
using std::vector;

// This class includes important functions, which are used by other classes.
class StringOperations {
private:
    static bool isLetter(char symbol);

    static void fillIndexes(vector<unsigned>& indexes, unsigned size);
    
    static void swapString(string& a, string& b);
    static void swapLongDouble(long double& a, long double& b);
    static void swapIndexes(unsigned& a, unsigned& b);
public:
    static const string findMinimalString(const vector<string>& values);
    static const double findMinimalNum(const vector<long double>& values);

    static const string findMaximalString(const vector<string>& values);
    static const double findMaximalNum(const vector<long double>& values);

    static const string& makePathEscapeSym(string& path);

    static const string getFileName(const string& path);

    static void removeTrailingNulls(string& value);

    static bool checkIsTitle(const string& title);

    static bool checkIsTextInQuotes(const string& value);

    static bool checkIsDate(const string& date);

    static const string splitRow(size_t indexComma, string& rowCopy);

    static unsigned stringToNumber(const string& str);

    static const unsigned countCommas(const string& row);


    static const string removeQuotesInText(const string& value);
    static const string addQuotes(const string& currentValue);

    static const vector<string> splitDate(const string& date);

    static const string findArgument(const string& command);

    static const string getFirstPart(const string& command); 

    static const vector<unsigned> getPermutation(const string& permutation);

    static vector<unsigned> getIndexesOfStringSorted(const vector<string>& stringValues, char s);
    static vector<unsigned> getIndexesOfNumberSorted(const vector<long double>& numberValues, char s);

    static const unsigned getWayOfFiltering(const string& wayOfFiltering);
};

#endif //STRING_OPERATIONS_H