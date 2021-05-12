#!/bin/sh
fontes = \
	src/Main.c\
	src/Apllyforces.c\
	src/Controlador.c\
	src/Elmlib_Wave.c\
	src/Especial_forces.c\
	src/Gauss.c\
	src/Geometria.c\
        src/Files.c\
	src/Matvec.c\
	src/Numeq.c\
	src/Pcg.c\
	src/Pform_Wave.c\
        src/Predict_Wave.c\
	src/Readfile_Wave.c
.SUFFIXES: .c .h .o
OS= $(shell uname -s)
CFLAGS=-I./include/ -O2  -ftree-vectorize
LDFLAGS= -lm  
OBJS= $(fontes:%.c=%.o)

build:	$(OBJS) 
	ls bin || mkdir -p bin
	$(CC) $(OBJS) -o bin/mef_wave  $(LDFLAGS)
list:
	(cd dist/$(projeto); ls $(projeto)_*.md5  \
	| sort  -r > files_$(projeto))
tags:	
	rm -f tags
	ctags -R src/*.c include/*.h

.PHONY: clean
clean:  
	rm src/*.o
	ls bin/ && rm bin/mef_wave

# DO NOT DELETE
