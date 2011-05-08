%{
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum Type {
    LOGARITHMIC = 1,
    TRIGONOMETRIC = 2,
    SQUARE = 4,
    ANOTHER = 7,
};

int type = 0;

%}

%token NUM LPAREN RPAREN VAR END
%token LOG EXP SIN COS TN
%left PLUS MINUS
%left TIMES DIV
%right POW

%%

equ: exp END               { printf("%d\n", $1); exit(0); }

exp: exp PLUS exp          { $$ = $1 + $3; }
   | exp MINUS exp         { $$ = $1 - $3; }
   | exp TIMES exp         { $$ = $1 * $3; }
   | exp DIV exp           { if ($3 == 0) yyerror("division by zero\n"); 
                             $$ = $1 / $3; }
   | exp POW exp           { $$ = (int)pow($1, $3);}
   | LPAREN exp RPAREN     { $$ = $2; }
   | func                  { $$ = $1; }
   | NUM func              { $$ = $1 * $2; }
   | NUM                   { $$ = $1; }

func: LOG LPAREN exp RPAREN { $$ = (int)log($3); }
    | EXP LPAREN exp RPAREN { $$ = (int)exp($3); }
    | SIN LPAREN exp RPAREN { $$ = (int)sin($3); }
    | COS LPAREN exp RPAREN { $$ = (int)cos($3); }
    | TN  LPAREN exp RPAREN { $$ = (int)tan($3); }

%%

void yyerror(char *s) {
    fprintf(stderr, s);
    exit(0);
}

int main(void) {
    yyparse();
    return 0;
}
