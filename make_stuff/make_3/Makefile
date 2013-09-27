CC = g++
CXXFLAGS = -w -fmax-errors=3

EXE = main
OBJECTS = binary unary simple expr parser table funcs
C_ONLY = lexer

all:: main

#------------------------------------------------------------------------------
#| Compile Objects                                                            |
#------------------------------------------------------------------------------

$(EXE): %: $(OBJECTS:%=%.o) $(EXE:%=%.cc) $(C_ONLY:%=%.cc)
	$(CC) -o $(EXE) $(CXXFLAGS) $(OBJECTS:%=%.o) $(EXE:%=%.cc) $(C_ONLY:%=%.cc)

$(OBJECTS:%=%.o): %.o: %.cc %.h
	$(CC) -c $(CFLAGS) $< -o $@


lexer.cc: lexer.l parser.h
	flex -o lexer.cc lexer.l

parser.cc: parser.y
	bison -o parser.cc --defines=parser.h parser.y

parser.h: parser.cc

#------------------------------------------------------------------------------
#| Misc Functions                                                             |
#------------------------------------------------------------------------------

backup:
	make clean
	cd backups; ./backup

clear:
	clear
	make

clean:
	rm lexer.cc -f
	rm parser.cc -f
	rm parser.h -f
	rm $(OBJECTS:%=%.o) -f
	rm $(EXE) -f

echo:
	echo $(OBJECTS:%=%.o)
