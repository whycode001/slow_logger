VERSION="\"1.0.0.1\""

CXX=g++
CFLAGS=-g --std=c++11 -Wall -finline-functions -D_REENTRANT -DVERSION=${VERSION}

INCDIR := -I./ -I../
LIBDIR := -L./ -L../

LIBS := -pthread

RM := rm -rf

SRC  = $(wildcard *.cpp ../*.cpp ../util/*.cpp)
OBJS = $(patsubst %cpp, %o, $(SRC))

TARGET = slow_logger

all : ${TARGET}

clean :
	${RM} ../*.o *.o ${TARGET} 

${TARGET} : ${OBJS}
	${CXX} $^ ${CFLAGS} ${INCDIR} ${LIBDIR} ${LIBS} -o $@

.cpp.o:
	${CXX} -c $^ ${CFLAGS} ${INCDIR} -o $@
