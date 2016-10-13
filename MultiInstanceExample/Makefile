OBJ_FILES := $(patsubst %.cpp, %.o, $(wildcard *.cpp))

all: multi_inst_exe

multi_inst_exe: $(OBJ_FILES)
	g++ -o $@ $^

%.o: %.cpp
	g++ -c -o $@ $<

clean:
	find . -name \*.o -type f -delete
	rm multi_inst_exe
