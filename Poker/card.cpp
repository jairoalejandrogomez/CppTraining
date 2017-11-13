#include "card.h"


//--------------------------------------------------------------
using namespace std;


//----------------------------------------------------------------------------------------------------------------------------------------
//Random number generator.
//----------------------------------------------------------------------------------------------------------------------------------------
std::random_device rd;
std::mt19937 RNG_MersenneTwister(rd());      //Non-deterministic 32-bit seed.
                                              //Possible slow.
                                              //Strongly platform-dependent.
                                              //Possibly crypto-secure.
                                              //Non-seedable, non-reproducible.

//--------------------------------------------------------------
//Functions.
//--------------------------------------------------------------

// random generator function:
int myrandom (int i)
{
    std::uniform_int_distribution<int> dist(0,i);
    return dist(RNG_MersenneTwister);
}

//This function is called by the function std::sort
bool cmp_numbers_in_cards(const card & left_arg, const card & right_arg)
{
  return left_arg.get_card_number() < right_arg.get_card_number();
}


//--------------------------------------------------------------
//Class implementation.
//--------------------------------------------------------------


card::card(unsigned t_given, unsigned n_given)      //Constructor with arguments
{
        if ((t_given>=0) && (t_given<4))
        {
         t=t_given;
        }
        else
        {
         cout<<"A card type is represented by a number between 0 and 3"<<endl;
        }


        if ((n_given>=0) && (n_given<13))
        {
            n= n_given;
        }
        else
        {
          cout<<"A card number is represented by a number between 0 and 12"<<endl;
        }
}

//--------------------------------------------------------------
unsigned int card::get_card_type() const
{
 return t;
}
//--------------------------------------------------------------
unsigned int card::get_card_number() const
{
 return n;
}
//--------------------------------------------------------------
void card::print_card_type() const
{
    cout<<v_card_type.at(t);
}
//--------------------------------------------------------------

void card::print_card_number() const
{
    cout<<v_card_number.at(n);
}
//--------------------------------------------------------------
void card::print_card() const
{   this->print_card_number();
    cout<<" "<< v_expr.at(0) <<" ";
    this->print_card_type();
    cout<<" ";
}

//--------------------------------------------------------------

void card::set_card_type(const unsigned &t_received)
{
    t=t_received;
}

//--------------------------------------------------------------
void card::set_card_number(const unsigned &n_received)
{
    n=n_received;
}


//--------------------------------------------------------------
void card::set_card(const unsigned &t_received, const unsigned &n_received)
{
    t=t_received;
    n=n_received;
}


//--------------------------------------------------------------
void card::operator = (const card & c_given)   //Assignment operator
{
       if (this == &c_given)  //If it is the same.
       {
            //Don't do anything
       }
       else
       {
         this->t = c_given.t;
         this->n = c_given.n;

       }
}
//--------------------------------------------------------------
ostream & operator << (ostream & out, const card & c)
{
    out<<v_card_number.at(c.get_card_number())<<" "<<v_expr.at(0)<<" "<< v_card_type.at(c.get_card_type())<<" ";
    return out;
}
//--------------------------------------------------------------
