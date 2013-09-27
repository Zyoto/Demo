#include "simple.h"

ExPtr NewSimpExp(char * id, bool var, bool val) {
	ExPtr rv = new Expression;
  rv->ref_count = 1;
	rv->type = SIMPLE;
	rv->value.simple = new SimpleStmt;
	rv->value.simple->id = id;
	rv->value.simple->var = var;
	rv->value.simple->val = val;

	return rv;
}

void Obliterate(SimplePtr & a) {
	return;
}

bool Evaluate(const SimplePtr & a) {
	return a->val;
}

ostream& operator << (ostream & out, const SimplePtr & a) {
	out << to_string(a);

	return out;
}

string to_string(const SimplePtr & a) {
	string rv;
	if (!a) {
		return "NULL";
	}

	return string(a->id);
}

string to_string(const bool & a) {
	if (a)
		return "T";
	return "F";
}
