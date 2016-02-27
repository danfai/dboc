#include "stringtokenizer.h"

StringTokenizer::StringTokenizer(std::string line)
    :line(line), pos(0), end(false)
{

}

std::string StringTokenizer::getString()
{
    if (this->end)
        throw InvalidLineException();
    if (line[pos] == ' ') { ++pos;
        return ""; }
    int oldpos = pos;
    for(; line[pos] != '\0'; ++pos) {
        if (line[pos] == ' ') {
            ++pos;
            std::string b = line.substr(oldpos, pos-oldpos-1);
            return b;
        }
    }
    this->end = true;
    return line.substr(oldpos);
}
