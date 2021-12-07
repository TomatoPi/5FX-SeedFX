CXXFLAGS=-Wall -I../src -g

all:
	make tests_mem_hetero
	make tests_mem_pool
	make tests_jack
	make tests_std_compliant_alloc

tests_jack: ../src/jack/jack.cpp

tests_std_compliant_alloc: ../src/alloc/static_allocator.hpp

% : %.cpp ../src/err/err.cpp ../src/alloc/heterogenous_allocator.hpp
	g++ --std=c++17 $(CXXFLAGS) $^ -o $@