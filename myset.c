#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "set.h"

#define MAX_SET_SIZE 128
#define MAX_ARR_SIZE 128
#define NUM_OF_SETS 6
#define NUM_OF_COMMENDS 7
#define MAX_INPUT_LEN 512/*assuming input is limited as maman12*/
#define SET_NAME_LEN 4
#define BASE 10 

/* array of all 6 valid command names */
static char *commands[]={"read_set","print_set", "union_set", "intersect_set","sub_set","symdiff_set","stop"};

/* array of all 6 valid set names */
static char *sets_names[]={"SETA","SETB","SETC","SETD","SETE","SETF"};

/* prototype declerations */
int command_line_is_valid(char *commend_line);
int command_name_is_valid(char *commend_name);
int set_name_is_valid(char *set_name);
int num_is_valid(char *num_str);
 

int main()
{
    set* sets_array[NUM_OF_SETS]; /*array of pointers to all sets*/
    char commend_line[MAX_INPUT_LEN] = {'\0'}; /* input from user */
    char *commend_line_ptr; /*poiter to commend_line string*/
    int num_array[MAX_ARR_SIZE] = {0};/*arrey to store the numbers from user into sets*/
    set *set1, *set2, *set3;
    int commend, numberOfSet;
    int i;
    
    

    printf("\nWELCOME TO SET OPERATION PROGRAM !\n\n");
    printf("This program make some operations on sets of numbers by your choise,\n");
    printf("such as union, intersection, subtraction ect.\n");
    printf("Here are some guidelines for understanding the usage of the program:\n\n");
    printf("# The operations you can make on sets are: read_set, print_set,\n");
    printf("union_set, intersect_set, sub_set, symdiff_set ,stop.\n\n");
    printf("# The sets names you can make some operations on are: SETA, SETB,\n");
    printf("SETC, SETD, SETE, SETF.\n\n");
    printf("# The valid range of numbers is 0-127.\n\n");
    printf("# To perform read_set, type:\n");
    printf("read_set <SETNAME>,<number>,...,<number>,-1\n");
	printf("For example: read_set SETA, 23, 1, 89, 45, -1\n\n");
	printf("# To perform print_set, type:\n");
	printf("print_set <SETNAME>\n");
	printf("For example: print_set SETA\n\n");
	printf("# To perform union_set/intersect_set/sub_set/syndiff_set, type:\n");
	printf("<operation> <SETNAME1>,<SETNAME2>,<SETNAME3>\n");
	printf("For example: union_set SETA, SETB, SETF\n\n");
	printf("#To exit the program, all you have to do is type stop\n");

    
    /*creating sets*/
    for (i=0; i<NUM_OF_SETS; i++){
        sets_array[i] = create();
        if (sets_array[i] == NULL){
            printf("sorry, memory has not been allocated.\n");
			exit(1);
        }
    }
    
    
	printf("\nlets start! write your first commend here: ");
	
	/*continue untill NULL or 'stop'*/
    while (fgets(commend_line, MAX_INPUT_LEN, stdin)) {
        
        commend_line_ptr = commend_line; /*pointer to string commend_line*/
        
        if (*commend_line_ptr == '\n'){
            continue;
        }
	    
        printf("\ninput is: %s\n" , commend_line);
        
        /*input validity*/
        if (command_line_is_valid(commend_line_ptr) == 0){
            printf("\nlets try again! type in a command:.. ");
            printf("\n.. but currect one this time (; : ");
            continue;
        }
        
        /*the commend*/
        while (isspace(*commend_line_ptr)){
            ++commend_line_ptr;
        }
        
        commend_line_ptr = strtok(commend_line, " \t\n"); /* holds the first word- commend*/
        commend = command_name_is_valid(commend_line_ptr);/* number of the commend in the commands array */
        if (commend==6){/*Execute program*/
            printf("i guess thats it, see you next time!\n\n");
            stop();
        }
        
        
        /*first set*/
        while (isspace(*commend_line_ptr)){
            ++commend_line_ptr;
        }
        commend_line_ptr = strtok(NULL, " \t\n,");
        numberOfSet = set_name_is_valid(commend_line_ptr);
        set1 = sets_array[numberOfSet];/*pointer to first set*/
        
        
        /* read_set */
        if (commend==0){
            
            commend_line_ptr = strtok(NULL, "");
            i=0;
            while (*commend_line_ptr != '\0'){
                while (isspace(*commend_line_ptr) || *commend_line_ptr==','){
                    ++commend_line_ptr;
                }
                num_array[i] = strtol(commend_line_ptr, &commend_line_ptr, BASE);
                i++;
            }
            read_set(set1, num_array);
        }
        
        /* print_set */
        if (commend==1){
            printf("\n%s: ",sets_names[numberOfSet] );
			print_set(set1);
        }
        
        /* for union_set, intersect_set, sub_set, symdiff_set */
        if (commend==2 || commend==3 || commend==4 || commend==5){
            
            /*set2*/
            commend_line_ptr = strtok(NULL, "");
            while (isspace(*commend_line_ptr) || *commend_line_ptr==','){
                ++commend_line_ptr;
            }
            numberOfSet = set_name_is_valid(commend_line_ptr);
            set2 = sets_array[numberOfSet];
            
            /*set3*/
            commend_line_ptr += SET_NAME_LEN;
            while (isspace(*commend_line_ptr) || *commend_line_ptr==','){
                ++commend_line_ptr;
            }
            numberOfSet = set_name_is_valid(commend_line_ptr);
            set3 = sets_array[numberOfSet];
            
            /* union_set */
            if(commend==2){
                union_set(set1, set2, set3);
            }
            /* intersect_set */
            if(commend==3){
                intersect_set(set1, set2, set3);
            }
            /* sub_set */
            if(commend==4){
                sub_set(set1, set2, set3);
            }
            /* symdiff_set */
            if(commend==5){
                symdiff_set(set1, set2, set3);
            }
        }
        printf("\nDone! type in the next command: "); 
    }
    
    /*if the loop stoped becouse of null and not stop:*/
    if (strcmp(commend_line,  "stop" ) != 0) {
        printf("\n\n\nNO STOP COMMEND IN YOUR FILE, follow the rules. see you next time.\n");
        printf("when you'll kmow how to play :P\n");

        exit(1);
    } 

  return 0;

}

