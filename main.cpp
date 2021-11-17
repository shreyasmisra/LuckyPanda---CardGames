#include <iostream>
#include <cstdlib>
#include <time.h>

#include "generic.h"
#include "blackjack.h"
#include "seven_up.h"
#include "poker_hand.h"
#include "graphics.h"
#include "solitaire.h"

int main() {

	// Main.cpp 
	// All header files and game playing and drawing functions should be called here

	srand(time(nullptr));

	std::string str;
	int num;
	std::cout << "Which Game do you want to play? ->\n";
	std::cout << "1 -- Blackjack\n";
	std::cout << "2 -- Poker\n";
	std::cout << "3 -- Seven up\n";
	std::cout << "4 -- Solitaire\n";

	std::cin >> num;

	// can play blackjack and seven up multiple times in the same run.

	if (num == 1)
	{
		std::cout << "\nPlaying BlackJack\n\n";

		// Blackjack
		BlackJack bj;
		bj.playBlackJackMultipleTimes();
	}
	else if (num == 2)
	{
		// Poker
		std::cout << "\nPlaying Poker\n\n";
		int userMoney = 1000; int compMoney = 1000;
		playpokerhand(userMoney, compMoney);
	}
	else if (num == 3)
	{
		// SevenUp

		std::cout << "\nPlaying Seven Up\n\n";

		SevenUp svn;
		svn.PlaySevenUp();
	}
	else if (num == 4) {

		std::cout << "\nPlaying Solitaire\n\n";

		Solitaire s;
		s.PlaySolitaire();
	}

	return 0;
}
