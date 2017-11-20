CC=gcc
CFLAGS=-W -Wall -g
LDFLAGS=
EXEC=CBot_com

all: $(EXEC)

$(EXEC): main.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