/* Function: command_name_is_valid
 * ----------------------------
 *validate commend name
 *
 *commend_name: pointer to commend name
 *
 *return: -1 if commend name is not valid, 
 *number of commend in commands array if valid
 */
int command_name_is_valid(char *commend_name){
    
    int i;
    for (i=0; i<NUM_OF_COMMENDS; i++){
        if (memcmp(commands[i], commend_name, strlen(commands[i])) == 0){
            return (i);
        }
    }
    return (-1);
}   

/* Function: set_name_is_valid
 * ----------------------------
 *validate set name
 *
 *set_name: pointer to set name
 *
 *return: -1 if set name is not valid, 
 *number of set in sets array if valid
 */
int set_name_is_valid(char *set_name){
    
    int i;
    for (i=0; i<NUM_OF_SETS; i++){
        if(memcmp(set_name, sets_names[i], SET_NAME_LEN) == 0){
            return (i);
        }
    }
    return (-1);
} 

/* Function: num_is_valid
 * ----------------------------
 *validate if a number in string is an integer
 *
 *num_str: pointer to a number in a string
 *
 *return: 0 if its not an integer or if the int is <127 or 0<
 *        1 if the number is valid and <=0 or <=9
 *        2 if the number is valid and <=10 or <=99
 *        3 if the number is valid and <=1000 or <=127
 *       -1 if number is -1
 */
int num_is_valid(char *num_str){
    
    long num;
    char *p;
    
    num = strtol(num_str, &p, BASE);
    
    if (*p == '.'){
        printf("Invalid set member - not an integer\n");
        return 0;
    }
    
    if (num == -1){
        return -1;
    }
    
    if (num == 0){
        
        if (*num_str == '0'){
            return 1;
        }
        else{
            printf("Invalid set member - not an integer\n");
        }
        
    }
    if (1 <= num && num <=9){
        return 1;
    }
    if (10 <= num && num <=99){
        return 2;
    }
    if (100 <= num && num <=127){
        return 3;
    }
    
    if (num < -1 || 127 < num){
		printf("Invalid set member - value out of range\n");
    }
    return 0;
    
}

/* Function: command_line_is_valid
 * ----------------------------
 *validate the input from user
 *
 *num_str: pointer to a string
 *
 *return: 0 if not valid
 *        1 if valid
 */
