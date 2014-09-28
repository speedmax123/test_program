INCLUDE	=	/home/speedmax/code/test_program/include
LIB	=		/home/speedmax/code/test_program/lib/libapue.a
LD =		-lpthread
make:
	clang -I$(INCLUDE) -Wall daemon_marco.c $(LIB) $(LD) -o daemon_marco.out
	clang -I$(INCLUDE) -Wall daemon_test_model.c $(LIB) $(LD) -o daemon_test_model.out
clean:
	rm -rf *.out
