CC = gcc -DENGLISH
OPTS = -c -O4
STDH = gendef.h
OBJS = genreg.o main.o optmid.o

genreg : $(OBJS)
	  cc -o $@ $(OBJS) $(LIBS)

genreg.o : genreg.c $(STDH)
	    $(CC) $(OPTS) genreg.c

main.o : main.c $(STDH)
	  $(CC) $(OPTS) main.c

optmid.o : optmid.c $(STDH)
	    $(CC) $(OPTS) optmid.c

manual : manual.eng.tex
	latex manual.eng.tex
	latex manual.eng.tex

tarfile :
	mkdir GENREG
	cp genreg.c main.c optmid.c readscd.c manual.eng.tex \
	   gendef.h README makefile GENREG
	tar cvf genreg.tar GENREG
	gzip genreg.tar
	rm -r GENREG
