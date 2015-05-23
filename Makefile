a.out: turing-machine.cpp
	g++ --std=c++11 $^

%.run: a.out %.tm
	cat $*.tm | ./a.out
