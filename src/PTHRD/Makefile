INCLUDE	=	/home/speedmax/code/test_program/include
LIB	=		/home/speedmax/code/test_program/lib/libapue.a
LD = 		-lpthread
make:
	clang -I$(INCLUDE) -Wall pthread_test.c $(LIB) $(LD) -o pthread_test
	clang -I$(INCLUDE) -Wall pthread_sth.c $(LIB) $(LD) -o pthread_sth
clean:
	rm -rf *.out
