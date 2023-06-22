#include "../headers/ParserCSV.h"

// erasing the vector of columns
void ParserCSV::erase() {
    for (BaseColumn* column : columns)
    {
        delete column;
    }
}

// check type is correct to be inserted in column, used in readFileCSV
void ParserCSV::checkTypeIsCorrect(const string& valueType,  
                                    const string& templateColumnType) const
{
    if (valueType != templateColumnType) {
        throw std::runtime_error("Wrong type added in column!");
    }
}

// set titles of columns
void ParserCSV::setColumnTitles(const string& row) { 
    size_t indexComma;
    string rowCopy = row;
    string currentTitle;
        
    while (rowCopy.size() != 0) {   
        currentTitle = StringOperations::splitRow(indexComma, rowCopy);
        titles.push_back(currentTitle);
    }
}

// create a column
BaseColumn* ParserCSV::createColumn(const string& type) const {
    if (type == "Number") {
        return createNumberColumn();
    }
    else if(type == "FacultyNumber") {
        return createFacultyNumberColumn();
    }
    else if(type == "Date") {
        return createDateColumn();
    }
    else if (type == "Text") {
        return createTextColumn();
    }
    else {
        throw std::runtime_error("Error while creating columns(wrong type!)");
    }
}

// This four methods are used to create a speicific type of column
BaseColumn* ParserCSV::createDateColumn() const {
    return new DateColumn();
}

BaseColumn* ParserCSV::createNumberColumn() const {
    return new NumberColumn();
}

BaseColumn* ParserCSV::createFacultyNumberColumn() const {
    return new FNumberColumn();
}

BaseColumn* ParserCSV::createTextColumn() const {
    return new TextColumn();
}

// writing to a file
void ParserCSV::writeColumns(std::fstream& out) {
    unsigned numberOfRows = columns[0]->getSize();
    vector<string> currentRow;
    unsigned countOfValuesInRow;

    for (unsigned i = 0; i < numberOfRows; i++)
    {
        countOfValuesInRow = 0;
        currentRow = getRowAtIndex(i);

        for (const string& currentValue : currentRow)
        {
            if (countOfValuesInRow == currentRow.size() - 1) {
                if (i == numberOfRows - 1) {
                    out << currentValue;
                } else {
                    out << currentValue << '\n';
                }
            }
            else {
                out << currentValue << ',';
                countOfValuesInRow++;
            }
        }
    } 
}

// printing titles (if exists)
void ParserCSV::printTitles() const {
    for (const string& title : titles)
    {
        std::cout << title << ' ';
    }

    std::cout << '\n';   
}

// printing a row
void ParserCSV::printRow(const vector<string>& currentRow) const {
    for (const string& currentValue : currentRow)
    {
        std::cout << currentValue << ' ';
    }
    
    std::cout << '\n';
}

// finding index of column by title, returns -1 if it doesn't have titles
unsigned ParserCSV::findIndexOfColumn(const string& title) const {
    unsigned index = 0;
    if (titles.empty()) {
        std::cout << "Columns have not titles!";
        return -1;
    }
    
    for (const string currentTitle : titles) {
        if (currentTitle == title) {
            return index;
        }
        index++;
    }

    throw std::out_of_range("Column with this title is not found!");    
}

// method for removing a column
void ParserCSV::removeColumn(unsigned indexColumn) {
    if (indexColumn > columns.size()) {
        std::cout << "The columns does not exist!\n";
        return;
    }

    if (!titles.empty()) {
        titles.erase(titles.begin() + indexColumn - 1); 
    }


    columnTemplate.erase(columnTemplate.begin() + indexColumn - 1);
    delete columns[indexColumn - 1];
    columns.erase(columns.begin() + indexColumn - 1);
    
    countOfColumns--;
}

// remove row with this index
void ParserCSV::removeRowAtIndex(unsigned index) {
    for (BaseColumn* currentColumn : columns) {
        currentColumn->removeValueAt(index);
    }
}

// this method do the permutation of rows
void ParserCSV::changeColumns(const vector<unsigned>& permutationVector) {
    vector<BaseColumn*> tempColumns;
    vector<string> tempTitles;
    vector<string> tempColumnTemplate;

    unsigned currentIndex = 0;

    bool haveTitles = (titles.size() > 0);

    for (unsigned i = 0; i < countOfColumns; i++) {
        currentIndex = permutationVector.at(i) - 1;

        if (haveTitles) {
            tempTitles.push_back(titles.at(currentIndex));
        }

        tempColumnTemplate.push_back(columnTemplate.at(currentIndex));
        tempColumns.push_back(columns.at(currentIndex));
    }

    if (haveTitles) {
        titles.swap(tempTitles);
    }
    
    columnTemplate.swap(tempColumnTemplate);
    columns.swap(tempColumns);
}

