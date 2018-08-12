/***************************
**Cardtest1.c: smithy card
***************************/
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
	
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
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
	printf("CARDTEST1: SMITHY\n");
	
	 //copy gameState to compare with tested state later.
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("-Player gains 3 cards: ");
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
	//the player throws away the Smithy card right after playing, so it's "+2" afte gaining 3 cards.
	compareNum(G.handCount[thisPlayer] + 2, testG.handCount[thisPlayer]);
	
	printf("-Player gains cards from his/her own deck: ");
	if(G.deckCount[thisPlayer] > testG.deckCount[thisPlayer])
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
	printf("-No changes in the other player' hand: ");
	compareNum(G.handCount[otherPlayer], testG.handCount[otherPlayer]);
	printf("-No changes in the other player' deck: ");
	compareNum(G.deckCount[otherPlayer], testG.deckCount[otherPlayer]);
	
	printf("-No changes in the Province pile: ");
	compareNum(G.supplyCount[province], testG.supplyCount[province]);
	printf("-No changes in the Duchy pile: ");
	compareNum(G.supplyCount[duchy], testG.supplyCount[duchy]);
	printf("-No changes in the Estate pile: ");
	compareNum(G.supplyCount[estate], testG.supplyCount[estate]);
	
	printf("-No changes in the Kingdowm pile:\n");
	for (i = 0; i < 10; i++){
		compareNum(G.supplyCount[k[i]], testG.supplyCount[k[i]]);
	}
	
	
  
	return 0;
}



