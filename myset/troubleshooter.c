#include "set.h"
#include <stdio.h>
#include <string.h>
/*Perform error examine for read_set*/
int troubleshooter_for_read(char *str , int length){
    int i = 0;
    char * temp;
    long number; /*the numbers of the user input*/
    /*Check if the user input is more long than 5  word else missing parameter. */
    if(length < 6){
        printf("Missing parameter\n");
        return ERROR;
    }
    /*Check for illegal comma*/
    if(str[0] == ',' || str[1] == ',' || str[2] == ',' || str[3] == ','){
        printf("Illegal comma.\n");
        return ERROR;
    }
    
    /*If user input of set is wrong*/
    if(str[0] !='S' || str[1] != 'E' || str[2] != 'T' || str[3] < 'A' || str[3] > 'F' ){
        printf("Undefined set name\n");
        return ERROR;
    }
    /*If missing comma.*/
    if(str[4] != ','){
        printf("Missing comma\n");
        return ERROR;
    }
    for(i = 4; i < length - 1 ; i++){
        /*Check if the user insert more than 1 comma each number*/
        if(str[i] == ',' && str[i+1] == ','){
            printf("Multiple consecutive commas\n");
            return ERROR;    
        }
    }
    
    /*Check the errors of  the numerical in the input */
    /*Convert the current char into a long integer*/
    number = strtol( str + 5 , &temp , 10);
    while( *temp != '\0'){
        /*Check if the number out of range [-1-127] and before we took care of -1 case*/
        if( number < -1 || number > 127){
            printf("Invalid set member - value out of range\n");
            return ERROR;
        }  
        /*Check if there text after terminate.*/ 
        if( *temp != '\0' && number == -1){
            printf("Extraneous text after end of command\n");
            return ERROR;
        }
        /*If the character is neither a comma nor null terminator,
         it means the character is not a valid separator and is not
          the end of the string, indicating that the input is not an integer.*/
        if( *temp != ',' && *temp != '\0'){
            printf("Invalid set member - not an integer\n");
            return ERROR;
        }
         
        number = strtol(temp+1,&temp,10);
    }/*End of while*/

    if(number != -1){
        printf("List of set members is not terminated correctly\n");
        return ERROR;
    }
    return PROPER;
}/*End of troubleshooter_for_read*/

/*Perform error examine for print_set*/
int troubleshooter_for_print(char *str, int length){
    /*Check if missing parameter*/
    if(length < MIN_LENGTH_OPERAND){
        printf("Missing parameter\n");
        return ERROR;
    }
    /*Check for illegal comma*/
    if(str[0] == ',' || str[1] == ',' || str[2] == ',' || str[3] == ','){
        printf("Illegal comma\n");
        return ERROR
    }
    /*Check if the input size contain extraneous text*/
    if(length > MIN_LENGTH_OPERAND){
        printf("Extraneous text after end of command\n");
        return ERROR;
    }

    /*Check if the set name is valid*/
    if(str[0] != 'S' || str[1] != 'E' || str[2] != 'T' || str[3] < 'A' || str[3] > 'F'){
        printf("Undefined set name \n");
        return ERROR;
    }
    
return PROPER;
}/*End of troubleshooter_for_print function */

/*Perform error examine for union_set , intersect_set , sub_set and symdiff_set*/
int troubleshooter_for_rest(char *str , int length){
    int i , comma_counter = 0 , set_counter = 0;
    /*Check if missing parameter*/
    if(length < MIN_LENGTH_OPERAND){
        printf("Missing parameter\n");
    }
    /*Check for multiple commas*/
    for(i = 0 ; i < length-1 ; i++){
        if(str[i] == ',' && str[i+1] == ','){
            printf("Multiple consecutive commas\n");
            return ERROR;
        }
    }
    /*Iritate over the user input to handle error cases*/
    for(i = 0; i < length; i++){
        /*Check for illegal comma*/
        if(i == MAX_LENGTH_OPERAND && comma_counter > 2){
            printf("Illegal comma\n");
            return ERROR;
        }
        /*Count the legal sets*/
        if(strncmp(str + i,"SET", 3) == 0){
            /*Check i + 3 < length to avoid out of bound issue*/
            if(i + 3 < length && (str[i+3] >= 'A' || str[i+3] <= 'F') ){
                set_counter++;
            }
        }
        /*Count commas*/
        if(str[i] == ','){
            comma_counter++;
        }
        /*If the input is not comma and not from the except set the set is undefined */
        if( !(str[i] >= 'A' || str[i] <= 'F') && str[i] != 'S' && str[i] != 'E' && str[i] != 'T'){
            if(str[i] != ','){
                printf("Undefined set name\n");
                return ERROR;
            }

        }
    }/*End of for*/
    
    /*Check for extra text*/
    if(length > MAX_LENGTH_OPERAND){
        printf("Extraneous text after end of command\n");
        return ERROR;
    }
    /*Check for missing parameter*/
    if(set_counter != 3){
        printf("Missing parameter\n");
        return ERROR;
    }
    /*Check for missing comma*/
    if(comma_counter < 2){
        printf("Missing comma\n");
        return ERROR;
    }
    
    return PROPER;
}/*End of troubleshooter_for_rest function*/