#include <iostream>
#include <typeinfo>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <iomanip>
#include "ast.h"
#include "symbolTableManager.h"

const Literal* IdentNode::eval() const { 
  const Literal* val = SymbolTableManager::getInstance().getValue(ident);
  return val;
}


AsgBinaryNode::AsgBinaryNode(Node* left, Node* right) : 
  BinaryNode(left, right) { 
  const Literal* res = right->eval();
  const std::string n = static_cast<IdentNode*>(left)->getIdent();
  SymbolTableManager::getInstance().setValue(n, res);
}


const Literal* AsgBinaryNode::eval() const { 
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* res = right->eval();
  const std::string n = static_cast<IdentNode*>(left)->getIdent();
  SymbolTableManager::getInstance().setValue(n, res);
  return res;
}

const Literal* AddBinaryNode::eval() const { 
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)+(*y));
}

const Literal* SubBinaryNode::eval() const { 
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)-(*y));
}

const Literal* MulBinaryNode::eval() const { 
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)*(*y));
}

const Literal* DivBinaryNode::eval() const { 
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)/(*y));
}

const Literal* DoubleStarBinaryNode::eval() const { 
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x).doubleStar(*y));
}

const Literal* PercentBinaryNode::eval() const { 
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)%(*y));
}

const Literal* DoubleSlashBinaryNode::eval() const { 
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x).doubleSlash(*y));
}

const Literal* FuncNode::eval() const { 
  std::vector<Node*>::iterator it = suite->begin();
  const std::string id = static_cast<IdentNode*>(left)->getIdent();
  int tmp = 1;
  if(scope == 1)
  {
    tmp = SymbolTableManager::getInstance().funcDepth;
    SymbolTableManager::getInstance().funcDepth = 1;
  }
  const Literal* res = NULL;
  while(it != suite->end())
  {
     res = (*it)->eval();
     const Literal* l = SymbolTableManager::getInstance().getValue("RETURN");    
     if(l != NULL)
	break;
     it++;
  }
  SymbolTableManager::getInstance().funcDepth = tmp;
  if(res != NULL) return res;
  else return NULL;
}

const Literal* PrintNode::eval() const { 
  const Literal* res = right->eval();
  if(res->getVal() == 1000000000) std::cout<<"None"<<std::endl;    
  else res->eval()->print();
  return NULL;
}

const Literal* GlobalNode::eval() const { 
  std::vector<Node*>::iterator it = vec->begin();
  while(it != vec->end())
  {
    const std::string id = static_cast<IdentNode*>(*it)->getIdent();
    const Literal* res = SymbolTableManager::getInstance().getGlobalValue(id);
    if(res != NULL) SymbolTableManager::getInstance().setValue(id, res);
    it++;
  }
  return NULL;
}

const Literal* ReturnNode::eval() const { 
  if(right != NULL)
  {
    const Literal* res = right->eval();
    SymbolTableManager::getInstance().setValue("RETURN", res);
    return res;
  }else{
    const Literal* res = new IntLiteral(1000000000);
    SymbolTableManager::getInstance().setValue("RETURN", res);
    return res;
  }
}

const Literal* SuiteNode::eval() const { 
  if (!left || !right) {
    throw std::string("error");
  }
  Node* res = new AsgBinaryNode(left,right);
  PoolOfNodes::getInstance().add(res);
  return NULL;
}

const Literal* CallNode::eval() const{
  SymbolTableManager::getInstance().funcDepth +=1;
  const std::string id = static_cast<IdentNode*>(funcName)->getIdent();
  Node* func = SymbolTableManager::getInstance().getFunctionTable(id);
  SymbolTableManager::getInstance().makeSymbolTable();
  const Literal* res = func->eval();
  SymbolTableManager::getInstance().removeSymbolTable();
  SymbolTableManager::getInstance().funcDepth -=1;
  if(res == NULL) return NULL;
  else return res;
}

const Literal* IfNode::eval() const { 
  const Literal* t = test->eval();
  float val = t->getVal();
  if(val){
    std::vector<Node*>::iterator it = left->begin();
    const Literal* res = NULL;
    while(it != left->end())
    {
      res = (*it)->eval();
      if(res!= NULL) break;
      it++;
    }
    return res;
  }else{
    if(right !=NULL){
      std::vector<Node*>::iterator it = right->begin();
      const Literal* res = NULL;
      while(it != right->end())
      {
        res = (*it)->eval();
        if(res!=NULL) break;
        it++;
      }
      return res;
    }
    return NULL;
  }
}

const Literal* LessBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  float l = x->getVal();
  float r = y->getVal();
  if(l < r)
  {
    const Literal* res = new IntLiteral(1);
    PoolOfNodes::getInstance().add(res);
    return res;
  }else{ 
    const Literal* res = new IntLiteral(0);
    PoolOfNodes::getInstance().add(res);
    return res;
  }
}

const Literal* LessEqualBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  float l = x->getVal();
  float r = y->getVal();
  if(l <= r)
  {
    const Literal* res = new IntLiteral(1);
    PoolOfNodes::getInstance().add(res);
    return res;
  }else{ 
    const Literal* res = new IntLiteral(0);
    PoolOfNodes::getInstance().add(res);
    return res;
  }
}

const Literal* GreaterBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  float l = x->getVal();
  float r = y->getVal();
  if(l > r)
  {
    const Literal* res = new IntLiteral(1);
    PoolOfNodes::getInstance().add(res);
    return res;
  }else{ 
    const Literal* res = new IntLiteral(0);
    PoolOfNodes::getInstance().add(res);
    return res;
  }
}

const Literal* GreaterEqualBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  float l = x->getVal();
  float r = y->getVal();
  if(l >= r)
  {
    const Literal* res = new IntLiteral(1);
    PoolOfNodes::getInstance().add(res);
    return res;
  }else{ 
    const Literal* res = new IntLiteral(0);
    PoolOfNodes::getInstance().add(res);
    return res;
  }
}

const Literal* EqEqualBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  float l = x->getVal();
  float r = y->getVal();
  if(l == r)
  {
    const Literal* res = new IntLiteral(1);
    PoolOfNodes::getInstance().add(res);
    return res;
  }else{ 
    const Literal* res = new IntLiteral(0);
    PoolOfNodes::getInstance().add(res);
    return res;
  }
}

const Literal* NotEqualBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  float l = x->getVal();
  float r = y->getVal();
  if(l != r)
  {
    const Literal* res = new IntLiteral(1);
    PoolOfNodes::getInstance().add(res);
    return res;
  }else{ 
    const Literal* res = new IntLiteral(0);
    PoolOfNodes::getInstance().add(res);
    return res;
  }
}

