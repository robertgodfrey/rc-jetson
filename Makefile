server: hello.o server.o
	g++ -o application server.o hello.o

server.o: server.cpp hello.h
	g++ -ansi -pedantic-errors -Wall -c -I ../Crow/include -lpthread -std=c++11 server.cpp

hello.o: hello.cpp hello.h
	g++ -ansi -pedantic-errors -Wall -c hello.cpp

clean:
	rm *.o

