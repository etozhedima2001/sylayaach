CC = gcc
CFLAGS = -Wall -Werror -Wextra
SRC = src/cipher.c src/logger.c
TARGET = build/logging_cipher

all: logging_cipher

logging_cipher: $(SRC)
	gcc -o ../build/logging_cipher *.o 

logger:
	gcc -c logger.c
	gcc -c cipher.c

cipher:
	gcc -o ../build/cipher cipher.c

clean:
	rm ../build/*
