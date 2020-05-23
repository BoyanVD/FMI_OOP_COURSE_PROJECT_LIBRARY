#ifndef __COMMAND_CPP
#define __COMMAND_CPP

#include "Command.h"
#include "Constants.h"

Command::Command(const Command &other)
{
    this->command = other.command;
    this->parameters.clear();
    for (int index = 0; index < other.getNumberOfParameters(); ++index)
    {
        this->parameters.push_back(other.getParameter(index));
    }
}

void Command::parseInput(std::string input)
{
    size_t current, previous = 0;
    current = input.find(INPUT_COMMAND_DELIMETER);
    unsigned numberOfParsedStrings = 0;

    while (current != std::string::npos) 
    {
        std::string currentStr = input.substr(previous, current - previous);
        if (numberOfParsedStrings == 0)
            this->command = currentStr;
        else 
            this->parameters.push_back(currentStr);

        previous = current + 1;
        current = input.find(INPUT_COMMAND_DELIMETER, previous);

        ++numberOfParsedStrings;
    }

    if (numberOfParsedStrings == 0)
            this->command = input.substr(previous, current - previous);
        else 
            this->parameters.push_back(input.substr(previous, current - previous));
}

std::string Command::getCancatenatedParameters(const unsigned start, const unsigned end) const
{
    std::string result = "";

    for (int index = start; index < end; ++index)
    {
        result += this->parameters[index];
        result += " ";
    }
    result += this->parameters[end];

    return result;
}

void Command::print() const 
{
    std::cout << "  Command name : " << command << std::endl;
    for (std::string param : parameters)
    {
        std::cout << "  Parameter : " << param << std::endl;
    }
}

#endif