flags=-O2 -Wall -std=c2x
ldflags=-lbu
#ldflags=-lbu

.PHONY: all clean

all: clean SenzuVM

~/Downloads/birchutils/birchutils/birchutils.o:~/Downloads/birchutils/birchutils/birchutils.c ~/Downloads/birchutils/birchutils/birchutils.h
	cpwd=$(PWD)
	(cd ~/Downloads/birchutils/birchutils/ && make)
	make birchutils.o
	cd $(cpwd)


SenzuVM: SenzuVM.o ~/Downloads/birchutils/birchutils/birchutils.o
	cc $(flags) $< -o $@ $(ldflags) ~/Downloads/birchutils/birchutils/birchutils.o

SenzuVM.o: SenzuVM.c SenzuVM.h
	cc $(flags) -c $<

clean:
	rm -f *.o SenzuVM
