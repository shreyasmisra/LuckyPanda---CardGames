#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <stdio.h>

#include "seven_up.h"
#include "blackjack.h"
#include "poker_hand.h"
#include "solitaire.h"
#include "graphics.h"
#include "generic.h"
#include "text_input.h"
#include "fssimplewindow.h"
#include "ysglfontdata.h"

const int windowWidth = 1000; // change to 800
const int windowHeight = 800;
const int nPics = 56; // 0 is card back
int money = 1000;

int main() {

	// Main.cpp 
	// All header files and game playing and drawing functions should be called here

	srand(time(nullptr));
	
	bool endProgram = false; int option;

	bool getPlayerName = true; bool getPlayerGame = true;
	std::string gameName; gameName = "";

	MainData dat; dat.Create(nPics); dat.DecodeImages(); dat.setWindowDimensions(windowWidth, windowHeight); dat.setMoney(money);
	TextInput t;

	FsOpenWindow(0, 0, windowWidth, windowHeight, 1);

	// first screen to enter player name

	while (getPlayerName) {

		FsPollDevice();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ColorBackGround();

		
		if (getPlayerName) {

			auto textKey = t.RunOneStep();
			if (FSKEY_ENTER == textKey) {

				dat.setPlayerName(t.GetText().GetPointer());
				getPlayerName = false;
			}
		}
		

		auto key = FsInkey();
		if (FSKEY_ESC == key) {
			exit(0);
		}

		Render(dat, 0, 600, 54);

		glColor3ub(0, 255, 255);
		glRasterPos2d(550, 350);
		YsGlDrawFontBitmap24x40("LUCKY HAND");

		glColor3ub(0, 255, 255);
		glRasterPos2d(430, 550);
		YsGlDrawFontBitmap12x16("A product of Lucky Panda Games");


		glColor3ub(255, 0, 0);
		glRasterPos2d(50, 700);
		YsGlDrawFontBitmap20x28("Enter your name:");
		t.Draw();

		FsSwapBuffers();
		FsSleep(10);
	}

	// MainMenu which includes all the games

	while (true) {
		FsSwapBuffers();
		FsPollDevice();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		auto key = FsInkey();
		if (FSKEY_ESC == key) {
			break;
		}
		if (FSKEY_1 == key && getPlayerGame == true) {
			gameName = "blackjack";
			getPlayerGame = false;
		}
		else if (FSKEY_2 == key && getPlayerGame == true) {
			gameName = "poker";
			getPlayerGame = false;
		}
		else if (FSKEY_3 == key && getPlayerGame == true) {
			gameName = "solitaire";
			getPlayerGame = false;
		}
		else if (FSKEY_4 == key && getPlayerGame == true) {
			gameName = "sevenup";
			getPlayerGame = false;
		}

		ColorBackGround();
		
		DisplayMoneyAndName(dat);

		if (getPlayerGame) {
			DisplayGames();
		}

		// Uncomment if you want to play
		if (gameName == "blackjack") {
		//	// sub conditions to play the game

			BlackJack bj;
			bj.getBet = true;
			bj.playGame = true;

			option = bj.playBlackJack(dat, money); // play one turn. infinite loop inside it
			if (option == 1) {
				// play more blackjack
				continue;
			}
			else if (option == 2) {
				// play different game
				gameName = "";
				getPlayerGame = true;
			}
			else {
				printf("Program terminated");
				break;
			}
		}

		if (gameName == "sevenup") {
			// sub conditions to play the game

			SevenUp svn;
			svn.playGame = true;

			option = svn.PlaySevenUp(dat, money); // play one turn. infinite loop inside it
			if (option == 1) 
			{
				continue;
			}
			else if (option == 2) {
				// play different game
				gameName = "";
				getPlayerGame = true;
			}
			else {
				printf("Program terminated");
				break;
			}
		}

		if (gameName == "poker") {
			// sub conditions to play the game

			Cpu cpu;
			player p1;
			int pmoney = 1000;
			int cpumoney = 10000;
			playertag(0, 0);
			pokerhand(cpu, p1, pmoney, cpumoney, dat);

			//option = pokerhand(cpu, p1, pmoney, cpumoney, dat); // play one turn. infinite loop inside it
			//if (option == 1)
			//{
			//	continue;
			//}
			//else if (option == 2) {
			//	// play different game
			//	gameName = "";
			//	getPlayerGame = true;
			//}
			//else {
			//	printf("Program terminated");
			//	break;
			//}
		}
		if (gameName == "solitaire") {
			
			Solitaire s;
			s.PlaySolitaire(dat);

			//option = s.PlaySolitaire(dat); // play one turn. infinite loop inside it
			//if (option == 1)
			//{
			//	continue;
			//}
			//else if (option == 2) {
			//	// play different game
			//	gameName = "";
			//	getPlayerGame = true;
			//}
			//else {
			//	printf("Program terminated");
			//	break;
			//}
		}

		FsSleep(10);
	}

	return 0;
}