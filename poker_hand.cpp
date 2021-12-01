#include <iostream>
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <math.h>

#include "poker_hand.h"
#include "generic.h"
#include "graphics.h"

using namespace std;

void playertag(int pbet, int cpubet, int pbalance) {
	string s = to_string(pbet);
	char const* pbetc = s.c_str();
	string s2 = to_string(cpubet);
	char const* cpubetc = s2.c_str();
	string s3 = to_string(pbalance);
	char const* pbalancec = s3.c_str();
	ColorGameBackGround();
	glColor3f(0, 0, 0);
	glRasterPos2i(50, 50);
	YsGlDrawFontBitmap16x20("Player1: CPU");
	glRasterPos2i(50, 500);
	YsGlDrawFontBitmap16x20("Player2: Player");
	glRasterPos2i(50, 600);
	YsGlDrawFontBitmap16x20("Balance:");
	glRasterPos2i(70, 100);
	YsGlDrawFontBitmap16x20(cpubetc);
	glRasterPos2i(70, 550);
	YsGlDrawFontBitmap16x20(pbetc);
	glRasterPos2i(200, 600);
	YsGlDrawFontBitmap16x20(pbalancec);
	glRasterPos2i(50, 100);
	YsGlDrawFontBitmap16x20("$");
	glRasterPos2i(50, 550);
	YsGlDrawFontBitmap16x20("$");
	glRasterPos2i(180, 600);
	YsGlDrawFontBitmap16x20("$");
	glEnd();
}

void PlayerBetFCHR(int pbet, int cpubet, int pbalance) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	playertag(pbet, cpubet, pbalance);
	glColor3ub(255, 95, 31);
	glRasterPos2d(200, 400);
	YsGlDrawFontBitmap10x14("0: Fold");
	glRasterPos2d(400, 400);
	YsGlDrawFontBitmap10x14("1: Check");
	glRasterPos2d(600, 400);
	YsGlDrawFontBitmap10x14("2: Raise");
	glEnd();
}

void PlayerBetFCallR(int pbet, int cpubet, int pbalance) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	playertag(pbet, cpubet, pbalance);
	glColor3ub(255, 95, 31);
	glRasterPos2d(200, 400);
	YsGlDrawFontBitmap10x14("0: Fold");
	glRasterPos2d(400, 400);
	YsGlDrawFontBitmap10x14("1: Call");
	glRasterPos2d(600, 400);
	YsGlDrawFontBitmap10x14("2: Raise");
	glEnd();
}

void PlayerBetChR(int pbet, int cpubet, int pbalance) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	playertag(pbet, cpubet, pbalance);
	glColor3ub(255, 95, 31);
	glRasterPos2d(300, 400);
	YsGlDrawFontBitmap10x14("1: Call");
	glRasterPos2d(500, 400);
	YsGlDrawFontBitmap10x14("2: Raise");
	glEnd();
}

void playerwinf(int pbet, int cpubet, int pbalance) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	playertag(pbet, cpubet, pbalance);
	glColor3ub(255, 0, 0);
	glRasterPos2i(320, 300);
	YsGlDrawFontBitmap16x20("Player Win!");
	glEnd();
}

void cpuwinf(int pbet, int cpubet, int pbalance) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	playertag(pbet, cpubet, pbalance);
	glColor3ub(255, 0, 0);
	glRasterPos2i(320, 300);
	YsGlDrawFontBitmap16x20("CPU Win!");
	glEnd();
}

void playerwin(int pbet, int cpubet, int pbalance) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	playertag(pbet, cpubet, pbalance);
	glColor3ub(255, 0, 0);
	glRasterPos2i(220, 300);
	YsGlDrawFontBitmap16x20("CPU Fold! Player Win!");
	glEnd();
}

void cpuwin(int pbet, int cpubet, int pbalance) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	playertag(pbet, cpubet, pbalance);
	glColor3ub(255, 0, 0);
	glRasterPos2i(320, 300);
	YsGlDrawFontBitmap16x20("CPU Win!");
	glEnd();
}


void cpucall(int pbet, int cpubet, int pbalance) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	playertag(pbet, cpubet, pbalance);
	glColor3ub(0, 0, 128);
	glRasterPos2i(350, 300);
	YsGlDrawFontBitmap16x20("CPU Call");
	glEnd();
}

void cpucheck(int pbet, int cpubet, int pbalance) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	playertag(pbet, cpubet, pbalance);
	glColor3ub(0, 0, 128);
	glRasterPos2i(320, 300);
	YsGlDrawFontBitmap16x20("CPU Check");
	glEnd();
}

void cpuraise(int pbet, int cpubet, int pbalance) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	playertag(pbet, cpubet, pbalance);
	glColor3ub(0, 0, 128);
	glRasterPos2i(320, 300);
	YsGlDrawFontBitmap16x20("CPU Raise");
	glEnd();
}

void playercheck(int pbet, int cpubet, int pbalance) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	playertag(pbet, cpubet, pbalance);
	glColor3ub(0, 0, 128);
	glRasterPos2i(300, 300);
	YsGlDrawFontBitmap16x20("Player Check");
	glEnd();
}

void playercall(int pbet, int cpubet, int pbalance) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	playertag(pbet, cpubet, pbalance);
	glColor3ub(0, 0, 128);
	glRasterPos2i(300, 300);
	YsGlDrawFontBitmap16x20("Player Call");
	glEnd();
}

void playerraise(int pbet, int cpubet, int pbalance) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	playertag(pbet, cpubet, pbalance);
	glColor3ub(0, 0, 128);
	glRasterPos2i(150, 300);
	YsGlDrawFontBitmap16x20("Add Amount(Press Enter When Done)");
	glEnd();
}

