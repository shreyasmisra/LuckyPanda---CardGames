#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <chrono>
#include <thread>

#include "blackjack.h"
#include "generic.h"
#include "graphics.h"
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yssimplesound.h"

BlackJack::BlackJack()
{
    int userMove = -1;
    mainDeck.shuffleDeck();
    mainDeck.setGraphicsIndices();
    
    ace1.setSuit(0); ace1.setRank(1);
    ace2.setSuit(1); ace1.setRank(1);
    ace3.setSuit(2); ace1.setRank(1);
    ace4.setSuit(3); ace1.setRank(1);
}
void BlackJack::setHands() {
    user.createHand(mainDeck);
    comp.createHand(mainDeck);
}

int BlackJack::checkWinner() const
{
    /*
    Checks the total counts of the dealer and the player to figure out who won.
    To improve - add more logic.

    BlackJack Logic

    return:
    1-> Player wins
    0-> Dealer wins
    -1-> Missing logic
    */

    if (user.getSum() == 21 && comp.getSum() != 21) {
        return 2;
    }
    else if (user.getSum() > 21) {
        return 0;
    }
    else if (user.getSum() > comp.getSum() && user.getSum() < 21) {
        return 1;
    }
    else if (comp.getSum() > user.getSum() && comp.getSum() < 21) {
        return 0;
    }
    else if (comp.getSum() > 21 && user.getSum() < 21) {
        return 1;
    }
    else if (comp.getSum() == user.getSum() && user.getSum() <= 21) {
        return 3;
    }
    else {
        return 0;
    }
    return -1; // Indicates that logic is missing
}
void BlackJack::PlayerTurn() {
    
    if (user.getMove() == 0) {
        user.countHand();
        playerTurn = false;
        dealerTurn = true;
        playerState = 0; // transitioning to dealer turn
    }
    else if (user.getMove() == 1) {
        if (numHits == MAX_HITS) {
            user.countHand();
            playerTurn = false;
            dealerTurn = true;
            playerState = 0; // transitioning to dealer turn
            }
        else {
            user.addCard(mainDeck.getRandomCard(user.getHand(), comp.getHand()));
            user.countHand();
            if (user.getSum() > 21 && (user.getHand().find(ace1) == true || comp.getHand().find(ace2) == true || comp.getHand().find(ace3) == true || comp.getHand().find(ace4) == true)) {
                user.setSum(user.getSum() - 10);
                //std::cout << "hi";
            }
            numHits++;
            playerState = 0; // to get the next input

            if (user.getSum() > 21) {
                playerTurn = false;
                dealerTurn = true;
                playerState = 0;
            }
        }
    }
    user.setCoordinates();
}
void BlackJack::DealerTurn() {

    if (comp.getSum() < DEALER_MIN_SUM) {

        comp.addCard(mainDeck.getRandomCard(user.getHand(), comp.getHand()));
        comp.countHand();

        if (comp.getSum() > DEALER_MIN_SUM && (comp.getHand().find(ace1) == true || comp.getHand().find(ace2) == true || comp.getHand().find(ace3) == true || comp.getHand().find(ace4) == true)) {
            comp.setSum(comp.getSum() - 10);
            //std::cout << "hi";
        }
        if (comp.getSum() > 21) {
            dealerTurn = false;
            goToWinner = true;
        }
    }
    else {
        dealerTurn = false;
        goToWinner = true;
    }
    comp.setCoordinates();
}
void BlackJack::EndGameOptions() const {
    glColor3ub(0, 0, 0);
    glRasterPos2d(10, 790);
    YsGlDrawFontBitmap16x20("N: New Game");
    
    glRasterPos2d(230, 790);
    YsGlDrawFontBitmap16x20("M: Main Menu");

    glRasterPos2d(460, 790);
    YsGlDrawFontBitmap16x20("ESC: Quit Program");

}
int BlackJack::playBlackJack(MainData& dat, int money)
{
    
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;

    setHands();    
    user.countHand(); user.initCoordinates();
    comp.countHand(); comp.initCoordinates();
    int winner = -2;
    bool sleep = true;
    
    int bet = 0;
    
    auto b = std::to_string(bet);

    YsSoundPlayer soundPlayer;
    YsSoundPlayer::SoundData wav;
    if (YSOK != wav.LoadWav(dat.soundName.c_str()))
    {
        printf("Failed to read %s\n", dat.soundName.c_str());
        return -1;
    }
    soundPlayer.Start();
 
    while (getBet) {
        
        FsPollDevice();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto key = FsInkey();
        if (key == FSKEY_ESC) {
            break;
        }
        else if (FSKEY_UP == key && bet != dat.getMoney()) {
            bet += betdx;
            b = std::to_string(bet);
        }
        else if (FSKEY_DOWN == key && bet != 0) {
            bet -= betdx;
            b = std::to_string(bet);
        }
        else if (FSKEY_ENTER == key) {
            getBet = false;
            dat.setMoney(-1 * bet);
            break;
        }
        

        ColorBackGround();
        DisplayBlackJackBackground(dat);
        
        DisplayMoneyAndName(dat);
        
        glColor3ub(255, 0, 0);
        glRasterPos2d(500, 80);
        YsGlDrawFontBitmap32x48("BlackJack");

        glColor3ub(255, 0, 0);
        glRasterPos2d(150, 750);
        YsGlDrawFontBitmap20x28("Enter Bet Amount: $");

        glRasterPos2d(535, 750);
        YsGlDrawFontBitmap20x28(b.c_str());
        
        FsSwapBuffers();
        FsSleep(10);
    }

    while (playGame) {
        
        FsPollDevice();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto key = FsInkey();
        if (key == FSKEY_ESC) {
            return 0;
        }

        if (playerTurn && FSKEY_S == key) {
            user.setMove(0);
            playerState = 1;
        }
        else if (playerTurn && FSKEY_H == key) {
            user.setMove(1);
            playerState = 1;
        }
        else if (!dealerTurn && !playerTurn && FSKEY_N == key) {
            return 1; // new blackjack game
        }
        else if (!dealerTurn && !playerTurn && FSKEY_M == key) {
            return 2; // choose new game in the main menu
        }

        if (playerTurn == true && dealerTurn == false && playerState == 1) {
            PlayerTurn();
        }
        if (dealerTurn == true && playerTurn == false) {
            DealerTurn();
        }

        if (dealerTurn == false && playerTurn == false && goToWinner) {
            winner = checkWinner();
            switch (winner) {
            case 1:
                dat.setMoney(2 * bet);
                soundPlayer.PlayOneShot(wav);
                break;
            case 2:
                dat.setMoney(3 * bet);
                soundPlayer.PlayOneShot(wav);
                break;
            case 3:
                dat.setMoney(1 * bet);
                break;
            case 0:
                dat.setMoney(0 * bet);
                break;
            }
            start = std::chrono::system_clock::now();
            goToWinner = false;
        }
        
        // Rendering functions

        ColorBackGround();
        DisplayBlackJackBackground(dat);

        DisplayMoneyAndName(dat);
        
        glColor3ub(255, 0, 0);
        glRasterPos2d(500, 80);
        YsGlDrawFontBitmap32x48("BlackJack");


        if (playerTurn == true && dealerTurn == false) {
            DisplayOptions();
            comp.drawOne(dat);
        }
        if (dealerTurn == true && playerTurn == false) {
            comp.drawTwo(dat);
        }

        if (dealerTurn == false && playerTurn == false) {
        
            int r = rand() % 256;
            int g = rand() % 256;
            int b = rand() % 256;
            if (winner == 3) {
                glColor3ub(0, 0, 255);
                glRasterPos2d(350, 750);
                YsGlDrawFontBitmap16x20("It's a  tie.");
            }
            else if (winner == 2) {
                glColor3ub(r, g, b);
                glRasterPos2d(150, 750);
                YsGlDrawFontBitmap16x20("You got a BlackJack! You Won!!");
            }
            else if (winner == 1) {
                glColor3ub(r, g, b);
                glRasterPos2d(150, 750);
                YsGlDrawFontBitmap16x20("You beat the dealer. You Won!!");
            }
            else if (winner == 0) {
                glColor3ub(0, 0, 255);
                glRasterPos2d(150, 750);
                YsGlDrawFontBitmap16x20("The dealer beat you. You Lose :(");
            }
            comp.drawTwo(dat);
            elapsed_seconds = std::chrono::system_clock::now() - start;
            if (elapsed_seconds.count() > 3.0 ) {
                EndGameOptions();
            }
        }
        user.drawHand(dat);
        FsSwapBuffers();
        FsSleep(25);
    }
    soundPlayer.End();
}
void BlackJack::DisplayOptions() const {
    
    glColor3ub(255, 0, 0);
    glRasterPos2d(20, 730);
    YsGlDrawFontBitmap16x20("Player's turn. Options --\n");
    glColor3ub(255, 0, 0);
    glRasterPos2d(20, 760);
    YsGlDrawFontBitmap16x20("S: To Stand\n");
    glColor3ub(255, 0, 0);
    glRasterPos2d(20, 790);
    YsGlDrawFontBitmap16x20("H: To Hit\n");
}
void BlackJack::DisplayBlackJackBackground(const MainData& dat) const {
    Render(dat, 0, 700, 53);
}

