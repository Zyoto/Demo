#include "table.h"

void PrintTable(ExPtr a) {
	vector<SimplePtr> vars, cons;
	int var_count, lc;

	CollectSimple(a, cons, vars);
	UniqueSimple(vars);
	UniqueSimple(cons);

	PrintHeader(cons, vars, a);
	cout << endl;

	lc = pow(2, vars.size());
	for (int i = 0; i < lc; i++) {
		AssignVars(i, vars);
			PrintDashesVars(vars);
			cout << "+";
			PrintDashesExpr(a);
			cout << endl;
		PrintVars(vars);
		cout << "|";
		PrintRow(a);
		cout << endl;
	}
}

void PrintHeader(vector<SimplePtr> cons, vector<SimplePtr> vars, ExPtr a) {
	// constants
	for (int i = 0; i < cons.size(); i++)
		if (string(cons[i]->id) != "T" or string(cons[i]->id) != "F")
			cout << cons[i]->id << " = " << to_string(cons[i]->var) << endl; 

	// variables
	for (int i = 0; i < vars.size(); i++) {
		if (i) cout << "|";
		cout << " " << vars[i]->id << " ";
	}

	cout << "|";

	// exprs
	PrintHeader(a);
}

void PrintHeader(ExPtr a) {
	if (a->type == UNARY) {
		PrintHeader(a->value.unary.val);
		if (a->value.unary.oper != PAREN) {
			cout << "| " << a << " ";
		}
	} else if (a->type == BINARY) {
		PrintHeader(a->value.binary.l_val);
		PrintHeader(a->value.binary.r_val);
		cout << "| " << a << " ";
	}
}

void PrintDashesExpr(ExPtr a) {
	if (a->type == UNARY) {
		PrintDashesExpr(a->value.unary.val);
		if (a->value.unary.oper != PAREN) {
			cout << "+-" << setw(to_string(a).length()) << setfill('-') << "" << "-";
		}
	} else if (a->type == BINARY) {
		PrintDashesExpr(a->value.binary.l_val);
		PrintDashesExpr(a->value.binary.r_val);
		cout << "+-" << setw(to_string(a).length()) << setfill('-') << "" << "-";
	}
	cout << setfill(' ');
}

void CollectSimple(ExPtr a, vector<SimplePtr> & cons, vector<SimplePtr> & vars) {
	if (a->type == UNARY) {
		CollectSimple(a->value.unary.val, cons, vars);
	} else if (a->type == BINARY) {
		CollectSimple(a->value.binary.l_val, cons, vars);
		CollectSimple(a->value.binary.r_val, cons, vars);
	} else if (a->type == SIMPLE) {
		if (a->value.simple->var) {
			vars.push_back(a->value.simple);
		} else {
			cons.push_back(a->value.simple);
		}
	}
}

void UniqueSimple(vector<SimplePtr> & a) {
	vector<SimplePtr> b;
	for (int i = 0; i < a.size(); i++) {
		if (find(b.begin(), b.end(), a[i]) == b.end())
			b.push_back(a[i]);
	}
	a = b;
}

void AssignVars(int a, vector<SimplePtr> vars) {
	for (int i = vars.size() - 1; i >= 0; i--) {
		vars[i]->val = a % 2;
		a = a / 2;
	}
}

void PrintVars(vector<SimplePtr> vars) {
	for (int i = 0; i < vars.size(); i++) {
		if (i) cout << "|";
		cout << " ";
		center(string(vars[i]->id).size(), to_string(vars[i]->val));
		cout << " ";
	}
}

void PrintDashesVars(vector<SimplePtr> vars) {
	cout << setfill('-');
	for (int i = 0; i < vars.size(); i++) {
		if (i) cout << "+";
		center(string(vars[i]->id).size(), "", 1, '-');
	}
}

void PrintRow(ExPtr a) {
	if (a->type == UNARY) {
		PrintRow(a->value.unary.val);
		if (a->value.unary.oper != PAREN) {
			cout << "| ";
			center(to_string(a).size(), to_string(Evaluate(a)));
			cout << " ";
		}
	} else if (a->type == BINARY) {
		PrintRow(a->value.binary.l_val);
		PrintRow(a->value.binary.r_val);
		cout << "|";
		center(to_string(a).size(), to_string(Evaluate(a)), 1);
		// NEW
	} 

}

void center(int a, string b, int padding, char fill) {
	int ls, rs, s;
	cout << setfill(fill);
	s = a - b.size() + 2 * padding;
	if (s < 0) s = 0;
	rs = s / 2;
	ls = s - rs;
	cout << setw(ls) << "" << b << setw(rs) << "";
}
