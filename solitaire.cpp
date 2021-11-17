#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>
#include "generic.h"
#include "solitaire.h"
#include "fssimplewindow.h"
#include "ysglfontdata.h"

using namespace std;

void DrawRect(double cx1, double cy1, double l, double h)
{
	glBegin(GL_QUADS);

	glVertex2i(cx1 + l / 2, cy1 + h / 2);
	glVertex2i(cx1 + l / 2, cy1 - h / 2);
	glVertex2i(cx1 - l / 2, cy1 - h / 2);
	glVertex2i(cx1 - l / 2, cy1 + h / 2);

	glEnd();
}

vector<Card> Pile::Remove(int num_cards)
{
	vector<Card> y(cards.end() - num_cards, cards.end());
	for (int i = 0; i < num_cards; i++)
	{
		cards.pop_back();
	}

	return(y);
}

void Pile::Add(vector<Card> incoming_cards)
{
	for (int i = 0; i < incoming_cards.size(); i++)
	{
		cards.push_back(incoming_cards[i]);
	}
}

void Pile::PrintPile(void)
{
	if (cards.size() != 0)
	{
		if (stacked == true)
		{
			if (faceup == false)
			{
				glColor3ub(100, 100, 100);
				glRasterPos2i(locx, locy);

				char const* blchar = "Down";
				YsGlDrawFontBitmap10x14(blchar);
			}
			else
			{
				auto top_card = cards[cards.size() - 1];
				top_card.PrintCard(locx, locy);
			}
		}
		else
		{
			if (faceup == false)
			{
				glColor3ub(100, 100, 100);
				char const* blchar = "Down";
				for (int i = 0; i < cards.size(); i++)
				{
					glRasterPos2i(locx, locy + i * 40);
					YsGlDrawFontBitmap10x14(blchar);
				}

			}
			else
			{
				for (int i = 0; i < cards.size(); i++)
				{	
					auto _card = cards[i];
					_card.PrintCard(locx, locy + 50.0 * i);
				}
			}
		}
	}
}

void Solitaire::MakeSolitarePiles(void)
{
	solitaireDeck.shuffleDeck();
	t1u.cards.push_back(solitaireDeck.subDeck(0, 0).cards[0]);

	t2u.cards.push_back(solitaireDeck.subDeck(1, 1).cards[0]);
	t2d.cards.push_back(solitaireDeck.subDeck(2, 2).cards[0]);

	t3u.cards.push_back(solitaireDeck.subDeck(3, 3).cards[0]);
	t3d.cards.push_back(solitaireDeck.subDeck(4, 5).cards[0]);
	t3d.cards.push_back(solitaireDeck.subDeck(4, 5).cards[1]);

	t4u.cards.push_back(solitaireDeck.subDeck(6, 6).cards[0]);
	Deck tempSubDeck = solitaireDeck.subDeck(7, 9);
	for (int i = 0; i < 3; i++)
	{
		t4d.cards.push_back(tempSubDeck.cards[i]);
	}

	t5u.cards.push_back(solitaireDeck.subDeck(10, 10).cards[0]);
	tempSubDeck = solitaireDeck.subDeck(11, 14);
	for (int i = 0; i < 4; i++)
	{
		t5d.cards.push_back(tempSubDeck.cards[i]);
	}

	t6u.cards.push_back(solitaireDeck.subDeck(15, 15).cards[0]);
	tempSubDeck = solitaireDeck.subDeck(16, 20);
	for (int i = 0; i < 5; i++)
	{
		t6d.cards.push_back(tempSubDeck.cards[i]);
	}

	t7u.cards.push_back(solitaireDeck.subDeck(21, 21).cards[0]);
	tempSubDeck = solitaireDeck.subDeck(22, 27);
	for (int i = 0; i < 6; i++)
	{
		t7d.cards.push_back(tempSubDeck.cards[i]);
	}

	tempSubDeck = solitaireDeck.subDeck(28, 51);
	for (int i = 0; i < 24; i++)
	{
		st.cards.push_back(tempSubDeck.cards[i]);
	}
}

void Solitaire::DrawGame(void)
{
	s1.PrintPile();
	s2.PrintPile();
	s3.PrintPile();
	s4.PrintPile();
	st.PrintPile();
	t1u.PrintPile();
	t2u.PrintPile();
	t3u.PrintPile();
	t4u.PrintPile();
	t5u.PrintPile();
	t6u.PrintPile();
	t7u.PrintPile();
	t2d.PrintPile();
	t3d.PrintPile();
	t4d.PrintPile();
	t5d.PrintPile();
	t6d.PrintPile();
	t7d.PrintPile();
	dis.PrintPile();
}

