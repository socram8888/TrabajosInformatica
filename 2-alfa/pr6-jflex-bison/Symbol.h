#include <fstream>

using namespace std;

class symbol {
public:
 symbol();
 symbol(const symbol &);
 int getType();
 double getValue();
 void putType(int);
 bool putValue(double);
 symbol & operator=(const symbol &);
 friend ostream& operator<<(ostream&, const symbol &);
 bool isConst();
 void setConst(bool);

private:
 int type;
 double value;
 bool isconst;
};