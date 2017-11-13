#include <iostream>

#include "search_algorithms.h"

#include "game_of_hex.h"


//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//Author:           Jairo Alejandro Gómez.
//Last modified on: 18th September 2015.
//Description:      This main file test some of the search algorithms developed earlier.
//                  There are some pre-defined case examples that can be accessed
//                  modifying the variable problem_definition from 1 to 5.
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------


using namespace std;

int main(void)
{


    //This variable allows you to change the setup (example) to test the behavior of the search algorithms that have been implemented.
    int problem_definition = 5; //Any number from 1 to 5...



//-----------------------------------------------------------------------------------------------
//Variable declaration for the examples
//-----------------------------------------------------------------------------------------------
    bool verbose;                //It helps to show more messages if it is set to true.
    int vertices;                //Number of vertices in the graph.
    int source_id;               //It can be any integer number between 0 and (vertices-1).
    int target_id;               //It can be any integer number between 0 and (vertices-1). If set to -1 there is no target.
    vector< string > node_names; //This is optional.
    vector< vector<double> > M;     //rows x cols
    vector<double> d;               //Vector with estimate of shortest distances to all other vertices from the root (notice that it can have either integer or double values >= 0)
    vector<int> p;               //Vector with the parent for each node.
    double MST_cost=0;

    //Notice that internally: "M", "d", and "MST_cost" have to be of the same type !!!

//-----------------------------------------------------------------------------------------------
//Example selection:
//-----------------------------------------------------------------------------------------------
    if (problem_definition==1)
    {
        //--------------------------------------------------
        //Problem definition 1
        //--------------------------------------------------
        //int inf=numeric_limits<int>::max();
        verbose=true;
        vertices =6;
        source_id=0;
        target_id=5;
        node_names=vector< string > {"r","a","b","c","d","e"};
        M=vector< vector<double> > {{0, 3, 9, 0, 0, 0},
                                    {3, 0, 2, 1, 7, 0},
                                    {9, 2, 0, 0, 6, 4},
                                    {0, 1, 0, 0, 3, 0},
                                    {0, 7, 6, 3, 0, 1},
                                    {0, 0, 4, 0, 1, 0}};
        d.resize(vertices);
        p.resize(vertices);
        MST_cost=0;

    }
    else if (problem_definition==2)
    {
        //--------------------------------------------------
        //Problem definition 2
        //--------------------------------------------------
        //int inf=numeric_limits<int>::max();
        verbose=true;
        vertices =7;
        source_id=0;
        target_id=6;
        node_names=vector< string > {"r","a","b","c","d","e","f"};
        M=vector< vector<double> >       {{0, 3, 9, 0, 0, 0, 0},
                                          {3, 0, 2, 1, 7, 0, 0},
                                          {9, 2, 0, 0, 6, 4, 0},
                                          {0, 1, 0, 0, 3, 0, 0},
                                          {0, 7, 6, 3, 0, 1, 0},
                                          {0, 0, 4, 0, 1, 0, 0},
                                          {0, 0, 0, 0, 0, 0, 0}}; //rows x cols
        d.resize(vertices);
        p.resize(vertices);
        MST_cost=0;

    }
    else if (problem_definition==3)
    {
        //--------------------------------------------------
        //Problem definition 3
        //--------------------------------------------------
        //double inf=numeric_limits<double>::max();
        verbose=false;
        vertices =4;
        source_id=0;
        target_id=3;
        node_names=vector< string >{"Cali","Yumbo","Palmira","Rozo"};
        M=vector< vector<double> > {{0,       11.8,   27.79,  0    },
                                    {11.8,    0,      28.52,  15.96},
                                    {27.79,   28.52,  0,      16.31},
                                    {0,       15.96,  16.31,  0    }};

        d.resize(vertices);
        p.resize(vertices);
        MST_cost=0;

    }
    else if (problem_definition==4)
    {
        //--------------------------------------------------
        //Problem definition 4
        //--------------------------------------------------
        //int inf=numeric_limits<int>::max();
        verbose=false;
        vertices =7;
        source_id=0;
        target_id=6;
        node_names=vector< string > {"A","E","F","G","D","I","H"};
        M=vector< vector<double> > {{0,  2,  3,  0,  0,  0,  0},
                                    {2,  0,  2,  4,  6,  4,  0},
                                    {3,  2,  0,  0,  0,  5,  0},
                                    {0,  4,  0,  0,  5,  0,  3},
                                    {0,  6,  0,  5,  0,  4,  5},
                                    {0,  4,  5,  0,  4,  0,  0},
                                    {0,  0,  0,  3,  5,  0,  0}};
        d.resize(vertices);
        p.resize(vertices);
        MST_cost=0;

    }
    else if (problem_definition==5)
    {
        //--------------------------------------------------
        //Problem definition 5
        //--------------------------------------------------
        //int inf=numeric_limits<int>::max();
        verbose=false;
        vertices =9;
        source_id=0;
        target_id=5;
        node_names=vector< string >  {"A","B","C","D","E","F","G","H","S"};
        M=vector< vector<double> >  {{0,  1,  0,  0,   0, 0,   0,  0,  1},
                                     {1,  0,  0,  0,   0, 0,   0,  0,  0},
                                     {0,  0,  0,  1,   1, 1,   0,  0,  1},
                                     {0,  0,  1,  0,   0, 0,   0,  0,  0},
                                     {0,  0,  1,  0,   0, 0,   0,  1,  0},
                                     {0,  0,  1,  0,   0, 0,   1,  0,  0},
                                     {0,  0,  0,  0,   0, 1,   0,  1,  1},
                                     {0,  0,  0,  0,   1, 0,   1,  0,  0},
                                     {1,  0,  1,  0,   0, 0,   1,  0,  0}};
        d.resize(vertices);
        p.resize(vertices);
        MST_cost=0;

    }
    else
    {
        cout<<endl<<"Example not valid"<<endl;
    }



//-----------------------------------------------------------------------------------------------
//Display example details
//-----------------------------------------------------------------------------------------------

    cout<<"----------------------------------------------------------------------------"<<endl;
    cout<<"The problem definition: "<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;
    cout<<"The dimension of matrix M is ["<<M.size()<<"x"<<M[0].size()<<"]"<<endl<<endl;
    cout<<"The content of Matrix M is:"<<endl<<M;
    cout<<"The source node is "<<source_id<<endl<<endl;


//----------------------------------------------------------------------------------------------
// Apply Dijkstra algorithm
//-----------------------------------------------------------------------------------------------------------------------------------------------

    cout<<"----------------------------------------------------------------------------"<<endl;
    cout<<"Dijkstra without a target"<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;

    //In its basic form
    my_dijkstra(vertices,source_id,M,d,p,-1,node_names);          //Function call without a specific target (this goes through all connected nodes), and using node names.
    //my_dijkstra(vertices,source_id,M,d,p);                      //Function call without a specific target (this goes through all connected nodes), without using node names.
    cout<<endl<<"Vector of shortest distances from all nodes to the source node: "<<endl<<d<<endl;
    cout<<endl<<"Parents of each node: "<<endl<<p<<endl;

    //-----------------------------------------------------------------------------------------------------------------------------------------------

    cout<<"----------------------------------------------------------------------------"<<endl;
    cout<<"Dijkstra with a target"<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;

    //Adapted to be used with a target...
    cout<<"The target node is "<<target_id<<endl;

    my_dijkstra(vertices,source_id,M,d,p, target_id,node_names);     //Function call with a target node id (this stops when the target is reached).
    cout<<endl<<"Vector of shortest distances (not all values are valid because of the early stop): "<<endl<<d<<endl;
    cout<<endl<<"Parents of each node (not all values are valid because of the early stop): "<<endl<<p<<endl;



//-----------------------------------------------------------------------------------------------------------------------------------------------
//Recovering the path....
//-----------------------------------------------------------------------------------------------------------------------------------------------

    cout<<"----------------------------------------------------------------------------"<<endl;
    cout<<"Recovering the path from source to target."<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;

    list<int> node_sequence;  //List usted to store the solution of nodes starting from the source and finishing in the target.
    get_nodes_from_source_to_target(source_id, target_id, d, p, node_sequence);

    cout<<"The trajectory from source to target, using the node's id is:"<<endl;
    print_doubly_linked_list(node_sequence);
    cout<<endl;

//-----------------------------------------------------------------------------------------------------------------------------------------------
//Dynamic programming. It finds the paths from all nodes to a given target
//-----------------------------------------------------------------------------------------------------------------------------------------------

    cout<<"----------------------------------------------------------------------------"<<endl;
    cout<<"Dynamic programming."<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;

    vector< list<int> >  dp(vertices);    //This variable create a vector with list elements of type int (to store node's id).


    cout<<"Using the names of the nodes:"<<endl;
    dynamic_programming(vertices, target_id, M, dp,node_names,verbose);     //Using optional parameter "node_names". Using verbose.

    cout<<endl;
    cout<<"Using the id of the nodes:"<<endl;
    dynamic_programming(vertices, target_id, M, dp);                         //Without optional parameter "node_names".

    //-----------------------------------------------------------------------------------------------------------------------------------------------
    //Minimum Spanning Tree (MST)
    //-----------------------------------------------------------------------------------------------------------------------------------------------
    cout<<"----------------------------------------------------------------------------"<<endl;
    cout<<"Minimum Spanning Tree in its basic form:"<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;

    my_minimum_spanning_tree(vertices,source_id,M,d,p,-1,node_names,verbose,MST_cost);             //Without a proper target
    cout<<endl<<"The cost of this MST: "<<MST_cost<<endl;
    cout<<endl<<"Vector of distances in MST: "<<endl<<d<<endl;
    cout<<endl<<"Parents of each node: "<<endl<<p<<endl;

    //-----------------------------------------------------------------------------------------------------------------------------------------------

    cout<<"----------------------------------------------------------------------------"<<endl;
    cout<<"Minimum Spanning Tree using a target (modified form):"<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;

    //Modified form with an actual target.
    my_minimum_spanning_tree(vertices,source_id,M,d,p, target_id,node_names,verbose,MST_cost);     //With a proper target.
    //my_minimum_spanning_tree(vertices,source_id,M,d,p, target_id,node_names,true,MST_cost);     //With a proper target.

    cout<<endl<<"The cost of this MST (as target_id!=-1 the value is not valid in general because of the early stop): "<<MST_cost<<endl;
    cout<<endl<<"Vector of distances in MST (as target_id!=-1 not all values are valid because of the early stop): "<<endl<<d<<endl;
    cout<<endl<<"Parents of each node (as target_id!=-1 not all values are valid because of the early stop): "<<endl<<p<<endl;


//--------------------------------------------------------------------------------------
// Breadth-First Search (BFS)
//--------------------------------------------------------------------------------------

    cout<<"----------------------------------------------------------------------------"<<endl;
    cout<<"Breadth First Search (BFS) in its basic form:"<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;

    my_breadth_first_search(vertices,source_id,M,d,p,-1,node_names,verbose);   //-1: There is no target used. Get a full solution.

    cout<<endl<<"Vector of distances in BFS: "<<endl<<d<<endl;
    cout<<endl<<"Parents of each node in BFS: "<<endl<<p<<endl;


//--------------------------------------------------------------------------------------
// Depth-First Search (DFS)
//--------------------------------------------------------------------------------------

    cout<<"----------------------------------------------------------------------------"<<endl;
    cout<<"Depth-First Search (DFS) in its basic form:"<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;

    my_depth_first_search(vertices,source_id,M,d,p,-1,node_names,verbose);   //-1: There is no target used. Get a full solution.

    cout<<endl<<"Vector of distances in DFS: "<<endl<<d<<endl;
    cout<<endl<<"Parents of each node in DFS: "<<endl;
    print_vector_of_parents(p,node_names);  //Print as columns the children and the name of the parent
    //print_vector_of_parents(p);  //Print as columns the children and the name of the parent
    cout<<endl;




//--------------------------------------------------------------------------------------
//Hex game.
//--------------------------------------------------------------------------------------


const int n= 11;
hex_board my_hex_board(n); //Empty board (full of zeros)
my_hex_board.set_position(0,0, 1);      //(0,0) player 1
my_hex_board.set_position(1,0, 1);      //(1,0) player 1


my_hex_board.set_position(1,1, 2);      //(1,1) player 2
my_hex_board.set_position(0,1, 2);      //(0,1) player 2

my_hex_board.print_board();



//Check if there is a winner (a path between (all non-zero nodes on one side of a given player, and all non-zero nodes of the same player in the opposite side of the board)
//Define who owns, north-south, and east-west.


//--------------------------------------------------------------------------------------
//TO DO....
//--------------------------------------------------------------------------------------

    //Instead of erasing an element from a vector, see if it is possible to swap it with the last element, and then delete the last element.
    //(This is much more efficient, but it can only be done if it is not important to preserve the order of the vector elements).

    //For a given problem, there can be more that one target.

    //Create similar algorithms, but this time using LIFO, and FIFO structures.

    //Instantiate some of the templates to create corresponding .cpp files.
//--------------------------------------------------------------------------------------


    return 0;
}


//------------------------------------------------------
// END
//------------------------------------------------------


