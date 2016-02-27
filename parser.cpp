#include "stringtokenizer.h"
#include "parser.h"
#include <fstream>
#include <sstream>

Parser::Parser(std::string inFile)
{
    std::ifstream in(inFile);

    std::string line;
    while(std::getline(in, line)) {
        if(line.size() > 0)
            parseLine(line);
    }
}

void Parser::parseLine(std::string line)
{
    StringTokenizer t(line);
    std::string t1;
    t1 = t.getString();
    if(t1.at(t1.size()-1) == ':') {
        // New class
        Class c;
        c.className = t1.substr(0, t1.size()-1);
        c.tableName = t.getString();
        //TODO: no-version, ...
        this->classes.push_back(c);
    } else {
        if(this->classes.size() == 0) {
            throw "Class identifier has to be set before column declarations";
        }
        // column
        Field f;
        f.type = getType(t1);
        if(f.type == Field::c || f.type == Field::p || f.type == Field::e) {
            f.additionalType = t.getString();
        }
        f.fieldName = t.getString();
        f.databaseName = t.getString();
        /*
        std::string s = t.getString();
        if(s.size() > 0) {
            //TODO: Relation
        }*/
        this->classes.back().fields.push_back(f);
    }

}

Field::Type Parser::getType(std::string token)
{
    switch(token.at(0)) {
        case 'b': return Field::b;
        case 'c': return Field::c;
        case 'd': return Field::d;
        case 'e': return Field::e;
        case 'f': return Field::f;
        case 'i': return Field::i;
        case 'l': return Field::l;
        case 'p': return Field::p;
        default:
                  if(token == "ss")
                      return Field::ss;
                  else if(token == "Wdt")
                      return Field::Wdt;
                  else if(token == "Ws")
                      return Field::Ws;
    }
    return Field::INVALID;
}

void Parser::write(std::string outFile)
{
    if(this->classes.empty()) {
        throw "No classed found";
    }
    std::ofstream out(outFile);
    std::set<std::string> includes;
    std::ostringstream definition;
    std::string headerguard = "DBO_" + this->classes.front().className + "_H";

    includes.insert("#include <Wt/Dbo/Types>");

    out << "#ifndef " << headerguard << std::endl;
    out << "#define " << headerguard << std::endl;
    out << std::endl;
    for(auto &c : this->classes) {
        definition << "class " << c.className << " : public Wt::Dbo::Dbo<" << c.className << ">" << std::endl;
        definition << "{" << std::endl << "  public:" << std::endl;
        // TODO: con-/destructor?
        //definition << "    virtual " << c.className << "();" << std::endl; 
        //definition << "    virtual ~" << c.className << "();" << std::endl; 
        std::ostringstream persist;
        for(auto &f : c.fields) {
            f.getIncludes(includes);
            f.getFieldName(definition);

            switch(f.relation) {
                default:
                    persist << "      Wt::Dbo::field(a, " << f.fieldName << ", \"" << f.databaseName << "\");" << std::endl;
            }
        }
        definition << std::endl;
        definition << "    template<Action>" << std::endl;
        definition << "    void persist(Action &a) {" << std::endl;
        definition << persist.str();
        definition << "    }" << std::endl;
        definition << "}" << std::endl;
        definition << "DBO_EXTERN_TEMPLATES(" << c.className << ");" << std::endl;
    }
    for(auto &s : includes)
        out << s << std::endl;

    out << definition.str() << std::endl;
    out << "#endif // " << headerguard << std::endl;
}
