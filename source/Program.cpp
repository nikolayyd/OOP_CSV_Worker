#include "../headers/Program.h"

// execute commands before saving the file
void Program::executeBeforeSave() {
    unsigned commandType;
    for (const string& currentCommand : commands) {
        commandType = CommandParser::commandParse(currentCommand);
        executeCommand(currentCommand, commandType);    
    }
}

// Opens a csv file
void Program::open() {
    string fileName = StringOperations::getFileName(pathOfFile);

    std::fstream file(pathOfFile, std::ios::in);

    if (!file.is_open()) {
        save();
        return;
    }

    if (!file.good()) {
        throw std::runtime_error("The file is broken!");
    }
        
    ValidatorCSV::validateFileSyntax(file);
    file.seekg(std::ifstream::beg);
    parserCSV.readCSVFile(file);
    std::cout << "Successfully opened " << fileName <<"\n";

    file.close();
}

// saving the file
void Program::save() {
    if (!commands.empty()) {
        executeBeforeSave();
    }

    string fileName = StringOperations::getFileName(pathOfFile);
    std::fstream file(pathOfFile, std::ios::out);
    if (!file.good()) {
        file.close();
        throw std::runtime_error("The file is broken!");
    }

    parserCSV.writeCSVFile(file);
    std::cout << "Successfully saved " << fileName << '\n';
    file.close();
    commands.clear();
}


// save as new file the info
void Program::saveAs(const string& filePath) {
    if (!commands.empty()) {
        executeBeforeSave();
    }

    string fileName = StringOperations::getFileName(filePath);
    
    std::fstream file(filePath, std::ios::out);
    
    if (!file.good()) {
        throw std::runtime_error("The file is broken!");
    } 
    
    parserCSV.writeCSVFile(file);
    std::cout << "Successfuly saved another " << fileName << '\n';
    file.close();
}

// undo the last command
void Program::undo() {
    if (isAlreadyUsedUndo) {
        std::cout << "Command undo is already used!\n";
        return;
    }    
    
    if (!commands.empty()) {
        commands.pop_back();
        isAlreadyUsedUndo = true;
    } 
    else {
        std::cout << "There are no commands which could be undo!\n";
    }
}


// prints columns
void Program::print() {
    parserCSV.printColumns();
}

// exit from the program
void Program::exit() {
    if (commands.empty()) {
        return;
    }
    
    char s;
    std::cout << "Do you want to save changed data?\nType Y(y)/N(n) \n";
    std::cin >> s;

    if (tolower(s) == 'y') {
        save();
    } 
    else if (tolower(s) == 'n') {
        return;
    } 
    else {
        exit();
    } 
}


// removing columns
void Program::removeColumn(const string& argument) {
    unsigned index = 0;
    if (StringOperations::checkIsTitle(argument)) {
        parserCSV.removeColumnByTitle(argument);
    }
    else {
        index = StringOperations::stringToNumber(argument);
        parserCSV.removeColumnByIndex(index);
    }
}

// removing duplicates
void Program::removeDuplicates() {
    parserCSV.removeDuplicates();
}


// adds a specific row in the table
void Program::addRow(const string& argument) {
    unsigned index = 0;
    string wayOfAdding = StringOperations::getFirstPart(argument);
    string indexString =  StringOperations::findArgument(argument);

    if (wayOfAdding == "copy") {
        indexString = StringOperations::findArgument(argument);
        index = StringOperations::stringToNumber(indexString);
        parserCSV.addRowWithCopiedValues(index);
    }
    else if (wayOfAdding == "min") {
        parserCSV.addRowWithMinValues();
    }
    else if (wayOfAdding == "max") {
        parserCSV.addRowWithMaxValues();
    }
    else {
        std::cout << "Could not recognize argument of the command!\n";
    }
}


// changing the sequence of columns
void Program::changeSequence(const string& argument) {
    parserCSV.changeSequenceOfColumns(argument);
}


// sort the table by column
void Program::sort(const string& argument) {
    unsigned index = 0;
    char typeOfSorting;
    // arg is title or index!
    string arg = StringOperations::getFirstPart(argument); 
    // increasing or decreasing
    string s = StringOperations::findArgument(argument);

    if (s.size() == 1) {
        typeOfSorting = s[0];
    } 
    else {
        std:: cout << "The type of sorting is not valid!\n";
        return;
    }
    
    if (StringOperations::checkIsTitle(arg)) {
        parserCSV.sortByColumnTitle(arg, typeOfSorting);
    }
    else {
        index = StringOperations::stringToNumber(arg);
        parserCSV.sortByColumnIndex(index - 1, typeOfSorting);
    }
}


// filter the table by column
void Program::filterColumns(const string& argument) {
    unsigned index = 0;
    string columnParameter = StringOperations::getFirstPart(argument);
    string wayAndValue = StringOperations::findArgument(argument);

    string wayOfFilteringParameter = StringOperations::getFirstPart(wayAndValue);
    string valueParameter = StringOperations::findArgument(wayAndValue);

    if (StringOperations::checkIsTitle(columnParameter)) {
        parserCSV.filterColumnsByTitle(columnParameter, wayOfFilteringParameter, valueParameter);
    }
    else {
        index = StringOperations::stringToNumber(columnParameter) - 1;
        parserCSV.filterColumnsByIndex(index, wayOfFilteringParameter, valueParameter);
    }
}

Program::Program() : commands(), parserCSV(), pathOfFile(), isAlreadyUsedUndo(false) {}


// This method starts the program 
void Program::startProgram() {
    string currentCommand;
    unsigned typeOfCommand;

    bool isBeginOfProgram = true;
    
    do {  
        std::cout << "Enter a command: \n";
        
        std::getline(std::cin, currentCommand);
        
        typeOfCommand = CommandParser::commandParse(currentCommand);

        if (isBeginOfProgram) {
            if (typeOfCommand == 1) {
                executeCommand(currentCommand, typeOfCommand);
            }
            else if (typeOfCommand == 4) {
                executeCommand(currentCommand, typeOfCommand);
                break;
            } 
            else {
                std::cout << "Please use command open at the beggining!\n";
                continue;
            }
        } 
        else if (!isBeginOfProgram && typeOfCommand == 1) {
            std::cout << "The file is already opened!\n";
        }
        else if (typeOfCommand == 5 || 
                typeOfCommand == 2 || 
                typeOfCommand == 3 ||
                typeOfCommand == 6) 
        {
            executeCommand(currentCommand, typeOfCommand);
        }
        else if (typeOfCommand == 4) {
            executeCommand(currentCommand,  typeOfCommand);
            break;
        }
        else {
            addCommand(currentCommand);
        }

        isBeginOfProgram = false;
    } while (true);
    
}

// adding command to vector, they will be executed before saving the file
void Program::addCommand(const string& command) {
    commands.push_back(command);
}

void Program::executeCommand(const string& command, unsigned commandType) {
    string argument = StringOperations::findArgument(command);

    switch (commandType) {
        case 1:
            pathOfFile = StringOperations::findArgument(command);
            open(); break;
        case 2:
            save(); break;
        case 3:
            saveAs(argument); break;
        case 4:
            exit(); break;
        case 5:
            undo(); break;
        case 6:
            print(); break;
        case 7:
            removeColumn(argument); break;
        case 8:
            sort(argument); break;
        case 9:
            removeDuplicates(); break;
        case 10:
            changeSequence(argument); break;
        case 11:
            filterColumns(argument); break;
        case 12:
            addRow(argument); break;
        default:
            std::cout << "Unknown command!\n";
            break;
    }
}