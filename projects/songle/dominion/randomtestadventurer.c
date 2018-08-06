/****************************************
**RandomtestAdventurer.c: Adventurer card
****************************************/
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
int discardFail = 0;
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
**void checkAdventurer
**Checks the effect on the game after the Adventurer card is played.
**Inputs: current player, current game state, previous game state.
*****************************************************************/
void checkAdventurer(int thisPlayer, struct gameState* G, struct gameState* preG){
	int i;
	int card = 0;
	int treasureG = 0; 
	int treasurePreG = 0;
	
	//Current player gained 2 treasure cards.
	for (i = 0; i < G->handCount[thisPlayer]; i++){
		card = G->hand[thisPlayer][i];
		if (card == gold || card == silver || card == copper)
			treasureG++;
	}
	for (i = 0; i < preG->handCount[thisPlayer]; i++){
		card = preG->hand[thisPlayer][i];
		if (card == gold || card == silver || card == copper)
			treasurePreG++;
	}
	if (treasurePreG + 2 != treasureG){
		gainCardFail++;
		printf("treasurePreG: %d; treasureG: %d\n", treasurePreG, treasureG);
	}
	
	//Current player discard the rest of the revealed cards.
	if (preG->discardCount[thisPlayer] >= G->discardCount[thisPlayer])
		discardFail++;
	
	////check other player's hand and deck
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
	
	int temphand[MAX_HAND];
	
	
	/**************Begin testing****************/
	printf("RANDOMCARDTEST1: ADVENTURER\n");
	
	for (i = 0; i < NUM_TESTS; i++){
		
		//randomize the number of players.
		playerCount = rand() % MAX_PLAYERS +1;
		
		//initialize the game with num players, the kingdom stack, random seed, and gamestate.
		initializeGame(playerCount, k, 3, &G);
		
		//randomize the deck and discard piles for each player.
		for (j = 0; j < playerCount; j++){
			
			G.deckCount[j] = rand() % (MAX_DECK);
			for (w = 0; w < G.deckCount[j]; w++){
				G.deck[j][w] = rand() % 26;
			}
			
			G.discardCount[j] = rand() % (MAX_DECK - 2) + 2;
			for (w = 0; w < G.discardCount[j]; w++){
				G.discard[j][w] = rand() % 26;
			}
			//manually making sure that each player at least has 2 treasure cards,
			//otherwise playAdventurer goes into infinite loop
			if (G.deckCount[j] < 2){
				G.discard[j][0] = copper;
				G.discard[j][1] = copper;
			}
			else if (G.deckCount[j] >= 2){
				G.deck[j][0] = copper;
				G.deck[j][1] = copper;
			}
			
			
		}
		
		//Pick a random player as the current player.
		thisPlayer = rand() % playerCount;
		
		//Copy gameState to compare with tested state later.
		memcpy(&preG, &G, sizeof(struct gameState));
		
		//Play the Adventurer card.
		//cardEffect(smithy, choice1, choice2, choice3, &G, handpos, &bonus);
		playAdventurer(&G, thisPlayer, temphand);
		
		//Check the effects of Smithy.
		checkAdventurer(thisPlayer, &G, &preG);
	}
	
	printf("Fail to gain 2 treasure cards: %d\n", gainCardFail);
	printf("Fail to discard other revealed cards: %d\n", discardFail);
	printf("Changes in opponent's hand: %d\n", opponentHandFail);
	printf("Changes in opponent's deck: %d\n", opponentDeckFail);
	printf("Kingdom pile failure: %d\n", kingdomCountFail);
	printf("Province pile failure: %d\n", provinceCountFail);
	printf("Duchy pile failure: %d\n", duchyCountFail);
	printf("Estate pile failure: %d\n", estateCountFail);
	
	return 0;
}