// change rows with argument permutation
// here every column is sorted
void ParserCSV::changeRows(const vector<unsigned>& permutationVector) {
    vector<BaseColumn*> copyColumns;
    string currentValue;

    for (unsigned i = 0; i < countOfColumns; i++) {
        copyColumns.push_back(createColumn(columnTemplate[i]));

        for (unsigned permIndex : permutationVector) {
            currentValue = columns[i]->getValueAtIndex(permIndex);
            copyColumns[i]->addValueInColumn(currentValue);
        }
    }

    erase();
    columns = copyColumns;
}

// sorts the rows (increasing or decreasing)
void ParserCSV::sort(unsigned index, char s) {
    vector<unsigned> permutation = columns[index]->getIndexesOfSortedColumn(s);

    changeRows(permutation);
}

// filter the columns by having a predicate and way
void ParserCSV::filter(unsigned indexOfColumn, const string& wayOfFiltering, const string& predicate) {
    vector<unsigned> forRemovingIndexes;
    unsigned way = StringOperations::getWayOfFiltering(wayOfFiltering);
    string currentValue;
    bool toRemove = false;

    if (way == -1) {
        return;
    }

    for (unsigned i = 0; i < columns[indexOfColumn]->getSize(); i++) {
        // (currentType == "NumberColumn") ? 
        currentValue = columns[indexOfColumn]->getValueAtIndex(i);
        switch (way)
        {
        case 1:
            toRemove = !(currentValue == predicate); break;
        case 2:
            toRemove = !(currentValue != predicate); break;
        case 3:
            toRemove = !(currentValue < predicate); break;
        case 4:
            toRemove = !(currentValue <= predicate); break;
        case 5:
            toRemove = !(currentValue > predicate); break;
        case 6:
            toRemove = !(currentValue >= predicate); break;
        default:
            break;
        }

        if (toRemove == true) {
            forRemovingIndexes.push_back(i);
            toRemove = false;
        }
    }

    for (unsigned i = 0; i < forRemovingIndexes.size(); i++) {
        removeRowAtIndex(forRemovingIndexes[i]);
        for (unsigned j = i + 1; j < forRemovingIndexes.size(); j++) {
            forRemovingIndexes[j]--;
        }
    }     
}

ParserCSV::ParserCSV() : columns(), 
                        countOfColumns(0), 
                        titles(), 
                        haveColumnsTitle(false), 
                        columnTemplate() {}

ParserCSV::~ParserCSV() {
    erase();
}

// Reading the file
void ParserCSV::readCSVFile(std::fstream& in) {
    if (!in.is_open()) {
        throw std::runtime_error("The file is not opened correctly");
    }

    string currentRow;

    string currentValue;
    string currentTypeOfValue;

    size_t indexComma;
    bool isFirstRow = true;
    unsigned indexOfCurrentColumn = 0;

    if (!in.eof()) {
        std::getline(in, currentRow, '\n');
    } else {
        throw std::runtime_error("The file is empty!");
    }

    if(ValidatorCSV::isFirstRowWithTitles(currentRow)) {
        haveColumnsTitle = true;
        setColumnTitles(currentRow);
    } else {
        in.seekg(std::ifstream::beg);
    }
    
    BaseColumn* currentColumn;
    while (!in.eof()) {
        std::getline(in, currentRow, '\n');
        indexOfCurrentColumn = 0;

        while (!currentRow.empty()) {            
            currentValue = StringOperations::splitRow(indexComma, currentRow);

            currentTypeOfValue = ValidatorCSV::validateType(currentValue);
            if (isFirstRow) {
                currentColumn = createColumn(currentTypeOfValue);
                columns.push_back(currentColumn);
                columnTemplate.push_back(currentTypeOfValue);
            }
            else {
                // check is value in correct column
                checkTypeIsCorrect(currentTypeOfValue, 
                                    columnTemplate[indexOfCurrentColumn]);
            }

            columns[indexOfCurrentColumn]->addValueInColumn(currentValue);
            ++indexOfCurrentColumn;
        }

        isFirstRow = false;
    }

    countOfColumns = columns.size();
}

// Writing the file
void ParserCSV::writeCSVFile(std::fstream& out) {
    if (!out.good()) {
        throw std::runtime_error("Error while saving! File is broken!");
    }

    for (const string& currentTitle : titles) {
        if (currentTitle == titles.back()) {
            out << currentTitle << '\n';
        } else {
            out << currentTitle << ',';
        }    
    }
    
    writeColumns(out);
}

