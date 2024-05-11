#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE_OF_BYTES 16 /*Size of the bits_array*/
#define SIZE_OF_BITS 8 /*Represent size of bit*/
#define SIX_SETS 6  /*Represent all the sets*/
#define REALLOC_FACTOR 5 /* Realloc factor for input string. */
#define ERROR -1; /*Error and success constants for troubleshooter*/
#define PROPER 1;
#define MIN_LENGTH_OPERAND 4
#define MAX_LENGTH_OPERAND 14

/*Define a struct 'set' representing a group of bits.*/
typedef struct set{
    char bits_array[SIZE_OF_BYTES]; /* Represents 128 bits (8 bits * 16 bytes)*/
}set;

/*Create pointer for set*/
typedef set* setptr;

/* Helper function declaration to reset all bits in the set to zero. */
void reset_bits(setptr *);


/* Function declarations for the avaliable operations */
/* Read a set of numbers and set the corresponding bits in the bit array. */
void read_set(setptr * , char *);
/* Print the elements of the set. */
void print_set(setptr);
/* Perform the union of two sets and store the result in a third set. */
void union_set(setptr , setptr , setptr *);
/* Perform the intersection of two sets and store the result in a third set. */
void intersect_set(setptr , setptr , setptr *);
/* Perform the set subtraction of two sets and store the result in a third set. */
void sub_set(setptr , setptr , setptr *);
/* Perform the symmetric difference of two sets and store the result in a third set. */
void symdiff_set(setptr , setptr , setptr *);


/* Function declarations for the troubleshooter */
/*Perform error examine for read_set*/
int troubleshooter_for_read(char * , int );
/*Perform error examine for print_set*/
int troubleshooter_for_print(char *, int );
/*Perform error examine for union_set , intersect_set , sub_set and symdiff_set*/
int troubleshooter_for_rest(char * , int );

