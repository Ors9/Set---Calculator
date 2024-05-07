#include "set.h"

/**
 * Reset all bits in the set to 0.
 * 
 * @param ptr Pointer to the set to reset.
 */
void reset_bits(setptr *ptr){
    int i;
    for(i = 0 ; i< SIZE_OF_BYTES ; i++){
        /* Check if the pointer is NULL */
        if((ptr) == NULL){
            printf("Null pointer to reset_bit function %d \n",i);
        }
        /* Reset each bit to 0 */
        (*ptr)->bits_array[i] = 0;
    }
    return;
}

/**
 * Read a set of numbers and set the corresponding bits in the bit array.
 * 
 * @param ptr Pointer to the set to modify.
 * @param numbers String containing comma-separated numbers to include in the set.
 */
void read_set(setptr *ptr, char *numbers){
     
    int i = 0; /* Index for bit array */
    char *number = NULL; /* Pointer to the current number (in char) */
    int integer; /* Parsed integer from the string */
    number = strtok(numbers, ",");
    while(number != NULL){
        /* Tokenize the input string and process each number */
        integer = atoi(number); /* Convert string to integer */

        /* Calculate the index in the bit array */
        i = (integer/8);

        /* Set the corresponding bit in the bit array */
        (*ptr)->bits_array[i] |= (1 << (SIZE_OF_BITS-1-(integer - SIZE_OF_BITS*i)));
        
        /* Move to the next number */
        number = strtok(NULL,",");
    }/*End of while*/
    return;
}/*End of read_set function*/

/**
 * Print the elements of the set.
 * 
 * @param ptr Pointer to the set to print.
 */
void print_set(setptr ptr){
    int i,j , the_number = 0 , is_empty = 1;/*Initilize The number the bit represent and Flag to track if the set is empty*/
     /* Iterate through each byte in the bit array */
    for(i = 0 ; i < SIZE_OF_BYTES ; i++){
         /* Iterate through each bit in the current byte */
        for(j = 0 ; j < SIZE_OF_BITS ; j++){
            /* Check if the current bit is set */
            if(ptr->bits_array[i] & (1 << (SIZE_OF_BITS - 1 - j)) ){
                 /* Print the corresponding number */
                printf("%d ",the_number);
                is_empty = 0; /* Mark that the set is not empty */
            }
            
            the_number++;
        }/*End of inner for*/  
     
    }/*End of for*/
    
    /* If the set is empty, print a message */
    if(is_empty == 1){
        printf("The set is empty\n");
    }
    return;
}/*End of print_set function*/

/**
 * Perform the union of two sets and store the result in a third set.
 * 
 * @param set_a Pointer to the first set.
 * @param set_b Pointer to the second set.
 * @param set_c Pointer to the third set to store the result.
 */
void union_set(setptr set_a, setptr set_b , setptr * set_c){
    int i,j;
      /* Allocate memory for a temporary set to store the union result */
    setptr union_copy = calloc(1,sizeof(set)); 
    if(union_copy == NULL){
        printf("Memory Allocation failed at union_set function\n");
        exit(1);
    }
    /* Iterate through each byte in the bit array */
    for(i = 0; i < SIZE_OF_BYTES ; i++){
        /* Iterate through each bit in the current byte */
        for(j = 0 ; j < SIZE_OF_BITS ; j++){
            /* Set the corresponding bit in union_copy */
            union_copy->bits_array[i] |= (set_a->bits_array[i] & (1 << (SIZE_OF_BITS - 1 - j)) ) | (set_b->bits_array[i] & (1 << (SIZE_OF_BITS - 1 - j)));
        }/*End of inner for*/ 

    }/*End of  for*/ 

    /* Reset all bits in set_c to zero before copying */
    reset_bits(set_c);

    /* Copy the result from union_copy to set_c */
    for(i = 0 ; i < SIZE_OF_BYTES ; i++){
        (*set_c)->bits_array[i] = union_copy->bits_array[i];
    }
    free(union_copy); /* Free the dynamically allocated memory */
    return;
}/*End of union_set function*/

/**
 * Perform the intersection of two sets and store the result in a third set.
 * 
 * @param set_a Pointer to the first set.
 * @param set_b Pointer to the second set.
 * @param set_c Pointer to the third set to store the result.
 */
