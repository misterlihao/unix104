CPPFLAGS := -g -std=c++11
.PHONY: all
all: a.out
a.out: main.o
	$(CXX) $(CPPFLAGS) $^ -o $@

clean:
	rm -rf *.o
