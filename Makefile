RecordOutput.o: RecordOutput.cpp RecordOutput.h
	g++ -c RecordOutput.cpp

RecordInput.o: RecordInput.cpp RecordInput.h
	g++ -c RecordInput.cpp

NewPoker.o: NewPoker.cpp RecordOutput.h RecordInput.h
	g++ -c NewPoker.cpp

NewPoker: NewPoker.o RecordOutput.o RecordInput.o
	g++ NewPoker.o RecordOutput.o RecordInput.o -o NewPoker