// Getting the row at index
const vector<string> ParserCSV::getRowAtIndex(unsigned index) const {
    vector<string> row;
    string typeText = "Text";
    string currentValue;
    unsigned numberOfRows = columns.at(0)->getColumn().size();
    if (index < numberOfRows) {
        for (unsigned i = 0; i < columns.size(); i++)
        {
            if (columns.at(i)->getTypeOfColumn() == typeText) {
                currentValue = StringOperations::addQuotes(columns.at(i)->getValueAtIndex(index));
            } else {
                currentValue = columns.at(i)->getValueAtIndex(index);
            }
            row.push_back(currentValue);
        }
    } else {
        throw std::runtime_error("Invalid size in method getRowAtIndex(ParserCSV)");
    }

    return row;
}

// get count of rows
const unsigned ParserCSV::getRowsNumber() const {
    return columns.at(0)->getColumn().size();
}

// print the columns
void ParserCSV::printColumns() const {
    std::cout << '\n';
    
    vector<string> currentRow;
    unsigned countOfRows = columns[0]->getSize();

    printTitles();

    std::cout << '\n';
    for (unsigned i = 0; i < countOfRows; i++) {
        currentRow = getRowAtIndex(i);
        printRow(currentRow);
    }

    std::cout << '\n';    
}

// removing column with argument title
void ParserCSV::removeColumnByTitle(const string& columnTitle) {
    unsigned indexOfColumn = findIndexOfColumn(columnTitle);
    if (indexOfColumn != -1) {
        removeColumn(indexOfColumn);
    }    
}

// removing column with argument index
void ParserCSV::removeColumnByIndex(unsigned indexColumn) {
    removeColumn(indexColumn);
} 

// remove duplicates rows
void ParserCSV::removeDuplicates() {
    vector<string> currentRow;
    unsigned countOfRows = columns.at(0)->getSize();

    //??sth is not ok
    for (unsigned i = 0; i < countOfRows; i++) {
        currentRow = getRowAtIndex(i);
        for (unsigned j = 0; j < countOfRows; j++)
        {
            if (currentRow == getRowAtIndex(j) && i != j) {
                removeRowAtIndex(j);
                countOfRows--;
            }
        }
    }
}

// adds row, which is a copy of row with this index
void ParserCSV::addRowWithCopiedValues(unsigned index) {
    if (titles.size() != 0 && index == 1) {
        std::cout << "You cannot copy titles row!\n";
        return;
    }

    vector<string> currentRow;
    if (titles.size() != 0) {
        currentRow = getRowAtIndex(index - 2);
    } else {
        currentRow = getRowAtIndex(index - 1);
    }

    string currentValue;

    for (unsigned i = 0; i < countOfColumns; i++) {
        currentValue = currentRow.at(i);
        columns.at(i)->addValueInColumn(currentValue);
    }
    
}


// adding row with max values of each column
void ParserCSV::addRowWithMaxValues() {
    string maxInColumn;
    for (BaseColumn* currentColumn : columns) {
        maxInColumn = currentColumn->getMaximalValue();
        currentColumn->addValueInColumn(maxInColumn);
    }

}


// adding row with min values of each column
void ParserCSV::addRowWithMinValues() {
    string minInColumn;
    for (BaseColumn* currentColumn : columns) {
        minInColumn = currentColumn->getMinimalValue();
        currentColumn->addValueInColumn(minInColumn);
    }
}


// change the sequence of row (using method changeColumns)
void ParserCSV::changeSequenceOfColumns(const string& permutation) {
    vector<unsigned> permutationVector = StringOperations::getPermutation(permutation);
    if (permutationVector.size() != countOfColumns) {
        std::cout << "Invalid use of command change sequence!\n";
        return;
    }

    changeColumns(permutationVector);
}


// sorting columns by argument title
void ParserCSV::sortByColumnTitle(const string& title, char s) {
    unsigned index = findIndexOfColumn(title);
    sort(index, s);
}


// sorting columns by argument index
void ParserCSV::sortByColumnIndex(unsigned index, char s) {
    if (index > countOfColumns) {
        std::cout << "Error with sort command: index is not correct!\n";
    } else {
        sort(index, s);
    }
}

void ParserCSV::filterColumnsByTitle(const string& argument, const string& way, const string& value) {
    unsigned indexOfColumn = findIndexOfColumn(argument);
    filter(indexOfColumn, way, value);
}
void ParserCSV::filterColumnsByIndex(unsigned index, const string& way, const string& value) {
    if (index >= countOfColumns) {
        std::cout << "Invalid index argument when using command filter!\n";
        return;
    }
    
    filter(index, way, value);
}