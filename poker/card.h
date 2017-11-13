#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

#include <iostream>
#include <vector>
#include <random>

//----------------------------------------------------------------------------------------------------------------------------------------
//Author:       Dr. Jairo Alejandro Gómez.
//Date:         14 September 2015.
//              23 November 2015.
//Description:  This library provides support for basic games of cards.

//----------------------------------------------------------------------------------------------------------------------------------------




//----------------------------------------------------------------------------------------------------------------------------------------
//Constants
//----------------------------------------------------------------------------------------------------------------------------------------


//Español
const std::vector<std::string> v_card_type   = {"PICAS","CORAZONES", "DIAMANTES", "TREBOLES"};
const std::vector<std::string> v_card_number = {"AS", "DOS", "TRES","CUATRO", "CINCO", "SEIS", "SIETE", "OCHO", "NUEVE", "DIEZ", "J", "Q", "K"};
const std::vector<std::string> v_expr        = {"DE"};
const std::vector<std::string> v_outcomes    = {"ESCALERA REAL O FLOR IMPERIAL", "ESCALERA DE COLOR", "PÓQUER", "FULL", "COLOR", "ESCALERA", "TRÍO", "DOBLES PAREJAS", "PAREJA", "CARTA ALTA"};


//English
//const std::vector<std::string> v_card_type   = {"SPADES", "HEARTS", "DIAMONDS", "CLUBS"};
//const std::vector<std::string> v_card_number = {"ACE", "TWO", "THREE","FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN", "J", "Q", "K"};
//const std::vector<std::string> v_expr        = {"OF"};
//const std::vector<std::string> v_outcomes    = {"ROYAL FLUSH", "STRAIGHT FLUSH", "FOUR OF A KIND OR QUAD", "FULL HOUSE", "FLUSH", "STRAIGHT", "THREE OF A KIND OR SET", "TWO PAIR OR POCKET", "ONE PAIR", "HIGH CARD"};


//----------------------------------------------------------------------------------------------------------------------------------------
//class card
//----------------------------------------------------------------------------------------------------------------------------------------
class card
{
    private:

    //Attributes
    unsigned t;  //card type
    unsigned n;  //card number

    public:
    card():t(0),n(0) {};                       //Default constructor
    card(unsigned t_given, unsigned n_given);  //Constructor with arguments
    ~card() {};                                //Basic Destructor

    //Basic methods
    unsigned int get_card_type() const;
    unsigned int get_card_number() const;
    void print_card_type() const;
    void print_card_number() const;
    void print_card() const;

    void set_card_type(const unsigned &t_received);
    void set_card_number(const unsigned &n_received);
    void set_card(const unsigned &t_received, const unsigned &n_received);


    //Overloaded operators
    void operator = (const card & c_given);               //Assignment operator
    friend std::ostream & operator << (std::ostream & out, const card & c);  //<< operator to use cout.


};


//----------------------------------------------------------------------------------------------------------------------------------------
//Functions
//----------------------------------------------------------------------------------------------------------------------------------------

// random generator function:
int myrandom (int i);

//This function is called by the function std::sort
bool cmp_numbers_in_cards(const card & left_arg, const card & right_arg);
//----------------------------------------------------------------------------------------------------------------------------------------



#endif // CARD_H_INCLUDED
