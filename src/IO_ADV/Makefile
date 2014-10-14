INCLUDE	=	/home/speedmax/code/apue/test_program/include
LIB	=		/home/speedmax/code/apue/test_program/lib/libapue.a
LD =		-lpthread
make:
	clang -I$(INCLUDE) -Wall long_no_block_io.c $(LIB) $(LD) -o long_no_block_io.out
clean:
	rm -rf *.out
