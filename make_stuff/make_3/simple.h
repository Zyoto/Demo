#ifndef _SIMPLE_H
#define _SIMPLE_H

#include <iostream>
#include <string>


using namespace std;

struct Expression;
typedef Expression * ExPtr;
struct SimpleStmt;
typedef SimpleStmt * SimplePtr;

struct SimpleStmt {
	char * id;
	bool var;
	bool val;
};

#include "expr.h"

ExPtr NewSimpExp(char *, bool variable = true, bool val = false);
void Obliterate(SimplePtr &);

bool Evaluate(const SimplePtr &);

ostream& operator << (ostream &, const SimplePtr &);
string to_string(const SimplePtr &);
string to_string(const bool &);

#endif
