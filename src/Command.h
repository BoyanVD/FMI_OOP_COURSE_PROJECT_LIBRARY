#ifndef __COMMAND_H
#define __COMMAND_H

#include <iostream>
#include <vector>
#include <string>

class Command
{
private:
    std::string command;
    std::vector<std::string> parameters;

    void parseInput(std::string input);
public:
    Command(std::string input)
    {
        parseInput(input);
    }

    Command(const Command &other);

    std::string getCommand() const
    {
        return this->command;
    }

    std::string getParameter(unsigned index) const
    {
        return this->parameters[index];
    }

    size_t getNumberOfParameters() const
    {
        return this->parameters.size();
    }

    void addParameter(const std::string& param)
    {
        this->parameters.push_back(param);
    }

    std::string getCancatenatedParameters(const unsigned start, const unsigned end) const
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

    void print()
    {
        std::cout << "  Command name : " << command << std::endl;
        for (std::string param : parameters)
        {
            std::cout << "  Parameter : " << param << std::endl;
        }
    }
};

#endif