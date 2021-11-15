#ifndef SEVEN_UP_H_IS_INCLUDED
#define SEVEN_UP_H_IS_INCLUDED

#include <iostream>
#include "generic.h"
#include <time.h>
#include <stdlib.h>



class SevenUp 
{
private:
	Deck mainDeck;
	int userResponse;
	int set;
	int bet;
	int total_money = 1000;
	int money_left;
	Card dealercard;
	char UI;



public:
	void PlaySevenUp();
	int ClassifySet();
	void CheckMatch();
	//int CountBet();
	SevenUp();

};




#endif