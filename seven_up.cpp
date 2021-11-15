#include "seven_up.h"


//Member functions for 7up class

SevenUp::SevenUp()
{
	bet = 0;
	set = 0;
	money_left = 0;
	userResponse = 0;
	srand(int(time(nullptr)));
	mainDeck.shuffleDeck();
	UI = 0;
}

int SevenUp::ClassifySet()
{
	if (dealercard.getRank() > 7)
	{
		set = 1;
	}
	else if (dealercard.getRank() < 7)
	{
		set = 2;
	}
	else
	{
		set = 3;
	}
	return set;
}

void SevenUp::CheckMatch()
{
	if (set == userResponse && set == 3)
	{
		money_left = total_money + 3 * bet;
		std::cout << "\nGood guess!! You won " << 3 * bet << " dollars.\n You have "<< money_left<< " money left.\n";
		
	}
	else if (set == userResponse)
	{
		money_left = total_money + 2 * bet;
		std::cout << "\nGood guess! You won  " << 2 * bet << " dollars.\n You have " << money_left << " money left.\n";
		
	}
	else
	{
		money_left = total_money - bet;
		std::cout << "\nSorry! Wrong guess. You lost " << bet << " dollars.\n You have " << money_left << " money left.\n";
	}
}

//int SevenUp::CountBet()
//{
//
//}

void SevenUp::PlaySevenUp()//Main game
{
	while (true)
	{
		std::cout << "Choose number: \n 1 -- 7up \n 2 -- 7down \n 3 -- 7  \n";
		std::cout << "Total amount = " << total_money << std::endl;
		std::cin >> userResponse;
		std::cout << "\nChoose bet amount: ";
		std::cin >> bet;

		dealercard = mainDeck.getRandomCard();
		dealercard.print();
		set = ClassifySet();
		CheckMatch();
		total_money = money_left;

		if (total_money <= 0) {
			std::cout << "you lost all money. you lose :(";
			break;
		}

		std::cout << "\nDo you want to play again (Y / N)? ";
		std::cin >> UI;
		if (UI == 'Y' || UI == 'y')
		{
			continue;
		}
		else if (UI == 'N' || UI == 'n')
		{
			break;
		}
		else {
			printf("Wrong input. Enter again>");
			std::cin >> UI;
		}
	}
	


}
