#include "sema/symbolTable.hpp"

void SymbolManager::dumpDemarcation(const char chr) {
  for (size_t i = 0; i < 110; ++i) {
    printf("%c", chr);
  }
  puts("");
}

void SymbolManager::dumpSymbol(void) {
  dumpDemarcation('=');
  printf("%-33s%-11s%-11s%-17s%-11s\n", "Name", "Kind", "Level", "Type",
                                        "Attribute");
  dumpDemarcation('-');
  {
    for(unsigned int i = 0;i < tables.top()->entries.size();i++){
        printf("%-33s", tables.top()->entries[i].name.c_str());
        printf("%-11s", tables.top()->entries[i].kind.c_str());
        if(tables.top()->entries[i].level > 0) printf("%d%-10s", tables.top()->entries[i].level, "(local)");
        else printf("%d%-10s", 0, "(global)");
        printf("%-17s", tables.top()->entries[i].type.c_str());
        printf("%-11s", tables.top()->entries[i].attribute.c_str());
        puts("");

        /* // debug mode
        fprintf(stderr,"%-33s", tables.top()->entries[i].name.c_str());
        fprintf(stderr,"%-11s", tables.top()->entries[i].kind.c_str());
        if(tables.top()->entries[i].level > 0) fprintf(stderr,"%d%-10s", tables.top()->entries[i].level, "(local)");
        else fprintf(stderr,"%d%-10s", 0, "(global)");
        fprintf(stderr,"%-17s", tables.top()->entries[i].type.c_str());
        fprintf(stderr,"%-11s", tables.top()->entries[i].attribute.c_str());
        fprintf(stderr,"\n");
        */
    }
  }
  dumpDemarcation('-');
}

void SymbolTable::addSymbol(std::string name,
                std::string kind,
                int level,
                PTypeSharedPtr type,
                // std::string type,
                std::string attribute){
    SymbolEntry entry_tmp(name,kind,level,type,attribute);
    entries.push_back(entry_tmp);
}
void SymbolTable::addSymbol(std::string name,
                std::string kind,
                int level,
                // PTypeSharedPtr type,
                std::string type,
                std::string attribute){
    SymbolEntry entry_tmp(name,kind,level,type,attribute);
    entries.push_back(entry_tmp);
}

void SymbolManager::pushScope(SymbolTable *new_scope){
    tables.push(new_scope);
}
void SymbolManager::popScope(){
    dumpSymbol();
    tables.pop();
}