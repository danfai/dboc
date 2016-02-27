#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "entry.h"

class Parser {
    public:
        Parser(std::string infile);
        void parseLine(std::string line);
        void write(std::string filename);

    private:
        std::vector<Class> classes;
        Field::Type getType(std::string token);

};

#endif // PARSER_H
