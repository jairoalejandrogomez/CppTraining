#ifndef POKER_H_INCLUDED
#define POKER_H_INCLUDED

#include "deck_of_cards.h"

//----------------------------------------------------------------------------------------------------------------------------------------
//Author:       Dr. Jairo Alejandro Gómez.
//Date:         14 September 2015.
//              23 November 2015.
//Description:  This library provides support for a basic game of poker.

//----------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------
//poker class.  For the theory behind it go to https://es.wikipedia.org/wiki/Póquer
//----------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------

class poker_player
{
private:
    std::vector < card > v_cards = std::vector < card > (5);

    //Possible states in poker for the current set of cards.
    bool is_a_Royal_flush;
    bool is_a_Straight_flush;
    bool is_a_Four_of_a_kind_or_Quad;
    bool is_a_Full_House;
    bool is_a_Flush;
    bool is_a_Straight;
    bool is_a_Three_of_a_kind_or_Set;
    bool is_a_Two_pair_or_Pocket;
    bool is_a_One_pair;
    unsigned what_is_the_High_card;


public:
    poker_player(deck_of_cards &d);                              //Constructor. Notice that the deck will be changed by this constructor, that is why it should be passed by reference.
    poker_player(card c0, card c1, card c2, card c3, card c4);   //Constructor used ONLY for testing poker behavior.
    ~poker_player(){};                                           //Destructor.

    int get_card(const unsigned &i, card & c) const;
    void sort_cards();
    void print_cards();

    //Poker related methods.
    bool is_a_set_of_the_same_type();
    bool is_a_set_of_the_same_color();
    bool is_a_set_of_consecutive_numbers();
    void get_histogram(unsigned &number_of_pairs, unsigned &number_of_three_of_a_kind, unsigned &number_of_four_of_a_kind);
    void clear_all_flags();          //This clears the state of the poker.
    void update_flags();

    void print_poker_status();


    friend std::ostream & operator << (std::ostream &out, const poker_player & p);
};

//----------------------------------------------------------------------------------------------------------------------------------------



#endif // POKER_H_INCLUDED
