 
 start     : functions EOL
           | ...

 functions : DRAW_TABLE '(' stmt ')'    { // actions ... }
           | ... 
 
 stmt      : bico_stmt                  { // actions ... }
 
 bico_stmt : bico_stmt YYBICO cond_stmt { // actions ... } 
           | cond_stmt                  { // actions ... }
 cond_stmt : cond_stmt YYCOND disj_stmt { // actions ... }
           | disj_stmt                  { // actions ... }
 disj_stmt : disj_stmt YYDISJ conj_stmt { // actions ... }
           | conj_stmt                  { // actions ... }
 conj_stmt : conj_stmt YYCONJ unar_stmt { // actions ... }
           | unar_stmt                  { // actions ... }
 
 unar_stmt : '-' unar_stmt              { // actions ... }
           | '(' stmt ')'               { // actions ... }
           | simp_stmt                  { // actions ... }

