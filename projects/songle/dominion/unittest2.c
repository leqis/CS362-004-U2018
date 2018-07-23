/*******************************
**Unittest2.c: isGameOver()
*******************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

/************************************************************
**void compareNum
**Compare the values of 2 numbers, 
**will be used for cards/treasure/coin counts during testing
************************************************************/
void compareNum(int a, int b){
	if(a == b)
		printf("PASSED\n");
	else
		printf("FAILED\n");
}


int main(){
	//int newCards = 0;
    //int discarded = 1;
    //int xtraCoins = 0;
    //int shuffledCards = 0;
	
	
	//int i;
	struct gameState G, testG;
	int result;
	
	//int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    //int remove1, remove2;
    int seed = 1000;
    //int thisPlayer = 0;
	//int otherPlayer = 1;
	
	//initialize kingdom cards.
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
		   sea_hag, tribute, smithy};
	
	//initialize the game with 2 players, the kingdom stack, random seed, and gamestate.
	initializeGame(2, k, seed, &G);
	
	//begin testing
	printf("UNIT TEST 2: isGameOver()\n");
	
	//copy gameState to compare with tested state later.
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("-When only the Province pile is empty: ");
	testG.supplyCount[province] = 0;
	result = isGameOver(&testG);
	compareNum(1, result);
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("-When there are 3 empty Kingdom piles: ");
	testG.supplyCount[gardens] = 0;
	testG.supplyCount[smithy] = 0;
	testG.supplyCount[village] = 0;
	result = isGameOver(&testG);
	compareNum(1, result);
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("-When there are 2 empty Kingdom piles: ");
	testG.supplyCount[gardens] = 0;
	testG.supplyCount[smithy] = 0;
	result = isGameOver(&testG);
	compareNum(0, result);
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("-When there is 1 empty Kingdom pile: ");
	testG.supplyCount[gardens] = 0;
	result = isGameOver(&testG);
	compareNum(0, result);
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("-When there is 1 empty Kingdom pile and 1 empty Province pile: ");
	testG.supplyCount[gardens] = 0;
	testG.supplyCount[province] = 0;
	result = isGameOver(&testG);
	compareNum(1, result);
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("-When there are no empty piles: ");
	result = isGameOver(&testG);
	compareNum(0, result);
	
	
	return 0 ;
}