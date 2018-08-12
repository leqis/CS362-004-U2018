/********************************
**Randomtestcard2.c: Sea_hag card
********************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

//Variables for fault counting
int gainCurseFail = 0;
int discardFail = 0;
int dicardFromTopDeckFail = 0;
int opponentHandFail = 0;
int currentHandFail = 0;
int currentDeckFail = 0;
int currentDiscardFail = 0;
int kingdomCountFail = 0;
int provinceCountFail = 0;
int duchyCountFail = 0;
int estateCountFail = 0;

//initialize kingdom cards.
int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

#define NUM_TESTS 1000


/*****************************************************************
**void checkSeaHag
**Checks the effect on the game after the Sea_hag card is played.
**Inputs: current player, current game state, previous game state.
*****************************************************************/
void checkSeaHag(int thisPlayer, struct gameState* G, struct gameState* preG){
	int i, j;
	int curseCount, preCurseCount, notTopOfDeck;
	
	//All other players gain a curse on the deck.
	for (i = 0; i < G->numPlayers; i++){
		if (i != thisPlayer){
			for (j = 0; j < G->deckCount[i]; j++){
				if (G->deck[i][j] == curse) 
					curseCount++;
				if (preG->deck[i][j] == curse) 
					preCurseCount++;
			}
		}
	}
	
	if (curseCount != preCurseCount + 1)
		gainCurseFail++;
	
	//All other players discard a card.
	for (i = 0; i < G->numPlayers; i++){
		if (i != thisPlayer){
			if (preG->discardCount[i] + 1 != G->discardCount[i])
				discardFail++;
		}
	}
	
	//The discarded cards are from top of the deck.
	for (i = 0; i < G->numPlayers; i++){
		if (i != thisPlayer){
			if (preG->deck[i][preG->deckCount[i] - 1] != G->discard[i][G->discardCount[i] - 1])
				notTopOfDeck++;
		}
	}
	if (notTopOfDeck != 0)
		dicardFromTopDeckFail++;
	
	//No change in the opponents' hand.
	for (i = 0; i < G->numPlayers; i++){
		if (i != thisPlayer){
			if (G->handCount[i] != preG->handCount[i])
				opponentHandFail++;
		}
	}
	
	//No change in current player's hand.
	if (G->handCount[thisPlayer] != preG->handCount[thisPlayer])
		currentHandFail++;
		
	//No change in current player's deck.
	if (G->deckCount[thisPlayer] != preG->deckCount[thisPlayer])
		currentDeckFail++;
	
	//No change in current player's discard.
	if (G->discardCount[thisPlayer] != preG->discardCount[thisPlayer])
		currentDiscardFail++;
	
	//check the kingdom pile
	for (i = 0; i < 10; i++){
		if (G->supplyCount[k[i]] != preG->supplyCount[k[i]])
			kingdomCountFail++;
	}
	
	//check the treasure cards
	if (G->supplyCount[province] != preG->supplyCount[province])
		provinceCountFail++;
	
	if (G->supplyCount[duchy] != preG->supplyCount[duchy])
		duchyCountFail++;
	
	if (G->supplyCount[estate] != preG->supplyCount[estate])
		estateCountFail++;
}


int main(){
	
	srand(time(NULL));
	
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;	
	int thisPlayer = 0;
	//int otherPlayer = 1;
	int playerCount = 0;
	struct gameState G, preG;
	int i, j, w;
	
	//set up handpos etc. for calling cardEffect.
	//int handpos = 0;
	
	/**************Begin testing****************/
	printf("RANDOMCARDTEST2: SEA_HAG\n");
	
	for (i = 0; i < NUM_TESTS; i++){
		
		//randomize the number of players.
		playerCount = rand() % MAX_PLAYERS +1;
		
		//initialize the game with num players, the kingdom stack, random seed, and gamestate.
		initializeGame(playerCount, k, 3, &G);
		
		//randomize the deck and discard piles for each player, each player need at least 2 cards in deck.
		for (j = 0; j < playerCount; j++){
			
			G.deckCount[j] = rand() % (MAX_DECK - 2) + 2;
			for (w = 0; w < G.deckCount[j]; w++)
				G.deck[j][w] = rand() % 26;
			
			G.discardCount[j] = rand() % (MAX_DECK - 1) + 1;
			for (w = 0; w < G.discardCount[j]; w++)
				G.discard[j][w] = rand() % 26;
			
		}
		
		//Pick a random player as the current player.
		thisPlayer = rand() % playerCount;
		
		//Copy gameState to compare with tested state later.
		memcpy(&preG, &G, sizeof(struct gameState));
		
		//Play the Sea_hag card.
		//playSea_hag(&G, thisPlayer);
		cardEffect(sea_hag, choice1, choice2, choice3, &G, handpos, &bonus);
		
		//Check the effects of Smithy.
		checkSeaHag(thisPlayer, &G, &preG);
	}
	
	printf("Gain Curse Fail: %d\n", gainCurseFail);
	printf("Discard Fail: %d\n", discardFail);
	printf("Discard from top of deck fail: %d\n", dicardFromTopDeckFail);
	printf("No change in opponent's hand: %d\n", opponentHandFail);
	
	printf("No change in current player's hand: %d\n", currentHandFail);
	printf("No change in current player's deck: %d\n", currentDeckFail);
	printf("No change in current player's discard: %d\n", currentDiscardFail);
	
	printf("Kingdom pile failure: %d\n", kingdomCountFail);
	printf("Province pile failure: %d\n", provinceCountFail);
	printf("Duchy pile failure: %d\n", duchyCountFail);
	printf("Estate pile failure: %d\n", estateCountFail);
	
	return 0;
}

