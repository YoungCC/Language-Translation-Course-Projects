#include "node.h"
#include <math.h>
#include <cmath>
#include <iomanip>  
#include "poolOfNodes.h"

class Literal : public Node {
public:
  virtual ~Literal() {}

  virtual const Literal* operator+(const Literal& rhs) const =0;
  virtual const Literal* opPlus(long double) const =0;
  virtual const Literal* opPlus(int) const =0;

  virtual const Literal* operator*(const Literal& rhs) const =0;
  virtual const Literal* opMult(long double) const =0;
  virtual const Literal* opMult(int) const =0;

  virtual const Literal* operator-(const Literal& rhs) const =0;
  virtual const Literal* opSubt(long double) const =0;
  virtual const Literal* opSubt(int) const =0;

  virtual const Literal* operator/(const Literal& rhs) const =0;
  virtual const Literal* opDiv(long double) const =0;
  virtual const Literal* opDiv(int) const =0;

  virtual const Literal* doubleStar(const Literal& rhs) const =0;
  virtual const Literal* opDStar(long double) const =0;
  virtual const Literal* opDStar(int) const =0;

  virtual const Literal* operator%(const Literal& rhs) const =0;
  virtual const Literal* opPerc(long double) const =0;
  virtual const Literal* opPerc(int) const =0;

  virtual const Literal* doubleSlash(const Literal& rhs) const =0;
  virtual const Literal* opDSlash(long double) const =0;
  virtual const Literal* opDSlash(int) const =0;

  virtual float getVal() const =0;
  virtual const Literal* eval() const = 0;
  virtual void print() const { 
    std::cout << "No Way" << std::endl; 
  }
};

class FloatLiteral: public Literal {
public:
  FloatLiteral(long double _val): val(_val) {}

