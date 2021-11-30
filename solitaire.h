#include <vector>
#include <iostream>
#include <string>
#include "generic.h"

using namespace std;
class Pile;

class Pile {
public:
	vector<Card> cards;
	bool faceup;
	bool stacked;
	string name;
	int locx;
	int locy;

	vector<Card> Remove(int num_cards);
	void Add(vector<Card> incoming_cards);
	void PrintPile(const MainData& dat);
};

class Solitaire {
public:

	Deck solitaireDeck;
	Pile s1, s2, s3, s4, st, t1u, t2u, t3u, t4u, t5u, t6u, t7u, t2d, t3d, t4d, t5d, t6d, t7d, dis;
	int turn = 0;

	void MakeSolitarePiles(void);
	void MoveCardsAndFlip(Pile& source, Pile& destination, int num_cards);
	bool checkSourceCardsValidity(Pile source, int num_cards);
	bool checkDestinationValiditySuits(Card card1, Card card2);
	bool checkDestinationValidityTable(Card card1, Card card2);
	bool diffColor(Card card1, Card card2);
	void ResetDeck(void);
	void DrawCard(void);
	bool CheckWin(void);
	void DrawGame(const MainData&);
	int PlaySolitaire(const MainData&);
	~Solitaire() {

	}
};
