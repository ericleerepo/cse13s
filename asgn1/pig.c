#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "names.h"

int main(void){
	typedef enum {SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER} Position;
	const Position pig[7] = {SIDE, SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER, JOWLER
	};
	
	int num_players = 2;
	printf("Number of players (2 to 10)? ");
	int scanf_result = scanf("%d", &num_players);
	if (scanf_result < 1 || num_players < 2 || num_players > 10){
		fprintf(stderr, "Invalid number of players. Using 2 instead.\n");	}
	unsigned seed = 2023;
	printf("Random-number seed? ");
	int seed_scan = scanf("%u", &seed);
	if (seed_scan<1){
		fprintf(stderr,"Invalid seed. Using 2023 instead.\n");
	}
	
	srandom(seed);
	int players [num_players];
	for (int i = 0; i < num_players; i++){
                players[i] = 0;
        }
	/*
	for (int i = 0; i < num_players; i++) {
 		printf("%d\n", players[i]);
	}
	*/	
	int turn = 0;
	bool game = true;
	printf("%s\n", player_name[turn]);
	while (game){
		int rand = random();
		/*printf("%d rand\n",rand);*/
		int roll = (rand%7);
		/*printf("%d side\n", pig[roll]);*/
		switch(pig[roll]){
			case SIDE:
				printf(" rolls 0, has %d\n", players[turn]);
				if (turn == (num_players-1)){
					turn = 0;
				}else{
					turn = turn + 1;
				}
				printf("%s\n", player_name[turn]);
				break;
			case RAZORBACK:
				players[turn] = (players[turn]) + 10;
				printf(" rolls 10, has %d\n", players[turn]);
				break;
			case TROTTER:
				players[turn] = (players[turn]) + 10;
				printf(" rolls 10, has %d\n", players[turn]);	
				break;
			case SNOUTER:
				players[turn] = (players[turn]) + 15;
				printf(" rolls 15, has %d\n", players[turn]);
				break;
			case JOWLER:
				players[turn] = (players[turn]) + 5;
				printf(" rolls 5, has %d\n", players[turn]);
				break;
			default:
				break;
			}
		if (players[turn]>=100){
			game = false;
			printf("%s won!\n",player_name[turn]);
			break;
			}
	}
	return 0;
}
