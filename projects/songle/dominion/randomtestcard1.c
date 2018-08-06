/********************************
**Randomtestcard1.c: Smithy card
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
int gainCardFail = 0;
int currentDeckFail = 0;
int opponentHandFail = 0;
int opponentDeckFail = 0;
int kingdomCountFail = 0;
int provinceCountFail = 0;
int duchyCountFail = 0;
int estateCountFail = 0;
int deckOverThree = 0;

//initialize kingdom cards.
int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

#define NUM_TESTS 1000


/*****************************************************************
**void checkSmithy
**Checks the effect on the game after the Smithy card is played.
**Inputs: current player, current game state, previous game state.
*****************************************************************/
void checkSmithy(int thisPlayer, struct gameState* G, struct gameState* preG){
	int i;
	
	//printf("Number of players: %d\n", G->numPlayers);
	
	//current player gains 3 cards.
	if (preG->handCount[thisPlayer] + 2 != G->handCount[thisPlayer])
		gainCardFail++;
	
	//current player gain 3 cards from the deck.
	if (preG->deckCount[thisPlayer] > 3){
		deckOverThree++;
		if (preG->deckCount[thisPlayer] - 3 != G->deckCount[thisPlayer])
			currentDeckFail++;
	}
	
	//check other player's hand and deck
	for (i = 0; i < G->numPlayers; i++){
		if (i != thisPlayer){
			if (G->handCount[i] != preG->handCount[i])
				opponentHandFail++;
			
			if (G->deckCount[i] != preG->deckCount[i])
				opponentDeckFail++;
		}
	}
	
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
	
	int thisPlayer = 0;
	//int otherPlayer = 1;
	int playerCount = 0;
	struct gameState G, preG;
	int i, j, w;
	

	//set up handpos etc. for calling cardEffect.
	int handpos = 0;
	
	
	/**************Begin testing****************/
	printf("RANDOMCARDTEST1: SMITHY\n");
	
	for (i = 0; i < NUM_TESTS; i++){
		
		//randomize the number of players.
		playerCount = rand() % MAX_PLAYERS +1;
		
		//initialize the game with num players, the kingdom stack, random seed, and gamestate.
		initializeGame(playerCount, k, 3, &G);
		
		//randomize the deck piles for each player, each player need at least 4 cards in deck.
		for (j = 0; j < playerCount; j++){
			
			G.deckCount[j] = rand() % (MAX_DECK - 4) + 4;
			for (w = 0; w < G.deckCount[j]; w++)
				G.deck[j][w] = rand() % 26;
			
		}
		
		//Pick a random player as the current player.
		thisPlayer = rand() % playerCount;
		
		//Place Smithy at a random hand position of the current player.
		//EDIT: this acutally doesn't matter.
		/*if (G.handCount[thisPlayer] > 0)
			handpos = rand() % G.handCount[thisPlayer];
		else
			handpos = 0;*/
		
		//Copy gameState to compare with tested state later.
		memcpy(&preG, &G, sizeof(struct gameState));
		
		//Play the Smithy card.
		//cardEffect(smithy, choice1, choice2, choice3, &G, handpos, &bonus);
		playSmithy(&G, thisPlayer, handpos);
		
		//Check the effects of Smithy.
		checkSmithy(thisPlayer, &G, &preG);
	}
	
	printf("Gain Card Fail: %d\n", gainCardFail);
	printf("Times of deck has over 3 cards: %d, Fail to gain 3 from Deck: %d\n", deckOverThree, currentDeckFail);
	printf("Gained from opponent's hand: %d\n", opponentHandFail);
	printf("Gained from opponent's deck: %d\n", opponentDeckFail);
	printf("Kingdom pile failure: %d\n", kingdomCountFail);
	printf("Province pile failure: %d\n", provinceCountFail);
	printf("Duchy pile failure: %d\n", duchyCountFail);
	printf("Estate pile failure: %d\n", estateCountFail);
	
	return 0;
}