  virtual const Literal* operator+(const Literal& rhs) const  {
    return rhs.opPlus(val);
  }
  virtual const Literal* opPlus(long double lhs) const  {
    const Literal* node = new FloatLiteral(lhs + val);
    PoolOfNodes::getInstance().add(node);
    return node; 
  }
  virtual const Literal* opPlus(int lhs) const  {
    const Literal* node = new FloatLiteral(lhs + val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator-(const Literal& rhs) const  {
    return rhs.opSubt(val);
  }
  virtual const Literal* opSubt(long double lhs) const  {
    const Literal* node = new FloatLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opSubt(int lhs) const  {
    const Literal* node = new FloatLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator*(const Literal& rhs) const  {
    return rhs.opMult(val);
  }
  virtual const Literal* opMult(long double lhs) const  {
    const Literal* node = new FloatLiteral(lhs * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opMult(int lhs) const  {
    const Literal* node = new FloatLiteral(static_cast<long double>(lhs) * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator/(const Literal& rhs) const  {
    return rhs.opDiv(val);
  }
  virtual const Literal* opDiv(long double lhs) const  {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node = new FloatLiteral(lhs / val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opDiv(int lhs) const  {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node = new FloatLiteral(lhs / val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* doubleStar(const Literal& rhs) const  {
    return rhs.opDStar(val);
  }
  virtual const Literal* opDStar(long double lhs) const  {
    const Literal* node = new FloatLiteral(pow(lhs,val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opDStar(int lhs) const  {
    const Literal* node = new FloatLiteral(pow(lhs,val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator%(const Literal& rhs) const  {
    return rhs.opPerc(val);
  }
  virtual const Literal* opPerc(long double lhs) const  {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node;
    if ( (fmod(lhs,val) == 0.0 ) && ((val < 0) || (lhs < 0)) )  
      node = new FloatLiteral(-fmod(lhs,val));
    else if ( ( lhs>0 && val<0 ) || ( lhs<0 && val>0) ) 
      node = new FloatLiteral(fmod(lhs,val) + val);
    else node = new FloatLiteral(fmod(lhs,val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opPerc(int lhs) const  {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node;
    if ( (fmod(lhs,val) == 0.0 ) && ((val < 0) || (lhs < 0)) )  
      node = new FloatLiteral(-fmod(lhs,val));
    else if ( ( lhs>0 && val<0 ) || ( lhs<0 && val>0) ) 
      node = new FloatLiteral(fmod(lhs,val) + val);
    else node = new FloatLiteral(fmod(lhs,val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* doubleSlash(const Literal& rhs) const  {
    return rhs.opDSlash(val);
  }
  virtual const Literal* opDSlash(long double lhs) const  {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node = new FloatLiteral(std::floor(lhs / val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opDSlash(int lhs) const  {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node = new FloatLiteral(std::floor(lhs / val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  float getVal() const {
	return val;
  }

  virtual const Literal* eval() const { return this; }
  virtual void print() const { 
    if(fmod(val,1) == 0)
      std::cout << std::setprecision(12) << val << ".0" <<std::endl; 
    else
      std::cout << std::setprecision(12) << val << std::endl;  
  }
private:
  long double val;
};

class IntLiteral: public Literal {
public:
  IntLiteral(int _val): val(_val) {}

  virtual const Literal* operator+(const Literal& rhs) const  {
    return rhs.opPlus(val);
  }
  virtual const Literal* opPlus(long double lhs) const  {
    const Literal* node = new FloatLiteral(static_cast<long double>(val) + lhs);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opPlus(int lhs) const  {
    const Literal* node = new IntLiteral(lhs + val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator-(const Literal& rhs) const  {
    return rhs.opSubt(val);
  }
  virtual const Literal* opSubt(long double lhs) const  {
    const Literal* node = new FloatLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opSubt(int lhs) const  {
    const Literal* node = new IntLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator*(const Literal& rhs) const  {
    return rhs.opMult(val);
  }
  virtual const Literal* opMult(long double lhs) const  {
    const Literal* node = new FloatLiteral(lhs * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opMult(int lhs) const  {
    const Literal* node = new IntLiteral(lhs * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator/(const Literal& rhs) const  {
    return rhs.opDiv(val);
  }
  virtual const Literal* opDiv(long double lhs) const  {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node = new FloatLiteral(lhs / val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opDiv(int lhs) const  {
    if ( val == 0 ) throw std::string("Zero Division Error");
    int tmp = lhs / val;
    if(( lhs>0 && val<0 ) || ( lhs<0 && val>0))
      tmp = tmp-1;
    const Literal* node = new IntLiteral(tmp);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* doubleStar(const Literal& rhs) const  {
    return rhs.opDStar(val);
  }
  virtual const Literal* opDStar(long double lhs) const  {
    const Literal* node = new FloatLiteral(pow(lhs,val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opDStar(int lhs) const  {
    const Literal* node;
    if ( val < 0 ) node = new FloatLiteral(pow(lhs,val));
    else node = new IntLiteral(pow(lhs,val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator%(const Literal& rhs) const  {
    return rhs.opPerc(val);
  }
  virtual const Literal* opPerc(long double lhs) const  {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node; 
    if ( (fmod(lhs,val) == 0.0 ) && ((val < 0) || (lhs < 0)) )  
      node = new FloatLiteral(-fmod(lhs,val));
    else if ( ( lhs>0 && val<0 ) || ( lhs<0 && val>0) ) 
      node = new FloatLiteral(fmod(lhs,val) + val);
    else node = new FloatLiteral(fmod(lhs,val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opPerc(int lhs) const  {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node;
    if ( ( lhs>0 && val<0 ) || ( lhs<0 && val>0) ) 
      node = new IntLiteral(fmod(lhs,val) + val); 
    else node = new IntLiteral(fmod(lhs,val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* doubleSlash(const Literal& rhs) const  {
    return rhs.opDSlash(val);
  }
  virtual const Literal* opDSlash(long double lhs) const  {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node = new FloatLiteral(std::floor(lhs / val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opDSlash(int lhs) const  {
    return opDiv(lhs);
  }

  float getVal() const {
    return (float)val;
  }

  virtual const Literal* eval() const { return this; }
  virtual void print() const { 
    std::cout << val << std::endl; 
  }
private:
  int val;
};

