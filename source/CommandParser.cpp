#include "../headers/CommandParser.h"


// helper for commandParse
const string CommandParser::getCommandKey(const string& command) {
    return StringOperations::getFirstPart(command);
}


// Here we are parsing the commands from the console
const unsigned CommandParser::commandParse(const string& command) {
    string commandKey = getCommandKey(command); 

    if (commandKey == "open") {
        return 1;
    } 
    else if (commandKey == "save") {
        return 2;
    } 
    else if (commandKey == "saveas") {
        return 3;
    } 
    else if (commandKey == "exit") {
        return 4;
    } 
    else if (commandKey == "undo") {
        return 5;
    } 
    else if(commandKey == "print") {
        return 6;
    } 
    else if(commandKey == "remove-column") {
        return 7;
    }
    else if(commandKey == "sort") {
        return 8;
    }
    else if(commandKey == "remove-duplicates") {
        return 9;
    }
    else if(commandKey == "change-sequence") {
        return 10;
    }
    else if (commandKey == "filter") {
        return 11;
    } 
    else if(commandKey == "add") {
        return 12;
    }
    else {
        return -1;
    }
}