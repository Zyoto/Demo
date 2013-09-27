#include "unary.h"

ExPtr NewUnExp(UnOp op, ExPtr val) {
	ExPtr rv = new Expression;
  rv->ref_count = 1;
	rv->type = UNARY;
	rv->value.unary.oper = op;
	rv->value.unary.val = val;
}

void Obliterate(UnaryStmt & a) {
	Obliterate(a.val);

	return;
}

bool Evaluate(const UnaryStmt & a) {
	bool rv;
	bool val = Evaluate(a.val);

	switch (a.oper) {
		case NEGATION:	rv = not val;		break;
		default:	rv = val;				break;
	}

	return rv;
}

ostream& operator << (ostream & out, const UnaryStmt & a) {
	out << to_string(a);

	return out;
}

string to_string(const UnaryStmt & a) {
	string rv;

	if (a.oper == NEGATION) rv += "-";
	else if (a.oper == PAREN) rv += "(";
	else if (a.oper == BRACES) rv += "{";
	else if (a.oper == BRACKETS) rv += "[";
	rv += to_string(a.val);
  if      (a.oper == PAREN) rv += ")";
	else if (a.oper == BRACES) rv += "}";
	else if (a.oper == BRACKETS) rv += "]";

	return rv;
}

ostream& operator << (ostream & out, const UnOp & a) {
	out << to_string(a); 
	return out;
}
string to_string(const UnOp & a) {
	string rv;

	switch (a) {
		case NEGATION: rv = "-"; break;
		case PAREN: rv = "()"; break;
		case BRACES: rv = "{}"; break;
		case BRACKETS: rv = "[]"; break;
	}

	return rv;
}
