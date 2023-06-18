output: pqueue.o dijkstra.o dial.o radix.o main.o
	g++ -std=c++11 -Wall main.o dijkstra.o pqueue.o dial.o radix.o -o output

# output2: pqueue.o dijkstra.o main.o
# 	g++ -std=c++11 -Wall main.o dijkstra.o pqueue.o -o output2

pqueue.o: pqueue.cpp pqueue.hpp
	g++ -c pqueue.cpp

main.o: main.cpp
	g++ -c main.cpp

dijkstra.o: dijkstra.cpp dijkstra.hpp
	g++ -c dijkstra.cpp

dial.o : dial.cpp dial.hpp
	g++ -c dial.cpp

radix.o: radix.cpp radix.hpp
	g++ -c radix.cpp