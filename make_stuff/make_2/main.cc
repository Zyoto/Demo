#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include "table.h"
#include "expr.h"
#include "parser.h"

using namespace std;

extern int yyparse();
extern FILE * yyin;

ExPtr yybisonval;

map <string, ExPtr> expr_tab;

void InsertConstants();
void TreeForm(ExPtr a, int tabs = 0);

int main(int argc, char * argv[]) {
  ifstream fin;
  bool input_from_file = false;
  string line;

  if (argc > 2 && string(argv[1]) == string("-f")) {
    cout << "INPUT FROM FILE" << endl;
    input_from_file = true;
    yyin = fopen(argv[2], "r");
    fin.open(argv[2]);
    cout << "INPUT FROM FILE" << endl;
  }

	InsertConstants();
	cout << " >";
  if (input_from_file) {
    getline(fin, line); 
    cout << line << endl;
  }
  
	while (yyparse()) {
		cout << " >";
    if (input_from_file) {
      getline(fin, line); 
      cout << line << endl;
    }
	}

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
