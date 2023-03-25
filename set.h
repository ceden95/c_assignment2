
typedef struct set set;	/* declaration of the struct set */

/*
 * Function: read_set
 * ----------------------------
 *   defines the values of the set from an array of numbers 
 *   in range of 0-127.
 *   if the set had previous data- it will be override by read_set.
 *
 *   setx: poiter of the set to insest the numbers in. 
 *   num: pointer to the array of the numbers to insert.
 *
 */
void read_set (set *setx, int *num);

/*
 * Function: print_set
 * ----------------------------
 *   print the numbers the set contains in ascending order.
 *   prints 16 numbers in a line.
 *
 *   setx: pointer to the set to print.
 *   
 */
void print_set (set *setx);

/*
 * Function: union_set
 * ----------------------------
 *   unit two sets into one and stores the data (the numbers which in the
 *   first OR the second set) on the 3rd set. 
 *   if the 3rd set has data, union_set will override the previous data
 *   and will store the new data.
 *
 *   set1: pointer to first set
 *   set2: pointer to second set
 *   set3: pointer to the third set in which the union results will be entered
 *
 */
void union_set (set *set1, set *set2, set *set3);

/*
 * Function: intersect_set
 * ----------------------------
 *   intersect two sets into one and stores the data (the numbers which in the
 *   first AND the second set) on the 3rd set. 
 *   if the 3rd set has data, intersect_set will override the previous data
 *   and will store the new data .
 *   
 *   set1: pointer to first set
 *   set2: pointer to second set
 *   set3: pointer to the third set in which the intersect results will be
 *   entered
 *
 */
void intersect_set (set *set1, set *set2, set *set3);

/*
 * Function: sub_set
 * ----------------------------
 *   subtract set2 from set1 stores the data (the numbers which are 
 *   in the first set AND NOT on the second set) on the 3rd set. 
 *   if the 3rd set has data, sub_set will override the previous data
 *   and will store the new data .
 *
 *   set1: pointer to first set
 *   set2: pointer to second set
 *   set3: pointer to the third set in which the subtract results will be
 *   entered
 *
 */
void sub_set (set *set1, set *set2, set *set3);


/*
 * Function: symdiff_set
 * ----------------------------
 *   make symmetric difference from set1 and set2 and stores the data (the 
 *   numbers which are in the first OR the second set, BUT NOT on both) on the
 *   3rd set.
 *   if the 3rd set has data, symdiff_set will override the previous data
 *   and will store the new data .
 *
 *   set1: pointer to first set
 *   set2: pointer to second set
 *   set3: pointer to the third set in which the symmetric difference results
 *   will be entered.
 *
 */
void symdiff_set (set *set1, set *set2, set *set3);

/*
 * Function: stop
 * ----------------------------
 *   terminate the program. stop the main loop.
 *
 */
void stop ();


/*private funcs*/


/*
 * Function: bit_is_1
 * ----------------------------
 *   check if number index is in the set.
 *   return 1 if the answer is yes.
 *   
 *
 *   setx: pointer to set to check
 *   index: the index of the bit in the set.
 *
 *   returns: 1 if the number exists in the set, 0 if not.
 */
int bit_is_1 (set *setx, int index);

/*
 * Function: set_bit
 * ----------------------------
 *   insert a number fron 0-127 into the set.
 *   
 *
 *   setx: pointer to the set to insest the numbers in. 
 *   index: = the number to insert
 *
 */
void set_bit (set *setx, int index);

/*
 * Function: temp_set
 * ----------------------------
 *   create a dynamic memory allocation of for a new set
 *
 *   returns: an adress of a set initialized to zero
 */
set* create ();



