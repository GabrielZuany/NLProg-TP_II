CC=gcc
FLAGS=-lm
pontosH=lib/*.h
pontosC=src/*.c


all1: compile1 exe1
vall1: compile1 vexe1


compile1: 
	@$(CC) -o indice $(pontosC) $(FLAGS)
	@echo compilado!

exe1:
	@./indice datasets/tiny/train.txt out.bin

vexe1: 
	@valgrind -s ./indice datasets/tiny/train.txt out.bin