#!/bin/bash

build:
	gcc -Wall -std=c99 main.c cerinta1.c cerinta2.c bonus.c -o minimax
run:
	./minimax
clean:
	rm minimax
