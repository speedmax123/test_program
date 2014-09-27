INCLUDE	=	/home/speedmax/code/test_program/include
LIB	=		/home/speedmax/code/test_program/lib/libapue.a
LD =		-lpthread
make:
	clang -I$(INCLUDE) -Wall pthread_attr_test.c $(LIB) $(LD) -o pthread_attr_test.out
	clang -I$(INCLUDE) -Wall pthread_fork.c $(LIB) $(LD) -o pthread_fork.out
	clang -I$(INCLUDE) -Wall pthread_signal_syc.c $(LIB) $(LD) -o pthread_signal_syc.out
	#clang -I$(INCLUDE) -Wall pthread_mutex_rescure.c pthread_utils.c $(LIB) $(LD) -o pthread_mutex_rescure.out
clean:
	rm -rf *.out