int playerselection(int pbet, int cpubet, int pbalance, const int pindex[2], const int cpuindex[2], const int openindex[5], MainData& dat) {

	for (;;) {
		FsPollDevice();
		auto lastKey = FsInkey();
		if (FSKEY_0 == lastKey) {
			return 0;
			break;
		}
		else if (FSKEY_1 == lastKey) {
			return 1;
			break;
		}
		else if (FSKEY_2 == lastKey) {
			return 2;
			break;
		}
		PlayerBetFCHR(pbet, cpubet, pbalance);
		Render(dat, 500, 590, pindex[0]);
		Render(dat, 400, 590, pindex[1]);
		Render(dat, 500, 100, 0);
		Render(dat, 400, 100, 0);
		for (int i = 0; i < 5; i++) {
			if (openindex[i] != 0) {
				Render(dat, 200 + 100 * i, 250, openindex[i]);
			}
		}
		FsSwapBuffers();
		FsSleep(10);
	}
}

int playerselection2(int pbet, int cpubet, int pbalance, const int pindex[2], const int cpuindex[2], const int openindex[5], MainData& dat) {

	for (;;) {
		FsPollDevice();
		auto lastKey = FsInkey();
		if (FSKEY_1 == lastKey) {
			return 1;
			break;
		}
		else if (FSKEY_2 == lastKey) {
			return 2;
			break;
		}
		PlayerBetChR(pbet, cpubet, pbalance);
		Render(dat, 500, 590, pindex[0]);
		Render(dat, 400, 590, pindex[1]);
		Render(dat, 500, 100, 0);
		Render(dat, 400, 100, 0);
		for (int i = 0; i < 5; i++) {
			if (openindex[i] != 0) {
				Render(dat, 200 + 100 * i, 250, openindex[i]);
			}
		}
		FsSwapBuffers();
		FsSleep(10);
	}
}

int playerselection3(int pbet, int cpubet, int pbalance, const int pindex[2], const int cpuindex[2], const int openindex[5], MainData& dat) {

	for (;;) {
		FsPollDevice();
		auto lastKey = FsInkey();
		if (FSKEY_0 == lastKey) {
			return 0;
			break;
		}
		else if (FSKEY_1 == lastKey) {
			return 1;
			break;
		}
		else if (FSKEY_2 == lastKey) {
			return 2;
			break;
		}
		PlayerBetFCallR(pbet, cpubet, pbalance);
		Render(dat, 500, 590, pindex[0]);
		Render(dat, 400, 590, pindex[1]);
		Render(dat, 500, 100, 0);
		Render(dat, 400, 100, 0);
		for (int i = 0; i < 5; i++) {
			if (openindex[i] != 0) {
				Render(dat, 200 + 100 * i, 250, openindex[i]);
			}
		}
		FsSwapBuffers();
		FsSleep(10);
	}
}

int praise(int pbet, int cpubet, int pbalance, const int pindex[2], const int cpuindex[2], const int openindex[2]) {
	playerraise(pbet, cpubet, pbalance);
	FsSwapBuffers();
	FsSleep(20);
	int amount[5] = { -1 }, count = 0, bet = 0;
	for (;;) {
		FsPollDevice();
		auto lastKey = FsInkey();
		if (count > 5) {
			break;
		}
		if (lastKey - FSKEY_0 <= 9 && lastKey - FSKEY_0 >= 0) {
			amount[count] = lastKey - FSKEY_0;
			count++;
		}
		else if (FSKEY_ENTER == lastKey) {
			break;
		}
		FsPushOnPaintEvent();
		FsSleep(10);
	}
	for (int i = 0; i < count; i++) {
		bet += amount[i] * pow(10, count - 1 - i);
	}
	playertag(pbet, cpubet, pbalance);
	string s = to_string(bet);
	char const* betamount = s.c_str();
	glColor3ub(0, 0, 128);
	glRasterPos2i(300, 300);
	YsGlDrawFontBitmap16x20("Add $");
	glRasterPos2i(400, 300);
	YsGlDrawFontBitmap16x20(betamount);
	FsSwapBuffers();
	FsSleep(2000);
	return bet;
}

//Random number generator
int randnum(int upper) {
	int num = rand() % upper;
	return num;
}

void player::pbalance(int pbalance, int pbet) {
	pmoney = pbalance - pbet;
}
int player::getScore() const {
	return pscore;
}

