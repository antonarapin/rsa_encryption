OPTS = -Wall

test: test.cc ReallyLongInt.o
	g++ ${OPTS} -o test test.cc ReallyLongInt.o

factorial: factorial.cc ReallyLongInt.o
	g++ ${OPTS} -o factorial factorial.cc ReallyLongInt.o

ReallyLongInt.o: ReallyLongInt.cc ReallyLongInt.h
	g++ ${OPTS} -c ReallyLongInt.cc

encrypt: encrypt.cc ReallyLongInt.o numberTheory.h
	g++ ${OPTS} -o encrypt encrypt.cc ReallyLongInt.o

decrypt: decrypt.cc ReallyLongInt.o numberTheory.h
	g++ ${OPTS} -o decrypt decrypt.cc ReallyLongInt.o

keygen: keygen.cc ReallyLongInt.o numberTheory.h
	g++ ${OPTS} -o keygen keygen.cc ReallyLongInt.o
