INCLUDE	=	/home/speedmax/code/test_program/include
LIB	=		/home/speedmax/code/test_program/lib/libapue.a
LD = 		-lpthread
make:
	clang -I$(INCLUDE) -Wall pthread_test.c $(LIB) $(LD) -o pthread_test.out
	clang -I$(INCLUDE) -Wall pthread_sth.c $(LIB) $(LD) -o pthread_sth.out
	clang -I$(INCLUDE) -Wall pthread_mem.c $(LIB) $(LD) -o pthread_mem.out
	clang -I$(INCLUDE) -Wall pthread_clean.c $(LIB) $(LD) -o pthread_clean.out
clean:
	rm -rf *.out
