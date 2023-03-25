#include <stdio.h>
#include <string.h>
#include <ctype.h> /*check if nesecery*/
#include <stdlib.h>
#include "set.h"

#define SIZE_OF_BYTE 8
#define NUM_OF_BYTES 16
#define NUM_OF_BITS 128
#define END_OF_LINE 16

/*a structure of a set, include 16 bytes of chars (16 * char(8) = 128 bits).*/
struct set{ 
	char bit_array[NUM_OF_BYTES];
};

/* 1.place numbers from array num into set */
void read_set(set *setx, int *num){  
    
    int i;
    memset(setx, 0, NUM_OF_BYTES);
    
	for (i=0; *num!=-1; i++)
	{
		set_bit(setx, *num);
		++num;
	}
}
 
/* 2.print set */
void print_set(set *setx){
    
    int is_empty = 1;
    int i, counter=0;
    
    for (i=0; i<NUM_OF_BITS; i++){
        if (bit_is_1(setx, i)){
            
            is_empty = 0; /*set is not empty*/
            ++counter; /*indication for end of line*/
            printf("%d ", i);
            if (counter%END_OF_LINE == 0){ /*if 16 numbers printed- <ENTERT>*/
                printf("\n");
            }
        }
    }
    if (!is_empty){
        printf("\n");
    }
    if (is_empty){
        printf("this set is empty\n");
    }
}

/* 3.unit 2 sets to set 3 */
void union_set(set *set1, set *set2, set *set3){
    
    int i;
    set *tempset;
    tempset = create(); /*pointer to pemporary set*/
    
    for (i=0; i<NUM_OF_BITS; i++){ /*insert data from set1&set2 into tempset*/
        if (bit_is_1(set1, i) || bit_is_1(set2, i)){
            set_bit(tempset, i);
        }
    }
    memcpy(set3, tempset, NUM_OF_BYTES); /*copy the data from tempset to set3*/
    free(tempset);
}

/* 4.&& of two sets to set 3 */
void intersect_set(set *set1, set *set2, set *set3){
 
    int i;
    set *tempset;
    tempset = create();
    
    for (i=0; i<NUM_OF_BITS; i++){
        if (bit_is_1(set1, i) && bit_is_1(set2, i)){
            set_bit(tempset, i);
        }
    }
    memcpy(set3, tempset, NUM_OF_BYTES);
    free(tempset);
}

/* 5.set1-set2=set3 */
void sub_set(set *set1, set *set2, set *set3){
    
    int i;
    set *tempset;
    tempset = create();
    
    for (i=0; i<NUM_OF_BITS; i++){
        
        if (bit_is_1(set1, i) && !(bit_is_1(set2, i))){
            set_bit(tempset, i);
        }
    }
    memcpy(set3, tempset, NUM_OF_BYTES);
    free(tempset);
}

/* 6.set3 has numbers which appears in only one of the sets(set1,set2) */
void symdiff_set(set *set1, set *set2, set *set3){
 
    int i;
    set *tempset;
    tempset = create();
    
    for (i=0; i<NUM_OF_BITS; i++){
        
        if (bit_is_1(set1, i) ^ bit_is_1(set2, i)){
            set_bit(tempset, i);
        }
    }
    memcpy(set3, tempset, NUM_OF_BYTES);
    free(tempset);
}

/* terminate program */
void stop(){
    exit(0);
}


/* return 1 if the bit of index is on, else-0 */
int bit_is_1(set *setx, int index){
    
    if (setx->bit_array[index/SIZE_OF_BYTE] & (1<<index%SIZE_OF_BYTE)){
        return 1;
    }
    return 0;
}

/* set 1 on the bit of the index */
void set_bit(set *setx, int index){
    
    setx->bit_array[index/SIZE_OF_BYTE] = setx->bit_array[index/SIZE_OF_BYTE] | (1<<index%SIZE_OF_BYTE);
}


/* return an adress of a set initialized to zero */
set* create(){
    
    set *set_poiner = (set*)calloc(NUM_OF_BYTES, SIZE_OF_BYTE);
    if (set_poiner == NULL){
		return (NULL);
    }
	return (set_poiner);
}


