#include <iostream>
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include "poker_hand.h"
using namespace std;

bool equals(const Card& c1, const Card& c2) {
	// comparing 2 cards

	return (c1.rank == c2.rank && c1.suit == c2.suit);
}

Deck merge(const Deck& d1, const Deck& d2)
{
	// merge two sorted decks (implementation of merge sort)

	Deck result(d1.cards.size() + d2.cards.size());
	int i = 0;
	int j = 0;
	Card winner;

	for (int k = 0; k < result.cards.size(); k++) {

		if (i == d1.cards.size()) {
			winner = d2.cards[j];
			result.cards[k] = winner;
			j++;
		}
		else if (j == d2.cards.size()) {
			winner = d1.cards[i];
			result.cards[k] = winner;
			i++;
		}

		else if (d1.cards[i].isGreater(d2.cards[j])) {
			winner = d2.cards[j];
			result.cards[k] = winner;
			j++;
		}
		else if (d2.cards[j].isGreater(d1.cards[i])) {
			winner = d1.cards[i];
			result.cards[k] = winner;
			i++;
		}
	}
	return result;
}

Deck mergeSort(const Deck& deck)
{

	if (deck.cards.size() == 0 || deck.cards.size() == 1) return deck;

	int mid = deck.cards.size() / 2;
	int size = deck.cards.size();

	Deck sub1 = deck.subDeck(0, mid - 1);
	Deck sub2 = deck.subDeck(mid, size - 1);

	sub1 = mergeSort(sub1);
	sub2 = mergeSort(sub2);

	Deck result = merge(sub1, sub2);
	return result;
}
Card::Card() {
	suit = 0;
	rank = 0;
}

Card::Card(int s, int r) {
	suit = s; rank = r;
}

void Card::print() const {
	vector<string> suits(4);
	vector<string> ranks(14);

	suits[0] = "Clubs";
	suits[1] = "Diamonds";
	suits[2] = "Hearts";
	suits[3] = "Spades";

	ranks[1] = "Ace";
	ranks[2] = "2";
	ranks[3] = "3";
	ranks[4] = "4";
	ranks[5] = "5";
	ranks[6] = "6";
	ranks[7] = "7";
	ranks[8] = "8";
	ranks[9] = "9";
	ranks[10] = "10";
	ranks[11] = "Jack";
	ranks[12] = "Queen";
	ranks[13] = "King";

	cout << ranks[rank] << "\t of \t" << suits[suit] << endl;
}


bool Card::isGreater(const Card& c2) const
{
	if (suit > c2.suit) return true;
	if (suit < c2.suit) return false;

	if (rank == 1 && c2.rank != 1) return true;
	if (rank != 1 && c2.rank == 1) return false;

	if (rank > c2.rank) return true;
	if (rank < c2.rank) return false;
	return false;
}

// Member functions for Deck class.

Deck::Deck(int n)
{
	vector<Card> temp(n);
	cards = temp;
}

Deck::Deck() {
	vector <Card> tmp(52);
	cards = tmp;

	int i = 0;
	for (int suit = 0; suit < 4; suit++) {
		for (int r = 1; r < 14; r++) {
			cards[i].suit = suit;
			cards[i].rank = r;
			i++;
		}
	}
}
void Deck::removecard(int p) {
	cards[p].rank = 0;
}
void Deck::print() const {
	for (int i = 0; i < cards.size(); i++) {
		cards[i].print();
	}
}

int Deck::find(const Card& c) const
{
	for (int i = 0; i < cards.size(); i++) {
		if (equals(cards[i], c)) return true;
	}
	return false;
}

void Deck::shuffleDeck()
{
	for (int i = 0; i < cards.size(); i++) {
		int ind = rand() % (cards.size() - i) + i;
		Card tmp = cards[ind];
		cards[ind] = cards[i];
		cards[i] = tmp;
	}
}
Deck Deck::subDeck(int low, int high) const
{
	Deck sub(high - low + 1);

	for (int i = 0; i < sub.cards.size(); i++) {
		sub.cards[i] = cards[low + i];
	}
	return sub;
}

