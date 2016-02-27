#ifndef STRINGTOKENIZER_H
#define STRINGTOKENIZER_H

#include <exception>
#include <string>

class StringTokenizer
{
    std::string line;
    unsigned int pos;
    int end;
public:
    class InvalidLineException : public std::exception
    {
        virtual const char *what() const throw()
        {
            return "Invalid Line exception.";
        }
    };
    StringTokenizer(std::string line);
    std::string getString();
};

#endif // STRINGTOKENIZER_H
