#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H
#include "ParserCSV.h"
class CommandParser
{
private:
    static const string getCommandKey(const string& command);
public:
    static const unsigned commandParse(const string& command);
};


#endif //COMMAND_PARSER_H