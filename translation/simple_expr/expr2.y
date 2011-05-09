%{
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum Type {
    LOGARITHMIC = 1,
    TRIGONOMETRIC = 2,
    SQUARE = 4,
    LINEAR = 8,
    ANOTHER = 16,
};

int type = 0;

struct Info {
    int val;
    int degree;
};

int max(int x, int y) {
    return x > y ? x : y;
}

%}

%union {
    struct Info inf;
}

%type <inf> equ
%type <inf> NUM
%type <inf> exp
%type <inf> func
%type <inf> varchain
%type <inf> add_exp
%type <inf> mul_exp
%type <inf> unary_exp
%type <inf> primary

%token NUM LPAREN RPAREN VAR END EQ
%token LOG EXP SIN COS TN 
%left PLUS MINUS
%left TIMES DIV
%left NEG
%right POW

%%

equ: exp EQ exp END          { printf("degree: %d\n", max($1.degree, $3.degree));
                               printf("val: %d - %d\n", $1.val, $3.val);
                             //if ($.degree1 == 1) type |= LINEAR;
                             if (max($1.degree, $3.degree) == 2) type |= SQUARE;
                             if (type == LOGARITHMIC)
                                printf("logarithmic\n");
                             else if (type == TRIGONOMETRIC)
                                printf("trigonometric\n");
                             else if (type == SQUARE)
                                printf("square\n");
                             else
                                printf("another\n");
                             exit(0); }
                             ;

exp: add_exp
   | exp POW add_exp       { if ($3.degree != 0) type = ANOTHER;
                             else $$.val = (int)pow($1.val, $3.val);
                           }
;

add_exp: mul_exp
       | add_exp PLUS mul_exp       { $$.val = $1.val + $3.val;
                                     $$.degree = max($1.degree, $3.degree);
                                    }
       | add_exp MINUS mul_exp      { $$.val = $1.val - $3.val; 
                                     $$.degree = max($1.degree, $3.degree);
                                    }
;

mul_exp: unary_exp
       | mul_exp TIMES unary_exp         { $$.val = $1.val * $3.val; 
                                           $$.degree = $1.degree + $3.degree; }
       | mul_exp DIV unary_exp           { if ($3.degree != 0) type = ANOTHER;
                                           else {
                                              if ($3.val == 0) yyerror("division by zero\n"); 
                                              $$.val = $1.val / $3.val; 
                                           }
                                         }
;

unary_exp: primary
         | MINUS primary %prec NEG        { $$.val = -$2.val;
                                            $$.degree = $2.degree;
                                          }
;

primary:
     LPAREN exp RPAREN     { $$.val = $2.val; 
                             $$.degree = $2.degree;
                           }
   | func                  { $$.val = $1.val; 
                             $$.degree = $1.degree;
                           }
   | NUM func              { $$.val = $1.val * $2.val; 
                             $$.degree = $2.degree;
                           }
   | NUM                   { $$.val = $1.val; }
   | NUM varchain          { $$.degree = $2.degree; }
   | NUM varchain func     { $$.degree = $2.degree; }
   | varchain func         { $$.degree = $1.degree; }
   | varchain              { $$.val = 0;
                             $$.degree = $1.degree; }
                             ;


varchain: VAR varchain     { $$.degree = $2.degree + 1; }
        | VAR              { $$.degree = 1; }
        ;

func: LOG LPAREN exp RPAREN { if ($3.val > 0) $$.val = (int)log($3.val); 
                              if ($3.degree != 0) type |= LOGARITHMIC;
                            }
    | EXP LPAREN exp RPAREN { $$.val = (int)exp($3.val);
                              if ($3.degree != 0) type |= LOGARITHMIC;
                            }
    | SIN LPAREN exp RPAREN { $$.val = (int)sin($3.val); 
                              if ($3.degree != 0) type |= TRIGONOMETRIC;
                            }
    | COS LPAREN exp RPAREN { $$.val = (int)cos($3.val); 
                              if ($3.degree != 0) type |= TRIGONOMETRIC;
                            }
    | TN  LPAREN exp RPAREN { $$.val = (int)tan($3.val); 
                              if ($3.degree != 0) type |= TRIGONOMETRIC;
                            }
;

%%

void yyerror(const char *s) {
    fprintf(stderr, s);
    exit(0);
}

int main(void) {
    yyparse();
    return 0;
}
