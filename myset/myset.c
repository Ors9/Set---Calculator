#include "set.h"


int main() {
      
    set* setptr[SIX_SETS]; /* Pointer array for SETA, SETB, SETC, SETD, SETE, and SETF in this order*/
    int user_stop_command = 0;
    int  realloc_counter = 2, i = 0 ;/* Initialize stop indicator and realloc counter */
    char user_char;
    char *user_input = malloc(REALLOC_FACTOR); /*Pointer to the user input*/
    if(user_input == NULL){
        printf("Memory allocation failed");
        exit(1);
    }
    /* Allocate memory for set array and initialize all bits to 0 in each set */
    for(i = 0 ; i < SIX_SETS ; i++){
        setptr[i] = calloc(1,sizeof(set)); /*Allocate memory for each set pointer in the array*/
        if(setptr[i] == NULL){
            printf("Memory allocation failed for setptr[%d]\n", i);
            exit(1);
        }
        /*Reset all the bits of all the sets SETA,SETB,SETC,SETD,SETE,SETF*/
        reset_bits(&setptr[i]);
        
    }/*End of for*/

    /* Provide user instructions */
    printf("\nThis program performs operations on 6 sets, SETA through SETF.\n");
    printf("The available operations are:\n\n");
    printf("1. read_set\n");
    printf("2. print_set\n");
    printf("3. union_set\n");
    printf("4. sub_set\n");
    printf("5. intersect_set\n");
    printf("6. symdiff_set\n\n");
    printf("Enter the 'stop' command to end the program.\n");

    /*Read user input */
    while(user_stop_command != -1){
        printf("\nPlease enter a command:\n");
        i = 0;
        while( (user_char = getchar())!= '\n'){
            printf("%c",user_char);
            if(user_char == EOF){ /*End of user input */
                printf("\nProgram stopped due to EOF\n");
                exit(1);
            }
            if( !isspace(user_char) && user_char != '\t'){ /*Filter tab and spaces*/
                user_input[i] = user_char;
                i++; 
            } 
            if(i % REALLOC_FACTOR == 0){ /* Check if memory needs to be reallocated */
                user_input = realloc(user_input,REALLOC_FACTOR*realloc_counter);/* If so, double the size of the buffer by the counter*/
            }
            /*Check if memory reallocation failed*/
            if(user_input == NULL){
                printf("Memory Allocation failled");
                exit(1);
            }
            realloc_counter++;
            
        }/*End of inner while*/
    user_input[i] = '\0';
    printf("\n");
    /* Process user commands */
    /*Compare if use inser stop command*/
    if(strncmp(user_input,"stop",4) == 0){
        /*Check if user didnt inser extra input*/
        if(strlen(user_input) == 4){
            user_stop_command = -1;
        }
        else {
            printf("Extraneous text after end of command\n"); 
            user_stop_command = -1;
        }
    }
    /*Compare if user input read_set */
    else if(strncmp(user_input,"read_set",8) == 0){
            /*Send the input to check and skip on the unneccecery input "read_set"*/
            if((troubleshooter_for_read(user_input + 8,strlen(user_input + 8)) == 1)){
                read_set(&setptr[(user_input[11]-65)],&user_input[12]);  
            }
    }
    /*Compare if user input read_set */
    else if(strncmp(user_input,"print_set",9) == 0){
        /*Check if the input valid in print_set part*/
        if(troubleshooter_for_print(user_input + 9, strlen(user_input + 9)) == 1){
            print_set(setptr[user_input[12]-65]);
        }
    }/*Compare if user input union_set */
    else if(strncmp(user_input,"union_set",9) == 0){
        /*Check if the input valid in union_set part*/
        if(troubleshooter_for_rest(user_input + 9,strlen(user_input + 9)) == 1){
            union_set(setptr[user_input[12]-65],setptr[user_input[17]-65],&setptr[user_input[22]-65]);
        }
    }/*Compare if user input intersect_set */
    else if(strncmp(user_input,"intersect_set",13) == 0){
        /*Check if the input valid in intersect_set part*/
        if(troubleshooter_for_rest(user_input + 13, strlen(user_input + 13)) == 1){
            intersect_set(setptr[user_input[16]-65],setptr[user_input[21]-65],&setptr[user_input[26]-65]);
        }
    }/*Compare if user input sub_set */
    else if(strncmp(user_input,"sub_set",7) == 0){
        /*Check if the input valid in sub_set part*/
        if(troubleshooter_for_rest(user_input + 7, strlen(user_input + 7)) == 1){
            sub_set(setptr[user_input[10]-65],setptr[user_input[15]-65],&setptr[user_input[20]-65]);
        }
    }/*Compare if user input symdiff_set */
    else if(strncmp(user_input,"symdiff_set",11) == 0){
        /*Check if the input valid in symdiff_set part*/
        if(troubleshooter_for_rest(user_input + 11 , strlen(user_input + 11)) == 1){
            symdiff_set(setptr[user_input[14]-65], setptr[user_input[19]-65], &setptr[user_input[24]-65]);
        }
    } 
    else{/*Unvalid command name*/
        printf("Undefined command name\n");
    }

    }/*End of while*/

     /* Free memory before exiting */
    free(user_input);
    for(i = 0 ; i < SIX_SETS; i++){
        free(setptr[i]);
    }

    return 0;
}/*End of main*/