void intersect_set(setptr set_a, setptr set_b , setptr * set_c){
    int i,j;
    /* Allocate memory for a temporary set to store the intersection result */
    setptr intersect_set_copy = calloc(1, sizeof(set));
    if(intersect_set_copy == NULL){
        printf("Memory allocation failed in intersect_set\n ");
        exit(1);
    }
    /* Iterate through each byte in the bit array */
    for(i = 0 ; i< SIZE_OF_BYTES ; i++){
        /* Iterate through each bit in the current byte */
        for(j = 0 ; j < SIZE_OF_BITS ; j++){
             /* Set the corresponding bit in intersect_set_copy */
            intersect_set_copy->bits_array[i] |= (set_a->bits_array[i] & (1 << (SIZE_OF_BITS - 1 - j))) & (set_b->bits_array[i] & (1 << (SIZE_OF_BITS - 1 - j)));
        }
    }/*End of  for*/ 
    /* Reset all bits in set_c to zero before copying */
    reset_bits(set_c);
    /* Copy intersect_set_copy bits to set_c bits */
    for(i = 0 ; i < SIZE_OF_BYTES ; i++){
        (*set_c)->bits_array[i] = intersect_set_copy->bits_array[i];
    }
    free(intersect_set_copy); /* Free the dynamically allocated memory */
    return;
}/*End of intersect_set function*/

/**
 * Perform the set subtraction of two sets and store the result in a third set.
 * 
 * @param set_a Pointer to the first set.
 * @param set_b Pointer to the second set.
 * @param set_c Pointer to the third set to store the result.
 */
void sub_set(setptr set_a, setptr set_b , setptr * set_c){
    int i,j;
    /* Allocate memory for a temporary set to store the subtraction result */
    setptr sub_set_copy = calloc(1, sizeof(set));
    if(sub_set_copy == NULL){
        printf("Memory allocation failed in intersect_set\n ");
        exit(1);
    }
    /* Iterate through each byte in the bit array */
    for(i = 0 ; i < SIZE_OF_BYTES ; i++){
        /* Iterate through each bit in the current byte */
        for(j = 0 ; j< SIZE_OF_BITS ; j++){
            /* Set the corresponding bit in sub_set_copy */
            sub_set_copy->bits_array[i] |= (set_a->bits_array[i] & (1 << (SIZE_OF_BITS - 1 - j))) & ~(set_b->bits_array[i] & (1 << (SIZE_OF_BITS - 1 - j)));
        }
    }/*End of for*/ 
    /* Reset all bits in set_c to zero before copying */
    reset_bits(set_c);
    /* Copy sub_set_copy bits to set_c bits */
    for(i = 0 ; i < SIZE_OF_BYTES ; i++){
        (*set_c)->bits_array[i] = sub_set_copy->bits_array[i];
    }
    free(sub_set_copy);  /* Free the dynamically allocated memory */
    return;
}/*End of sub_set function*/

/**
 * Perform the symmetric difference of two sets and store the result in a third set.
 * 
 * @param set_a Pointer to the first set.
 * @param set_b Pointer to the second set.
 * @param set_c Pointer to the third set to store the result.
 */
void symdiff_set(setptr set_a, setptr set_b , setptr * set_c){
   int i,j;
    /* Allocate memory for a temporary set to store the symmetric difference */
    setptr symdiff_set_copy = calloc(1, sizeof(set));
    if(symdiff_set_copy == NULL){
        printf("Memory allocation failed in intersect_set\n ");
        exit(1);
    }
    /* Iterate through each byte in the bit array */
    for(i = 0 ; i< SIZE_OF_BYTES ; i++){
        /* Iterate through each bit in the current byte */
        for(j = 0 ; j < SIZE_OF_BITS ; j++){
             /* Set the corresponding bit in symdiff_set_copy */
            symdiff_set_copy->bits_array[i] |= ( ( (set_a->bits_array[i]) & (1 << (SIZE_OF_BITS - 1 - j)) ) ^ ( (set_b->bits_array[i]) & (1 << (SIZE_OF_BITS - 1 - j)) ) );
        }
    }
    /* Reset all bits in set_c to zero before copying */
    reset_bits(set_c);
    /* Copy symdiff_set_copy bits to set_c bits */
    for(i = 0 ; i < SIZE_OF_BYTES ; i++){
        (*set_c)->bits_array[i] = symdiff_set_copy->bits_array[i];
    }
    free(symdiff_set_copy); /* Free dynamically allocated memory */
    return;
}/*End of symdiff_set function*/

