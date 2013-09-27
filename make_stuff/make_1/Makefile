# what program "make" will build
all:: main

# how to build main
# target: dependancies (main.c\C\cc\cpp are included by default)
main: binary.o unary.o simple.o expr.o parser.o table.o funcs.o lexer.cc

# how to build objects
# target: depandancies (binary.c\C\cc\cpp are included by default)
binary.o:

unary.o:

simple.o:

expr.o:

parser.o:

table.o:

funcs.o:

#------------------------------------------------------------------------------
#| Misc Functions                                                             |
#------------------------------------------------------------------------------

# "make clear" will run the following commands
# command must follow the line of the rule
# LINES MUST START WITH A TAB
clear:
	clear
	make

clean:
	rm lexer.cc -f
	rm parser.cc -f
	rm parser.h -f
	rm binary.o unary.o simple.o expr.o parser.o table.o funcs.o -f
	rm main -f

#---------------------------
#| Don't worry about these |
#---------------------------

lexer.cc: lexer.l parser.h
	flex -o lexer.cc lexer.l

parser.cc: parser.y
	bison -o parser.cc --defines=parser.h parser.y

parser.h: parser.cc

