CXX         = g++-4.9
CPPFLAGS    = -DNDEBUG 
CXXFLAGS    = -std=c++11 -fcilkplus -g -Wall -O3 # -Winline
TARGET_ARCH = -march=corei7 -mtune=corei7
LDFLAGS     = -lcilkrts

TARGET = treewalk

all: $(TARGET)

semigroup.o: config.hpp semigroup.cpp semigroup.hpp
treewalk.o: config.hpp test.hpp treewalk.cpp treewalk.hpp semigroup.hpp
treewalk: treewalk.o semigroup.o
	$(CXX) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

clean:
	rm -rf $(TARGET) *.o 

test: all
	./treewalk

