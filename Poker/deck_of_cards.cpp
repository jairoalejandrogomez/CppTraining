#include "deck_of_cards.h"

//--------------------------------------------------------------

using namespace std;




//--------------------------------------------------------------
//Class implementation.
//--------------------------------------------------------------

deck_of_cards::deck_of_cards(void)
{
    RNG_Mersenne_Twister=std::mt19937(rd());


    unsigned int t=0;
    unsigned int n=0;

    for (unsigned i=0; i<deck.size(); i++ )
    {
        //cout<<"t= "<<t<<", n= "<<n<<endl;
        deck[i].set_card(t,n);

        if (n<12) {n++;} else {n=0; t++;}
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------

deck_of_cards::~deck_of_cards(void)  //Destructor
{

}

//----------------------------------------------------------------------------------------------------------------------------------------

unsigned deck_of_cards::get_num_of_cards() const
{
    return deck.size();
}
//----------------------------------------------------------------------------------------------------------------------------------------

int deck_of_cards::see_card(const unsigned &i, card & c) const
{
    if ((i>=0) && (i<deck.size()))
    {
      c = deck.at(i);     //*it;
      return 0;   //Success;
    }
    else
    {
      cout<<"Index i for the card to see should be between 0 and "<<deck.size()<<endl;
      return 1;    //Failure;
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------

int deck_of_cards::extract_card(const unsigned &i, card & c)
{
            if ((i>=0) && (i<deck.size()))
            {
                auto it = deck.begin();  //This is equivalent to:      vector <card>::iterator it = deck.begin();
                it+=i;                   //Increment iterator so that it point to the desired card.
                c = deck.at(i);     //*it;
                deck.erase(it);

                return 0;   //Success;
            }
            else
            {
                cout<<"Index i for the card to extract should be between 0 and "<<deck.size()<<endl;
                return 1;    //Failure;
            }
}
//----------------------------------------------------------------------------------------------------------------------------------------

int deck_of_cards::extract_n_cards(const unsigned &n, vector<card> & v)
{
            if ((n>=0) && (n<deck.size()))
            {
                vector< card >::iterator it_b = deck.begin();    //Initial iterator
                vector< card >::iterator it_e = it_b + n;         //End iterator (remember that this is a sentinel so it goes all the way up to +1)

                copy (it_b,it_e,v.begin());   //Copy function from the STL of c++11.
                this->deck.erase(it_b,it_e);  //Remove the cards from the deck of cards.

                return 0;   //Success;
            }
            else
            {
                cout<<"The number of cards has to be between 0 and "<<deck.size()<<endl;
                return 1;    //Failure;
            }
}

//----------------------------------------------------------------------------------------------------------------------------------------

void deck_of_cards::shuffle_cards()
{
    std::shuffle(deck.begin(), deck.end(),RNG_Mersenne_Twister);   //This is available in STL of c++
}

//----------------------------------------------------------------------------------------------------------------------------------------

 void deck_of_cards::print_deck()
 {
     for (auto it=deck.begin(); it!=deck.end(); ++it)
     {
        cout<<(*it)<<endl;
     }
 }

//----------------------------------------------------------------------------------------------------------------------------------------

ostream & operator << (ostream & out, const deck_of_cards & d)  //<< operator to use cout.
{
     for (auto it=d.deck.begin(); it!=d.deck.end(); ++it)
     {
        out<<(*it)<<endl;
     }

     return out;
}

//----------------------------------------------------------------------------------------------------------------------------------------
