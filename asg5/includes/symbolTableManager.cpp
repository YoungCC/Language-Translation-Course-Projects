#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <iterator>
#include "literal.h"
#include "symbolTableManager.h"

SymbolTableManager& SymbolTableManager::getInstance() {
    static SymbolTableManager instance;
    return instance;
}

void SymbolTableManager::makeSymbolTable() {
    SymbolTable* st = new SymbolTable();
    scope.push_back(st);
    PoolOfNodes::getInstance().addSymbolTable(st);
}

void SymbolTableManager::removeSymbolTable() {
    scope.pop_back();
}

const Literal* SymbolTableManager::getValue(std::string name) const {
    if(funcDepth != 1){
        std::vector<SymbolTable*>::const_reverse_iterator it = scope.rbegin();
	while(it != scope.rend())	
	{
	    const Literal* res = (*it) -> SymbolTable::getValue(name);
	    if(res != NULL) return res;
	    it++;
	}
    }else{
	const Literal* res = scope.back() -> SymbolTable::getValue(name);
        if(res != NULL) return res;
        const Literal* res1 = scope.front() -> SymbolTable::getValue(name);
        if(res1 != NULL) return res1;
    }
    return NULL;
}

void SymbolTableManager::setValue(std::string name, const Literal* val) {
    if(SymbolTableManager::getInstance().funcDepth == 0)
    {
	scope.front() -> SymbolTable::setValue(name, val);
    }else{
	scope.back() -> SymbolTable::setValue(name, val);	
    }
}

Node* SymbolTableManager::getFunctionTable(std::string name) {
    std::map<std::string, Node*>::const_iterator it = functionTable.find(name);
    if ( it == functionTable.end() ) throw name+std::string(" not found");
    return it->second;
}

void SymbolTableManager::setFunctionTable(const std::string& name, Node* func){
    functionTable[name] = func;
}

const Literal* SymbolTableManager::getGlobalValue(std::string name) const{
    const Literal* res = scope.front() -> SymbolTable::getValue(name);
    if(res != NULL) return res;
    return NULL;
}

