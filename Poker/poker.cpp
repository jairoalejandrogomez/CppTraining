#include "poker.h"

//--------------------------------------------------------------

using namespace std;



//--------------------------------------------------------------
//Class implementation.
//--------------------------------------------------------------

poker_player::poker_player(deck_of_cards &d)
{
   clear_all_flags();

   int flag = d.extract_n_cards(5,v_cards);
   if (flag==1)
   {
       cout<<"There was an error getting the cards for the player"<<endl;
   }
   else
   {
       sort_cards();
       update_flags();
   }
}

//--------------------------------------------------------------

//Constructors for testing:
poker_player::poker_player(card c0, card c1, card c2, card c3, card c4)
{
   clear_all_flags();

   //Assign hand.
   v_cards.at(0)=c0;
   v_cards.at(1)=c1;
   v_cards.at(2)=c2;
   v_cards.at(3)=c3;
   v_cards.at(4)=c4;

   sort_cards();
   update_flags();
}



//----------------------------------------------------------------------------------------------------------------------------------------

void poker_player::clear_all_flags()
{
    is_a_Royal_flush= false;
    is_a_Straight_flush= false;
    is_a_Four_of_a_kind_or_Quad= false;
    is_a_Full_House= false;
    is_a_Flush= false;
    is_a_Straight= false;
    is_a_Three_of_a_kind_or_Set= false;
    is_a_Two_pair_or_Pocket= false;
    is_a_One_pair= false;
    what_is_the_High_card= 0;
}
//----------------------------------------------------------------------------------------------------------------------------------------

void poker_player::update_flags()
{
    bool flag_is_a_set_of_the_same_type  = is_a_set_of_the_same_type();
    //bool flag_is_a_set_of_the_same_color = is_a_set_of_the_same_color();  //This is not used in Poker
    bool flag_is_a_set_of_consecutive_numbers = is_a_set_of_consecutive_numbers();

    unsigned number_of_pairs          =0;
    unsigned number_of_three_of_a_kind=0;
    unsigned number_of_four_of_a_kind =0;

    get_histogram(number_of_pairs,number_of_three_of_a_kind,number_of_four_of_a_kind);

    //----------------------------------
    //Check a Royal Flush
    //----------------------------------
    if   (flag_is_a_set_of_the_same_type  &&  flag_is_a_set_of_consecutive_numbers && (v_cards.at(0).get_card_number() == 0))  //The last sentence is to verify that the first card is an ace.
    {
        is_a_Royal_flush= true;
    }
    else
    {
        is_a_Royal_flush= false;
    }

    //----------------------------------
    //Check a Straight_flush
    //----------------------------------

    if   (flag_is_a_set_of_the_same_type &&  flag_is_a_set_of_consecutive_numbers)
    {
            is_a_Straight_flush= true;
    }
    else
    {
            is_a_Straight_flush= false;
    }
    //----------------------------------
    //Check a Four of a kind or Quad
    //----------------------------------
    if (number_of_four_of_a_kind == 1)
    {
        is_a_Four_of_a_kind_or_Quad= true;
    }
    else
    {
        is_a_Four_of_a_kind_or_Quad= false;
    }
    //----------------------------------
    //Check a Full House
    //----------------------------------


    if ((number_of_three_of_a_kind == 1) && (number_of_pairs ==1 ) )
    {
        is_a_Full_House= true;
    }
    else
    {
        is_a_Full_House= false;
    }
    //----------------------------------
    //Check a Flush
    //----------------------------------

    is_a_Flush=flag_is_a_set_of_the_same_type;

    //----------------------------------
    //Check a Straight
    //----------------------------------

    is_a_Straight=flag_is_a_set_of_consecutive_numbers;

    //----------------------------------
    //Check a Three of a kind or Set
    //----------------------------------

    if (number_of_three_of_a_kind == 1)
    {
        is_a_Three_of_a_kind_or_Set= true;
    }
    else
    {
        is_a_Three_of_a_kind_or_Set= false;
    }

    //----------------------------------
    //Check a Two pair or Pocket
    //----------------------------------

    if (number_of_pairs == 2)
    {
        is_a_Two_pair_or_Pocket= true;
    }
    else
    {
        is_a_Two_pair_or_Pocket= false;
    }

    //----------------------------------
    //Check a One pair
    //----------------------------------
    if (number_of_pairs == 1)
    {
        is_a_One_pair= true;
    }
    else
    {
        is_a_One_pair= false;
    }

    //----------------------------------
    //Get the highest card
    //----------------------------------

    what_is_the_High_card=v_cards.at(4).get_card_number();  //Because the way cards are ordered, the highest card is the last one (5th card = 4th index).

}

//----------------------------------------------------------------------------------------------------------------------------------------

