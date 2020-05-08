RecordOutput.o: RecordOutput.cpp RecordOutput.h
	g++ -c RecordOutput.cpp

RecordInput.o: RecordInput.cpp RecordInput.h
	g++ -c RecordInput.cpp

Poker.o: Poker.cpp RecordOutput.h RecordInput.h
	g++ -c Poker.cpp

Poker: Poker.o RecordOutput.o RecordInput.o
	g++ Poker.o RecordOutput.o RecordInput.o -o Poker
