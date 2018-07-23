/*******************************
**Unitetest1.c: fullDeckCount()
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
	
	//int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    //int remove1, remove2;
    int seed = 1000;
    int thisPlayer = 0;
	int otherPlayer = 1;
	
	//initialize kingdom cards.
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
		   sea_hag, tribute, smithy};
	
	//initialize the game with 2 players, the kingdom stack, random seed, and gamestate.
	initializeGame(2, k, seed, &G);
	
	//begin testing
	printf("UNIT TEST1: fullDeckCount()\n");
	
	//copy gameState to compare with tested state later.
	memcpy(&testG, &G, sizeof(struct gameState));
	
	
	printf("-Count the card at the beginning of a normally generated game:\n");
	printf("	Both players have 7 coppers: ");
	if (7 == fullDeckCount(thisPlayer, copper, &G) && 7 == fullDeckCount(otherPlayer, copper, &G))
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
	printf("	Both players have 3 estates: ");
	if (3 == fullDeckCount(thisPlayer, estate, &G) && 3 == fullDeckCount(otherPlayer, estate, &G))
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
	printf("	Both players have 0 curse cards: ");
	if (0 == fullDeckCount(thisPlayer, curse, &G) && 0 == fullDeckCount(otherPlayer, curse, &G))
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
	//Manually set up a full player board.
	printf("-Set the player's pile as 3 estates + 7 coppers on deck and hand; and 5 smithy and 5 coppers on discard\n");
	G.discardCount[thisPlayer] = 10;
	for (i = 0; i < 10; i++){
		if (i < 5)
			G.discard[thisPlayer][i] = smithy;
		else
			G.discard[thisPlayer][i] = copper;
	}
	
	printf("	-Count the coppers: ");
	compareNum(12, fullDeckCount(thisPlayer, copper, &G));
	printf("	-Count the smithy: ");
	compareNum(5, fullDeckCount(thisPlayer, smithy, &G));
	
	//Manually set up an all empty player board.
	printf("-Count coppers from 3 empty piles: ");
	G.discardCount[thisPlayer] = 0;
	G.handCount[thisPlayer] = 0;
	G.deckCount[thisPlayer] = 0;
	compareNum(0, fullDeckCount(thisPlayer, copper, &G));
	
	
	return 0;
}