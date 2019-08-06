#pragma once

#include "q4.h"


//=======define===============define===============define===============define===============define===============define===============define===

#define LSB_MASK 1			//00000000 00000000 00000000 00000001 no type- int is the default
#define TYPED_LSB_MASK(TYPE) ((TYPE)1)		//tell the type= char1 00000001
#define LSB8_MASK(TYPE) ((TYPE)0xFF)		//8 right bits are 1
#define ALL_1_MASK(TYPE) (~(TYPE)(0))		//all bit non zero- all 1
#define BIT_I_SET(I, TYPE) ((TYPE)(1)<<(I));	//set 1 at the i place
#define BIT_I_CLEAR(I, TYPE) (~((TYPE)(1)<<(I)));	//clear to 0 at the i place
#define MSB_SET(TYPE) ((TYPE)(1)<<(sizeof(TYPE)*8 -1))	//set 1 at the left place
//create a mask with i bit on and "OR |" between two
#define SET_BIT(NUM, I, TYPE) NUM |= BIT_I_SET(I,TYPE)	//set the i bit to 1 in a variable
//create a mask with i bit off and all the rest on and "AND &" between two
#define CLEAR_BIT(NUM, I, TYPE) NUM &= BIT_I_CLEAR(I,TYPE)	//set the i bit to 0 in a variable
//move the i bit i times to the right-to be at the lsb and "AND &" with the num 1-only lsb set
#define IS_BIT_I_SET(I, NUM) ((NUM>>I) & 1)
//set bits at odd positions- 4 byts types
#define LONG_ODD_POS_BITS_MASK 0xAAAAAAAA		//if the size isnt 4- there is a function
//set on the n LSB
//option 1- create LSB mask, move the set LSB N times left and minus 1 will set on all the N LSB
#define MASK_WITH_N_LSBS_SET1(TYPE, N) ((TYPED_LSB_MASK(TYPE)<<N)-1)
//option 2- create all set mask, move it to the left all the bits of the type minus N wanted on
#define MASK_WITH_N_LSBS_SET2(TYPE, N) ((ALL_1_MASK(TYPE))>>((sizeof(TYPE))*8 -N))	//type must be unsigned
//set "from-to" bits. set to-from+1 amount of LSB bits and move the "from size" to the left
#define MASK_WITH_RANGE_BITS_SET(TYPE, FROM, TO) ((MASK_WITH_N_LSBS_SET1(TYPE, TO-FROM+1))<<FROM)


//=======define===============define===============define===============define===============define===============define===============define===


//************prototype************************prototype************************prototype************************prototype**********************

void StoreBoard(Board board, char *filename); //q5

//************prototype************************prototype************************prototype************************prototype**********************