int player::getMoney() const {
	return pmoney;
}
void player::addcard(int position, int rank, int suit) {
	pcards[position].setSuit(suit);
	pcards[position].setRank(rank);
}
void player::printcard() const {
	int i = 0;
	std::cout << "Player Cards: " << endl;
	while (pcards[i].getRank() != 0 && i < 7) {
		pcards[i].print();
		i++;
	}
}
void player::sort() {
	int temprank = 0;
	int tempsuit = 0;
	for (int i = 0; i <= 4; i++) {
		for (int j = i + 1; j <= 4; j++) {
			if ((pcards[j].getRank() < pcards[i].getRank() && pcards[j].getRank() != 0 && pcards[i].getRank() != 0 && pcards[j].getRank() != 1) || (pcards[i].getRank() == 1 && pcards[j].getRank() != 0)) {
				temprank = pcards[i].getRank();
				tempsuit = pcards[i].getSuit();
				pcards[i].setRank(pcards[j].getRank());
				pcards[i].setSuit(pcards[j].getSuit());
				pcards[j].setRank(temprank);
				pcards[j].setSuit(tempsuit);
			}
		}
	}
}
void player::addscore(int p) {
	if (pscore != p) {
		pscore = pscore + p;
	}
}
int player::checkorraise(bool& raise, int onecpubet, int pbet, int cpubet, const int pindex[2], const int cpuindex[2], const int openindex[2], int pbalance, MainData& dat) {
	int chr = 0, onepbet = 0;
	bool validba = false, validnum = false;
	chr = playerselection2(pbet, cpubet, pbalance, pindex, cpuindex, openindex, dat);
	while (validnum == false) {
		if (chr == 1) {
			playercheck(pbet, cpubet, pbalance);
			FsSwapBuffers();
			FsSleep(2000);
			std::cout << "Player Check!" << endl;
			pmoney -= onecpubet;
			raise = false;
			return onecpubet;
		}
		else if (chr == 2) {
			playerraise(pbet, cpubet, pbalance);
			FsSwapBuffers();
			FsSleep(2000);
			std::cout << "Player Raise!" << endl;
			while (validba == false) {
				onepbet = praise(pbet, cpubet, pbalance, pindex, cpuindex, openindex);
				//onepbet += onecpubet;
				if (onepbet <= pmoney) {
					validba = true;
					raise = true;
					pmoney -= onepbet;
					return onepbet;
				}
				else {

					std::cout << "Not enough balance!" << endl;
					playertag(pbet, cpubet, pbalance);
					glColor3ub(255, 0, 0);
					glRasterPos2i(250, 300);
					YsGlDrawFontBitmap16x20("Not Enough Money!");
					FsSwapBuffers();
					FsSleep(2000);
				}
			}
		}
		else {
			std::cout << "Wrong Input!" << endl;
			std::cout << "Check(0) or Raise(1): ";
			cin >> chr;
		}
	}
}

int player::fcheckorraise(bool& raise, int onecpubet, int pbet, int cpubet, const int pindex[2], const int cpuindex[2], const int openindex[2], int pbalance, MainData& dat) {
	int chr = 0, onepbet = 0;
	bool validba = false, validnum = false;
	if (raise == true) {
		chr = playerselection3(pbet, cpubet, pbalance, pindex, cpuindex, openindex, dat);
	}
	else {
		chr = playerselection(pbet, cpubet, pbalance, pindex, cpuindex, openindex, dat);
	}

	std::cout << "Fold(0), Check(1) or Raise(2): \n";
	while (validnum == false) {
		if (chr == 1 && raise != true) {
			playercheck(pbet, cpubet, pbalance);
			FsSwapBuffers();
			FsSleep(2000);
			std::cout << "Player Check!" << endl;
			pmoney -= onecpubet;
			raise = false;
			return onecpubet;
		}
		else if (chr == 1 && raise == true) {
			playercall(pbet, cpubet, pbalance);
			FsSwapBuffers();
			FsSleep(2000);
			std::cout << "Player Check!" << endl;
			pmoney -= onecpubet;
			raise = false;
			return onecpubet;
		}
		else if (chr == 0) {
			cpuwin(pbet, cpubet, pbalance);
			FsSwapBuffers();
			FsSleep(2000);
			std::cout << "Player Fold! CPU Win!" << endl;
			pmoney -= cpubet;
			raise = false;
			return -1;
		}
		else if (chr == 2) {
			std::cout << "Player Raise!" << endl;
			playerraise(pbet, cpubet, pbalance);
			FsSwapBuffers();
			FsSleep(2000);
			while (validba == false) {
				onepbet = praise(pbet, cpubet, pbalance, pindex, cpuindex, openindex);
				//onepbet += onecpubet;
				if (onepbet <= pmoney) {
					validba = true;
					raise = true;
					pmoney -= onepbet;
					return onepbet;
				}
				else {
					std::cout << "Not enough balance!" << endl;
					std::cout << "Not enough balance!" << endl;
					playertag(pbet, cpubet, pbalance);
					glColor3ub(255, 0, 0);
					glRasterPos2i(250, 300);
					YsGlDrawFontBitmap16x20("Not Enough Money!");
					FsSwapBuffers();
					FsSleep(2000);
				}
			}
		}
		else {
			std::cout << "Wrong Input!" << endl;
			std::cout << "Check(0) or Raise(1): ";
			cin >> chr;
		}
	}
}

player::player() {

}

player::~player() {
	pmoney = 0;
	pscore = 0;
}

void Cpu::cpubalance(int cpubalance, int cpubet) {
	cpumoney = cpubalance - cpubet;
}

int Cpu::getScore() const {
	return cpuscore;
}

int Cpu::getMoney() const {
	return cpumoney;
}

void Cpu::addcard(int position, int rank, int suit) {
	cpucards[position].setRank(rank);
	cpucards[position].setSuit(suit);
}

void Cpu::printcard() const {
	int i = 0;
	std::cout << "CPU Cards: " << endl;
	while (cpucards[i].getRank() != 0 && i < 7) {
		cpucards[i].print();
		i++;
	}
}

void Cpu::sort() {
	int temprank = 0;
	int tempsuit = 0;
	for (int i = 0; i <= 4; i++) {
		for (int j = i + 1; j <= 4; j++) {
			if ((cpucards[j].getRank() < cpucards[i].getRank() && cpucards[j].getRank() != 0 && cpucards[i].getRank() != 0 && cpucards[j].getRank() != 1) || (cpucards[i].getRank() == 1 && cpucards[j].getRank() != 0)) {
				temprank = cpucards[i].getRank();
				tempsuit = cpucards[i].getSuit();
				cpucards[i].setRank(cpucards[j].getRank());
				cpucards[i].setSuit(cpucards[j].getSuit());
				cpucards[j].setRank(temprank);
				cpucards[j].setSuit(tempsuit);
			}
		}
	}
}

