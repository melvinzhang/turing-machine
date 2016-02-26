SHELL=/bin/bash

a.out: turing-machine.cpp
	g++ --std=c++11 $^

%.run: a.out %.tm
	cat $*.tm | ./a.out

%.out: a.out %.tm
	cat $*.tm | ./a.out > $@

%.test: a.out %.tm
	diff <(cat $*.tm | ./a.out) $*.out

tests:
	for i in *.tm; do make `basename $$i .tm`.test; done
