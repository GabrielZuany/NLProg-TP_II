CC=gcc
FLAGS=-lm 
pontosH=lib/*.h
pontosC=src/tDocumento.c src/tPalavra.c src/uteis.c
#k = segunda entrada
K=2
DiretorioBinario=out.bin
DiretorioEntrada=datasets/tiny/train.txt
PROG1=exe1
PROG2=exe2

teste1:
	@echo $(pontosC)

compile1: 
	@$(CC) -o $(PROG1) src/prog1.c $(pontosC) $(FLAGS)
	@echo compilado!

exe1: compile1
	@./$(PROG1) $(DiretorioEntrada) $(DiretorioBinario)

vexe1: compile1
	@valgrind -s ./$(PROG1) $(DiretorioEntrada) $(DiretorioBinario)

compile2:
	@$(CC) -o $(PROG2) src/prog2.c $(pontosC) $(FLAGS)
	@echo compilado!

exe2: compile2
	@./$(PROG2) $(DiretorioBinario) $(K)

vexe2: compile2
	@valgrind -s ./$(PROG2) $(DiretorioBinario) $(K)
