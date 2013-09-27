#include "funcs.h"

void ForEachEval( ExPtr exp,  
                  // ^ expression used as argument to iteration function
                  void (*func)(ExPtr, vector <SimplePtr> & , vector <SimplePtr> &),
                  // ^ iteration function
                  void (*header)(ExPtr, vector <SimplePtr> & , vector <SimplePtr> &)
                  // ^ optional header function
                ) {
  vector<SimplePtr> cons, vars;
  int lc;

  CollectSimple(exp, cons, vars);
  UniqueSimple(vars);
  UniqueSimple(cons);

  if (header)
    header(exp, cons, vars);

  lc = pow(2, vars.size());

  for (int i = 0; i < lc; i++) {
    AssignVars(i, vars);
    func(exp, cons, vars);
  }

  return;
}

template <class funcRv>
void ForEachEval( ExPtr exp,  
                  // ^ expression used as argument to iteration function
                  funcRv (*func)(ExPtr, vector <SimplePtr> &, vector <SimplePtr> &),
                  // ^ iteration function
                  vector<funcRv> & evals,
                  // ^ return value from iteration function
                  void (*header)(ExPtr, vector <SimplePtr> &, vector <SimplePtr> &)
                  // ^ optional header function
                ) {
  vector<SimplePtr> vars, cons;
  int lc;

  CollectSimple(exp, cons, vars);
  UniqueSimple(vars);
  UniqueSimple(cons);

  if (header)
    header(exp, cons, vars);

  lc = pow(2, vars.size());

  evals.resize(lc);
  for (int i = 0; i < lc; i++) {
    AssignVars(i, vars);
    evals[i] = func(exp, cons, vars);
  }

  return;
}

void EvaluateAll(ExPtr exp, vector<bool> & rv) {
  ForEachEval(exp, &Evaluate, rv);
}

bool Evaluate(ExPtr exp, vector <SimplePtr> & cons, vector <SimplePtr> & vars) {
  bool rv;

  rv = Evaluate(exp);

  return rv;
}


bool Equivalence(const ExPtr & lhs, const ExPtr & rhs) {
	bool rv = false;

	ExPtr a = NewBinExp(lhs, BICONDITIONAL, rhs);

	if (IsEquivalence(a), 0) {
		cout << lhs << " and " << rhs << " are equivalent." << endl;
		rv = true;
	}

	return rv;
}

bool Implication(const ExPtr & lhs, const ExPtr & rhs) {
	bool rv = false;

	ExPtr a = NewBinExp(lhs, CONDITIONAL, rhs);

	if (IsImplication(a), 0) {
		cout << rhs << " is an implication of " << rhs << "." << endl;
		rv = true;
	}

	return rv;
}

void DrawTree(const ExPtr & a) {
  //PrintTree(a);
}

void DrawTable(const ExPtr & a) {
  PrintTable(a);
}

void PrintExpr(const ExPtr & a) {
  cout << a << endl;
}

void IsAnything(const ExPtr & a) {
	IsTautology(a, 1);
	IsEquivalence(a, 1);
	IsImplication(a, 1);
	IsContradiction(a, 1);

  return;
}

bool IsTautology(const ExPtr & a, bool verbose) {
	bool rv = true;
  vector<bool> evals;

  EvaluateAll(a, evals);

  for (int i = 0; i < evals.size() && rv; i++)
    rv &= evals[i];

  if (verbose & rv)
    cout << a << " is a tautology." << endl;

	return rv;
}

bool IsEquivalence(const ExPtr & a, bool verbose) {
	bool rv = false;
  vector<bool> evals;

  if (a->type == BINARY && a->value.binary.oper == BICONDITIONAL) {
    rv = true;

    EvaluateAll(a, evals);

    for (int i = 0; i < evals.size() && rv; i++)
      rv &= evals[i];
  }

  if (verbose & rv)
    cout << a << " is an equivalence." << endl;

	return rv;
}

bool IsImplication(const ExPtr & a, bool verbose) {
	bool rv = false;
  vector<bool> evals;

  if (a->type == BINARY && a->value.binary.oper == CONDITIONAL) {
    rv = true;

    EvaluateAll(a, evals);

    for (int i = 0; i < evals.size() && rv; i++) {
      rv &= evals[i];
    }
  }

  if (verbose & rv)
    cout << a->value.binary.r_val << " is an implication of " << a->value.binary.l_val << endl;

  else
    cout << a->value.binary.r_val << " is not an implication of " << a->value.binary.l_val << endl;

	return rv;
}

bool IsContradiction(const ExPtr & a, bool verbose) {
	bool rv = false;
  vector<bool> evals;

  EvaluateAll(a, evals);

  for (int i = 0; i < evals.size() && !rv; i++)
    rv |= evals[i];

  rv = !rv;

  if (verbose && rv)
    cout << a << " is a contradiction." << endl;

	return rv;
}
