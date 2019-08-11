CC = g++
SOURCEOBJS = partition.o count.o topK.o
MAINOBJS = $(SOURCEOBJS) main.o
TESTOBJS = $(SOURCEOBJS) test.o
OBJECTS = $(SOURCEOBJS) main.o test.o
MAINEXEC = main
TESTEXEC = test


all : main test

main : $(MAINOBJS)
	$(CC) -o $(MAINEXEC) $(MAINOBJS)

test : $(TESTOBJS)
	$(CC) -o $(TESTEXEC) $(TESTOBJS)

main.o : main.cpp
	$(CC) -c -g main.cpp
partition.o : partition.cpp consts.h
	$(CC) -c -g partition.cpp
count.o : count.h consts.h
	$(CC) -c -g count.cpp
topK.o : topK.h consts.h
	$(CC) -c -g topK.cpp
test.o : test.cpp
	$(CC) -c -g test.cpp

.PHONY : clean
clean :
	rm $(OBJECTS)
