#ifndef PROGRAM_H
#define PROGRAM_H
#include "ParserCSV.h"
#include "CommandParser.h"

class Program {    
private:
    vector<string> commands;
    ParserCSV parserCSV;
    string pathOfFile;

    bool isAlreadyUsedUndo;

    void executeBeforeSave();

    void open();
    void save();
    void saveAs(const string& filePath);
    void undo();
    void print();
    void exit();
    void removeColumn(const string& argument);
    void removeDuplicates();
    void addRow(const string& argument);
    void changeSequence(const string& argument);
    void sort(const string& argument);
    void filterColumns(const string& argument);


public:
    Program();
    ~Program() = default;

    void startProgram();
    void addCommand(const string& command);
    void executeCommand(const string& command, unsigned commandType);
};
#endif // PROGRAM_H