int Deck::countHand() const
{
	int sum = 0;
	for (int i = 0; i < cards.size(); i++) {
		if (cards[i].rank >= 11) {
			sum += 10;
		}
		else if (cards[i].rank == 1) {
			sum += 11;
			if (sum > 21) {
				sum -= 11;
				sum++;
			}
		}
		else {
			sum += cards[i].rank;
		}
	}
	return sum;
}

void Deck::printDealerHand(bool both = true) const
{
	if (!both) {
		cout << "1: ";
		cards[0].print();
		cout << "2: CARD HIDDEN\n\n";
	}
	else {
		for (int i = 0; i < cards.size(); i++) {
			cout << i + 1 << ": ";
			cards[i].print();
		}
	}
}

void Deck::addCard(const Deck& sub, const Deck& deck)
{
	int size = cards.size();
	int otherHandSize = sub.cards.size();

	int ind = size + otherHandSize;

	int randomInd = rand() % (deck.cards.size() - ind) + ind;

	Card randomCard = deck.cards[randomInd];

	cards.push_back(randomCard);
}
//Random number generator
int randnum(int upper) {
	int num = rand() % upper;
	return num;
}
//Player Class
//class player {
//private:
//	int pbet = 0;
//	int pmoney = 0;
//	int pscore = 0;
//public:
//	Card pcards[5];
//	player();
//	~player();
//	void pbalance(int pbalance,int pbet);
//	int getScore() const;
//	int getMoney() const;
//	void addcard(int position, int rank, int suit);
//	void printcard() const;
//	void sort();
//	void addscore(int p);
//	int checkorraise(bool &raise, int onecpubet);
//};

void player::pbalance(int pbalance,int pbet) {
	pmoney = pbalance - pbet;
}
int player::getScore() const{
	return pscore;
}

