flags=-Wextra -Wall -lm -std=c17 -pedantic -Wall 
srcDir=src
objDir=$(srcDir)/obj
main=rotor.exe

run: compile

run_ex1: compile ex1

run_ex2: compile ex2

compile:
	@if [ ! -d $(objDir) ]; then \
		mkdir $(objDir); \
    fi
	gcc -c $(flags) $(srcDir)/rotor.c -o $(objDir)/rotor.o 
	gcc -c $(flags) $(srcDir)/utils.c -o $(objDir)/utils.o
	gcc $(objDir)/rotor.o $(objDir)/utils.o $(srcDir)/main.c -o rotor.exe 

ex1:
	$(main) C 5 GIROSCOPIO BAUNILHA FEIJAO ARROZ BATATA 1000000000 255 1 13 25 26 1 3 0 0 carta.txt carta.bin

ex2:
	$(main) 5 GIROSCOPIO BAUNILHA FEIJAO ARROZ BATATA 1000000000 255 1 13 25 26 1 3 0 0 carta.bin decodificado.txt

remove:
	rm -rf *.exe *.bin src/obj
