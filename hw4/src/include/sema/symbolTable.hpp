#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include "AST/PType.hpp"
#include "sstream"

class SymbolEntry {
public:
    SymbolEntry(PTypeSharedPtr ptype,std::string const_value) : ptype(ptype), const_value(const_value) {}
    SymbolEntry(std::string name,
                std::string kind,
                int level,
                PTypeSharedPtr ptype,
                std::string attribute) : name(name), kind(kind), level(level), ptype(ptype), attribute(attribute) {
                    type = ptype->getPTypeCString();
                }
    SymbolEntry(std::string name,
                std::string kind,
                int level,
                std::string type,
                std::string attribute) : name(name), kind(kind), level(level), type(type), attribute(attribute) {
                    std::stringstream ss;
                    int first_para = 1;
                    ss << attribute;
                    while(true){
                        std::string str;
                        ss >> str;
                        if(ss.fail())break;
                        if(str.back() == ',')str.erase(str.end() - 1, str.end());
                        if(str[0] == '[' && first_para) {
                            parameter_.back() = parameter_.back() + " ";
                            parameter_.back() = parameter_.back() + str;
                            first_para = 0;
                        }
                        else if(str[0] == '[') parameter_.back() = parameter_.back() + str;
                        else parameter_.push_back(str);
                    }
                }
    std::string name;
    std::string kind;
    int level;
    std::string type;
    std::string attribute;
    std::string const_value;
    PTypeSharedPtr ptype;
    int not_valid_entry = 0;
    std::vector<std::string> parameter_;
};

class SymbolTable {
public:
    void addSymbol(std::string name,
                std::string kind,
                int level,
                std::string type,
                std::string attribute);
    void addSymbol(std::string name,
                std::string kind,
                int level,
                PTypeSharedPtr type,
                std::string attribute);
    
    std::vector<SymbolEntry> entries;
    std::string func_name = "";
    SymbolEntry* find_entry(std::string str) {
        for(unsigned int i =0;i < entries.size();i++){
            //fprintf(stderr,"in symbol table:%s\n",entries[i].name.c_str());
            if(entries[i].name == str)return &entries[i];
        }
        return nullptr;
    }
};

class SymbolManager {
public:
    void pushScope(SymbolTable *new_scope);
    void popScope();
    std::stack <SymbolTable *> tables;
    void dumpDemarcation(const char chr);
    void dumpSymbol(void);
};