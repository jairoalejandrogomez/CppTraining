#include <iostream>

#include "poker.h"


using namespace std;

int main()
{
    card c(1,2);
    c.print_card();


    cout<<endl;
    card c2;
    c2.print_card();

    cout<<endl;
    card c3(c);
    c3.print_card();

    cout<<endl;
    c3=c2;
    c3.print_card();

    cout<<endl<<"c: "<<c<<" c2: "<<c2 <<" c3: "<<c3<<endl;

    deck_of_cards d;
    cout<<endl<<"Now, let's print the deck of cards"<<endl;
    d.print_deck();

    card c4;
    d.extract_card(0, c4);  //The removed card is stored in c4.

    cout<<endl<<"The extracted card was "<<c4<<endl;

    cout<<endl<<"Now, let's print the deck of cards again using cout this time"<<endl;
    cout<<d<<endl;

    d.shuffle_cards();      //Mezclar las cartas
    cout<<endl<<"The deck after shuffling it is:"<<endl<<d<<endl;


    poker_player p1(d);

    cout<<"Cards from player 1 are: "<<endl;
    p1.print_cards();

    p1.sort_cards();
    cout<<endl<<"Cards from player 1 ordered by number are:"<<endl<<p1<<endl;

    //cout<<endl<<"The deck after giving the cards to the first player:"<<endl<<d<<endl;



    //-----------------------------------------------------------------------------------------
    //This section is for testing...
    //-----------------------------------------------------------------------------------------

    //Royal flush
    card cp10(3,0);
    card cp11(3,12);
    card cp12(3,11);
    card cp13(3,10);
    card cp14(3,9);
    poker_player px1(cp10,cp11,cp12,cp13,cp14);
    cout<<endl<<"The cards for the current player are: "<<endl<<px1;
    cout<<endl<<"Statistics for current player"<<endl;
    px1.print_poker_status();


    //Straight flush
    card cp20(2,6);
    card cp21(2,7);
    card cp22(2,8);
    card cp23(2,9);
    card cp24(2,10);
    poker_player px2(cp20,cp21,cp22,cp23,cp24);
    cout<<endl<<"The cards for the current player are: "<<endl<<px2;
    cout<<endl<<"Statistics for current player"<<endl;
    px2.print_poker_status();


    //Four of a kind o Quad
    card cp30(1,8);
    card cp31(0,8);
    card cp32(3,8);
    card cp33(2,8);
    card cp34(2,2);
    poker_player px3(cp30,cp31,cp32,cp33,cp34);
    cout<<endl<<"The cards for the current player are: "<<endl<<px3;
    cout<<endl<<"Statistics for current player"<<endl;
    px3.print_poker_status();

    //Full House
    card cp40(2,5);
    card cp41(0,5);
    card cp42(1,5);
    card cp43(3,2);
    card cp44(0,2);
    poker_player px4(cp40,cp41,cp42,cp43,cp44);
    cout<<endl<<"The cards for the current player are: "<<endl<<px4;
    cout<<endl<<"Statistics for current player"<<endl;
    px4.print_poker_status();


    //Flush
    card cp50(1,1);
    card cp51(1,6);
    card cp52(1,10);
    card cp53(1,0);
    card cp54(1,3);
    poker_player px5(cp50,cp51,cp52,cp53,cp54);
    cout<<endl<<"The cards for the current player are: "<<endl<<px5;
    cout<<endl<<"Statistics for current player"<<endl;
    px5.print_poker_status();



    //Straight
    card cp60(2,2);
    card cp61(3,3);
    card cp62(2,4);
    card cp63(0,5);
    card cp64(1,6);
    poker_player px6(cp60,cp61,cp62,cp63,cp64);
    cout<<endl<<"The cards for the current player are: "<<endl<<px6;
    cout<<endl<<"Statistics for current player"<<endl;
    px6.print_poker_status();


    //Three of a kind o Set
    card cp70(1,7);
    card cp71(0,7);
    card cp72(3,7);
    card cp73(3,1);
    card cp74(2,9);
    poker_player px7(cp70,cp71,cp72,cp73,cp74);
    cout<<endl<<"The cards for the current player are: "<<endl<<px7;
    cout<<endl<<"Statistics for current player"<<endl;
    px7.print_poker_status();


    //Two pair o Pocket
    card cp80(2,11);
    card cp81(0,11);
    card cp82(1,4);
    card cp83(3,1);
    card cp84(0,4);
    poker_player px8(cp80,cp81,cp82,cp83,cp84);
    cout<<endl<<"The cards for the current player are: "<<endl<<px8;
    cout<<endl<<"Statistics for current player"<<endl;
    px8.print_poker_status();


    //One pair
    card cp90(3,12);
    card cp91(2,12);
    card cp92(3,6);
    card cp93(0,1);
    card cp94(1,10);
    poker_player px9(cp90,cp91,cp92,cp93,cp94);
    cout<<endl<<"The cards for the current player are: "<<endl<<px9;
    cout<<endl<<"Statistics for current player"<<endl;
    px9.print_poker_status();


    //High card
    card cp100(2,11);
    card cp101(0,6);
    card cp102(1,4);
    card cp103(3,2);
    card cp104(0,9);
    poker_player px10(cp100,cp101,cp102,cp103,cp104);
    cout<<endl<<"The cards for the current player are: "<<endl<<px10;
    cout<<endl<<"Statistics for current player"<<endl;
    px10.print_poker_status();


    return 0;
}


//----------------------------------------------------------------------------------------------------------------------------------------
//TO DO
//----------------------------------------------------------------------------------------------------------------------------------------
//Improve printing of cards with ace, and K

//When presenting the highest cards, there is a look up table missing to convert the index to the actual value. 
//Find out if J Q K 10 have the same value, as well as the value of the ace.
//----------------------------------------------------------------------------------------------------------------------------------------





