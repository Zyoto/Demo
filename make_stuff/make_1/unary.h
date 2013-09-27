#ifndef _UNARY_H
#define _UNARY_H

#include <ostream>
#include <string>

using namespace std;

struct Expression;
typedef Expression * ExPtr;

enum UnOp {NEGATION, PAREN, BRACES, BRACKETS};

struct UnaryStmt {
	UnOp oper;
	ExPtr val;
};

#include "expr.h"

ExPtr NewUnExp(UnOp op, ExPtr a);
void Obliterate(UnaryStmt &);

bool Evaluate(const UnaryStmt &);

ostream& operator << (ostream &, const UnaryStmt &);
ostream& operator << (ostream &, const UnOp &);
string to_string(const UnaryStmt &);
string to_string(const UnOp &);

#endif
