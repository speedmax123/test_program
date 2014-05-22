INCLUDE	=	/home/speedmax/apue/code/test_program/include
OBJECT	=	/home/speedmax/apue/code/test_program/src/APUE/*.o
TARGET	=	/home/speedmax/apue/code/test_program/lib/libapue.a
make:
	gcc -I$(INCLUDE) -Wall -fpic -c apue_log.c apue_err.c
	ar -cr $(TARGET) $(OBJECT)
clean:
	rm -rf *.o

