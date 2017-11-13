#ifndef GAME_OF_HEX_H_INCLUDED
#define GAME_OF_HEX_H_INCLUDED

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//Author:           Jairo Alejandro Gómez.
//Last modified on: 24th September 2015.
//Description:      Basic implementation of the game of hex
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

//Custom libraries
#include "node.h"
#include "utilities_for_graphs.h"

#include <iomanip>      // std::setfill, std::setw
#include <algorithm>    //To call  std::min_element
#include <iterator>     //To use the iterators that arise in std::min_element

using namespace std;

//---------------------------------------------------------------------------------------

//Note:

//The following three libraries are included in "node.h":
//#include <iostream>
//#include <vector>
//#include <limits>     //This is to use  numeric_limits<type>::max()()   in c++11



//The following libraries are included in "utilities_for_graphs.h":
//#include <iostream>
//#include <vector>
//#include <list>
//#include <limits>     //This is to use  numeric_limits<type>::max()()   in c++11
//#include <iomanip>    //To use std::setfill, std::setw  (for formatting strings in cout).


//---------------------------------------------------------------------------------------


class hex_node: public graph_node<int>
{
protected:
    int player; //0: no player. 1: player 1. 2: player 2.

public:
    hex_node();   //Constructor
    ~hex_node();  //Destructor

    void clear_players();                             //player = 0 (no player)
    void set_player(const int &given_player);         //player either 1 or 2.


    int get_player();    //Return the player id that owns the node.

    bool is_available(); //True if the node has not been taken by a given player.
    bool is_taken();     //True if the node has been taken by a given player.

};

//---------------------------------------------------------------------------------------
hex_node::hex_node()
{
  player = 0;
}
//---------------------------------------------------------------------------------------

//Destructor
hex_node::~hex_node()
{

}
//---------------------------------------------------------------------------------------
//player = 0  (no player)
void hex_node::clear_players()
{
  player = 0;
}
//---------------------------------------------------------------------------------------

void hex_node::set_player(const int &given_player)
{
    if (given_player==1)
    {
        player = 1;
    }
    else if (given_player==2)
    {
        player = 2;
    }

}

//---------------------------------------------------------------------------------------
//Return the player id that owns the node.
int  hex_node::get_player()
{
 return player;
}
//---------------------------------------------------------------------------------------

//True if the node has not been taken by a given player.
bool hex_node::is_available()
{
   return (player == 0) ? true : false;
}


//---------------------------------------------------------------------------------------

//True if the node has been taken by a given player.
bool hex_node::is_taken()
{
   return (player != 0) ? true : false;
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

class hex_board
{
protected:
    int n;                                 //The board will have size n x n
    vector< vector < hex_node > > board;        //Matrix of hex_nodes of size n x n

    vector < vector < vector < int > > > M;     //M[0]: Connectivity matrix for player 1 of size (n*n) x (n*n).
                                                //M[1]: Connectivity matrix for player 2 of size (n*n) x (n*n).

public:
    hex_board(const int & n_given);
    ~hex_board();

    bool is_a_valid_coordinate(const int &i, const int &j);
    void update_connectivity(const int &i, const int &j, const int &player);
    void set_position(const int &i, const int &j, const int &player);

    void print_board();
};


//---------------------------------------------------------------------------------------

//Constructor : It creates an hex board of n x n.
hex_board::hex_board(const int & n_given)
{
    n=n_given;
    board.resize(n);                                          //Set the rows
    for (int i=0; i<n; ++i)
    {
       board[i].resize(n);                                    //Set the columns
    }

    //---------------------------------------
    //Initialize connectivity matrices for both players in zero, considering that there are n*n nodes in total.

    M.resize(2);
    M[0].resize((n*n));
    M[1].resize((n*n));
    for (int i=0; i<(n*n); ++i)
    {
       M[0][i].resize((n*n));
       M[1][i].resize((n*n));                                    //Set the columns
    }

    //cout<<"dims for M ="<<M.size()<<"; dims for M[0]="<< M[0].size()<<"; dims for M[0][0]="<<M[0][0].size()<<endl;

}


//---------------------------------------------------------------------------------------
//Destructor
hex_board::~hex_board()
{
}

//---------------------------------------------------------------------------------------


bool hex_board::is_a_valid_coordinate(const int &i, const int &j)
{
    return ((i>=0) && (i<n) && (j>=0) && (j<n)) ? true : false;
}

//---------------------------------------------------------------------------------------

void hex_board::update_connectivity(const int &i, const int &j, const int &player)
{

    int index_current_node   = (( i)*n)+ j;  //To index the M matrix

    for (int ii = -1; ii < 2; ++ii)
    {
        for (int jj=-1; jj < 2; ++jj)
        {

            if ((ii!=0) || (jj!=0))
            {
                int ci = i + ii;
                int cj = j + jj;

                if  ((ci>-1) && (ci<n) && (cj>-1) && (cj<n) )  //Verify that the position being inspected lies within the boundaries of the board
                {

                    int neighbour_player= board[ci][cj].get_player();

                    //cout<<"("<<ci<<","<<cj<<") occupied by "<<neighbour_player<<endl;

                    if (neighbour_player==player)   //If the neighbor belongs to the same player, update the connectivity matrix.
                    {


                        int index_neighbour_node = ((ci)*n)+cj;
                        M[(player-1)][index_current_node][index_neighbour_node]=1;   //The -1 is necessary because player can be either 1 or 2, but valid indices are 0 and 1.
                        M[(player-1)][index_neighbour_node][index_current_node]=1;

                        cout<<"Connection established between node "<<index_current_node<<" and node "<<index_neighbour_node<<" and viceversa."<<endl;
                    }

                }
            }

        }
    }

}

//---------------------------------------------------------------------------------------


 void hex_board::set_position(const int &i, const int &j, const int &player)
 {
    if (this->is_a_valid_coordinate(i,j))
    {
        if (board[i][j].is_available())
        {
            board[i][j].set_player(player);
            update_connectivity(i,j,player); //Update connectivity Matrix M.
        }
        else
        {
            cout<<"The position requested has been already taken"<<endl;
        }
    }
    else
    {
       cout<<"Invalid coordinate, i and j should be unsigned numbers between 0 and "<<n<<endl;
    }
 }

//---------------------------------------------------------------------------------------
void hex_board::print_board()
{
    const int n_spaces = 3;

    //-----------------------------------------------------------------
    //Top Bar
    //-----------------------------------------------------------------
    for (int j=0; j<((n_spaces+1)*n+2*2); ++j)
    {
        //cout << setfill (' ') << setw (3);   //The ' ' is to set fill character. setw(2) is to use at least two characters
        cout<<"=";
    }
    cout<<endl;


    //-----------------------------------------------------------------
    //Lateral bars and board...
    //-----------------------------------------------------------------
    for (int i = 0; i<n; ++i)
    {
            cout<<"||";
            for (int j=0; j<n; ++j)
            {
                 cout << std::setfill (' ') << std::setw (n_spaces);   //The ' ' is to set fill character. setw(2) is to use at least two characters
                 cout << board[i][j].get_player()<<" " ;
            }
            cout <<"||"<<endl;
    }
    //-----------------------------------------------------------------
    //Bottom bar Bar
    //-----------------------------------------------------------------
    for (int j=0; j<((n_spaces+1)*n+2*2); ++j)
    {
        //cout << setfill (' ') << setw (3);   //The ' ' is to set fill character. setw(2) is to use at least two characters
        cout<<"=";
    }
    cout<<endl;

}
//---------------------------------------------------------------------------------------



#endif // GAME_OF_HEX_H_INCLUDED
