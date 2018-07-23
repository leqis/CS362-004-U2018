/*******************************
**Cardtest3.c: Gardens card
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
	int expectScore = 0;
	int actualScore = 0;
	int gardensCount = 0;
	
	int i;
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
	printf("CARDTEST3: GARDENS\n");
	printf("Calculating scores:\n");
	
	//copy gameState to compare with tested state later.
	memcpy(&testG, &G, sizeof(struct gameState));
	
	//manually set up current Player's hand, 10 for each pile.
	G.handCount[thisPlayer] = 10;
	for (i = 0; i < 9 ; i++){
		G.hand[thisPlayer][i] = copper;
	}
	G.hand[thisPlayer][9] = gardens;
	
	G.deckCount[thisPlayer] = 10;
	for (i = 0; i < 9 ; i++){
		G.deck[thisPlayer][i] = copper;
	}
	G.deck[thisPlayer][9] = gardens;
	
	G.discardCount[thisPlayer] = 10;
	for (i = 0; i < 9 ; i++){
		G.discard[thisPlayer][i] = copper;
	}
	G.discard[thisPlayer][9] = gardens;
	printf("-Player has 10 cards on each pile and 1 Gardens on EACH pile: ");
	actualScore = scoreFor(thisPlayer, &G);
	gardensCount = fullDeckCount(thisPlayer, gardens, &G);
	expectScore = 9;
	compareNum(expectScore, actualScore);
	printf("	Expected score: %d, Actual score: %d, Gardens count: %d\n\n", expectScore, actualScore, gardensCount);
	
	
	//manually set up current Player's hand, 10 for each pile, 1 gardens on hand.
	G.handCount[thisPlayer] = 10;
	for (i = 0; i < 9 ; i++){
		G.hand[thisPlayer][i] = copper;
	}
	G.hand[thisPlayer][9] = gardens;
	
	G.deckCount[thisPlayer] = 10;
	for (i = 0; i < 10 ; i++){
		G.deck[thisPlayer][i] = copper;
	}
		
	G.discardCount[thisPlayer] = 10;
	for (i = 0; i < 10 ; i++){
		G.discard[thisPlayer][i] = copper;
	}
	
	printf("-Player has 10 cards on each pile and 1 Gardens on HAND pile: ");
	actualScore = scoreFor(thisPlayer, &G);
	gardensCount = fullDeckCount(thisPlayer, gardens, &G);
	expectScore = 3;
	compareNum(expectScore, actualScore);
	printf("	Expected score: %d, Actual score: %d, Gardens count: %d\n\n", expectScore, actualScore, gardensCount);
	
	
	//manually set up current Player's hand, 10 for each pile, 1 gardens on deck.
	G.handCount[thisPlayer] = 10;
	for (i = 0; i < 10 ; i++){
		G.hand[thisPlayer][i] = copper;
	}
	
	G.deckCount[thisPlayer] = 10;
	for (i = 0; i < 9 ; i++){
		G.deck[thisPlayer][i] = copper;
	}
	G.deck[thisPlayer][9] = gardens;
		
	G.discardCount[thisPlayer] = 10;
	for (i = 0; i < 10 ; i++){
		G.discard[thisPlayer][i] = copper;
	}
	
	printf("-Player has 10 cards on each pile and 1 Gardens on DECK pile: ");
	actualScore = scoreFor(thisPlayer, &G);
	gardensCount = fullDeckCount(thisPlayer, gardens, &G);
	expectScore = 3;
	compareNum(expectScore, actualScore);
	printf("	Expected score: %d, Actual score: %d, Gardens count: %d\n\n", expectScore, actualScore, gardensCount);
	
	
	//manually set up current Player's hand, 10 for each pile, 1 gardens on discard.
	G.handCount[thisPlayer] = 10;
	for (i = 0; i < 10 ; i++){
		G.hand[thisPlayer][i] = copper;
	}
	
	G.deckCount[thisPlayer] = 10;
	for (i = 0; i < 10 ; i++){
		G.deck[thisPlayer][i] = copper;
	}
		
	G.discardCount[thisPlayer] = 10;
	for (i = 0; i < 9 ; i++){
		G.discard[thisPlayer][i] = copper;
	}
	G.discard[thisPlayer][9] = gardens;
	
	printf("-Player has 10 cards on each pile and 1 Gardens on DISCARD pile: ");
	actualScore = scoreFor(thisPlayer, &G);
	gardensCount = fullDeckCount(thisPlayer, gardens, &G);
	expectScore = 3;
	compareNum(expectScore, actualScore);
	printf("	Expected score: %d, Actual score: %d, Gardens count: %d\n\n", expectScore, actualScore, gardensCount);
	
	
	//manually set up current Player's hand, 10 on HAND pile with 1 gardnes, others less than 10 in total.
	G.handCount[thisPlayer] = 10;
	for (i = 0; i < 9 ; i++){
		G.hand[thisPlayer][i] = copper;
	}
	G.hand[thisPlayer][9] = gardens;
	
	G.deckCount[thisPlayer] = 1;
	G.deck[thisPlayer][0] = copper;
		
	G.discardCount[thisPlayer] = 1;
	G.discard[thisPlayer][0] = copper;
	
	printf("-Player has 10 cards on HAND pile with 1 Gardens, other piles have less than 10 in total with no gardens: ");
	actualScore = scoreFor(thisPlayer, &G);
	gardensCount = fullDeckCount(thisPlayer, gardens, &G);
	expectScore = 1;
	compareNum(expectScore, actualScore);
	printf("	Expected score: %d, Actual score: %d, Gardens count: %d\n\n", expectScore, actualScore, gardensCount);
	
	
	//manually set up current Player's hand, 10 on DECK pile with 1 gardnes, others less than 10 in total.
	G.handCount[thisPlayer] = 1;
	G.hand[thisPlayer][0] = copper;
	
	G.deckCount[thisPlayer] = 10;
	for (i = 0; i < 9; i++){
		G.deck[thisPlayer][i] = copper;
	}
	G.deck[thisPlayer][9] = gardens;
		
	G.discardCount[thisPlayer] = 1;
	G.discard[thisPlayer][0] = copper;
	
	printf("-Player has 10 cards on DECK pile with 1 Gardens, other piles have less than 10 in total with no gardens: ");
	actualScore = scoreFor(thisPlayer, &G);
	gardensCount = fullDeckCount(thisPlayer, gardens, &G);
	expectScore = 1;
	compareNum(expectScore, actualScore);
	printf("	Expected score: %d, Actual score: %d, Gardens count: %d\n\n", expectScore, actualScore, gardensCount);
	
	
	//manually set up current Player's hand, 10 on DISCARD pile with 1 gardnes, others less than 10 in total.
	G.handCount[thisPlayer] = 1;
	G.hand[thisPlayer][0] = copper;
	
	G.deckCount[thisPlayer] = 1;
	G.deck[thisPlayer][0] = copper;
		
	G.discardCount[thisPlayer] = 10;
	for (i = 0; i < 9; i++){
		G.discard[thisPlayer][i] = copper;
	}
	G.discard[thisPlayer][9] = gardens;
	
	printf("-Player has 10 cards on DISCARD pile with 1 Gardens, other piles have less than 10 in total with no gardens: ");
	actualScore = scoreFor(thisPlayer, &G);
	gardensCount = fullDeckCount(thisPlayer, gardens, &G);
	expectScore = 1;
	compareNum(expectScore, actualScore);
	printf("	Expected score: %d, Actual score: %d, Gardens count: %d\n\n", expectScore, actualScore, gardensCount);
	

	//manually set up current Player's hand with 1 garden, the player has less than 10 card for each pile, but adding up to >10 and <20.
	G.handCount[thisPlayer] = 1;
	G.hand[thisPlayer][0] = copper;
	
	G.deckCount[thisPlayer] = 1;
	G.deck[thisPlayer][0] = copper;
		
	G.discardCount[thisPlayer] = 9;
	for (i = 0; i < 8; i++){
		G.discard[thisPlayer][i] = copper;
	}
	G.discard[thisPlayer][8] = gardens;
	
	printf("-Player has less than 10 for each pile, but adding up to >10 and <20, 1 gardens total: ");
	actualScore = scoreFor(thisPlayer, &G);
	gardensCount = fullDeckCount(thisPlayer, gardens, &G);
	expectScore = 1;
	compareNum(expectScore, actualScore);
	printf("	Expected score: %d, Actual score: %d, Gardens count: %d\n\n", expectScore, actualScore, gardensCount);
	
	
	return 0;
}