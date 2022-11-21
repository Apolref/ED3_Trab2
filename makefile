all : exec

run:
	./exec

clean:
	rm -f *.o
	rm -f exec

main.o : main.c
	gcc -o main.o -c main.c

Functionally1.o: Functionally1.c
	gcc -o Functionally1.o -c Functionally1.c

Functionally2.o : Functionally2.c
	gcc -o Functionally2.o -c Functionally2.c

Functionally3.o : Functionally3.c
	gcc -o Functionally3.o -c Functionally3.c

Functionally4.o: Functionally4.c
	gcc -o Functionally4.o -c Functionally4.c

Functionally5.o : Functionally5.c
	gcc -o Functionally5.o -c Functionally5.c

Functionally6.o : Functionally6.c
	gcc -o Functionally6.o -c Functionally6.c

funcoesFornecidas.o : funcoesFornecidas.c
	gcc -o funcoesFornecidas.o -c funcoesFornecidas.c

DefaultPrints.o : DefaultPrints.c DefaultPrints.h
	gcc -o DefaultPrints.o -c DefaultPrints.c

FernandoBiblioteca.o : FernandoBiblioteca.c FernandoBiblioteca.h
	gcc -o FernandoBiblioteca.o -c FernandoBiblioteca.c

LuigiBiblioteca.o : LuigiBiblioteca.c LuigiBiblioteca.h
	gcc -o LuigiBiblioteca.o -c LuigiBiblioteca.c

AlexandreBiblioteca.o : AlexandreBiblioteca.c AlexandreBiblioteca.h
	gcc -o AlexandreBiblioteca.o -c AlexandreBiblioteca.c

exec : main.o Functionally1.o Functionally2.o Functionally3.o Functionally4.o Functionally5.o Functionally6.o funcoesFornecidas.o DefaultPrints.o FernandoBiblioteca.o LuigiBiblioteca.o AlexandreBiblioteca.o
	gcc -o exec main.o Functionally1.o Functionally2.o Functionally3.o Functionally4.o Functionally5.o Functionally6.o funcoesFornecidas.o DefaultPrints.o FernandoBiblioteca.o LuigiBiblioteca.o AlexandreBiblioteca.o