int Dealer::getSum() const
{
    return sum;
}
void Dealer::countHand()
{
    sum = 0;
    for (int i = 0; i < hand.getCards().size(); i++) {
        if (hand.getCards()[i].getRank() >= 11) {
            sum += 10;
        }
        else if (hand.getCards()[i].getRank() == 1)  {
            sum += 11;
            if (sum > 21) {
                sum -= 11;
                sum++;
            }
        }
        else {
            sum += hand.getCards()[i].getRank();
        }
    }
}
void Dealer::createHand(const Deck& mainDeck)
{
    hand = mainDeck.subDeck(0, 1);
}
Deck Dealer::getHand() const {
    return hand;
}
void Dealer::addCard(const Card& c)
{
    hand.getCards().push_back(c);
}
void Dealer::setSum(int x) {
    sum = x;
}
void Dealer::initCoordinates() {
    std::vector<Card>& cards = hand.getCards(); // careful

    cards[0].setPos(280, 350);
    cards[1].setPos(430, 350);
}
void Dealer::setCoordinates() {
    if (hand.getDeckSize() == 5) {
        std::vector<Card>& c = hand.getCards();

        c.back().setPosY(350); // same as others
        c.back().setPosX(c[c.size() - 2].getPos()[0] + 100); // set x as previous cards x

        for (int i = 0; i < hand.getDeckSize() - 1; ++i) {
            c[i].setPosX(c[i].getPos()[0] - 50); // move all previous cards by 100 towards left
        }
    }
    else if (hand.getDeckSize() == 4) {
         std::vector<Card>& c = hand.getCards();

         c.back().setPosY(350); // same as others
         c.back().setPosX(c[c.size() - 2].getPos()[0] + 100); // set x as previous cards x

         for (int i = 0; i < hand.getDeckSize() - 1; ++i) {
             c[i].setPosX(c[i].getPos()[0] - 50); // move all previous cards by 100 towards left
         }
    }
    else if (hand.getDeckSize() == 3) {
         std::vector<Card>& c = hand.getCards();

         c.back().setPosY(350); // same as others
         c.back().setPosX(c[c.size() - 2].getPos()[0] + 50); // set x as previous cards x

         for (int i = 0; i < hand.getDeckSize() - 1; ++i) {
             c[i].setPosX(c[i].getPos()[0] - 100); // move all previous cards by 100 towards left
         }
    }
}
void Dealer::drawOne(const MainData& dat) {
    
    Render(dat, hand.getCards()[0].getPos()[0], hand.getCards()[0].getPos()[1], hand.getCards()[0].getGraphicsIndex(), 1.4);
    Render(dat, hand.getCards()[1].getPos()[0], hand.getCards()[1].getPos()[1], 0, 1.4);

}
void Dealer::drawTwo(const MainData& dat) {

    for (int i = 0; i < hand.getDeckSize(); ++i) {
        Render(dat, hand.getCards()[i].getPos()[0], hand.getCards()[i].getPos()[1], hand.getCards()[i].getGraphicsIndex(), 1.4);
    }
    showSum();
}
void Dealer::showSum() const {
    glColor3ub(255, 255, 255);
    glRasterPos2d(260, 200);
    YsGlDrawFontBitmap16x24("Dealer total: ");

    auto f = std::to_string(sum);
    const char* sumChar = f.c_str();

    glRasterPos2d(490, 200);
    YsGlDrawFontBitmap16x24(sumChar);
}


