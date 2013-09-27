
 SIMPLE_ID      [A-Z]

 DRAW_TABLE     (?i:drawtable)

 {DRAW_TABLE}   { return (DRAW_TABLE); }

 "("            { return ('('); }
 ")"            { return (')'); }
 "&"            { return (YYCONJ); }
 "+"            { return (YYDISJ); }
 "->"           { return (YYCOND); }
 "<->"          { return (YYBICO); }




a
