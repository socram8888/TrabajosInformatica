
#include "Symbol.h"
#include <cmath>

symbol::symbol() {
  type = 0;
  value = 0.0;
  isconst = false;
}

symbol::symbol(const symbol &s) {
  type = s.type;
  value = s.value;
  isconst = s.isconst;
}

int symbol::getType() {
  return type; 
}

double symbol::getValue() {
  return value;
}

bool symbol::isConst() {
  return isconst;
}

void symbol::putType(int i) {
  type = i; 
}

void symbol::setConst(bool i) {
  isconst = i;
}

bool symbol::putValue(double v) {
  switch (type) {
    case 1:
      if (v == 0 || v == 1) {
	value = v;
	return true;
      }
      return false;

    case 2:
      value = floor(v);
      return true;

    case 3:
      value = v;
      return true;
  }

  return false;
}

ostream& operator<<(ostream& f, const symbol &s) {
  switch (s.type) {
    case 1:
      f << "(" << (s.value == 1 ? "true" : "false") << ",bool";
      break;
    case 2:
      f << "(" << s.value << ",int";
      break;
    case 3:
      f << "(" << s.value << ",double";
      break;
  }
  if (s.isconst) {
    f << ",const";
  }
  f << ")";
  return f;
}

symbol & symbol::operator=(const symbol & s) {
  value = s.value;
  type = s.type;
  return *this;
}