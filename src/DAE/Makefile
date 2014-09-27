INCLUDE	=	/home/speedmax/code/test_program/include
LIB	=		/home/speedmax/code/test_program/lib/libapue.a
LD = 		-lpthread
make:
	clang -I$(INCLUDE) -Wall daemon_marco.c $(LIB) $(LD) -o daemon_marco.out
clean:
	rm -rf *.out
