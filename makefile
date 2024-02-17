# final: lexer.o lookuptable.o
# gcc -o final lexer.o lookuptable.o

# lexer.o: lexer.c
# gcc -c lexer.c

# lookuptable.o: lookuptable.c
# gcc -c lookuptable.c

# clean:
# rm -f final lexer.o lookuptable.o
All:
		gcc -c lexer.c symboltable.c
		gcc -o final lexer.o symboltable.o