void Cpu::addscore(int p) {
	if (cpuscore != p) {
		cpuscore = cpuscore + p;
	}
}

bool Cpu::callorfold(int round, int pscore) const {
	if (round == 5) {
		if (pscore > cpuscore) {
			int randomnr = randnum(10);
			//20% CPU Call on a losing game
			return randomnr < 2;
		}
		else {
			int randomnr = randnum(10);
			// 80% CPU Call on a winning game
			return randomnr < 8;
		}
	}
	else {
		if (pscore > cpuscore) {
			int randomnr = randnum(10);
			// 40% CPU Call when Score lower
			return randomnr < 4;
		}
		else if (pscore == cpuscore && pscore != 0 && cpuscore != 0) {
			int randomnr = randnum(10);
			// 50% CPU Call on equal score
			return randomnr < 5;
		}
		else {
			int randomnr = randnum(100);
			// 99% CPU Call when score higher or both score 0
			return randomnr < 99;
		}
	}
}

int Cpu::ifraise(int pscore, int pmoney) const {
	//When CPU has less asset
	if (getMoney() < pmoney) {
		if (pscore > cpuscore) {
			int randomnr = randnum(10);
			// 20% CPU Bluff
			if (randomnr < 2) {
				// If raise, raise amount is balance/1000
				int raisel = randnum(getMoney() / 2000);
				if (raisel > 50) {
					raisel = 50;
				}
				return raisel;
			}
			else return 0;
		}
		else if (pscore == cpuscore && pscore != 0 && cpuscore != 0) {
			int randomnr = randnum(10);
			// 30% CPU Raise on same score
			if (randomnr < 3) {
				// If raise, raise amount is balance/800
				int raisee = randnum(getMoney() / 1800);
				if (raisee > 80) {
					raisee = 80;
				}
				return raisee;
			}
			else return 0;
		}
		else {
			int randomnr = randnum(10);
			// 50% CPU raise on higher score
			if (randomnr < 5) {
				// If raise, raise amount is balance/500
				int raiseh = randnum(getMoney() / 1500);
				if (raiseh > 100) {
					raiseh = 100;
				}
				return raiseh;
			}
			else return 0;
		}
	}
	//CPU has more than or same asset as player
	else if (getMoney() >= pmoney) {
		if (pscore > cpuscore) {
			int randomnr = randnum(10);
			// 30% CPU Bluff
			if (randomnr < 3) {
				// If raise, raise amount is balance/1800
				int raisel = randnum(getMoney() / 1800);
				if (raisel > 50) {
					raisel = 50;
				}
				return raisel;
			}
			else return 0;
		}
		else if (pscore == cpuscore && !pscore == 0 && !cpuscore == 0) {
			int randomnr = randnum(10);
			// 50% CPU Raise on same score
			if (randomnr < 5) {
				// If raise, raise amount is balance/1600
				int raisee = randnum(getMoney() / 1600);
				if (raisee > 90) {
					raisee = 90;
				}
				return raisee;
			}
			else return 0;
		}
		else {
			int randomnr = randnum(10);
			// 70% CPU Raise on higher score
			if (randomnr < 7) {
				// If raise, raise amount is balance/1400
				int raiseh = randnum(getMoney() / 1400);
				if (raiseh > 120) {
					raiseh = 120;
				}
				return raiseh;
			}
			else return 0;
		}
	}
}

Cpu::Cpu() {

}
Cpu::~Cpu() {
	cpumoney = 0;
	cpuscore = 0;
}

int pairs(Card cards[7]) {
	int i = 0;
	int count = 0;
	while (cards[i].getRank() != 0 && i < 7) {
		if (cards[i].getRank() == cards[i + 1].getRank() && cards[i].getRank() != 0 && cards[i + 1].getRank() != 0) {
			i = i + 2;
			count++;
		}
		else {
			i++;
		}
	}
	return count;
}

int nofkinds(Card cards[7]) {
	int count = 0;
	for (int i = 0; i <= 3; i++) {
		if (cards[i].getRank() == cards[i + 1].getRank() && cards[i + 1].getRank() == cards[i + 2].getRank() && cards[i].getRank() != 0 && cards[i + 1].getRank() != 0 && cards[i + 2].getRank() != 0)
			count++;
	}
	if (count == 2) {
		return 6;
	}
	else if (count == 1) {
		return 3;
	}
	return 0;
}

