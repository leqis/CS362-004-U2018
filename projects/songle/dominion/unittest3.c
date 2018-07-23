/*******************************
**Unittest3.c: gainCard
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
	int result;
	struct gameState G, testG;
	
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
	printf("UNIT TSET 3: gainCard\n");
	
	//copy gameState to compare with tested state later.
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("-Gain a card from an empty pile: ");
	testG.supplyCount[curse] = 0;
	result = gainCard(curse, &testG, 1, thisPlayer);
	compareNum(-1, result);
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("-Gain a card and put it into hand: \n");
	result = gainCard(gold, &testG, 2, thisPlayer);
	printf("	The card is in hand: ");
	compareNum(G.handCount[thisPlayer] + 1, testG.handCount[thisPlayer]);
	printf("	The supply pile decreased: ");
	compareNum(G.supplyCount[gold] - 1, testG.supplyCount[gold]);
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("-Gain a card and put it into deck: \n");
	result = gainCard(curse, &testG, 1, thisPlayer);
	printf("	The card is in deck: ");
	compareNum(G.deckCount[thisPlayer] + 1, testG.deckCount[thisPlayer]);
	printf("	The supply pile decreased: ");
	compareNum(G.supplyCount[curse] - 1, testG.supplyCount[curse]);
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("-Gain a card and put it into discard: \n");
	result = gainCard(copper, &testG, 0, thisPlayer);
	printf("	The card is in discard: ");
	compareNum(G.discardCount[thisPlayer] + 1, testG.discardCount[thisPlayer]);
	printf("	The supply pile decreased: ");
	compareNum(G.supplyCount[copper] - 1, testG.supplyCount[copper]);
	memcpy(&testG, &G, sizeof(struct gameState));
	
	
	
	return 0 ;
}