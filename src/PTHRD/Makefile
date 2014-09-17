INCLUDE	=	/home/speedmax/code/apue/test_program/include
LIB	=	/home/speedmax/code/apue/test_program/lib/libapue.a
LD = -lpthread
make:
	clang -I$(INCLUDE) -Wall pthread_test.c $(LIB) $(LD) -o pthread_test
clean:
	rm -rf *.out
