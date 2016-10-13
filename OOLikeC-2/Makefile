OBJ_FILES := $(patsubst ./%.c, ./%.o, $(wildcard ./*.c))

all: ooc2_exe

ooc2_exe: $(OBJ_FILES)
	gcc -o $@ $^

./%.o: ./%.cpp
	gcc -c -o $@ $<

clean:
	find . -name \*.o -type f -delete
	rm ooc2_exe
