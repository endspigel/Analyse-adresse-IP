#compile toute l'application
all:
	gcc -c fonctions.c
	gcc fonctions.o main.c -o main

#Fait l'édition de liens si .o plus récents que main
main: main.o fonctions.o
	gcc -o main main.o fonctions.o

#Efface les objets et l'éxecutable
clean:
	rm main.o fonctions.o
	rm main
