CXXFLAGS=-Wall -I../src -g

all:
	make tests_mem_hetero
	make tests_mem_pool
	make tests_jack

tests_jack: ../src/jack/jack.cpp

% : %.cpp ../src/err/err.cpp ../src/alloc/heterogenous_allocator.hpp
	g++ $(CXXFLAGS) $^ -o $@