#include "binary.h"

ExPtr NewBinExp(ExPtr l_val, BinOp op, ExPtr r_val) {
	ExPtr rv = new Expression;
  rv->ref_count = 1;
	rv->type = BINARY;
	rv->value.binary.l_val = l_val;
	rv->value.binary.oper = op;
	rv->value.binary.r_val = r_val;
}

void Obliterate(BinaryStmt & a) {
	Obliterate(a.l_val);
	Obliterate(a.r_val);

	return;
}

bool Evaluate(const BinaryStmt & a) {
	bool rv;
	bool l_val, r_val;
	l_val = Evaluate(a.l_val);
	r_val = Evaluate(a.r_val);

	switch (a.oper) {
    case    LIST:
		case	 CONJUNCTION:	rv = l_val and r_val;							break;
		case	 DISJUNCTION:	rv = l_val or r_val;							break;
		case	 CONDITIONAL:	rv = (not l_val) or r_val;				break;
		case BICONDITIONAL: rv = (((not l_val) or r_val) and
															((not r_val) or l_val));		break;
	}

	return rv;
}

ostream& operator << (ostream & out, const BinaryStmt & a) {
	out << to_string(a);

	return out;
}

string to_string(const BinaryStmt & a) {
	string rv;

//	rv += "[";
	rv += to_string(a.l_val);
	rv += to_string(a.oper);
	rv += to_string(a.r_val);
//	rv += "]";

	return rv;
}

ostream& operator << (ostream & out, const BinOp & a) {
	out << to_string(a) << endl;
	return out;
}

string to_string(const BinOp & a) {
	string rv;

	switch (a) {
    case          LIST: rv = ", ";  break;
		case	 CONJUNCTION:	rv = "&";		break;
		case	 DISJUNCTION:	rv = "+";		break;
		case	 CONDITIONAL: rv = "->";	break;
		case BICONDITIONAL: rv = "<->";	break;
	}

	return rv;
}










