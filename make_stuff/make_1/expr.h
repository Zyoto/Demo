#ifndef _EXPR_H
#define _EXPR_H

#include <ostream>
#include <string>

#include "binary.h"
#include "simple.h"
#include "unary.h"

using namespace std;

struct Expression;
typedef Expression * ExPtr;
typedef SimpleStmt * SimplePtr;

enum ExprType {UNARY = 1, BINARY, SIMPLE};

struct Expression {
	ExprType type;
	int ref_count;
	bool last_eval;
	union {
		UnaryStmt unary;
		BinaryStmt binary;
		SimplePtr simple;
	} value;
};

void Obliterate(ExPtr & a);
bool Evaluate(const ExPtr & a);
ostream& operator << (ostream & out, const ExPtr & a);
string to_string(const ExPtr & a);
void AddRef(ExPtr);
void RemRef(ExPtr);

#endif
