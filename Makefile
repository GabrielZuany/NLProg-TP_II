CC=gcc
FLAGS=-c -lm -Wall -pedantic
DEPS = $(wildcard lib/*.h)
OBJ = $(wildcard objects/*.o)
SRC = $(wildcard src/*.c)
EXE = exe_prog1 exe_prog2
OBJ_Prog1 = objects/prog1.o objects/tDocumento.o objects/tPalavra.o objects/uteis.o
OBJ_Prog2 = objects/prog2.o objects/tDocumento.o objects/tPalavra.o objects/uteis.o

all: prog1 prog2

Compile $(DEPS): CreateFolder
	@$(CC) -o objects/prog1.o prog1.c $(FLAGS)
	@$(CC) -o objects/prog2.o prog2.c $(FLAGS)
	@$(CC) -o objects/tDocumento.o src/tDocumento.c $(FLAGS)
	@$(CC) -o objects/tPalavra.o src/tPalavra.c $(FLAGS)
	@$(CC) -o objects/uteis.o src/uteis.c $(FLAGS)
	@echo compilado objects!

prog1: Compile
	@$(CC) -o exe_prog1 $(OBJ_Prog1) -lm
	@echo compilado executavel prog1!

prog2: Compile
	@$(CC) -o exe_prog2 $(OBJ_Prog2) -lm
	@echo compilado executavel prog2!

CreateFolder:
	@mkdir -p objects

clean:
	@rm -rf objects && rm -rf exe_prog1 && rm -rf exe_prog2
	@rm *.bin
	@echo removidos!
	
#K=2
#DiretorioBinario=out.bin
#DiretorioEntrada=datasets/tiny/train.txt
#porg1: ./exe_prog1 datasets/tiny/train.txt out.bin
#prog2: ./exe_prog2 out.bin 14