int straight(Card cards[7]) {
	int count = 0;
	for (int i = 0; i < 4; i++) {
		if (cards[i].getRank() + 1 == cards[i + 1].getRank()) {
			count++;
			continue;
		}
		if (cards[i].getRank() == cards[i + 1].getRank()) {
			continue;
		}
		else if (cards[i].getRank() == 13 && cards[i + 1].getRank() == 1) {
			count++;
			continue;
		}
		else {
			return 0;
		}
	}
	if (count == 4) {
		return 4;
	}
}
int fullhouse(Card cards[7]) {
	if (cards[0].getRank() == cards[1].getRank() && cards[1].getRank() == cards[2].getRank() && cards[2].getRank() == cards[3].getRank() && (cards[4].getRank() == cards[5].getRank() || cards[5].getRank() == cards[6].getRank())) {
		return 5;
	}
	else if (cards[1].getRank() == cards[2].getRank() && cards[2].getRank() == cards[3].getRank() && cards[3].getRank() == cards[4].getRank() && (cards[5].getRank() == cards[6].getRank())) {
		return 5;
	}
	else if (cards[2].getRank() == cards[3].getRank() && cards[3].getRank() == cards[4].getRank() && cards[4].getRank() == cards[5].getRank() && (cards[0].getRank() == cards[1].getRank())) {
		return 5;
	}
	else if (cards[3].getRank() == cards[4].getRank() && cards[4].getRank() == cards[5].getRank() && cards[5].getRank() == cards[6].getRank() && (cards[0].getRank() == cards[1].getRank() || cards[1].getRank() == cards[2].getRank())) {
		return 5;
	}
	else {
		return 0;
	}

}
void tiebreaker(int& cpupoints, int& ppoints, Card ccards[7], Card pcards[7]) {
	if (cpupoints == 0 || cpupoints == 4) {
		if (ccards[6].getRank() > pcards[6].getRank() && pcards[6].getRank() != 1) {
			cpupoints++;
		}
		else if (ccards[6].getRank() < pcards[6].getRank() && ccards[6].getRank() != 1) {
			ppoints++;
		}
		else if (ccards[6].getRank() != pcards[6].getRank() && ccards[6].getRank() == 1) {
			cpupoints++;
		}
		else if (ccards[6].getRank() != pcards[6].getRank() && pcards[6].getRank() == 1) {
			ppoints++;
		}
		else if (ccards[6].getRank() == pcards[6].getRank() && ccards[5].getRank() > pcards[5].getRank()) {
			cpupoints++;
		}
		else if (ccards[6].getRank() == pcards[6].getRank() && ccards[5].getRank() < pcards[5].getRank()) {
			ppoints++;
		}
	}
	else {
		int cpumulti = 0;
		int pmulti = 0;
		int count = 0;
		for (int i = 0; i < 5; i++) {
			if (ccards[i].getRank() == ccards[i + 1].getRank()) {
				if (cpumulti < ccards[i].getRank()) {
					cpumulti = ccards[i].getRank();
				}
			}
			if (pcards[i].getRank() == pcards[i + 1].getRank()) {
				if (pmulti < pcards[i].getRank()) {
					pmulti = pcards[i].getRank();
				}
			}
		}
		if (cpumulti == 1) {
			cpumulti = 14;
		}
		if (pmulti == 1) {
			pmulti = 14;
		}
		if (cpumulti > pmulti) {
			cpupoints++;
		}
		else if (cpumulti == pmulti) {
			if (ccards[6].getRank() > pcards[6].getRank() && pcards[6].getRank() != 1) {
				cpupoints++;
			}
			else if (ccards[6].getRank() < pcards[6].getRank() && ccards[6].getRank() != 1) {
				ppoints++;
			}
			else if (ccards[6].getRank() != pcards[6].getRank() && ccards[6].getRank() == 1) {
				cpupoints++;
			}
			else if (ccards[6].getRank() != pcards[6].getRank() && pcards[6].getRank() == 1) {
				ppoints++;
			}
			else if (ccards[6].getRank() == pcards[6].getRank() && ccards[5].getRank() > pcards[5].getRank()) {
				cpupoints++;
			}
			else if (ccards[6].getRank() == pcards[6].getRank() && ccards[5].getRank() < pcards[5].getRank()) {
				ppoints++;
			}
		}
		else {
			ppoints++;
		}
	}
}

