D           [0-9]
L           [a-zA-Z_]
H           [a-fA-F0-9]
E           ([Ee][+-]?{D}+)
P           ([Pp][+-]?{D}+)
FS          (f|F|l|L)
IS          ((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))

%%

"int"           { count(); return(INT); }
{D}+        { count(); return(CONSTANT); }
{L}({L}|{D})*       { count(); return(IDENTIFIER); }

L?\"(\\.|[^\\\"\r\n])*\"    { count(); return(STRING_LITERAL); }

";"         { count(); return(';'); }
("{"|"<%")  { count(); return('{'); }
("}"|"%>")  { count(); return('}'); }
"="         { count(); return('='); }
"("         { count(); return('('); }
")"         { count(); return(')'); }
"-"         { count(); return('-'); }
"+"         { count(); return('+'); }

[ \t\v\r\n\f]       { count(); }
.           { /* Add code to complain about unmatched characters */ }

%%


