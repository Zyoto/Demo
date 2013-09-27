#include "expr.h"

void Obliterate(ExPtr & a) {
	if (a && (a->ref_count == 0)) {
		switch (a->type) {
			case BINARY:
				Obliterate(a->value.binary);
				delete a;
				a = 0;
				break;
			case SIMPLE:
				break;
			case  UNARY:
				Obliterate(a->value.unary);
				delete a;
				a = 0;
				break;
		}
	}


	return;
}

bool Evaluate(const ExPtr & a) {
	bool rv;

	switch (a->type) {
		case BINARY:	rv = Evaluate(a->value.binary);		break;
		case SIMPLE:	rv = Evaluate(a->value.simple);		break;
		case  UNARY:	rv = Evaluate(a->value.unary);		break;
	}

	return rv;
}

ostream& operator << (ostream & out, const ExPtr & a) {
	out << to_string(a);

	return out;
}

string to_string(const ExPtr & a) {
	string rv;
	if (a == 0) {
		return "NULL";
	}

	switch (a->type) {
		case BINARY:	rv = to_string(a->value.binary);	break;
		case SIMPLE:	rv = to_string(a->value.simple);	break;
		case  UNARY:	rv = to_string(a->value.unary);		break;
	}

	return rv;
}

void AddRef(ExPtr a) {
  a->ref_count++;
}
void RemRef(ExPtr a) {
  a->ref_count--;
  if (a->ref_count == 0)
    Obliterate(a);
    
}
