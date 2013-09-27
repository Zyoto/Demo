#include <string>
#include <map>
#include "parser.h"
#include "expr.h"

map <string, ExPtr> expr_tab;

extern int yyparse();
void InsertConstants();

int main(int argc, char * argv[]) {
	InsertConstants();

	cout << ">";
	while (yyparse())
		cout << ">";

  return 0;
}

void InsertConstants() {
	expr_tab["T"] = NewSimpExp("T", 0, 1);
	expr_tab["F"] = NewSimpExp("F", 0, 0);
	return;
}

void TreeForm(ExPtr a, int tabs) {

	switch(a->type) {
		case BINARY:
			TreeForm(a->value.binary.l_val, tabs+1);
			for (int i = 0; i < tabs; i++)
				cout << "   ";
			cout << to_string(a->value.binary.oper) << endl;
			TreeForm(a->value.binary.r_val, tabs+1);
			break;
		case UNARY:
			for (int i = 0; i < tabs; i++)
				cout << "   ";
			cout << to_string(a->value.unary.oper) << endl;
			TreeForm(a->value.unary.val, tabs+1);
			break;
		case SIMPLE:
			for (int i = 0; i < tabs; i++)
				cout << "   ";
			cout << a->value.simple->id << endl;
			break;
	}
}
