YFLAGS        = -d
PROGRAM       = expr
OBJS          = expr.tab.o lex.yy.o
SRCS          = expr.tab.c lex.yy.c
CC            = gcc 

all:            $(PROGRAM)
.c.o:           $(SRCS)
								$(CC) -c $*.c -o $@ -O

expr.tab.c:     expr.y
								bison $(YFLAGS) expr.y

lex.yy.c:      expr.l 
								flex expr.l

expr:           $(OBJS)
								$(CC) $(OBJS)  -o $@ -lfl -lm

clean:;         rm -f $(OBJS) core *~ \#* *.o $(PROGRAM) \
								y.* lex.yy.* expr.tab.*
