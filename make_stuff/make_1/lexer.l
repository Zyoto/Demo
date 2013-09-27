%option noyywrap yylineno
%{

#include "expr.h"
#include "parser.h"
 
%}
SIMPLE_ID         [A-Z][0-9]*
VARIABLE_ID       [a-z]+
WS                [ \t]+

EXIT              (?i:exit)
EQUIVALENCE       (?i:equivalence)
IMPLICATION       (?i:implication)
DRAW_TABLE        (?i:drawtable)
IS_ANYTHING       (?i:isanything)
IS_TAUTOLOGY      (?i:istautology)
IS_EQUIVALENCE    (?i:isequivalence)
IS_IMPLICATION    (?i:isimplication)
IS_CONTRADICTION  (?i:iscontradiction)
LAST_EXPR         (?i:last)
%%

{EXIT}              { return (EXIT);             }
{EQUIVALENCE}       { return (EQUIVALENCE);      }
{IMPLICATION}       { return (IMPLICATION);      }
{DRAW_TABLE}        { return (DRAW_TABLE);       }
{IS_ANYTHING}       { return (IS_ANYTHING);      }
{IS_TAUTOLOGY}      { return (IS_TAUTOLOGY);     }
{IS_EQUIVALENCE}    { return (IS_EQUIVALENCE);   }
{IS_IMPLICATION}    { return (IS_IMPLICATION);   }
{IS_CONTRADICTION}  { return (IS_CONTRADICTION); }
{LAST_EXPR}         { return (LAST_EXPRESSION);  }

"="   { return ('='); }
","   { return (','); }
":"   { return (':'); }
"-"   { return ('-'); }
"("   { return ('('); }
")"   { return (')'); }
"["   { return ('['); }
"]"   { return (']'); }
"{"   { return ('{'); }
"}"   { return ('}'); }
"&"   { return (YYCONJ); }
"+"   { return (YYDISJ); }
"->"  { return (YYCOND); }
"<->" { return (YYBICO); }

{WS}    {               }
"\n"    { return (EOL); }
<<EOF>> { return (EOF); }

{SIMPLE_ID}   { yylval.str = strdup(yytext);  return (SIMPLE_ID);   }
{VARIABLE_ID} { yylval.str = strdup(yytext);  return (VARIABLE_ID); }

%%
