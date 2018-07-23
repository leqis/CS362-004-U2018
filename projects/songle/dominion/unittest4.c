/*******************************
**Unittest4.c: updateCoins()
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
	
	
	int i;
	struct gameState G, testG;
	int result;
	
	//int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    //int remove1, remove2;
    int seed = 1000;
    int thisPlayer = 0;
	//int otherPlayer = 1;
	
	//initialize kingdom cards.
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
		   sea_hag, tribute, smithy};
	
	//initialize the game with 2 players, the kingdom stack, random seed, and gamestate.
	initializeGame(2, k, seed, &G);
	
	//begin testing
	printf("UNIT TEST 4: updateCoins()\n");
	
	//copy gameState to compare with tested state later.
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("-When the player has no Treasure cards nor bonus in hand: ");
	for (i = 0; i < testG.handCount[thisPlayer]; i++){
		testG.hand[thisPlayer][i] = estate;
	}
	result = updateCoins(thisPlayer, &testG, 0);
	compareNum(0, testG.coins);
	memcpy(&testG, &G, sizeof(struct gameState));
	
	
	printf("-When the hand is filled with gold with no bonus: ");
	for (i = 0; i < testG.handCount[thisPlayer]; i++){
		testG.hand[thisPlayer][i] = gold;
	}
	result = updateCoins(thisPlayer, &testG, 0);
	compareNum(testG.handCount[thisPlayer]*3, testG.coins);
	memcpy(&testG, &G, sizeof(struct gameState));
	
	
	printf("-When the hand is filled with gold with 1 bonus point: ");
	for (i = 0; i < testG.handCount[thisPlayer]; i++){
		testG.hand[thisPlayer][i] = gold;
	}
	result = updateCoins(thisPlayer, &testG, 1);
	compareNum(testG.handCount[thisPlayer]*3 + 1, testG.coins);
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("-When the hand has all 3 treasure cards with 1 bonus point: ");
	for (i = 0; i < testG.handCount[thisPlayer]; i++){
		if (i == 0)
			testG.hand[thisPlayer][i] = gold;
		else if (i == 1)
			testG.hand[thisPlayer][i] = silver;
		else if (i == 2)
			testG.hand[thisPlayer][i] = copper;
		else
			testG.hand[thisPlayer][i] = estate;
	}
	result = updateCoins(thisPlayer, &testG, 1);
	result = 3*1 + 1*2 + 1*1 + 1;
	compareNum(result, testG.coins);
	//printf("Manuall count: %d, updateCoins: %d\n", result, testG.coins);
	memcpy(&testG, &G, sizeof(struct gameState));
	
	
	return 0;
}
	