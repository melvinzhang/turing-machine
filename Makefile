SHELL=/bin/bash

tm: turing-machine.cpp
	g++ --std=c++11 -O3 $^ -o $@

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

bb4.out: bb4.tm
	cat $^ | ./tm 200 -1 > $@

bb5.out: bb5.tm
	cat $^ | ./tm 50000000 -1 > $@
