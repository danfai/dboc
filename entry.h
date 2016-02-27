#ifndef ENTRY_H
#define ENTRY_H

#include <vector>
#include <string>
#include <set>
#include <sstream>

class Field {
    public:
        enum Type {
            b, c, d, e, f, i, l, p, ss, Wdt, Ws,
            INVALID
        };
        enum Relation {
            COLUMN,
            BELONGS_TO,
            MANY_TO_ONE,
            MANY_TO_MANY
        };

        Type type;
        std::string additionalType;
        Relation relation;
        std::string fieldName;
        std::string databaseName;

        void getIncludes(std::set<std::string> &s) {
            switch(type) {
                case Field::c:
                case Field::p:
                    s.insert("class " + additionalType + ";");
                    break;
                case Field::ss:
                    s.insert("#include <string>");
                    break;
                case Field::Wdt:
                    s.insert("#include <Wt/WDateTime>");
                    s.insert("#include <Wt/Dbo/WtSqlTraits>");
                    break;
                case Field::Ws:
                    s.insert("#include <Wt/WString>");
                    break;
                default:
                    // built-in types
                    break;
            }
        }

        void getFieldName(std::ostringstream &oss) {
            oss << "    ";
            //TODO: Check for relation
            switch(type) {
                case Field::b:
                    oss << "bool";
                    break;
                case Field::e:
                case Field::c:
                    oss << additionalType;
                    break;
                case Field::d:
                    oss << "double";
                    break;
                case Field::f:
                    oss << "float";
                    break;
                case Field::i:
                    oss << "int";
                    break;
                case Field::l:
                    oss << "long";
                    break;
                case Field::p:
                    oss << "Wt::Dbo::ptr<" << additionalType << ">";
                    break;
                case Field::ss:
                    oss << "std::string";
                    break;
                case Field::Wdt:
                    oss << "Wt::WDateTime";
                    break;
                case Field::Ws:
                    oss << "Wt::WString";
                    break;
                default:
                    // I dont know
                    break;
            }
            oss  << " " << fieldName << ";" << std::endl;
        }
};

class Class {
    public:
        bool noVersion;
        std::string className;
        std::string tableName;
        std::vector<Field> fields;
};


#endif // ENTRY_H