// Player class member functions

void Player::setName(std::string str)
{
    name = str;
}
void Player::createHand(const Deck& mainDeck) {
    hand = mainDeck.subDeck(2, 3);
}
int Player::getSum() const
{
    return sum;
}
void Player::setSum(const int x) {
    sum = x;
}
void Player::countHand()
{
    sum = 0;
    for (int i = 0; i < hand.getCards().size(); i++) {
        if (hand.getCards()[i].getRank() >= 11) {
            sum += 10;
        }
        else if (hand.getCards()[i].getRank() == 1) {
            sum += 11;
            if (sum > 21) {
                sum -= 11;
                sum++;
            }
        }
        else {
            sum += hand.getCards()[i].getRank();
        }
    }
}
void Player::setMove(const int val) {
    move = val;
}
int Player::getMove() const {
    return move;
}
Deck Player::getHand() const {
    return hand;
}
void Player::addCard(const Card& c)
{
    hand.getCards().push_back(c);
}

void Player::setBet(const int x)
{
    bet = x;
}
void Player::setRemMoney(const int x)
{
    totalMoney += x;
}

int Player::getBet() const
{
    return bet;
}
int Player::getRemMoney() const
{
    return totalMoney;
}
void Player::initCoordinates() {
    std::vector<Card>& cards = hand.getCards();

    cards[0].setPos(280, 500);
    cards[1].setPos(430, 500);
}
void Player::drawHand(const MainData& dat) {

    std::vector<Card> c = hand.getCards();
    double scale = 1.4;
    for (int i = 0; i < hand.getDeckSize(); ++i) {
        Render(dat, c[i].getPos()[0], c[i].getPos()[1], c[i].getGraphicsIndex(), scale);
    }
    
    showSum();
}
void Player::showSum() const {
    glColor3ub(255, 255, 255);
    glRasterPos2d(270, 550);
    YsGlDrawFontBitmap20x28("Player Total: ");

    auto f = std::to_string(sum);
    const char* sumChar = f.c_str();
    
    glRasterPos2d(530, 550);
    YsGlDrawFontBitmap20x28(sumChar);
}
void Player::setCoordinates()
{
    // init coords are 250, 350 in X and 500 in Y
    if (hand.getDeckSize() == 5) {
        std::vector<Card>& c = hand.getCards();

        c.back().setPosY(500); // same as others
        c.back().setPosX(c[c.size() - 2].getPos()[0] + 50); // set x as previous cards x

        for (int i = 0; i < hand.getDeckSize() - 1; ++i) {
            c[i].setPosX(c[i].getPos()[0] - 100); // move all previous cards by 100 towards left
        }
    }
    else if (hand.getDeckSize() == 4) {
         std::vector<Card>& c = hand.getCards();

         c.back().setPosY(500); // same as others
         c.back().setPosX(c[c.size() - 2].getPos()[0] + 100); // set x as previous cards x

         for (int i = 0; i < hand.getDeckSize() - 1; ++i) {
             c[i].setPosX(c[i].getPos()[0] - 50); // move all previous cards by 100 towards left
         }
    }
    else if (hand.getDeckSize() == 3) {
         std::vector<Card>& c = hand.getCards();

         c.back().setPosY(500); // same as others
         c.back().setPosX(c[c.size() - 2].getPos()[0] + 100); // set x as previous cards x      

         for (int i = 0; i < hand.getDeckSize() - 1; ++i) {
             c[i].setPosX(c[i].getPos()[0] - 50); // move all previous cards by 100 towards left

         }
    }
}