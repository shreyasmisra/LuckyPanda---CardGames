#include "seven_up.h"
#include <string>
#include <chrono>

//Member functions for 7up class

SevenUp::SevenUp()
{
	bet = 0;
	set = 0;
	userResponse = 0;
	mainDeck.setGraphicsIndices();
	mainDeck.shuffleDeck();
	dealercard = mainDeck.getRandomCard();
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

int SevenUp::CheckMatch()
{
	if (set == userResponse && set == 3)
	{
		return 7;
		//money_left = total_money + 3 * bet;
		//std::cout << "\nGood guess!! You won " << 3 * bet << " dollars.\n You have "<< money_left<< " money left.\n";
		
	}
	else if (set == userResponse)
	{
		//money_left = total_money + 2 * bet;
		//std::cout << "\nGood guess! You won  " << 2 * bet << " dollars.\n You have " << money_left << " money left.\n";
		return 8;
	}
	else
	{
		//money_left = total_money - bet;
		//std::cout << "\nSorry! Wrong guess. You lost " << bet << " dollars.\n You have " << money_left << " money left.\n";
		return 9;
	}
}

void SevenUp::DispOnScreen()
{
	ColorBackGround();
	glColor3ub(0, 0, 0);
	glRasterPos2d(300, 300);
	YsGlDrawFontBitmap16x20("Dealer");
}

int SevenUp::PlaySevenUp(MainData& dat, int money) //Main game
{
	int out; bool updateMoney = false;
	auto b = std::to_string(bet);

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;
	
	while (playGame)
	{
		FsPollDevice();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		DispOnScreen();
		
		
		auto key = FsInkey();
		if (FSKEY_ESC == key)
		{
			break;
		}
		if (playerturn)
		{
			DisplayMoneyAndName(dat);
			Render(dat, 450, 300, 0);
			Render(dat, 0, 700, 55);

			if (userResponse == 0)
			{
				glColor3ub(255, 0, 0);
				glRasterPos2d(500, 500);
				YsGlDrawFontBitmap16x20("Choose number : \n  ");

				glRasterPos2d(500, 550);
				YsGlDrawFontBitmap16x20("1 -- 7up \n");

				glRasterPos2d(500, 600);
				YsGlDrawFontBitmap16x20("2 -- 7down \n");

				glRasterPos2d(500, 650);
				YsGlDrawFontBitmap16x20("3 -- 7  \n");

				if (FSKEY_1 == key) 
				{
					userResponse = 1;
				}
				else if (FSKEY_2 == key)
				{
					userResponse = 2;
				}
				else if (FSKEY_3 == key) 
				{
					userResponse = 3;
				}
				getbet = true;
			}
			
			/*else
			{
				glRasterPos2d(400, 450);
				YsGlDrawFontBitmap16x20("Wrong choice! please re-enter \n");
			}*/
			else if (userResponse != 0)
			{
				if (getbet)
				{
					glRasterPos2d(100, 450);
					YsGlDrawFontBitmap16x24("Choose bet amount: $\n");
					if (FSKEY_UP == key && bet != dat.getMoney())
					{
						bet += 50;
						b = std::to_string(bet);
					}
					else if (FSKEY_DOWN == key && bet != 0)
					{
						bet -= 50;
						b = std::to_string(bet);
					}
					else if (FSKEY_ENTER == key)
					{
						dat.setMoney(-bet);
						getbet = false;
					}
					glColor3ub(255, 255, 255);
					glRasterPos2d(470, 450);
					YsGlDrawFontBitmap16x24(b.c_str());
				}
				
				else if (!getbet)
				{
					playerturn = false;
					dealerturn = true;
					updateMoney = true;
					start = std::chrono::system_clock::now();
				}
			}
		}
		
		else if (dealerturn)
		{
			DisplayMoneyAndName(dat);
			Render(dat, 0, 700, 55);
			set = ClassifySet();
			Render(dat, 450, 350, dealercard.getGraphicsIndex());
			out = CheckMatch();
			if (out == 7)
			{
				if (updateMoney) {
					dat.setMoney(2 * bet);
					updateMoney = false;
				}

				// Put this code below (showing the money won or lost) in a function and call it instead of writing the same thing thrice. 
				// pass the bet as a parameter.
				// Figure out how to show the words "won" and "lost" in the same function at different calls
				// Call this function after showing EndGameOptions also maybe? Looks better

				glColor3ub(0, 0, 0);
				glRasterPos2d(150, 350);
				YsGlDrawFontBitmap12x16("Good Guess! You got it right!");

				glRasterPos2d(150, 370);
				YsGlDrawFontBitmap12x16("You win $");

				auto winnings = std::to_string(bet * 2);

				glRasterPos2d(320, 370);
				YsGlDrawFontBitmap12x16(winnings.c_str());
			}

			else if (out == 9)
			{
				if (updateMoney) {
					dat.setMoney(0 * bet);
					updateMoney = false;
				}
				glColor3ub(0, 0, 0);
				glRasterPos2d(150, 350);
				YsGlDrawFontBitmap12x16("You got it wrong :(");

				glRasterPos2d(150, 370);
				YsGlDrawFontBitmap12x16("You lost $");

				auto winnings = std::to_string(bet * 1);

				glRasterPos2d(320, 370);
				YsGlDrawFontBitmap12x16(winnings.c_str());
			}

			else if (out == 8)
			{
				if (updateMoney) {
					dat.setMoney(3 * bet);
					updateMoney = false;
				}
				glColor3ub(0, 0, 0);
				glRasterPos2d(150, 350);
				YsGlDrawFontBitmap12x16("Lucky 7! You Win!");

				glRasterPos2d(320, 370);
				YsGlDrawFontBitmap12x16("You win $");

				auto winnings = std::to_string(bet * 3);

				glRasterPos2d(220, 370);
				YsGlDrawFontBitmap12x16(winnings.c_str());
			}

			auto end = std::chrono::system_clock::now();
			elapsed_seconds = end - start;
			if (elapsed_seconds.count() > 5) {
				dealerturn = false;
			}
		}

		else if (!playerturn && !dealerturn)
		{
			Render(dat, 0, 700, 55);
			DisplayMoneyAndName(dat);
			Render(dat, 450, 350, dealercard.getGraphicsIndex());
			EndGameOptions();
			if (FSKEY_N == key)
			{
				return 1;
			}
			else if (FSKEY_M == key)
			{
				return 2;
			}
			else if (FSKEY_Q == key)
			{
				printf("program terminated");
				exit(0);
			}
		}

		FsSwapBuffers();
		FsSleep(10);
	}
}