int playpokerhand(int pbalance, int cpubalance, MainData& dat) {
	int option = 0;
	int money = pbalance;
	srand(time(NULL));
	Cpu cpu;
	player player;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	playertag(0, 0, money);
	bool play = true;
	while (play == true) {
		int round = 0, pscore = 0, pmoney = 0, cpumoney = 0, cpubet = 0, pbet = 0, onecpubet = 0, onepbet = 0, chfr = 0, pindex[2] = { 0 }, cpuindex[2] = { 0 }, openindex[5] = { 0 };
		bool fold = false, raise = false;
		Deck deck;
		deck.shuffleDeck();
		int cpunum = 0; int pnum = 0; int dnum = 0; int cpupoints = 0; int ppoints = 0;
		cpu.cpubalance(cpubalance, cpubet);
		player.pbalance(pbalance, pbet);
		//dealer deal first two cards to each player
		//for (;;) {

		for (int i = 0; i < 2; i++) {
			cpunum = randnum(52);
			while (deck.getCards()[cpunum].getRank() == 0) {
				cpunum = randnum(52);
			}
			cpu.addcard(i, deck.getCards()[cpunum].getRank(), deck.getCards()[cpunum].getSuit());
			deck.removecard(cpunum);
			pnum = randnum(52);
			while (deck.getCards()[pnum].getRank() == 0) {
				pnum = randnum(52);
			}
			player.addcard(i, deck.getCards()[pnum].getRank(), deck.getCards()[pnum].getSuit());
			deck.removecard(pnum);
			round++;
			pindex[i] = getIndexForGraphics(player.pcards[i]);
			cpuindex[i] = getIndexForGraphics(cpu.cpucards[i]);
		}
		//Player and CPU put initial bet $10
		cpubet = 10, pbet = 10;
		cpu.cpubalance(cpubalance, cpubet);
		player.pbalance(pbalance, pbet);

		playertag(pbet, cpubet, player.getMoney());
		Render(dat, 500, 590, pindex[0]);
		Render(dat, 400, 590, pindex[1]);
		Render(dat, 500, 100, 0);
		Render(dat, 400, 100, 0);
		FsSwapBuffers();
		FsSleep(20);
		//dealer deal one card each round
		for (int j = 0; j < 5; j++) {
			if (fold == true) {
				break;
			}
			dnum = randnum(52);
			while (deck.getCards()[dnum].getRank() == 0) {
				dnum = randnum(52);
			}
			cpu.addcard(2 + j, deck.getCards()[dnum].getRank(), deck.getCards()[dnum].getSuit());
			openindex[j] = getIndexForGraphics(cpu.cpucards[2 + j]);
			player.addcard(2 + j, deck.getCards()[dnum].getRank(), deck.getCards()[dnum].getSuit());
			deck.removecard(dnum);
			player.sort();
			cpu.sort();
			cpu.printcard();
			player.printcard();
			cpupoints = max(pairs(cpu.cpucards), max(nofkinds(cpu.cpucards), max(straight(cpu.cpucards), fullhouse(cpu.cpucards))));
			ppoints = max(pairs(player.pcards), max(nofkinds(player.pcards), max(straight(player.pcards), fullhouse(player.pcards))));
			cpu.addscore(cpupoints);
			player.addscore(ppoints);
			pscore = player.getScore();
			if (cpu.callorfold(round, pscore) == false) {
				fold = true;
				std::cout << "CPU Fold! Player Win!" << endl;
				playerwin(pbet, cpubet, pbalance);
				Render(dat, 500, 590, pindex[0]);
				Render(dat, 400, 590, pindex[1]);
				Render(dat, 500, 100, cpuindex[0]);
				Render(dat, 400, 100, cpuindex[1]);
				for (int i = 0; i < 5; i++) {
					if (openindex[i] != 0) {
						Render(dat, 200 + 100 * i, 250, openindex[i]);
					}
				}
				FsSwapBuffers();
				FsSleep(2000);
				int newpbet = -1 * (pbet + cpubet);
				pmoney = player.getMoney();
				player.pbalance(pmoney, newpbet);
			}
			else {
				pmoney = player.getMoney();
				cpumoney = cpu.getMoney();
				pscore = player.getScore();
				onecpubet = cpu.ifraise(pscore, pmoney);
				cpubet += onecpubet;
				cpu.cpubalance(cpubalance, cpubet);
				if (pmoney <= 0) {
					cpuwin(pbet, cpubet, player.getMoney());
					Render(dat, 500, 590, pindex[0]);
					Render(dat, 400, 590, pindex[1]);
					Render(dat, 500, 100, cpuindex[0]);
					Render(dat, 400, 100, cpuindex[1]);
					for (int i = 0; i < 5; i++) {
						if (openindex[i] != 0) {
							Render(dat, 200 + 100 * i, 250, openindex[i]);
						}
					}
					FsSwapBuffers();
					FsSleep(2000);
					std::cout << "CPU Win!" << endl;
					int newcpubet = -1 * (pbet + cpubet);
					cpu.cpubalance(cpumoney, newcpubet);
					fold = true;
					break;
				}
				if (onecpubet == 0) {
					std::cout << "CPU Check!" << endl;
					cpucheck(pbet, cpubet, player.getMoney());
					Render(dat, 500, 590, pindex[0]);
					Render(dat, 400, 590, pindex[1]);
					Render(dat, 500, 100, 0);
					Render(dat, 400, 100, 0);
					for (int i = 0; i < 5; i++) {
						if (openindex[i] != 0) {
							Render(dat, 200 + 100 * i, 250, openindex[i]);
						}
					}
					FsSwapBuffers();
					FsSleep(2000);
					chfr = playerselection(pbet, cpubet, player.getMoney(), pindex, cpuindex, openindex, dat);
					//cin >> chfr;
					if (chfr == 0 || pmoney <= 0) {
						cpuwin(pbet, cpubet, player.getMoney());
						Render(dat, 500, 590, pindex[0]);
						Render(dat, 400, 590, pindex[1]);
						Render(dat, 500, 100, cpuindex[0]);
						Render(dat, 400, 100, cpuindex[1]);
						for (int i = 0; i < 5; i++) {
							if (openindex[i] != 0) {
								Render(dat, 200 + 100 * i, 250, openindex[i]);
							}
						}
						FsSwapBuffers();
						FsSleep(2000);
						std::cout << "CPU Win!" << endl;
						int newcpubet = -1 * (pbet + cpubet);
						cpu.cpubalance(cpumoney, newcpubet);
						fold = true;
						break;
					}
					else if (chfr == 1) {
						playercheck(pbet, cpubet, player.getMoney());
						Render(dat, 500, 590, pindex[0]);
						Render(dat, 400, 590, pindex[1]);
						Render(dat, 500, 100, 0);
						Render(dat, 400, 100, 0);
						for (int i = 0; i < 5; i++) {
							if (openindex[i] != 0) {
								Render(dat, 200 + 100 * i, 250, openindex[i]);
							}
						}
						FsSwapBuffers();
						FsSleep(2000);
						std::cout << "Player Check!" << endl;
						pbet += onecpubet;
						player.pbalance(pbalance, pbet);
					}
					else if (chfr == 2) {
						while (raise == false) {
							playerraise(pbet, cpubet, player.getMoney());
							Render(dat, 500, 590, pindex[0]);
							Render(dat, 400, 590, pindex[1]);
							Render(dat, 500, 100, 0);
							Render(dat, 400, 100, 0);
							for (int i = 0; i < 5; i++) {
								if (openindex[i] != 0) {
									Render(dat, 200 + 100 * i, 250, openindex[i]);
								}
							}
							FsSwapBuffers();
							FsSleep(2000);
							onepbet = praise(pbet, cpubet, player.getMoney(), pindex, cpuindex, openindex);
							//onepbet += onecpubet;
							if (onepbet <= pbalance) {
								raise = true;
							}
							else {
								std::cout << "Not enough balance!" << endl;
								playertag(pbet, cpubet, pbalance);
								glColor3ub(255, 0, 0);
								glRasterPos2i(250, 300);
								YsGlDrawFontBitmap16x20("Not Enough Money!");
								FsSwapBuffers();
								FsSleep(2000);
							}
						}
						pbet += onepbet;
						std::cout << "Player Raise to: " << pbet << endl;
						player.pbalance(pbalance, pbet);
						do {
							pmoney = player.getMoney();
							cpumoney = cpu.getMoney();
							pscore = player.getScore();
							onecpubet = cpu.ifraise(pscore, pmoney);
							cpubet = onecpubet + pbet;
							cpu.cpubalance(cpubalance, cpubet);
							if (pmoney <= 0) {
								cpuwin(pbet, cpubet, player.getMoney());
								Render(dat, 500, 590, pindex[0]);
								Render(dat, 400, 590, pindex[1]);
								Render(dat, 500, 100, cpuindex[0]);
								Render(dat, 400, 100, cpuindex[1]);
								for (int i = 0; i < 5; i++) {
									if (openindex[i] != 0) {
										Render(dat, 200 + 100 * i, 250, openindex[i]);
									}
								}
								FsSwapBuffers();
								FsSleep(2000);
								std::cout << "CPU Win!" << endl;
								int newcpubet = -1 * (pbet + cpubet);
								cpu.cpubalance(cpumoney, newcpubet);
								fold = true;
								break;
							}
							if (onecpubet == 0) {
								cpucall(pbet, cpubet, player.getMoney());
								Render(dat, 500, 590, pindex[0]);
								Render(dat, 400, 590, pindex[1]);
								Render(dat, 500, 100, 0);
								Render(dat, 400, 100, 0);
								for (int i = 0; i < 5; i++) {
									if (openindex[i] != 0) {
										Render(dat, 200 + 100 * i, 250, openindex[i]);
									}
								}
								FsSwapBuffers();
								FsSleep(2000);
								std::cout << "CPU Check!" << endl;
								raise = false;
							}
							else {
								cpuraise(pbet, cpubet, player.getMoney());
								Render(dat, 500, 590, pindex[0]);
								Render(dat, 400, 590, pindex[1]);
								Render(dat, 500, 100, 0);
								Render(dat, 400, 100, 0);
								for (int i = 0; i < 5; i++) {
									if (openindex[i] != 0) {
										Render(dat, 200 + 100 * i, 250, openindex[i]);
									}
								}
								FsSwapBuffers();
								FsSleep(2000);
								std::cout << "CPU Raise to $ " << cpubet << endl;
								raise = true;
								onepbet = player.checkorraise(raise, onecpubet, pbet, cpubet, pindex, cpuindex, openindex, player.getMoney(), dat);
								pbet += onepbet;
							}

						} while (raise == true);
					}
				}
				else {
					std::cout << "CPU Raise to $" << cpubet << endl;
					raise = true;
					cpuraise(pbet, cpubet, player.getMoney());
					Render(dat, 500, 590, pindex[0]);
					Render(dat, 400, 590, pindex[1]);
					Render(dat, 500, 100, 0);
					Render(dat, 400, 100, 0);
					for (int i = 0; i < 5; i++) {
						if (openindex[i] != 0) {
							Render(dat, 200 + 100 * i, 250, openindex[i]);
						}
					}
					FsSwapBuffers();
					FsSleep(2000);
					int count = 0;
					do {
						if (pmoney <= 0) {
							cpuwin(pbet, cpubet, player.getMoney());
							Render(dat, 500, 590, pindex[0]);
							Render(dat, 400, 590, pindex[1]);
							Render(dat, 500, 100, cpuindex[0]);
							Render(dat, 400, 100, cpuindex[1]);
							for (int i = 0; i < 5; i++) {
								if (openindex[i] != 0) {
									Render(dat, 200 + 100 * i, 250, openindex[i]);
								}
							}
							FsSwapBuffers();
							FsSleep(2000);
							std::cout << "CPU Win!" << endl;
							int newcpubet = -1 * (pbet + cpubet);
							cpu.cpubalance(cpumoney, newcpubet);
							fold = true;
							break;
						}
						if (count == 0) {
							onepbet = player.fcheckorraise(raise, onecpubet, pbet, cpubet, pindex, cpuindex, openindex, player.getMoney(), dat);
						}
						else {
							onepbet = player.checkorraise(raise, onecpubet, pbet, cpubet, pindex, cpuindex, openindex, player.getMoney(), dat);
						}
						if (onepbet == -1 || pmoney <= 0) {
							cpuwin(pbet, cpubet, player.getMoney());
							Render(dat, 500, 590, pindex[0]);
							Render(dat, 400, 590, pindex[1]);
							Render(dat, 500, 100, cpuindex[0]);
							Render(dat, 400, 100, cpuindex[1]);
							for (int i = 0; i < 5; i++) {
								if (openindex[i] != 0) {
									Render(dat, 200 + 100 * i, 250, openindex[i]);
								}
							}
							FsSwapBuffers();
							FsSleep(2000);
							std::cout << "CPU Win!" << endl;
							int newcpubet = -1 * (pbet + cpubet);
							cpu.cpubalance(cpumoney, newcpubet);
							fold = true;
							break;
						}
						pbet += onepbet;
						std::cout << "Player Raise to: " << pbet << endl;
						if (raise == true) {
							pmoney = player.getMoney();
							cpumoney = cpu.getMoney();
							pscore = player.getScore();
							onecpubet = cpu.ifraise(pscore, pmoney);
							cpubet = onecpubet + pbet;
							cpu.cpubalance(cpubalance, cpubet);
							if (onecpubet == 0) {
								cpucall(pbet, cpubet, player.getMoney());
								Render(dat, 500, 590, pindex[0]);
								Render(dat, 400, 590, pindex[1]);
								Render(dat, 500, 100, 0);
								Render(dat, 400, 100, 0);
								for (int i = 0; i < 5; i++) {
									if (openindex[i] != 0) {
										Render(dat, 200 + 100 * i, 250, openindex[i]);
									}
								}
								FsSwapBuffers();
								FsSleep(2000);
								std::cout << "CPU Call!" << endl;
								raise = false;
							}
							else {
								cpuraise(pbet, cpubet, player.getMoney());
								Render(dat, 500, 590, pindex[0]);
								Render(dat, 400, 590, pindex[1]);
								Render(dat, 500, 100, 0);
								Render(dat, 400, 100, 0);
								for (int i = 0; i < 5; i++) {
									if (openindex[i] != 0) {
										Render(dat, 200 + 100 * i, 250, openindex[i]);
									}
								}
								FsSwapBuffers();
								FsSleep(2000);
								std::cout << "CPU Raise to $ " << cpubet << endl;
								raise = true;
							}
						}
						count++;
					} while (raise == true);
				}
			}
			round++;
		}

		player.sort();
		cpu.sort();
		cpu.printcard();
		player.printcard();
		if (round == 7) {
			cpupoints = max(pairs(cpu.cpucards), max(nofkinds(cpu.cpucards), max(straight(cpu.cpucards), fullhouse(cpu.cpucards))));
			ppoints = max(pairs(player.pcards), max(nofkinds(player.pcards), max(straight(player.pcards), fullhouse(player.pcards))));
			if (cpupoints == ppoints) {
				tiebreaker(cpupoints, ppoints, cpu.cpucards, player.pcards);
			}
			std::cout << "Cpu: " << cpupoints << "\nPlayer: " << ppoints << endl;
			if (cpupoints > ppoints || pmoney <= 0) {
				cpuwinf(pbet, cpubet, player.getMoney());
				Render(dat, 500, 590, pindex[0]);
				Render(dat, 400, 590, pindex[1]);
				Render(dat, 500, 100, cpuindex[0]);
				Render(dat, 400, 100, cpuindex[1]);
				for (int i = 0; i < 5; i++) {
					if (openindex[i] != 0) {
						Render(dat, 200 + 100 * i, 250, openindex[i]);
					}
				}
				FsSwapBuffers();
				FsSleep(2000);
				std::cout << "CPU Win!" << endl;
				int newcpubet = -1 * pbet;
				cpu.cpubalance(cpubalance, newcpubet);
				player.pbalance(pbalance, pbet);
				cpubalance = cpu.getMoney();
				pbalance = player.getMoney();

			}
			else {
				playerwinf(pbet, cpubet, player.getMoney());
				Render(dat, 500, 590, pindex[0]);
				Render(dat, 400, 590, pindex[1]);
				Render(dat, 500, 100, cpuindex[0]);
				Render(dat, 400, 100, cpuindex[1]);
				for (int i = 0; i < 5; i++) {
					if (openindex[i] != 0) {
						Render(dat, 200 + 100 * i, 250, openindex[i]);
					}
				}
				FsSwapBuffers();
				FsSleep(2000);
				std::cout << "Player Win!" << endl;
				int npbet = -1 * cpubet;
				cpu.cpubalance(cpubalance, cpubet);
				player.pbalance(pbalance, npbet);
				cpubalance = cpu.getMoney();
				pbalance = player.getMoney();
			}
		}
		else {
			cpubalance = cpu.getMoney();
			pbalance = player.getMoney();
		}
		dat.setMoney(-money + pbalance);
		for (;;) {
			FsPollDevice();
			auto key = FsInkey();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			if (key == FSKEY_N && pbalance > 10) {
				play = false;
				return 1;
			}
			else if (key == FSKEY_N && pbalance <= 10) {
				play = false;
				playertag(pbet, cpubet, player.getMoney());
				glColor3ub(255, 0, 0);
				glRasterPos2d(100, 700);
				YsGlDrawFontBitmap16x20("Not Enough Balance!Back to Main Menue");
				FsSwapBuffers();
				FsSleep(2000);
				return 2;
			}
			else if (key == FSKEY_M) {
				play = false;
				return 2;
			}
			else if (key == FSKEY_ESC) {
				play = false;
				return 0;
			}
			playertag(pbet, cpubet, player.getMoney());
			Render(dat, 500, 590, pindex[0]);
			Render(dat, 400, 590, pindex[1]);
			Render(dat, 500, 100, cpuindex[0]);
			Render(dat, 400, 100, cpuindex[1]);
			for (int i = 0; i < 5; i++) {
				if (openindex[i] != 0) {
					Render(dat, 200 + 100 * i, 250, openindex[i]);
				}
			}
			glColor3ub(255, 0, 0);
			glRasterPos2d(20, 650);
			YsGlDrawFontBitmap16x20("Money remaining: $");
			glRasterPos2d(310, 650);
			YsGlDrawFontBitmap16x20(dat.getMoneyChar().c_str());
			EndGameOptions();
			FsSwapBuffers();
			FsSleep(20);
		}
	}
	std::cout << "Player Balance: " << pbalance << "\nCPU Balance: " << cpubalance << endl;
	return option;
}
