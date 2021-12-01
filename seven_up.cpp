#include <string>
#include <chrono>

#include "seven_up.h"
#include "yssimplesound.h"
#include "fssimplewindow.h"
#include "ysglfontdata.h"
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
		return 7; //lucky 7
		
	}
	else if (set == userResponse)
	{
		return 8; //correct guess
	}
	else
	{
		return 9; //wrong guess
	}
}

void SevenUp::DisplaySevenUpBackground(const MainData& dat) const
{
	Render(dat, 0, 700, 55);
}

void SevenUp::DispOnScreen(const MainData& dat) const
{
	ColorGreenBackGround();
	DisplaySevenUpBackground(dat);
	glColor3ub(0, 0, 0);
	glRasterPos2d(300, 300);
	YsGlDrawFontBitmap20x28("Dealer");
	glColor3ub(0, 0, 0);
	glRasterPos2d(550, 80);
	YsGlDrawFontBitmap32x48("SevenUp");
}

int SevenUp::PlaySevenUp(MainData& dat, int money) //Main game
{
	int out; bool updateMoney = false;
	auto b = std::to_string(bet);

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;
	
	YsSoundPlayer soundPlayer;
	YsSoundPlayer::SoundData wav;
	if (YSOK != wav.LoadWav(dat.soundName.c_str()))
	{
		printf("Failed to read %s\n", dat.soundName.c_str());
		return -1;
	}
	soundPlayer.Start();

	while (playGame)
	{
		FsPollDevice();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		DispOnScreen(dat);
		
		auto key = FsInkey();
		if (FSKEY_ESC == key)
		{
			break;
		}
		if (playerturn)
		{
			DisplayMoneyAndName(dat);
			Render(dat, 450, 300, 0);

			if (userResponse == 0)
			{
				glColor3ub(0, 0, 0);
				glRasterPos2d(550, 500);
				YsGlDrawFontBitmap16x20("Choose number : \n  ");

				glRasterPos2d(550, 550);
				YsGlDrawFontBitmap16x20("1 -- 7up \n");

				glRasterPos2d(550, 600);
				YsGlDrawFontBitmap16x20("2 -- 7down \n");

				glRasterPos2d(550, 650);
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

					glColor3ub(0, 0, 0);
					glRasterPos2d(150, 750);
					YsGlDrawFontBitmap20x28("Choose bet amount: $\n");
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
					glColor3ub(0, 0, 0);
					glRasterPos2d(550, 750);
					YsGlDrawFontBitmap20x28(b.c_str());
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
			set = ClassifySet();
			Render(dat, 450, 350, dealercard.getGraphicsIndex());
			out = CheckMatch();
			if (out == 8)
			{
				if (updateMoney) {
					dat.setMoney(2 * bet);
					updateMoney = false;
					soundPlayer.PlayOneShot(wav);
				}

				glColor3ub(rand() % 255, rand() % 255, rand() % 255);
				glRasterPos2d(150, 730);
				YsGlDrawFontBitmap16x24("Good Guess! You got it right!");

				/*glRasterPos2d(150, 370);
				YsGlDrawFontBitmap20x28("You win $");*/

				auto winnings = std::to_string(bet * 2);

				/*glRasterPos2d(320, 370);
				YsGlDrawFontBitmap20x28(winnings.c_str());*/
			}

			else if (out == 9)
			{
				if (updateMoney) {
					dat.setMoney(0 * bet);
					updateMoney = false;
				}
				glColor3ub(0, 0, 0);
				glRasterPos2d(150, 730);
				YsGlDrawFontBitmap16x24("You got it wrong. You lose:(");

				/*glRasterPos2d(150, 370);
				YsGlDrawFontBitmap20x28("You lost $");*/

				auto winnings = std::to_string(bet * 1);

				/*glRasterPos2d(320, 370);
				YsGlDrawFontBitmap20x28(winnings.c_str());*/
			}

			else if (out == 7)
			{
				if (updateMoney) {
					dat.setMoney(3 * bet);
					updateMoney = false;
					soundPlayer.PlayOneShot(wav);
				}
				glColor3ub(rand() % 255, rand() % 255, rand() % 255);
				glRasterPos2d(150, 730);
				YsGlDrawFontBitmap16x24("Lucky 7! You Win!");

				/*glRasterPos2d(320, 370);
				YsGlDrawFontBitmap20x28("You win $");*/

				auto winnings = std::to_string(bet * 3);

				/*glRasterPos2d(220, 370);
				YsGlDrawFontBitmap20x28(winnings.c_str());*/
			}

			auto end = std::chrono::system_clock::now();
			elapsed_seconds = end - start;
			if (elapsed_seconds.count() > 5) 
			{
				dealerturn = false;
			}
		}

		else if (!playerturn && !dealerturn)
		{
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
	soundPlayer.End();
}
