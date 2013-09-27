#ifndef _TABLE_H
#define _TABLE_H

#include <vector>
#include "expr.h"
#include <cmath>
#include <algorithm>
#include <iomanip>

void PrintTable(ExPtr a);
void PrintHeader(vector<SimplePtr> cons, vector<SimplePtr> vars, ExPtr a);
void PrintHeader(ExPtr a);
void CollectSimple(ExPtr exp, vector<SimplePtr> & cons, vector<SimplePtr> & vars);
void UniqueSimple(vector<SimplePtr> & a);
void AssignVars(int a, vector<SimplePtr> vars);
void PrintVars(vector<SimplePtr> vars);
void PrintRow(ExPtr a);
void PrintDashesExpr(ExPtr a);
void center(int a, string b, int padding = 0, char fill = ' ');
void PrintDashesVars(vector<SimplePtr> vars);

#endif
