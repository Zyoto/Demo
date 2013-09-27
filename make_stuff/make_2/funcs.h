#ifndef _FUNCS_H
#define _FUNCS_H

#include "expr.h"
#include "table.h"
#include <vector>

using namespace std;

using std::vector;

void ForEachEval( ExPtr exp,  
                  // ^ expression used as argument to iteration function
                  void (*func)(ExPtr, vector <SimplePtr> &, vector <SimplePtr> &),
                  // ^ iteration function
                  void (*header)(ExPtr, vector <SimplePtr> &, vector <SimplePtr> &) = 0
                  // ^ optional header function
                );

template <class funcRv>
void ForEachEval( ExPtr exp,  
                  // ^ expression used as argument to iteration function
                  funcRv (*func)(ExPtr, vector <SimplePtr> &, vector <SimplePtr> &),
                  // ^ iteration function
                  vector<funcRv> & evals,
                  // ^ return value from iteration function
                  void (*header)(ExPtr, vector <SimplePtr> &, vector <SimplePtr> &) = 0
                  // ^ optional header function
                );

void EvaluateAll(ExPtr exp, vector<bool> & rv);
bool Evaluate(ExPtr exp, vector <SimplePtr> & cons, vector <SimplePtr> & vars);

//---------------//
// From parser.y //
//---------------//

bool Equivalence(const ExPtr &, const ExPtr &);
bool Implication(const ExPtr &, const ExPtr &);
void DrawTree(const ExPtr &);
void DrawTable(const ExPtr &);
void PrintExpr(const ExPtr &);
void IsAnything(const ExPtr &);
bool IsTautology(const ExPtr &, bool verbose = true);
bool IsEquivalence(const ExPtr &, bool verbose = true);
bool IsImplication(const ExPtr &, bool verbose = true);
bool IsContradiction(const ExPtr &, bool verbose = true);

#endif
