SHELL=/bin/bash

tm: turing-machine.cpp
	g++ --std=c++11 $^ -o $@

%.run: tm %.tm
	cat $*.tm | ./tm

%.out: tm %.tm
	cat $*.tm | ./tm > $@

%.test: tm %.tm
	diff <(cat $*.tm | ./tm) $*.out

output:
	for i in *.tm; do make `basename $$i .tm`.out; done

tests:
	for i in *.tm; do make `basename $$i .tm`.test; done

utm.tm: states.utm
	awk -f states2tm.awk < $^  > $@

%.run: tm %.tape
	cat utm.tm $*.tape | ./tm 10000
