INCLUDE	=	/home/speedmax/code/apue/include
OBJECT	=	/home/speedmax/code/apue/src/APUE/*.o
TARGET	=	/home/speedmax/code/apue/lib/libapue.a
make:
	gcc -I$(INCLUDE) -Wall -fpic -c apue_log.c apue_err.c
	ar -cr $(TARGET) $(OBJECT)
clean:
	rm -rf *.o
