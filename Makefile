SRCS=util.cc pri_queue.cc drusilla_select.cc afn.cc main.cc
OBJS=${SRCS:.cc=.o}

CXX=g++ -std=c++11
CPPFLAGS=-w -O3

.PHONY: clean

all: ${OBJS}
	${CXX} ${CPPFLAGS} -o drusilla ${OBJS}

util.o: util.h

pri_queue.o: pri_queue.h

drusilla_select.o: drusilla_select.h

afn.o: afn.h

main.o:

clean:
	-rm ${OBJS} drusilla