int command_line_is_valid(char *commend_line){
   
    int commend, num;
    int val_case = 1;
   
    while (*commend_line != '\0' && *commend_line != EOF && *commend_line != '\n'){

        while (isspace(*commend_line)){
            ++commend_line;
        }
       
        switch(val_case){
           
            case 1:/* COMMEND */
               
                commend = command_name_is_valid(commend_line);
               
                /*if commenend is stop*/
                if (commend == 6){/*if correct*/
                   
                    commend_line += strlen(commands[6])+1;/*move 4 chars ahead*/
                   
                    while (isspace(*commend_line)){
                        ++commend_line;
                    }
                    
                    if (*commend_line != '\0'){
                        printf("EXtraneous text after end of commend\n");
                        return 0;
                    }
                    
                    return 1;
                }
               
                /*commenend name is not valid*/
                if (commend == -1){
                    printf("Undefined commend name\n");
                    return 0;
                }
               
                /*commend line is correct*/
                commend_line += strlen(commands[commend]);
                
                while (isspace(*commend_line)){
                    ++commend_line;
                }
		        
                if (*commend_line == '\0'){/*check to down \n*/
                    printf("Missing parameters\n");
                    return 0;
                }
                
                val_case = 2;
                break;
                
               
            case 2:/* SET1 */
                
                if (*commend_line == ','){/*if ',' after commend*/
                    printf("Illegal comma\n");
                    return 0;
                }
               
                else if (set_name_is_valid(commend_line) == -1){/*SETNAME is not valid*/
                    printf("Undefined set name\n");
                    return 0;
                }
               
                else{/*set name is valid*/
                    
                    commend_line += SET_NAME_LEN;
                    
                    while (isspace(*commend_line)){
                        ++commend_line;
                    }
                    
                    /*print_set */
                    if (commend == 1){
                       
                        if (*commend_line != '\0'){
                            printf("EXtraneous text after end of commend\n");
                            return 0;
                        }
                        return 1;
                    }
                    
                    if(*commend_line == '\0'){
                        
                        if (commend == 0){
                            printf("Missing numbers\n");
                        }
                        
                        else{
                            printf("Missing parameters\n");
                        }
                        return 0;
                    }
                    
                    /*for all other funcs*/
                    else {
                        val_case = 3; 
                    }
                   
                }
                
                break;
                
            case 3: /* COMMA AFTER SET1 */
               
                if (*commend_line != ','){
                    printf("Missing comma\n");
                    return 0;
                }
                
                else{
                    
                    if (commend == 0){ /* for read_set */
                        val_case = 4;
                    }
                    
                    else{ /* for union, intersect, sub, symdiff */
                        val_case = 5;
                    }
                    
                    ++commend_line;
                }
                
                while (isspace(*commend_line)){
                    ++commend_line;
                }
                if(*commend_line == '\0'){
                    
                    if (commend == 0){
                        printf("Missing numbers\n");
                    }
                    
                    else{
                        printf("Missing parameters\n");
                    }
                    return 0;
                }
                
                
                if (*commend_line == ','){
                    printf("Multiple consecutive commas\n");
                    return 0;
                }
                
                break;

            case 4: /* NUMBERS */
                 
                if (strstr(commend_line, "-1") == NULL){
                    printf("List of set members is not terminated correctly\n");
                    return 0;
                }
                
                if(*commend_line == '\0'){
                    printf("Missing numbers\n");
                    return 0;
                }
                
                num = num_is_valid(commend_line);
                /* 0 not in reange or not an int
                1<= ok
                -1 end*/
                
                if (num == -1){ /* check if its last in line */
                    
                    commend_line += 2;
                    
                    while (isspace(*commend_line)){
                        ++commend_line;
                    }
                    
                    if(*commend_line != '\0'){
                        printf("EXtraneous text after end of commend.\n");
                        return 0;
                    }
                    
                    else{
                        return 1;
                    }
                }
                
                if (num == 0){/*number is not valid*/
                    return 0;
                }
                
                if (1 <= num){/*number is valid*/
                    
                    commend_line += num;
                    val_case = 3;
                }

                break;
                
            case 5: /* SET2 */
                
                if (set_name_is_valid(commend_line) == -1){/*SETNAME is not valid*/
                    printf("Undefined set name\n");
                    return 0;
                }
               
                else{/*set name is valid*/
                    
                    commend_line += SET_NAME_LEN;
                    
                    while (isspace(*commend_line)){
                        ++commend_line;
                    }
                    
                    if(*commend_line == '\0'){
                        printf("Missing parameters\n");
                        return 0;
                    }
                }    
                    
                val_case = 6; 

                break;
                
            case 6: /*COMMA AFTER SET2*/
                
                if (*commend_line != ','){
                    printf("Missing comma\n");
                    return 0;
                }
                
                else if(*commend_line == '\0'){
                    printf("Missing parameters\n");
                    return 0;
                }
                
                else{
                    
                    val_case = 7;
                    
                    if (*(commend_line+1) == '\0' || *(commend_line+1) == '\n'){
                        printf("Missing parameters\n");
                        return 0;
                    }
                    ++commend_line;
                }
                
                break;
                
            case 7: /* SET3 */
                
                if (*commend_line == ','){
                    printf("Multiple consecutive commas\n");
                    return 0;
                }
                
                if(*commend_line == '\0'){
                    printf("Missing parameters\n");
                    return 0;
                }
                
                else if (set_name_is_valid(commend_line) == -1){/*SETNAME is not valid*/
                    printf("Undefined set name\n");
                    return 0;
                }
                
               
                else{/*set name is valid*/
                    
                    commend_line += SET_NAME_LEN;
                    
                    while (isspace(*commend_line)){
                        ++commend_line;
                    }
                    
                    if(*commend_line != '\0'){
                        printf("Extraneous text after end of commend\n");
                        return 0;
                    }
                }

                break;   
        }
    }
    return 1;
}

