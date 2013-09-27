%{
#include <string>
#include <iostream>
#include <cstdlib>
#include <map>
#include <string.h>
#include "expr.h"
#include "funcs.h"

using namespace std;

void yyerror(string msg);
ExPtr GetSimplePtr(char *);
ExPtr GetTablePtr(char *);
void TableInsert(char *, ExPtr a);

extern int yylex();
extern ExPtr yybisonval;
extern map<string, ExPtr> expr_tab;

%}

%union {
    char * str;
    ExPtr exp;
}

%token EXIT EOL
%token <str> SIMPLE_ID VARIABLE_ID
%token YYBICO YYCOND YYDISJ YYCONJ
%token <exp> LAST_EXPRESSION
%token EQUIVALENCE IMPLICATION
%token DRAW_TREE DRAW_TABLE PRINT_EXPR
%token IS_ANYTHING IS_TAUTOLOGY IS_EQUIVALENCE IS_IMPLICATION IS_CONTRADICTION

%type <exp> stmt bico_stmt cond_stmt disj_stmt conj_stmt unar_stmt simp_stmt arg_list

%%

start     :               { return 0; }
          | EXIT EOL      { return 0; }
          | EOL           { return 1; }
          | functions EOL { return 1; }
          | assign EOL    { return 1; }
          | stmt EOL      { TableInsert("LAST", $1);  return 1; }

stmt      : bico_stmt { $$ = $1; }

assign    : VARIABLE_ID '=' bico_stmt { TableInsert($1, $3); delete $1; }

bico_stmt : bico_stmt YYBICO cond_stmt { $$ = NewBinExp($1, BICONDITIONAL, $3); } 
          | cond_stmt                  { $$ = $1;                               }
cond_stmt : cond_stmt YYCOND disj_stmt { $$ = NewBinExp($1, CONDITIONAL,   $3); }
          | disj_stmt                  { $$ = $1;                               }
disj_stmt : disj_stmt YYDISJ conj_stmt { $$ = NewBinExp($1, DISJUNCTION,   $3); }
          | conj_stmt                  { $$ = $1;                               }
conj_stmt : conj_stmt YYCONJ unar_stmt { $$ = NewBinExp($1, CONJUNCTION,   $3); }
          | unar_stmt                  { $$ = $1;                               }

unar_stmt : '-' unar_stmt { $$ = NewUnExp(NEGATION, $2); }
          | '(' stmt ')'  { $$ = NewUnExp(PAREN,    $2); }
          | '{' stmt '}'  { $$ = NewUnExp(BRACES,   $2); }
          | '[' stmt ']'  { $$ = NewUnExp(BRACKETS, $2); }
          | simp_stmt     { $$ = $1;                     }

simp_stmt : SIMPLE_ID       { $$ = GetSimplePtr($1);    }
            /*need to seperate these functions*/
          | VARIABLE_ID     { $$ = GetTablePtr($1); 
            /*error here on undefined expressions*/     }
          | LAST_EXPRESSION { $$ = GetTablePtr("LAST");
            /*error on first expression*/               }

functions : EQUIVALENCE '(' stmt ',' stmt ')'      { Equivalence($3, $5); }
          | IMPLICATION '(' arg_list  ':' stmt ')' { Implication($3, $5); }
          | DRAW_TREE        '(' stmt ')' { DrawTree        ($3); }
          | DRAW_TABLE       '(' stmt ')' { DrawTable       ($3); }
          | PRINT_EXPR       '(' stmt ')' { PrintExpr       ($3); }
          | IS_ANYTHING      '(' stmt ')' { IsAnything      ($3); }
          | IS_TAUTOLOGY     '(' stmt ')' { IsTautology     ($3); }
          | IS_EQUIVALENCE   '(' stmt ')' { IsEquivalence   ($3); }
          | IS_IMPLICATION   '(' stmt ')' { IsImplication   ($3); }
          | IS_CONTRADICTION '(' stmt ')' { IsContradiction ($3); }

arg_list  : stmt ',' arg_list	{ $$ = NewBinExp($1, LIST, $3); }
          | stmt              { $$ = $1;                      }

%%

ExPtr GetSimplePtr(char * id) {
  ExPtr rv;
  map<string, ExPtr>::iterator it;
  it = expr_tab.find(id);
  if (it == expr_tab.end()) {
    rv = (expr_tab[id] = NewSimpExp(id));
  } else {
    rv = it->second;
    AddRef(rv);
    delete id;
  }
  return rv;
}

ExPtr GetTablePtr(char * id) {
  ExPtr rv;
  map<string, ExPtr>::iterator it;
  it = expr_tab.find(id);
  if (it == expr_tab.end()) {
    // error here
    rv = 0;
    delete id;
  } else {
    rv = it->second;
    AddRef(rv);
    delete id;
  }
  return rv;
}

void TableInsert(char * id, ExPtr a) {
  map<string, ExPtr>::iterator it;
  it = expr_tab.find(id);
  if (it == expr_tab.end()) {
    expr_tab[id] = a;
  } else {
    RemRef(expr_tab[id]);
    expr_tab[id] = a;
  }
}

extern string yytext;
void yyerror(string msg) {
    cout << "Error @ " << "'" << msg << "'" << endl;
    return;
}
