OBJS = tokenizer.o history.o uimain.o

CFLAGS = -g -O3 

all: tokenizer

tokenizer: $(OBJS) 
	gcc $(CFLAGS) -o tokenizer $(OBJS)

tokenizer.o: tokenizer.c tokenizer.h
	gcc $(CFLAGS) -c tokenizer.c -o tokenizer.o

history.o: history.c history.h
	gcc $(CFLAGS) -c history.c -o history.o

uimain.o: uimain.c tokenizer.h history.h
	gcc $(CFLAGS) -c uimain.c -o uimain.o

clean:
	rm -f *.o tokenizer

run:tokenizer
	./tokenizer