int player::getMoney() const{
	return pmoney;
}
void player::addcard(int position, int rank, int suit) {
	pcards[position].rank = rank;
	pcards[position].suit = suit;
}
void player::printcard() const {
	int i = 0;
	cout << "Player Cards: " << endl;
	while (pcards[i].rank != 0 && i < 5) {
		pcards[i].print();
		i++;
	}
}
void player::sort() {
	int temprank = 0;
	int tempsuit = 0;
	for (int i = 0; i <= 4; i++) {
		for (int j = i + 1; j <= 4; j++) {
			if ((pcards[j].rank < pcards[i].rank && pcards[j].rank != 0 && pcards[i].rank != 0 && pcards[j].rank != 1) || (pcards[i].rank == 1 && pcards[j].rank != 0)) {
				temprank = pcards[i].rank;
				tempsuit = pcards[i].suit;
				pcards[i].rank = pcards[j].rank;
				pcards[i].suit = pcards[j].suit;
				pcards[j].rank = temprank;
				pcards[j].suit = tempsuit;
			}
		}
	}
}
void player::addscore(int p) {
	if (pscore != p) {
		pscore = pscore + p;
	}
}
int player::checkorraise(bool& raise, int onecpubet) {
	int chr = 0, onepbet = 0;
	bool validba = false, validnum = false;
	cout << "Check(0) or Raise(1): ";
	cin >> chr;
	while (validnum == false) {
		if (chr == 0) {
			cout << "Player Check!" << endl;
			pmoney -= onecpubet;
			raise = false;
			return onecpubet;
		}
		else if (chr == 1) {
			cout << "Player Raise!" << endl;
			while (validba == false) {
				cout << "How much you add to CPU bet: ";
				cin >> onepbet;
				onepbet += onecpubet;
				if (onepbet <= pmoney) {
					validba = true;
					raise = true;
					pmoney -= onepbet;
					return onepbet;
				}
				else {
					cout << "Not enough balance!" << endl;
				}
			}
		}
		else {
			cout << "Wrong Input!" << endl;
			cout << "Check(0) or Raise(1): ";
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

//CPU Class
//class Cpu {
//private:
//	int cbet = 0;
//	int cpumoney = 0;
//	int cpuscore = 0;
//public:
//	Card cpucards[5];
//	Cpu();
//	~Cpu();
//	void cpubalance(int cpubalance, int cpubet);
//	int getScore() const;
//	int getMoney() const;
//	void addcard(int position, int rank, int suit);
//	void printcard() const;
//	void sort();
//	void addscore(int p);
//	bool callorfold(int round,int pscore) const;
//	int ifraise(int pscore,int pbalance) const;
//};

void Cpu::cpubalance(int cpubalance,int cpubet) {
	cpumoney = cpubalance - cpubet;
}

int Cpu::getScore() const{
	return cpuscore;
}

int Cpu::getMoney() const{
	return cpumoney;
}

void Cpu::addcard(int position, int rank, int suit) {
	cpucards[position].rank = rank;
	cpucards[position].suit = suit;
}

void Cpu::printcard() const{
	int i = 0;
	cout << "CPU Cards: " << endl;
	while (cpucards[i].rank != 0 && i < 5) {
		cpucards[i].print();
		i++;
	}
}

void Cpu::sort() {
	int temprank = 0;
	int tempsuit = 0;
	for (int i = 0; i <= 4; i++) {
		for (int j = i + 1; j <= 4; j++) {
			if ((cpucards[j].rank < cpucards[i].rank && cpucards[j].rank!=0 && cpucards[i].rank!=0 && cpucards[j].rank!= 1) || (cpucards[i].rank == 1 && cpucards[j].rank != 0)) {
				temprank = cpucards[i].rank;
				tempsuit = cpucards[i].suit;
				cpucards[i].rank = cpucards[j].rank;
				cpucards[i].suit = cpucards[j].suit;
				cpucards[j].rank = temprank;
				cpucards[j].suit = tempsuit;
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
			int randomnr = randnum(10);
			// 90% CPU Call when score higher or both score 0
			return randomnr < 9;
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
				// If raise, raise amount is balance/10
				int raisel = randnum(getMoney() / 10);
				return raisel;
			}
			else return 0;
		}
		else if (pscore == cpuscore && pscore != 0 && cpuscore != 0) {
			int randomnr = randnum(10);
			// 30% CPU Raise on same score
			if (randomnr < 3) {
				// If raise, raise amount is balance/8
				int raisee = randnum(getMoney() / 5);
				return raisee;
			}
			else return 0;
		}
		else {
			int randomnr = randnum(10);
			// 50% CPU raise on higher score
			if (randomnr < 5) {
				// If raise, raise amount is balance/5
				int raiseh = randnum(getMoney() / 5);
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
				// If raise, raise amount is balance/8
				int raisel = randnum(getMoney() / 8);
				return raisel;
			}
			else return 0;
		}
		else if (pscore == cpuscore && !pscore == 0 && !cpuscore == 0) {
			int randomnr = randnum(10);
			// 50% CPU Raise on same score
			if (randomnr < 5) {
				// If raise, raise amount is balance/6
				int raisee = randnum(getMoney() / 6);
				return raisee;
			}
			else return 0;
		}
		else {
			int randomnr = randnum(10);
			// 70% CPU Raise on higher score
			if (randomnr < 7) {
				// If raise, raise amount is balance/4
				int raiseh = randnum(getMoney() / 4);
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

int pairs(Card cards[5]) {
	int i = 0;
	int count = 0;
	while (cards[i].rank != 0 && i < 5) {
		if (cards[i].rank == cards[i+1].rank && cards[i].rank !=0 && cards[i+1].rank !=0) {
			i = i + 2;
			count++;
		}
		else {
			i++;
		}
	}
	return count;
}

int nofkinds(Card cards[5]) {
	int count = 0;
	for (int i = 0; i <= 2; i++) {
		if (cards[i].rank == cards[i + 1].rank && cards[i + 1].rank == cards[i + 2].rank && cards[i].rank!=0 && cards[i+1].rank != 0 && cards[i+2].rank != 0)
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

int straight(Card cards[5]) {
	int count = 0;
	for (int i = 0; i < 4; i++) {
		if (cards[i].rank + 1 == cards[i + 1].rank) {
			count++;
			continue;
		}
		else if (cards[i].rank == 13 && cards[i + 1].rank == 1) {
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
int fullhouse(Card cards[5]) {
	if (cards[0].rank == cards[1].rank && cards[1].rank == cards[2].rank && cards[3].rank == cards[4].rank) {
		return 5;
	}
	else if (cards[0].rank == cards[1].rank && cards[2].rank == cards[3].rank && cards[3].rank == cards[4].rank) {
		return 5;
	}
	else {
		return 0;
	}

}
void tiebreaker(int &cpupoints, int &ppoints, Card ccards[5], Card pcards[5]) {
	if (cpupoints == 0 || cpupoints == 4) {
		if (ccards[4].rank > pcards[4].rank && pcards[4].rank!=1) {
			cpupoints++;
		}
		else if (ccards[4].rank < pcards[4].rank && ccards[4].rank!=1) {
			ppoints++;
		}
		else if (ccards[4].rank != pcards[4].rank && ccards[4].rank == 1) {
			cpupoints++;
		}
		else if (ccards[4].rank != pcards[4].rank && pcards[4].rank == 1) {
			ppoints++;
		}
		else if (ccards[4].rank == pcards[4].rank && ccards[3].rank > pcards[3].rank) {
			cpupoints++;
		}
		else if (ccards[4].rank == pcards[4].rank && ccards[3].rank < pcards[3].rank) {
			ppoints++;
		}
	}
	else {
		int cpumulti = 0;
		int pmulti = 0;
		int count = 0;
		for (int i = 0; i < 5; i++) {
			if (ccards[i].rank == ccards[i + 1].rank) {
				if (cpumulti < ccards[i].rank) {
					cpumulti = ccards[i].rank;
				}
			}
			if (pcards[i].rank == pcards[i + 1].rank) {
				if (pmulti < pcards[i].rank) {
					pmulti = pcards[i].rank;
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
			if (ccards[4].rank > pcards[4].rank && pcards[4].rank != 1) {
				cpupoints++;
			}
			else if (ccards[4].rank < pcards[4].rank && ccards[4].rank != 1) {
				ppoints++;
			}
			else if (ccards[4].rank != pcards[4].rank && ccards[4].rank == 1) {
				cpupoints++;
			}
			else if (ccards[4].rank != pcards[4].rank && pcards[4].rank == 1) {
				ppoints++;
			}
			else if (ccards[4].rank == pcards[4].rank && ccards[3].rank > pcards[3].rank) {
				cpupoints++;
			}
			else if (ccards[4].rank == pcards[4].rank && ccards[3].rank < pcards[3].rank) {
				ppoints++;
			}
		}
		else {
			ppoints++;
		}
	}
}



void pokerhand(Cpu cpu,player player,int &pbalance,int &cpubalance) {
	int round = 0, pscore = 0, pmoney = 0, cpumoney = 0, cpubet = 0, pbet = 0, onecpubet = 0, onepbet = 0, chfr = 0;
	bool fold = false, raise = false;
	Deck deck;
	deck.shuffleDeck();
	int cpunum = 0; int pnum = 0; int dnum = 0; int cpupoints = 0; int ppoints = 0;
	cpu.cpubalance(cpubalance,cpubet);
	player.pbalance(pbalance,pbet);
	//dealer deal first two cards to each player
	for (int i = 0; i < 2; i++) {
		cpunum = randnum(52);
		while (deck.cards[cpunum].rank == 0) {
			cpunum = randnum(52);
		}
		cpu.addcard(i, deck.cards[cpunum].rank, deck.cards[cpunum].suit);
		deck.removecard(cpunum);
		pnum = randnum(52);
		while (deck.cards[pnum].rank == 0) {
			pnum = randnum(52);
		}
		player.addcard(i, deck.cards[pnum].rank, deck.cards[pnum].suit);
		deck.removecard(pnum);
		round++;
	}
	//Player and CPU put initial bet $10
	cpubet = 10, pbet = 10;
	cpu.cpubalance(cpubalance, cpubet);
	player.pbalance(pbalance, pbet);

	//dealer deal one card each round
	for (int j = 0; j < 3; j++) {
		if (fold == true) {
			break;
		}
		dnum = randnum(52);
		while (deck.cards[dnum].rank == 0) {
			dnum = randnum(52);
		}
		cpu.addcard(2+j, deck.cards[dnum].rank, deck.cards[dnum].suit);
		player.addcard(2+j, deck.cards[dnum].rank, deck.cards[dnum].suit);
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
		if (cpu.callorfold(round,pscore) == false) {
			fold = true;
			cout << "CPU Fold! Player Win!" << endl;
			pbet = -1*(pbet + cpubet);
			pmoney = player.getMoney();
			player.pbalance(pmoney, pbet);
		}
		else {
			pmoney = player.getMoney();
			cpumoney = cpu.getMoney();
			pscore = player.getScore();
			onecpubet = cpu.ifraise(pscore, pmoney);
			cpubet += onecpubet;
			cpu.cpubalance(cpubalance, cpubet);
			if (onecpubet == 0) {
				cout << "CPU Call!" << endl;
				cout << "Player Choose Fold(0) or Check(1) or Raise(2): ";
				cin >> chfr;
				if (chfr == 0) {
					cout << "CPU Win!" << endl;
					cpubet = -1 * (pbet + cpubet);
					cpu.cpubalance(cpumoney, cpubet);
					break;
				}
				else if (chfr == 1) {
					pbet += onecpubet;
					player.pbalance(pbalance, pbet);
				}
				else if (chfr == 2) {
					while (raise == false) {
						cout << "How much you add to CPU bet: ";
						cin >> onepbet;
						onepbet += onecpubet;
						if (onepbet <= pbalance) {
							raise = true;
						}
						else {
							cout << "Not enough balance!" << endl;
						}
					}
					pbet += onepbet;
					player.pbalance(pbalance, pbet);
					do {
						pmoney = player.getMoney();
						cpumoney = cpu.getMoney();
						pscore = player.getScore();
						onecpubet = cpu.ifraise(pscore, pmoney);
						cpubet = onecpubet + pbet;
						cpu.cpubalance(cpubalance, cpubet);
						if (onecpubet == 0) {
							cout << "CPU Check!" << endl;
							raise = false;
						}
						else {
							cout << "CPU Raise to $ " << cpubet << endl;
							raise = true;
							onepbet = player.checkorraise(raise, onecpubet);
							pbet += onepbet;
						}
					
					} while (raise == true);
				}
			}
			else {
				cout << "CPU Raise to $" << cpubet << endl;
				do {
					onepbet = player.checkorraise(raise, onecpubet);
					pbet += onepbet;
					if (raise == true) {
						pmoney = player.getMoney();
						cpumoney = cpu.getMoney();
						pscore = player.getScore();
						onecpubet = cpu.ifraise(pscore, pmoney);
						cpubet = onecpubet + pbet;
						cpu.cpubalance(cpubalance, cpubet);
						if (onecpubet == 0) {
							cout << "CPU Check!" << endl;
							raise = false;
						}
						else {
							cout << "CPU Raise to $ " << cpubet << endl;
							raise = true;
						}
					}
				} while (raise == true);
			}
		}
		round++;
	}
	
	player.sort();
	cpu.sort();
	cpu.printcard();
	player.printcard();
	if (round == 5) {
		cpupoints = max(pairs(cpu.cpucards), max(nofkinds(cpu.cpucards), max(straight(cpu.cpucards), fullhouse(cpu.cpucards))));
		ppoints = max(pairs(player.pcards), max(nofkinds(player.pcards), max(straight(player.pcards), fullhouse(player.pcards))));
		if (cpupoints == ppoints) {
			tiebreaker(cpupoints, ppoints, cpu.cpucards, player.pcards);
		}
		cout << "Cpu: " << cpupoints << "\nPlayer: " << ppoints << endl;
		if (cpupoints > ppoints) {
			cout << "CPU Win!" << endl;
			cpubet = -1 * pbet;
			cpu.cpubalance(cpubalance, cpubet);
			player.pbalance(pbalance, pbet);
			cpubalance = cpu.getMoney();
			pbalance = player.getMoney();
		
		}
		else {
			cout << "Player Win!" << endl;
			pbet = -1 * cpubet;
			cpu.cpubalance(cpubalance, cpubet);
			player.pbalance(pbalance, pbet);
			cpubalance = cpu.getMoney();
			pbalance = player.getMoney();
		}
	}
	else {
		cpubalance = cpu.getMoney();
		pbalance = player.getMoney();
	}

}

void playpokerhand(int &pbalance , int &cpubalance) {
	srand(time(NULL));
	Cpu cpu;
	player p1;
	pokerhand(cpu, p1, pbalance, cpubalance);
	cout << "Player Balance: " << pbalance << "\nCPU Balance: " << cpubalance << endl;
}

