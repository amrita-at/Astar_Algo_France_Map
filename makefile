# makefile
#
# dynamic version: must include .so directory in LD_LIBRARY_PATH
######################################################################

# makefile for the C project: implementation of A star algorithm
# @AmritaTiwari


OBJ = list.c status.c map.c main.c
project : $(OBJ)
	cc -o project $(OBJ) -lm
list.o : list.c list.h
	cc -c list.c
status.o : status.c status.h
	cc -c status.c
city.o : map.c map.h
	cc -c map.c
main.o : main.c
	cc -c main.c
