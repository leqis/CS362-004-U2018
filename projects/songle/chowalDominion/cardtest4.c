/*******************************
**Cardtest4.c: Sea_hag card
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
	int curseCount, testCurseCount;
	
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
	printf("CARDTEST4: SEA HAG\n");
	
	//copy gameState to compare with tested state later.
	memcpy(&testG, &G, sizeof(struct gameState));
	
	//play Sea_hag.
	cardEffect(sea_hag, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	printf("-All other players gain a curse on the deck: ");
	for (i = 0; i < G.deckCount[otherPlayer]; i++){
		if (G.deck[otherPlayer][i] == curse) 
			curseCount++;
    }
	for (i = 0; i < testG.deckCount[otherPlayer]; i++){
		if (testG.deck[otherPlayer][i] == curse) 
			testCurseCount++;
	}
	compareNum(curseCount + 1, testCurseCount);
	printf("	CurseCont: %d, testCurseCount: %d\n", curseCount, testCurseCount);
	
	printf("-All other players discard a card: ");
	compareNum(G.discardCount[otherPlayer] + 1, testG.discardCount[otherPlayer]);
	printf("-And the discarded card(s) are from the top of their deck: ");
	if (G.deck[otherPlayer][G.deckCount[otherPlayer] - 1] == testG.discard[otherPlayer][testG.discardCount[otherPlayer] - 1])
		printf("PASSED\n");
	else
		printf("FAILED\n");
	
	//other players will discard 1 from deck and then gain a curse, so the deckCount remains the same.
	printf("-All other players have the correct deck count: ");
	compareNum(G.deckCount[otherPlayer], testG.deckCount[otherPlayer]);
	printf("	Original deckCount: %d, test deckCount: %d\n", G.deckCount[otherPlayer], testG.deckCount[otherPlayer]);
	
	printf("-No changes in the other player's hand: ");
	compareNum(G.handCount[otherPlayer], testG.handCount[otherPlayer]);
	
	printf("-No chages in the currrent player's hand: ");
	compareNum(G.handCount[thisPlayer], testG.handCount[thisPlayer]);
	printf("-No chages in the currrent player's deck: ");
	compareNum(G.deckCount[thisPlayer], testG.deckCount[thisPlayer]);
	printf("-No chages in the currrent player's discard: ");
	compareNum(G.discardCount[thisPlayer], testG.discardCount[thisPlayer]);
	
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