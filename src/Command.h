/**
 * \class Command
 *
 * \brief Class, used for user input parsing
 *
 * Wrapper class for user input strings. Splits
 * and parses user input in format, that the application supports.
 *
 * \author $Author: Boyan Dafov $
 * 
 * Contact: boyandafov123@gmail.com
 *
 */
#ifndef __COMMAND_H
#define __COMMAND_H

#include <iostream>
#include <vector>
#include <string>

class Command
{
private:
    /**
    * The command name.
    */
    std::string command;

    /**
    * Parsed parameters.
    */
    std::vector<std::string> parameters;

    /**
    * Helper function, used for parsing user input string.
    */
    void parseInput(std::string input);
public:
    Command(std::string input)
    {
        parseInput(input);
    }

    /**
    * Returns command parameters between start and end indexes, concatenated with intervals
    * between them.
    *
    * @param start start index.
    * @param end end index
    * @return concatenated parameters string.
    */
    std::string getCancatenatedParameters(const unsigned start, const unsigned end) const;

    /**
    * Prints command in format - <command_name> <param_1> ... <param_n>
    */
    void print() const;

    /**
     * Getter
     * 
     * @return command string
     */
    std::string getCommand() const;

    /**
     * Getter for parameter at index.
     * 
     * @return parameter at index
     */
    std::string getParameter(unsigned index) const;

    /**
     * Function, returning number of command parameters.
     * 
     * @return number of parameters
     */
    size_t getNumberOfParameters() const;

    /**
     * Adds new parameter to command
     */
    void addParameter(const std::string& param);
};

#endif