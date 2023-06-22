#ifndef PARSER_CSV_H
#define PARSER_CSV_H
#include "DateColumn.h"
#include "NumberColumn.h"
#include "FNumberColumn.h"
#include "TextColumn.h"
#include "ValidatorCSV.h"

class ParserCSV {
private:
    vector<BaseColumn*> columns;
    unsigned countOfColumns;
    
    vector<string> titles;
    bool haveColumnsTitle;

    // This vector includes types of columns.
    vector<string> columnTemplate;

private:
    void erase();
    void checkTypeIsCorrect(const string& valueType,  
                            const string& templateColumnType) const;

    void setColumnTitles(const string& row);

    BaseColumn* createColumn(const string& type) const;
    BaseColumn* createDateColumn() const;
    BaseColumn* createNumberColumn() const;
    BaseColumn* createFacultyNumberColumn() const;
    BaseColumn* createTextColumn() const;

    void writeColumns(std::fstream& out);

    void printTitles() const;
    void printRow(const vector<string>& currentRow) const;

    unsigned findIndexOfColumn(const string& title) const;
    void removeColumn(unsigned indexColumn);
    void removeRowAtIndex(unsigned index);
    
    void changeColumns(const vector<unsigned>& permutationVector);
    void changeRows(const vector<unsigned>& permutationVector);

    void sort(unsigned index, char s);

    void filter(unsigned indexOfColumn, const string& wayOfFiltering, const string& predicate);
public:
    ParserCSV();
    ~ParserCSV();

    // void addColumn(BaseColumn* column);
    void readCSVFile(std::fstream& in);
    void writeCSVFile(std::fstream& out);

    const vector<string> getRowAtIndex(unsigned index) const;
    
    const unsigned getRowsNumber() const;

    void printColumns() const;

    void removeColumnByTitle(const string& columnTitle);
    void removeColumnByIndex(unsigned indexColumn);
    
    void removeDuplicates();

    void addRowWithCopiedValues(unsigned index);
    void addRowWithMaxValues();
    void addRowWithMinValues();

    void changeSequenceOfColumns(const string& permutation);

    void sortByColumnTitle(const string& argument, char s);
    void sortByColumnIndex(unsigned index, char s);

    void filterColumnsByTitle(const string& columnTitle, const string& way, const string& value);
    void filterColumnsByIndex(unsigned index, const string& way, const string& value);
};

#endif //PARSER_CSV_H