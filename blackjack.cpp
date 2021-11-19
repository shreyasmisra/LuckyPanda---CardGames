#include <iostream>
#include <stdio.h>

#include "blackjack.h"
#include "fssimplewindow.h"
#include "ysglfontdata.h"

BlackJack::BlackJack()
{
    /*userIn = '.';
    std::cout << "Playing BlackJack--\nEnter your name-> ";
    std::getline(std::cin, player_name);*/
    player_name = "Player";
    user.setName(player_name);

    std::cout << player_name << " vs " << dealer_name << "\n" << std::endl;

    mainDeck.shuffleDeck();

    ace1.setSuit(0); ace1.setRank(1);
    ace2.setSuit(1); ace1.setRank(1);
    ace3.setSuit(2); ace1.setRank(1);
    ace4.setSuit(3); ace1.setRank(1);
}
void BlackJack::setHands() {
    user.createHand(mainDeck);
    comp.createHand(mainDeck);
}
void BlackJack::playBlackJackMultipleTimes()
{
    while (true) {
        playBlackJack();
        printf("Total money = %d\n", user.getRemMoney());
        printf("Do you want to play again (y/n)? ->");
        std::cin >> userIn;
        if (userIn == 'y' || userIn == 'Y') {
            printf("Total money = %d\n", user.getRemMoney());
            continue;
        }
        else if (userIn == 'n' || userIn == 'N') {
            printf("Total money = %d\n", user.getRemMoney());
            break;
        }
        else {
            printf("Wrong input. Enter again->");
            //exit(-1);
        }
    }
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
        std::cout << "You got a BlackJack! You Won!\n\n";
        return 2;
    }
    else if (user.getSum() > 21) {
        std::cout << "You went over 21. You lost.\n\n";
        return 0;
    }
    else if (user.getSum() > comp.getSum() && user.getSum() < 21) {
        std::cout << "You beat the dealer. You won!\n\n";
        return 1;
    }
    else if (comp.getSum() > user.getSum() && comp.getSum() < 21) {
        std::cout << "The dealer beat you. You lost. Try again.\n\n";
        return 0;
    }
    else if (comp.getSum() > 21 && user.getSum() < 21) {
        std::cout << "The dealer bust. You won!\n\n";
        return 1;
    }
    else if (comp.getSum() == user.getSum() && user.getSum() <= 21) {
        std::cout << "It is a tie.\n\n";
        return 3;
    }
    else {
        std::cout << "The dealer won. You lost.\n\n";
        return 0;
    }
    return -1; // Indicates that logic is missing

}

void BlackJack::getUserInput() const
{
    /*
    Convert to a key based input
    S -> Stand
    H -> Hit
    or mouse based
    */

    std::cout << "What would you like to do?\n";
    std::cout << "Stand: \t0" << "\n";
    std::cout << "Hit: \t1" << "\n";
}
void BlackJack::playBlackJack()
{
    // Get user bet
    printf("Total Money: %d \n\nEnter bet amount>", user.getRemMoney());
    user.setBet(std::cin);
    user.setRemMoney(user.getBet() * -1); // decrease total by bet amount

    setHands();
    //comp.countHand();
    user.countHand();
    user.showHand();
    
    comp.changeBool(false);
    std::cout << dealer_name << "'s hand ---------\n\n";
    comp.showHand();

    while (gameOver == false) {
        getUserInput();
        user.setMove(std::cin); 
        if (user.getMove() == 0) {
            std::cout << "\nYou have chosen to stand.---------------\n\n";
            user.countHand(); 
            user.showHand(); 
            gameOver = true;
            break;
        }
        if (user.getMove() == 1) {
            if (numHits > MAX_HITS) {
                std::cout << "\nYou cannot get any more cards.-------------------\n\n";
                user.countHand();
                user.showHand();
                gameOver = true;
                break;
            }
            
            user.addCard(mainDeck.getRandomCard(user.getHand(), comp.getHand()));
            user.countHand(); 
            if (user.getSum() > 21 && (user.getHand().find(ace1) == true || comp.getHand().find(ace2) == true || comp.getHand().find(ace3) == true || comp.getHand().find(ace4) == true)) {
                comp.setSum(comp.getSum() - 10);
            }
            user.showHand(); 
            numHits++;
            if (user.getSum() > 21) {
                std::cout << "\nYou went over 21.-----------------\n\n";
                gameOver = true;
                break;
            }
            if (user.getSum() == 21) {
                std::cout << "\nYou got a BlackJack!\n\n";
                gameOver = true;
                break;
            }
            std::cout << dealer_name << "'s hand ---------\n\n";
            comp.showHand();
        }
    }

    comp.changeBool(true);
    comp.countHand();
    comp.showHand();
    
    while (comp.getSum() < DEALER_MIN_SUM) {
        
        comp.addCard(mainDeck.getRandomCard(user.getHand(), comp.getHand()));
        comp.countHand(); 

        if (comp.getSum() > DEALER_MIN_SUM && (comp.getHand().find(ace1) == true || comp.getHand().find(ace2) == true || comp.getHand().find(ace3) == true || comp.getHand().find(ace4) == true)) {
            comp.setSum(comp.getSum() - 10);
            
        }
        comp.showHand();
        
    }
    std::cout << "Dealer cannot take anymore cards.\n\n";

    if (checkWinner() == 2) {
        user.setRemMoney(user.getBet() * 3);
    }
    else if (checkWinner() == 1) {
        user.setRemMoney(user.getBet() * 2);
    }
    else if (checkWinner() == 3) {
        user.setRemMoney(user.getBet() * 1);
    }
    else if (checkWinner() == -1) {
        std::cout << "Logic error";
        exit(-1);
    }
    else {
        user.setRemMoney(user.getBet() * 0);
    }
}
void BlackJack::DisplayOptions() {
    
    glColor3ub(255, 0, 0);
    glRasterPos2d(70, 550);
    YsGlDrawFontBitmap16x24("Options --\n");
    glColor3ub(255, 0, 0);
    glRasterPos2d(70, 600);
    YsGlDrawFontBitmap16x24("S: To Stand\n");
    glColor3ub(255, 0, 0);
    glRasterPos2d(70, 650);
    YsGlDrawFontBitmap16x24("H: To Hit\n");
}

// Dealer class member functions

void Dealer::showHand()
{
    // Change this to a draw function
    if (!showBothCards) {
        std::cout << "1: ";
        hand.getCards()[0].print();
        std::cout << "2: CARD HIDDEN\n\n";
    }
    else {
        for (int i = 0; i < hand.getDeckSize(); i++) {
            std::cout << i + 1 << ": ";
            hand.getCards()[i].print();
        }
        std::cout << "\nTotal dealer sum = \t" << getSum() << "\n\n";
    }
    
    
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
void Dealer::changeBool(bool flag)
{
    showBothCards = flag;
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


// Player class member functions

void Player::setName(std::string str)
{
    name = str;
}
void Player::createHand(const Deck& mainDeck) {
    hand = mainDeck.subDeck(2, 3);
}
void Player::showHand()
{
    std::cout << name << "'s hand is------\n\n";
    hand.print();
    std::cout << "\nTotal player sum = \t" << getSum() << "\n\n";
}
int Player::getSum() const
{
    return sum;
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
void Player::setMove(std::istream& stream) {
    stream >> move;
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

void Player::setBet(std::istream& stream)
{
    stream >> bet;
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
