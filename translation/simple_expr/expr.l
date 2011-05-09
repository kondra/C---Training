%{
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


struct Info {
    int val;
    int degree;
};

#include "expr.tab.h"

char var = '\0';

%}
 
%%
"+"                  { return PLUS;       }
"-"                  { return MINUS;      }
"*"                  { return TIMES;      }
"/"                  { return DIV;        }
"^"                  { return POW;        }
"("                  { return LPAREN;     }
")"                  { return RPAREN;     }
"="                  { return EQ;         }
[lL][oO][gG]         { return LOG;        }
[lL][nN]             { return LOG;        }
[eE][xX][pP]         { return EXP;        }
[sS][iI][nN]         { return SIN;        }
[cC][oO][sS]         { return COS;        }
[tT][nN]             { return TN;         }
[0-9]*               { if (strlen(yytext) > 1 && yytext[0] == '0') yyerror("leading zero\n");
                       yylval.inf.val = atoi(yytext); return NUM; 
                     }
[a-zA-Z]             { if (var == '\0') var = tolower(yytext[0]);
                       else if (tolower(yytext[0]) != var) yyerror("more than one variable\n");
                       return VAR; }
\n                   { if (var == '\0') yyerror("no variables\n");
                       return END; }
[ \t]                {}
%%