void Solitaire::MoveCardsAndFlip(Pile &source, Pile &destination, int num_cards)
{
	if ((source.name == "discard" || source.name == "suit") && (num_cards == 1) && source.cards.size() >= 1)
	{
		if (source.name == "discard" && destination.name == "suit")
		{
			if (destination.cards.size() != 0)
			{
				if (checkDestinationValiditySuits(source.cards[source.cards.size() - 1], destination.cards[destination.cards.size() - 1]))
				{
					auto temp = source.Remove(1);
					destination.Add(temp);
				}
			}
			else if (source.cards[source.cards.size() - 1].rank==1)
			{
				auto temp = source.Remove(1);
				destination.Add(temp);
			}

		}
		else if (destination.name == "tu")
		{
			if (source.cards[source.cards.size() - 1].rank == 13)
			{
				if (destination.cards.size() == 0)
				{
					auto temp = source.Remove(1);
					destination.Add(temp);
				}
			}
			else
			{				
				if (checkDestinationValidityTable(source.cards[source.cards.size() - 1], destination.cards[destination.cards.size() - 1]))
				{
					auto temp = source.Remove(1);
					destination.Add(temp);
				}
			}
		}
	}
	else if ((source.name == "tu") && (1 <= num_cards) && (num_cards <= source.cards.size()) && checkSourceCardsValidity(source, num_cards))
	{
		if (destination.name == "suit" && num_cards == 1)
		{
			if (destination.cards.size() != 0)
			{
				if (checkDestinationValiditySuits(source.cards[source.cards.size() - 1], destination.cards[destination.cards.size() - 1]))
				{
					auto temp = source.Remove(1);
					destination.Add(temp);
				}
			}
			else if (source.cards[source.cards.size() - 1].rank == 1)
			{
				auto temp = source.Remove(1);
				destination.Add(temp);
			}
		}
		else if (destination.name == "tu")
		{
			if (source.cards[source.cards.size() - 1 - (num_cards - 1)].rank == 13)
			{
				if (destination.cards.size() == 0)
				{
					auto temp = source.Remove(num_cards);
					destination.Add(temp);
				}
			}
			else
			{
				if (checkDestinationValidityTable(source.cards[source.cards.size() - 1 - (num_cards - 1)], destination.cards[destination.cards.size() - 1]))
				{
					auto temp = source.Remove(num_cards);
					destination.Add(temp);
				}
			}
		}

		if (t2u.cards.size() == 0 && t2d.cards.size() > 0)
		{
			auto temp = t2d.Remove(1);
			t2u.Add(temp);
		}

		if (t3u.cards.size() == 0 && t3d.cards.size() > 0)
		{
			auto temp = t3d.Remove(1);
			t3u.Add(temp);
		}

		if (t4u.cards.size() == 0 && t4d.cards.size() > 0)
		{
			auto temp = t4d.Remove(1);
			t4u.Add(temp);
		}

		if (t5u.cards.size() == 0 && t5d.cards.size() > 0)
		{
			auto temp = t5d.Remove(1);
			t5u.Add(temp);
		}

		if (t6u.cards.size() == 0 && t6d.cards.size() > 0)
		{
			auto temp = t6d.Remove(1);
			t6u.Add(temp);
		}

		if (t7u.cards.size() == 0 && t7d.cards.size() > 0)
		{
			auto temp = t7d.Remove(1);
			t7u.Add(temp);
		}
	}
}

void Solitaire::ResetDeck(void)
{
	if (st.cards.size() == 0 && dis.cards.size() != 0)
	{
		auto temp = dis.Remove(dis.cards.size());
		std::reverse(temp.begin(), temp.end());
		st.Add(temp);
	}
}

void Solitaire::DrawCard(void)
{
	if (st.cards.size() != 0)
	{
		auto temp = st.Remove(1);
		dis.Add(temp);
	}
}

