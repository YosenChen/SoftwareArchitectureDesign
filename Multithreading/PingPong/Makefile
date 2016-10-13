CFLAGS=	-g
OBJ=	TwoThreadsPingPong_sol1.o

pingpong: ${OBJ}
	c++ ${CFLAGS} -o $@ ${OBJ} -pthread

${OBJ}: %.o: %.cpp
	c++ ${CFLAGS} -c $< -pthread

clean:
	rm -f pingpong ${OBJ}

