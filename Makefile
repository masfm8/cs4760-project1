CC = gcc
CFLAGS = -Wall

all: oss user

oss: oss.c
	$(CC) $(CFLAGS) oss.c -o oss

user: user.c
	$(CC) $(CFLAGS) user.c -o user

clean:
	rm -f oss user