bool Solitaire::diffColor(Card card1, Card card2)
{
	if (card1.suit == 0 || card1.suit == 3)
	{
		if (card2.suit == 0 || card2.suit == 3)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else if (card1.suit == 1 || card1.suit==2)
	{
		if (card2.suit == 0 || card2.suit == 3)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool Solitaire::checkSourceCardsValidity(Pile source, int num_cards)
{
	for (int i = 0; i < num_cards - 1; i++)
	{
		auto card1 = source.cards[source.cards.size() - 1 - i];
		auto card2 = source.cards[source.cards.size() - 2 - i];

		if (diffColor(card1, card2) && (card1.rank == card2.rank - 1))
		{

		}
		else
		{
			return false;
		}
	}
	return true;
}

bool Solitaire::checkDestinationValidityTable(Card card1, Card card2)
{
	if (diffColor(card1, card2) && (card1.rank == card2.rank - 1))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Solitaire::checkDestinationValiditySuits(Card card1, Card card2)
{
	if ((card1.suit == card2.suit) && (card1.rank == card2.rank + 1))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Solitaire::CheckWin(void)
{
	if (st.cards.size() == 0 && dis.cards.size() == 0 && t1u.cards.size() == 0 && t2u.cards.size() == 0 && t3u.cards.size() == 0 && t4u.cards.size() == 0 && t5u.cards.size() == 0 && t6u.cards.size() == 0 && t7u.cards.size() == 0 && t2d.cards.size() == 0 && t3d.cards.size() == 0 && t4d.cards.size() == 0 && t5d.cards.size() == 0 && t6d.cards.size() == 0 && t7d.cards.size() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Solitaire::PlaySolitaire(void)
{
    srand(time(NULL));

    MakeSolitarePiles();

    st.locy = 40;
    st.locx = 20;
    dis.locx = 100;
    dis.locy = 20;
    s1.locx = 200;
    s1.locy = 20;
    s2.locx = 300;
    s2.locy = 20;
    s3.locx = 400;
    s3.locy = 20;
    s4.locx = 500;
    s4.locy = 20;

    t2d.locx = 275;
    t2d.locy = 120;
    t3d.locx = 375;
    t3d.locy = 120;
    t4d.locx = 475;
    t4d.locy = 120;
    t5d.locx = 575;
    t5d.locy = 120;
    t6d.locx = 675;
    t6d.locy = 120;
    t7d.locx = 775;
    t7d.locy = 120;

    t1u.locx = 175;
    t1u.locy = 100;
    t2u.locx = 275;
    t2u.locy = t2d.cards.size() * 40 + 100;
    t3u.locx = 375;
    t3u.locy = t3d.cards.size() * 40 + 100;
    t4u.locx = 475;
    t4u.locy = t4d.cards.size() * 40 + 100;
    t5u.locx = 575;
    t5u.locy = t5d.cards.size() * 40 + 100;
    t6u.locx = 675;
    t6u.locy = t6d.cards.size() * 40 + 100;
    t7u.locx = 775;
    t7u.locy = t7d.cards.size() * 40 + 100;

    s1.stacked = true;
    s2.stacked = true;
    s3.stacked = true;
    s4.stacked = true;
    s1.faceup = true;
    s2.faceup = true;
    s3.faceup = true;
    s4.faceup = true;
    st.stacked = true;
    st.faceup = false;
    t1u.stacked = false;
    t2u.stacked = false;
    t3u.stacked = false;
    t4u.stacked = false;
    t5u.stacked = false;
    t6u.stacked = false;
    t7u.stacked = false;
    t1u.faceup = true;
    t2u.faceup = true;
    t3u.faceup = true;
    t4u.faceup = true;
    t5u.faceup = true;
    t6u.faceup = true;
    t7u.faceup = true;
    t2d.stacked = false;
    t3d.stacked = false;
    t4d.stacked = false;
    t5d.stacked = false;
    t6d.stacked = false;
    t7d.stacked = false;
    t2d.faceup = false;
    t3d.faceup = false;
    t4d.faceup = false;
    t5d.faceup = false;
    t6d.faceup = false;
    t7d.faceup = false;
    dis.stacked = true;
    dis.faceup = true;

    s1.name = "suit";
    s2.name = "suit";
    s3.name = "suit";
    s4.name = "suit";
    st.name = "stack";
    t1u.name = "tu";
    t2u.name = "tu";
    t3u.name = "tu";
    t4u.name = "tu";
    t5u.name = "tu";
    t6u.name = "tu";
    t7u.name = "tu";
    t2d.name = "td";
    t3d.name = "td";
    t4d.name = "td";
    t5d.name = "td";
    t6d.name = "td";
    t7d.name = "td";
    dis.name = "discard";

    int turn = 0;
    int tempPileNum = 0;
    int tempNumCards;

    FsOpenWindow(0, 0, 1000, 600, 1);

    while (CheckWin() == false)
    {
        int mx, my, lb, mb, rb;
        auto evt = FsGetMouseEvent(lb, mb, rb, mx, my);

        t2u.locx = 275;
        t2u.locy = t2d.cards.size() * 40 + 100;
        t3u.locx = 375;
        t3u.locy = t3d.cards.size() * 40 + 100;
        t4u.locx = 475;
        t4u.locy = t4d.cards.size() * 40 + 100;
        t5u.locx = 575;
        t5u.locy = t5d.cards.size() * 40 + 100;
        t6u.locx = 675;
        t6u.locy = t6d.cards.size() * 40 + 100;
        t7u.locx = 775;
        t7u.locy = t7d.cards.size() * 40 + 100;

        FsPollDevice();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (FSMOUSEEVENT_LBUTTONDOWN == evt)
        {
            std::cout << "Mouse click" << endl;

            if (mx > st.locx && mx < st.locx + 10 && my > st.locy - 10 && my < st.locy)
            {
                turn = 0;
                if (st.cards.size() != 0)
                {
                    DrawCard();
                    std::cout << "DrawCard" << endl;
                }
                else if (dis.cards.size() != 0)
                {
                    ResetDeck();
                    std::cout << "ResetDeck" << endl;
                }
            }

            else if (turn == 0)
            {
                if (mx > dis.locx && mx < dis.locx + 10 && my > dis.locy - 10 && my < dis.locy)
                {
                    std::cout << "Source is discard pile" << endl;
                    tempPileNum = 0;
                    tempNumCards = 1;
                    turn = 1;
                }
                else if (mx > s1.locx && mx < s1.locx + 10 && my > s1.locy - 10 && my < s1.locy)
                {
                    std::cout << "Source is suit1 pile" << endl;
                    tempPileNum = 1;
                    tempNumCards = 1;
                    turn = 1;
                }
                else if (mx > s2.locx && mx < s2.locx + 10 && my > s2.locy - 10 && my < s2.locy)
                {
                    std::cout << "Source is suit2 pile" << endl;
                    tempPileNum = 2;
                    tempNumCards = 1;
                    turn = 1;
                }
                else if (mx > s3.locx && mx < s3.locx + 10 && my > s3.locy - 10 && my < s3.locy)
                {
                    std::cout << "Source is suit3 pile" << endl;
                    tempPileNum = 3;
                    tempNumCards = 1;
                    turn = 1;
                }
                else if (mx > s4.locx && mx < s4.locx + 10 && my > s4.locy - 10 && my < s4.locy)
                {
                    std::cout << "Source is suit4 pile" << endl;
                    tempPileNum = 4;
                    tempNumCards = 1;
                    turn = 1;
                }
                else if (mx > t1u.locx && mx < t1u.locx + 10)
                {
                    if (my > t1u.locy - 10 && my < t1u.locy + 40 * (t1u.cards.size() - 1))
                    {
                        std::cout << "Source is t1u pile" << endl;
                        tempPileNum = 5;
                        tempNumCards = 1 + (my - t1u.locy) / 40;
                        turn = 1;
                    }
                }
                else if (mx > t2u.locx && mx < t2u.locx + 10)
                {
                    if (my > t2u.locy - 10 && my < t2u.locy + 40 * (t2u.cards.size() - 1))
                    {
                        std::cout << "Source is t2u pile" << endl;
                        tempPileNum = 6;
                        tempNumCards = 1 + (my - t2u.locy) / 40;
                        turn = 1;
                    }
                }
                else if (mx > t3u.locx && mx < t3u.locx + 10)
                {
                    if (my > t3u.locy - 10 && my < t3u.locy + 40 * (t3u.cards.size() - 1))
                    {
                        std::cout << "Source is t3u pile" << endl;
                        tempPileNum = 7;
                        tempNumCards = 1 + (my - t3u.locy) / 40;
                        turn = 1;
                    }
                }
                else if (mx > t4u.locx && mx < t4u.locx + 10)
                {
                    if (my > t4u.locy - 10 && my < t4u.locy + 40 * (t4u.cards.size() - 1))
                    {
                        std::cout << "Source is t4u pile" << endl;
                        tempPileNum = 8;
                        tempNumCards = 1 + (my - t4u.locy) / 40;
                        turn = 1;
                    }
                }
                else if (mx > t5u.locx && mx < t5u.locx + 10)
                {
                    if (my > t5u.locy - 10 && my < t5u.locy + 40 * (t5u.cards.size() - 1))
                    {
                        std::cout << "Source is t5u pile" << endl;
                        tempPileNum = 9;
                        tempNumCards = 1 + (my - t5u.locy) / 40;
                        turn = 1;
                    }
                }
                else if (mx > t6u.locx && mx < t6u.locx + 10)
                {
                    if (my > t6u.locy - 10 && my < t6u.locy + 40 * (t6u.cards.size() - 1))
                    {
                        std::cout << "Source is t6u pile" << endl;
                        tempPileNum = 10;
                        tempNumCards = 1 + (my - t6u.locy) / 40;
                        turn = 1;
                    }
                }
                else if (mx > t7u.locx && mx < t7u.locx + 10)
                {
                    if (my > t7u.locy - 10 && my < t7u.locy + 40 * (t7u.cards.size() - 1))
                    {
                        std::cout << "Source is t7u pile" << endl;
                        tempPileNum = 11;
                        tempNumCards = 1 + (my - t7u.locy) / 40;
                        turn = 1;
                    }
                }
            }

            else if (turn == 1)
            {
                if (mx > s1.locx && mx < s1.locx + 10 && my > s1.locy - 10 && my < s1.locy)
                {
                    std::cout << "Destination is s1 pile" << endl;
                    if (tempPileNum == 0)
                    {
                        MoveCardsAndFlip(dis, s1, tempNumCards);
                    }
                    else if (tempPileNum == 1)
                    {
                        MoveCardsAndFlip(s1, s1, tempNumCards);
                    }
                    else if (tempPileNum == 2)
                    {
                        MoveCardsAndFlip(s2, s1, tempNumCards);
                    }
                    else if (tempPileNum == 3)
                    {
                        MoveCardsAndFlip(s3, s1, tempNumCards);
                    }
                    else if (tempPileNum == 4)
                    {
                        MoveCardsAndFlip(s4, s1, tempNumCards);
                    }
                    else if (tempPileNum == 5)
                    {
                        MoveCardsAndFlip(t1u, s1, tempNumCards);
                    }
                    else if (tempPileNum == 6)
                    {
                        MoveCardsAndFlip(t2u, s1, tempNumCards);
                    }
                    else if (tempPileNum == 7)
                    {
                        MoveCardsAndFlip(t3u, s1, tempNumCards);
                    }
                    else if (tempPileNum == 8)
                    {
                        MoveCardsAndFlip(t4u, s1, tempNumCards);
                    }
                    else if (tempPileNum == 9)
                    {
                        MoveCardsAndFlip(t5u, s1, tempNumCards);
                    }
                    else if (tempPileNum == 10)
                    {
                        MoveCardsAndFlip(t6u, s1, tempNumCards);
                    }
                    else if (tempPileNum == 11)
                    {
                        MoveCardsAndFlip(t7u, s1, tempNumCards);
                    }
                }
                else if (mx > s2.locx && mx < s2.locx + 10 && my > s2.locy - 10 && my < s2.locy)
                {
                    std::cout << "Destination is s2 pile" << endl;

                    if (tempPileNum == 0)
                    {
                        MoveCardsAndFlip(dis, s2, tempNumCards);
                    }
                    else if (tempPileNum == 1)
                    {
                        MoveCardsAndFlip(s1, s2, tempNumCards);
                    }
                    else if (tempPileNum == 2)
                    {
                        MoveCardsAndFlip(s2, s2, tempNumCards);
                    }
                    else if (tempPileNum == 3)
                    {
                        MoveCardsAndFlip(s3, s2, tempNumCards);
                    }
                    else if (tempPileNum == 4)
                    {
                        MoveCardsAndFlip(s4, s2, tempNumCards);
                    }
                    else if (tempPileNum == 5)
                    {
                        MoveCardsAndFlip(t1u, s2, tempNumCards);
                    }
                    else if (tempPileNum == 6)
                    {
                        MoveCardsAndFlip(t2u, s2, tempNumCards);
                    }
                    else if (tempPileNum == 7)
                    {
                        MoveCardsAndFlip(t3u, s2, tempNumCards);
                    }
                    else if (tempPileNum == 8)
                    {
                        MoveCardsAndFlip(t4u, s2, tempNumCards);
                    }
                    else if (tempPileNum == 9)
                    {
                        MoveCardsAndFlip(t5u, s2, tempNumCards);
                    }
                    else if (tempPileNum == 10)
                    {
                        MoveCardsAndFlip(t6u, s2, tempNumCards);
                    }
                    else if (tempPileNum == 11)
                    {
                        MoveCardsAndFlip(t7u, s2, tempNumCards);
                    }
                }
                else if (mx > s3.locx && mx < s3.locx + 10 && my > s3.locy - 10 && my < s3.locy)
                {
                    std::cout << "Destination is s3 pile" << endl;

                    if (tempPileNum == 0)
                    {
                        MoveCardsAndFlip(dis, s3, tempNumCards);
                    }
                    else if (tempPileNum == 1)
                    {
                        MoveCardsAndFlip(s1, s3, tempNumCards);
                    }
                    else if (tempPileNum == 2)
                    {
                        MoveCardsAndFlip(s2, s3, tempNumCards);
                    }
                    else if (tempPileNum == 3)
                    {
                        MoveCardsAndFlip(s3, s3, tempNumCards);
                    }
                    else if (tempPileNum == 4)
                    {
                        MoveCardsAndFlip(s4, s3, tempNumCards);
                    }
                    else if (tempPileNum == 5)
                    {
                        MoveCardsAndFlip(t1u, s3, tempNumCards);
                    }
                    else if (tempPileNum == 6)
                    {
                        MoveCardsAndFlip(t2u, s3, tempNumCards);
                    }
                    else if (tempPileNum == 7)
                    {
                        MoveCardsAndFlip(t3u, s3, tempNumCards);
                    }
                    else if (tempPileNum == 8)
                    {
                        MoveCardsAndFlip(t4u, s3, tempNumCards);
                    }
                    else if (tempPileNum == 9)
                    {
                        MoveCardsAndFlip(t5u, s3, tempNumCards);
                    }
                    else if (tempPileNum == 10)
                    {
                        MoveCardsAndFlip(t6u, s3, tempNumCards);
                    }
                    else if (tempPileNum == 11)
                    {
                        MoveCardsAndFlip(t7u, s3, tempNumCards);
                    }
                }
                else if (mx > s4.locx && mx < s4.locx + 10 && my > s4.locy - 10 && my < s4.locy)
                {
                    std::cout << "Destination is s4 pile" << endl;

                    if (tempPileNum == 0)
                    {
                        MoveCardsAndFlip(dis, s4, tempNumCards);
                    }
                    else if (tempPileNum == 1)
                    {
                        MoveCardsAndFlip(s1, s4, tempNumCards);
                    }
                    else if (tempPileNum == 2)
                    {
                        MoveCardsAndFlip(s2, s4, tempNumCards);
                    }
                    else if (tempPileNum == 3)
                    {
                        MoveCardsAndFlip(s3, s4, tempNumCards);
                    }
                    else if (tempPileNum == 4)
                    {
                        MoveCardsAndFlip(s4, s4, tempNumCards);
                    }
                    else if (tempPileNum == 5)
                    {
                        MoveCardsAndFlip(t1u, s4, tempNumCards);
                    }
                    else if (tempPileNum == 6)
                    {
                        MoveCardsAndFlip(t2u, s4, tempNumCards);
                    }
                    else if (tempPileNum == 7)
                    {
                        MoveCardsAndFlip(t3u, s4, tempNumCards);
                    }
                    else if (tempPileNum == 8)
                    {
                        MoveCardsAndFlip(t4u, s4, tempNumCards);
                    }
                    else if (tempPileNum == 9)
                    {
                        MoveCardsAndFlip(t5u, s4, tempNumCards);
                    }
                    else if (tempPileNum == 10)
                    {
                        MoveCardsAndFlip(t6u, s4, tempNumCards);
                    }
                    else if (tempPileNum == 11)
                    {
                        MoveCardsAndFlip(t7u, s4, tempNumCards);
                    }
                }

                else if (mx > t1u.locx && mx < t1u.locx + 10)
                {
                    std::cout << "Destination is t1u pile" << endl;

                    if (tempPileNum == 0)
                    {
                        MoveCardsAndFlip(dis, t1u, tempNumCards);
                    }
                    else if (tempPileNum == 1)
                    {
                        MoveCardsAndFlip(s1, t1u, tempNumCards);
                    }
                    else if (tempPileNum == 2)
                    {
                        MoveCardsAndFlip(s2, t1u, tempNumCards);
                    }
                    else if (tempPileNum == 3)
                    {
                        MoveCardsAndFlip(s3, t1u, tempNumCards);
                    }
                    else if (tempPileNum == 4)
                    {
                        MoveCardsAndFlip(s4, t1u, tempNumCards);
                    }
                    else if (tempPileNum == 5)
                    {
                        MoveCardsAndFlip(t1u, t1u, tempNumCards);
                    }
                    else if (tempPileNum == 6)
                    {
                        MoveCardsAndFlip(t2u, t1u, tempNumCards);
                    }
                    else if (tempPileNum == 7)
                    {
                        MoveCardsAndFlip(t3u, t1u, tempNumCards);
                    }
                    else if (tempPileNum == 8)
                    {
                        MoveCardsAndFlip(t4u, t1u, tempNumCards);
                    }
                    else if (tempPileNum == 9)
                    {
                        MoveCardsAndFlip(t5u, t1u, tempNumCards);
                    }
                    else if (tempPileNum == 10)
                    {
                        MoveCardsAndFlip(t6u, t1u, tempNumCards);
                    }
                    else if (tempPileNum == 11)
                    {
                        MoveCardsAndFlip(t7u, t1u, tempNumCards);
                    }
                }
                else if (mx > t2u.locx && mx < t2u.locx + 10)
                {
                    std::cout << "Destination is t2u pile" << endl;
                    if (tempPileNum == 0)
                    {
                        MoveCardsAndFlip(dis, t2u, tempNumCards);
                    }
                    else if (tempPileNum == 1)
                    {
                        MoveCardsAndFlip(s1, t2u, tempNumCards);
                    }
                    else if (tempPileNum == 2)
                    {
                        MoveCardsAndFlip(s2, t2u, tempNumCards);
                    }
                    else if (tempPileNum == 3)
                    {
                        MoveCardsAndFlip(s3, t2u, tempNumCards);
                    }
                    else if (tempPileNum == 4)
                    {
                        MoveCardsAndFlip(s4, t2u, tempNumCards);
                    }
                    else if (tempPileNum == 5)
                    {
                        MoveCardsAndFlip(t1u, t2u, tempNumCards);
                    }
                    else if (tempPileNum == 6)
                    {
                        MoveCardsAndFlip(t2u, t2u, tempNumCards);
                    }
                    else if (tempPileNum == 7)
                    {
                        MoveCardsAndFlip(t3u, t2u, tempNumCards);
                    }
                    else if (tempPileNum == 8)
                    {
                        MoveCardsAndFlip(t4u, t2u, tempNumCards);
                    }
                    else if (tempPileNum == 9)
                    {
                        MoveCardsAndFlip(t5u, t2u, tempNumCards);
                    }
                    else if (tempPileNum == 10)
                    {
                        MoveCardsAndFlip(t6u, t2u, tempNumCards);
                    }
                    else if (tempPileNum == 11)
                    {
                        MoveCardsAndFlip(t7u, t2u, tempNumCards);
                    }
                }
                else if (mx > t3u.locx && mx < t3u.locx + 10)
                {
                    std::cout << "Destination is t3u pile" << endl;
                    if (tempPileNum == 0)
                    {
                        MoveCardsAndFlip(dis, t3u, tempNumCards);
                    }
                    else if (tempPileNum == 1)
                    {
                        MoveCardsAndFlip(s1, t3u, tempNumCards);
                    }
                    else if (tempPileNum == 2)
                    {
                        MoveCardsAndFlip(s2, t3u, tempNumCards);
                    }
                    else if (tempPileNum == 3)
                    {
                        MoveCardsAndFlip(s3, t3u, tempNumCards);
                    }
                    else if (tempPileNum == 4)
                    {
                        MoveCardsAndFlip(s4, t3u, tempNumCards);
                    }
                    else if (tempPileNum == 5)
                    {
                        MoveCardsAndFlip(t1u, t3u, tempNumCards);
                    }
                    else if (tempPileNum == 6)
                    {
                        MoveCardsAndFlip(t2u, t3u, tempNumCards);
                    }
                    else if (tempPileNum == 7)
                    {
                        MoveCardsAndFlip(t3u, t3u, tempNumCards);
                    }
                    else if (tempPileNum == 8)
                    {
                        MoveCardsAndFlip(t4u, t3u, tempNumCards);
                    }
                    else if (tempPileNum == 9)
                    {
                        MoveCardsAndFlip(t5u, t3u, tempNumCards);
                    }
                    else if (tempPileNum == 10)
                    {
                        MoveCardsAndFlip(t6u, t3u, tempNumCards);
                    }
                    else if (tempPileNum == 11)
                    {
                        MoveCardsAndFlip(t7u, t3u, tempNumCards);
                    }
                }
                else if (mx > t4u.locx && mx < t4u.locx + 10)
                {
                    std::cout << "Destination is t4u pile" << endl;

                    if (tempPileNum == 0)
                    {
                        MoveCardsAndFlip(dis, t4u, tempNumCards);
                    }
                    else if (tempPileNum == 1)
                    {
                        MoveCardsAndFlip(s1, t4u, tempNumCards);
                    }
                    else if (tempPileNum == 2)
                    {
                        MoveCardsAndFlip(s2, t4u, tempNumCards);
                    }
                    else if (tempPileNum == 3)
                    {
                        MoveCardsAndFlip(s3, t4u, tempNumCards);
                    }
                    else if (tempPileNum == 4)
                    {
                        MoveCardsAndFlip(s4, t4u, tempNumCards);
                    }
                    else if (tempPileNum == 5)
                    {
                        MoveCardsAndFlip(t1u, t4u, tempNumCards);
                    }
                    else if (tempPileNum == 6)
                    {
                        MoveCardsAndFlip(t2u, t4u, tempNumCards);
                    }
                    else if (tempPileNum == 7)
                    {
                        MoveCardsAndFlip(t3u, t4u, tempNumCards);
                    }
                    else if (tempPileNum == 8)
                    {
                        MoveCardsAndFlip(t4u, t4u, tempNumCards);
                    }
                    else if (tempPileNum == 9)
                    {
                        MoveCardsAndFlip(t5u, t4u, tempNumCards);
                    }
                    else if (tempPileNum == 10)
                    {
                        MoveCardsAndFlip(t6u, t4u, tempNumCards);
                    }
                    else if (tempPileNum == 11)
                    {
                        MoveCardsAndFlip(t7u, t4u, tempNumCards);
                    }
                }
                else if (mx > t5u.locx && mx < t5u.locx + 10)
                {
                    std::cout << "Destination is t5u pile" << endl;
                    if (tempPileNum == 0)
                    {
                        MoveCardsAndFlip(dis, t5u, tempNumCards);
                    }
                    else if (tempPileNum == 1)
                    {
                        MoveCardsAndFlip(s1, t5u, tempNumCards);
                    }
                    else if (tempPileNum == 2)
                    {
                        MoveCardsAndFlip(s2, t5u, tempNumCards);
                    }
                    else if (tempPileNum == 3)
                    {
                        MoveCardsAndFlip(s3, t5u, tempNumCards);
                    }
                    else if (tempPileNum == 4)
                    {
                        MoveCardsAndFlip(s4, t5u, tempNumCards);
                    }
                    else if (tempPileNum == 5)
                    {
                        MoveCardsAndFlip(t1u, t5u, tempNumCards);
                    }
                    else if (tempPileNum == 6)
                    {
                        MoveCardsAndFlip(t2u, t5u, tempNumCards);
                    }
                    else if (tempPileNum == 7)
                    {
                        MoveCardsAndFlip(t3u, t5u, tempNumCards);
                    }
                    else if (tempPileNum == 8)
                    {
                        MoveCardsAndFlip(t4u, t5u, tempNumCards);
                    }
                    else if (tempPileNum == 9)
                    {
                        MoveCardsAndFlip(t5u, t5u, tempNumCards);
                    }
                    else if (tempPileNum == 10)
                    {
                        MoveCardsAndFlip(t6u, t5u, tempNumCards);
                    }
                    else if (tempPileNum == 11)
                    {
                        MoveCardsAndFlip(t7u, t5u, tempNumCards);
                    }
                }
                else if (mx > t6u.locx && mx < t6u.locx + 10)
                {
                    std::cout << "Destination is t6u pile" << endl;
                    if (tempPileNum == 0)
                    {
                        MoveCardsAndFlip(dis, t6u, tempNumCards);
                    }
                    else if (tempPileNum == 1)
                    {
                        MoveCardsAndFlip(s1, t6u, tempNumCards);
                    }
                    else if (tempPileNum == 2)
                    {
                        MoveCardsAndFlip(s2, t6u, tempNumCards);
                    }
                    else if (tempPileNum == 3)
                    {
                        MoveCardsAndFlip(s3, t6u, tempNumCards);
                    }
                    else if (tempPileNum == 4)
                    {
                        MoveCardsAndFlip(s4, t6u, tempNumCards);
                    }
                    else if (tempPileNum == 5)
                    {
                        MoveCardsAndFlip(t1u, t6u, tempNumCards);
                    }
                    else if (tempPileNum == 6)
                    {
                        MoveCardsAndFlip(t2u, t6u, tempNumCards);
                    }
                    else if (tempPileNum == 7)
                    {
                        MoveCardsAndFlip(t3u, t6u, tempNumCards);
                    }
                    else if (tempPileNum == 8)
                    {
                        MoveCardsAndFlip(t4u, t6u, tempNumCards);
                    }
                    else if (tempPileNum == 9)
                    {
                        MoveCardsAndFlip(t5u, t6u, tempNumCards);
                    }
                    else if (tempPileNum == 10)
                    {
                        MoveCardsAndFlip(t6u, t6u, tempNumCards);
                    }
                    else if (tempPileNum == 11)
                    {
                        MoveCardsAndFlip(t7u, t6u, tempNumCards);
                    }
                }
                else if (mx > t7u.locx && mx < t7u.locx + 10)
                {
                    std::cout << "Destination is t7u pile" << endl;
                    if (tempPileNum == 0)
                    {
                        MoveCardsAndFlip(dis, t7u, tempNumCards);
                    }
                    else if (tempPileNum == 1)
                    {
                        MoveCardsAndFlip(s1, t7u, tempNumCards);
                    }
                    else if (tempPileNum == 2)
                    {
                        MoveCardsAndFlip(s2, t7u, tempNumCards);
                    }
                    else if (tempPileNum == 3)
                    {
                        MoveCardsAndFlip(s3, t7u, tempNumCards);
                    }
                    else if (tempPileNum == 4)
                    {
                        MoveCardsAndFlip(s4, t7u, tempNumCards);
                    }
                    else if (tempPileNum == 5)
                    {
                        MoveCardsAndFlip(t1u, t7u, tempNumCards);
                    }
                    else if (tempPileNum == 6)
                    {
                        MoveCardsAndFlip(t2u, t7u, tempNumCards);
                    }
                    else if (tempPileNum == 7)
                    {
                        MoveCardsAndFlip(t3u, t7u, tempNumCards);
                    }
                    else if (tempPileNum == 8)
                    {
                        MoveCardsAndFlip(t4u, t7u, tempNumCards);
                    }
                    else if (tempPileNum == 9)
                    {
                        MoveCardsAndFlip(t5u, t7u, tempNumCards);
                    }
                    else if (tempPileNum == 10)
                    {
                        MoveCardsAndFlip(t6u, t7u, tempNumCards);
                    }
                    else if (tempPileNum == 11)
                    {
                        MoveCardsAndFlip(t7u, t7u, tempNumCards);
                    }
                }
                turn = 0;
            }
        }
        glColor3ub(200, 200, 200);
        DrawRect(s1.locx + 5, s1.locy - 5, 10, 10);
        DrawRect(s2.locx + 5, s2.locy - 5, 10, 10);
        DrawRect(s3.locx + 5, s3.locy - 5, 10, 10);
        DrawRect(s4.locx + 5, s4.locy - 5, 10, 10);
        DrawRect(dis.locx + 5, dis.locy - 5, 10, 10);
        DrawRect(st.locx + 5, st.locy - 5, 10, 10);
        DrawRect(t1u.locx + 5, t1u.locy - 5, 10, 10);
        DrawRect(t2u.locx + 5, t2u.locy - 5, 10, 10);
        DrawRect(t3u.locx + 5, t3u.locy - 5, 10, 10);
        DrawRect(t4u.locx + 5, t4u.locy - 5, 10, 10);
        DrawRect(t5u.locx + 5, t5u.locy - 5, 10, 10);
        DrawRect(t6u.locx + 5, t6u.locy - 5, 10, 10);
        DrawRect(t7u.locx + 5, t7u.locy - 5, 10, 10);
        DrawGame();

        FsSwapBuffers();
    }
}