int poker_player::get_card(const unsigned &i, card & c) const
{
    if ((i>=0) && (i<5))
    {
        c = v_cards.at(i);
        return 0;  //Success
    }
    else
    {
        cout<<"There are only 5 cards, therefore, i should be an unsigned integer from 0 to 4"<<endl;
        return 1; //Failure.
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------

void poker_player::sort_cards()
{
    sort(v_cards.begin(), v_cards.end(), cmp_numbers_in_cards);   //This function is from STL.
}

//----------------------------------------------------------------------------------------------------------------------------------------

void  poker_player::print_cards()
{
    for (auto it=v_cards.begin(); it!=v_cards.end(); ++it)
    {
        cout<<(*it)<<endl;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------

ostream & operator << (ostream &out, const poker_player & p)
{
    for (auto it=p.v_cards.begin(); it!=p.v_cards.end(); ++it)
    {
        cout<<(*it)<<endl;
    }

    return out;
}

//----------------------------------------------------------------------------------------------------------------------------------------

bool poker_player::is_a_set_of_the_same_type()
{
        bool flag=true;
        for (auto it=v_cards.begin(); it!=(v_cards.end()-1); ++it)
        {
            if  ((*it).get_card_type() != (*(it+1)).get_card_type())  //If two cards don't have the same type, the set, doesn't have the same type.
            {
                flag = false;
                break;
            }
        }
        return flag;
}

//----------------------------------------------------------------------------------------------------------------------------------------

//This is not used in Poker.
bool poker_player::is_a_set_of_the_same_color()
{
        bool flag=true;
        bool all_black=true;
        bool all_red=true;

        for (auto it=v_cards.begin(); it!=(v_cards.end()-1); ++it)
        {
            // Check black color
            if  (!((((*it).get_card_type() == 0) && ((*(it+1)).get_card_type() ==3)) || (((*it).get_card_type() == 3) && ((*(it+1)).get_card_type() ==0))))
            {
                all_black = false;
            }
            //--------------------
            //Check red color
            if  (!((((*it).get_card_type() == 1) && ((*(it+1)).get_card_type() ==2)) || (((*it).get_card_type() == 2) && ((*(it+1)).get_card_type() ==1))))
            {
                all_red = false;
            }
        }

        flag = all_red || all_black;

        return flag;
}

//----------------------------------------------------------------------------------------------------------------------------------------

 bool poker_player::is_a_set_of_consecutive_numbers()
 {
      bool flag=false;

      //Auxiliar variables
      unsigned n0=v_cards.at(0).get_card_number();
      unsigned n1=v_cards.at(1).get_card_number();
      unsigned n2=v_cards.at(2).get_card_number();
      unsigned n3=v_cards.at(3).get_card_number();
      unsigned n4=v_cards.at(4).get_card_number();

      if ((n0==0) && (n4==12))
      {
         //There seems to be four exceptions of consecutive numbers, after ordering the cards by increasing index. All the exceptions start with an ace, and finish with K
         bool exception1 =   ((n1==9) && (n2==10) && (n3==11)); //ace 10 J Q K
         bool exception2 =   ((n1==1) && (n2==10) && (n3==11)); //ace 2  J Q K
         bool exception3 =   ((n1==1) && (n2==2)  && (n3==11)); //ace 2  3 Q K
         bool exception4 =   ((n1==1) && (n2==2)  && (n3== 3)); //ace 2  3 4 K

         flag = (exception1 || exception2 || exception3 || exception4);
      }
      else if (((n0+1)==n1) && ((n1+1)==n2) && ((n2+1)==n3) && ((n3+1)==n4))
      {
          flag = true;
      }

      return flag;
 }

//----------------------------------------------------------------------------------------------------------------------------------------

 void poker_player::get_histogram(unsigned &number_of_pairs, unsigned &number_of_three_of_a_kind, unsigned &number_of_four_of_a_kind)
 {
    vector<unsigned> h(13,0); //a vector of 13 elements (= to the number of cards from a given kind), initialized in 0.

    number_of_pairs = 0;
    number_of_three_of_a_kind = 0;
    number_of_four_of_a_kind = 0;

    //Get the histogram.
    for (card c : v_cards)
    {
        h.at(c.get_card_number()) =  h.at(c.get_card_number()) + 1;  //This is a histogram
    }

    //Find out how many pairs and three of a kind are in the current set.
    for (unsigned n_cards : h)
    {
        if (n_cards == 2)
        {
          number_of_pairs++;
        }
        else if (n_cards == 3)
        {
          number_of_three_of_a_kind++;
        }
        else if (n_cards == 4)
        {
          number_of_four_of_a_kind++;
        }
    }

 }

//----------------------------------------------------------------------------------------------------------------------------------------


void poker_player::print_poker_status()
{
    cout<<"Royal flush \t\t"           <<" = "<< is_a_Royal_flush<<endl;
    cout<<"Straight flush \t\t"        <<" = "<< is_a_Straight_flush<<endl;
    cout<<"Four of a kind or Quad \t"  <<" = "<< is_a_Four_of_a_kind_or_Quad<<endl;
    cout<<"Full_House \t\t"            <<" = "<< is_a_Full_House<<endl;
    cout<<"Flush \t\t\t"               <<" = "<< is_a_Flush<<endl;
    cout<<"Straight \t\t"              <<" = "<< is_a_Straight<<endl;
    cout<<"Three of a kind or Set \t"  <<" = "<< is_a_Three_of_a_kind_or_Set<<endl;
    cout<<"Two pair or Pocket \t"      <<" = "<< is_a_Two_pair_or_Pocket<<endl;
    cout<<"One pair \t\t"              <<" = "<< is_a_One_pair<<endl;
    cout<<"Highest card \t\t"          <<" = "<< v_card_number.at(what_is_the_High_card) <<endl;
}


//----------------------------------------------------------------------------------------------------------------------------------------




