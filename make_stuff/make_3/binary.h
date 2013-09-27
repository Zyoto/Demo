#ifndef _BINARY_H
#define _BINARY_H

#include <string>
#include <ostream>

using namespace std;

struct Expression;
typedef Expression * ExPtr;

enum BinOp {CONJUNCTION = '&', DISJUNCTION ='+', CONDITIONAL = '>', BICONDITIONAL = '<', LIST = ',' };

struct BinaryStmt {
	BinOp oper;
	ExPtr l_val;	
	ExPtr r_val;	
};

#include "expr.h"

ExPtr NewBinExp(ExPtr l_val, BinOp op, ExPtr r_val);
void Obliterate(BinaryStmt &);

bool Evaluate(const BinaryStmt &);

ostream& operator << (ostream &, const BinaryStmt &);
ostream& operator << (ostream &, const BinOp &);
string to_string(const BinaryStmt &);
string to_string(const BinOp &);

#endif
