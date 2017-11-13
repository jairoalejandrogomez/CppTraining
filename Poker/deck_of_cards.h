#ifndef DECK_OF_CARDS_H_INCLUDED
#define DECK_OF_CARDS_H_INCLUDED
//----------------------------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <iterator>
#include <random>
#include <algorithm>   //To do sort, shuffle,  and things like that...

//----------------------------------------------------------------------------------------------------------------------------------------

#include "card.h"

//----------------------------------------------------------------------------------------------------------------------------------------
//Author:       Dr. Jairo Alejandro Gómez.
//Date:         14 September 2015.
//              23 November 2015.
//Description:  This library provides support for basic games of cards.

//----------------------------------------------------------------------------------------------------------------------------------------







//----------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------
//Class deck_of_cards
//----------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------


class deck_of_cards
{
private:
    std::vector <card> deck = std::vector <card> (52);  //There are 52 cards for a new deck of cards

    std::random_device rd;
    std::mt19937 RNG_Mersenne_Twister;           //Non-deterministic 32-bit seed.
                                                  //Possible slow.
                                                  //Strongly platform-dependent.
                                                  //Possibly crypto-secure.
                                                  //Non-seedable, non-reproducible.
public:
    deck_of_cards(void);      //Constructor
    ~deck_of_cards(void);     //Destructor


    //Methods
    int see_card(const unsigned &i, card & c) const;            //The card remains in the deck
    int extract_card(const unsigned &i, card & c);              //The card is removed from the deck and passed as reference in c.
    int extract_n_cards(const unsigned &n, std::vector<card> & v);   //This removes n cards from the deck, and sends them to v.
    unsigned get_num_of_cards() const;
    void     print_deck();
    void shuffle_cards();

    //Operators
    friend std::ostream & operator << (std::ostream & out, const deck_of_cards & d);  //<< operator to use cout.
};


//----------------------------------------------------------------------------------------------------------------------------------------


#endif // DECK_OF_CARDS_H_INCLUDED
