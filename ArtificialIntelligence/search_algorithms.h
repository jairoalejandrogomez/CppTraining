#ifndef SEARCH_ALGORITHMS_H_INCLUDED
#define SEARCH_ALGORITHMS_H_INCLUDED


//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//Author:           Jairo Alejandro Gómez.
//Last modified on: 18th September 2015.

//Description: this library provides generic functions using templates,
//of the following algorithms using Standard Template Library (STL) and c++11:
//
//1) Dijkstra algorithm, also called uniform-cost search. It can handle directed or undirected graphs
//   (it all depends on the values set in the connectivity matrix M).
//2) Dynamic programming.
//3) Minimum Spanning Tree.
//4) Breadth first search algorithm.
//5) Depth-first search.
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

//Custom libraries
#include "node.h"
#include "utilities_for_graphs.h"


#include <algorithm>    //To call  std::min_element
#include <iterator>     //To use the iterators that arise in std::min_element

using namespace std;
//---------------------------------------------------------------------------------------

//Note:

//The following three libraries are included in "node.h":
//#include <iostream>
//#include <vector>
//#include <limits>        //This is to use  numeric_limits<type>::max()()   in c++11



//The following three libraries are included in "utilities_for_graphs.h":
//#include <iostream>
//#include <vector>
//#include <list>
//#include <limits>        //This is to use  numeric_limits<type>::max()()   in c++11
//#include <iomanip>      //To use std::setfill, std::setw  (for formatting strings in cout).


//---------------------------------------------------------------------------------------
//This function applies Dijkstra algorithm to a graph (In some fields,
//artificial intelligence in particular, Dijkstra's algorithm or a
//variant of it is known as "uniform-cost search"),
//characterized by a number of "vertices", starting from
//a node identified by a "source_id", and optionally going to
//a node identified by a "target_id". It is optional to use
//a vector of strings to attach a name for each node.
//The connection matrix of the graph is stored in the matrix M,
//which is built as a vector of vectors. The function
//also receives by reference two vectors of length vertices.
//The vector "d" stores the distance from a given node to the source node,
//whereas the vector "p" stores the id of the parent of a given node
//according to the solution found by Dijkstra's algorithm.
//Notice that if a "target_id" is specified, Dijkstra's algorithm is
//stopped as soon as it reaches a path from source to target, and therefore
//not all values in "d" and "p" would be valid. If you want the full
//Dijkstra's algorithm, do not  provide a "target_id" (it is an optional argument).
//In general, it the algorithm will return a 1 if the graph is not fully connected
//(i.e: not all nodes can be reached from the source node) or if it is not possible
//to reach the target node from the source node in the current graph. Otherwise, if
//the program returns 0 (i.e: success).
//Notice that Dijkstra's algorithm finds the path with the smallest "distance" from a
//source node to a given node.

template<class T>
int my_dijkstra(const int & vertices, const int & source_id, const vector< vector<T> > & M, vector<T> & d, vector<int> & p, const int & target_id=-1, const vector< string > & node_names= vector<string>(0), bool verbose=false )
{
    //cout<<"The dimension of matrix M is ["<<M.size()<<"x"<<M[0].size()<<"]"<<endl<<endl;
    //cout<<"The content of Matrix M is:"<<endl<<M;

    const T inf=numeric_limits<T>::max();
    //cout<<"The largest number for int is "<<inf;


    //Make sure d and p are initialized in the correct values.
    d.assign (vertices,inf);
    p.assign (vertices,-1);

    //---------------------------------------------------------------------------------------

    int index_closed_set=0;
    int index_in_opened_set;
    int faulty_search;      //0. The search was successful. 1: The search failed.
    int node_id;            //Node identifier.
    T node_d;             //Distance from the source node to current node.
    //int node_p;             //Parent node id, in the path to the source node.



    vector<bool> available_in_open_set(vertices,true);  //A "true" in an index i, will indicate that the node with id==i is available in the open_set
                                                        //to be expanded

    vector< graph_node<T> > open_set(vertices);       // A vector, with (vertices) nodes, initialized in infinity.
    vector< graph_node<T> > closed_set(vertices);     // A vector linked list, with (vertices) nodes, initialized in infinity.

    //---------------------------------------------------------------------------------------
    //Graph representation.
    //---------------------------------------------------------------------------------------

    //Set a unique id and name for each node
    for (int i=0; i<vertices; ++i)
    {
        open_set[i].id = i;

        if (node_names.size()==static_cast<unsigned>(vertices))   //If the user did provide a string identifier for each node
        {
            open_set[i].name=node_names[i];
        }
    }

    //cout<<"The open set is initially given by:"<<endl<<open_set<<endl;
    //cout<<"open_set:"<<endl<<open_set;
    //cout<<"closed_set"<<endl<<closed_set;

    //---------------------------------------------------------------------------------------

    if ((source_id>=0) && (source_id<vertices))  //If source_id is a valid index.....
    {
            faulty_search=find_element_in_vector_from_id(open_set, source_id,index_in_opened_set); //Return the index_in_opened_set if faulty_search==0

            if (faulty_search==0)
            {
                open_set[index_in_opened_set].d=0;                                 //The distance from the source node to itself is zero.
                open_set[index_in_opened_set].p=source_id;                         //The source node has no parent as such. Therefore it can be its own father.

                d[source_id]=0;
                p[source_id]=source_id;

                closed_set.at(index_closed_set)=open_set[index_in_opened_set]; //Add node to the closed set.
                open_set.erase(open_set.begin()+index_in_opened_set);          //Erase node from the opened_set.
                                                                               //THIS CAN BE IMPROVED USING A DATA STRUCTURE
                                                                               //SUCH AS A DOUBLY LINKED LIST OR A SIMPLY LINKED LIST INSTEAD OF A VECTOR.

                available_in_open_set[source_id]=false;                        //This is to mark that the node is no longer in the open_set.

                //If the source node is the target node return.
                if ((target_id!=-1) && ( (closed_set.at(index_closed_set).id) == target_id))  //if the user has specified a target and it has found it, then finish.....
                {

                if (verbose) cout<<"There is a path between source node "<<source_id<<" and target node "<<target_id<<" in the current graph"<<endl;

                return 0;
                }
            }
            else
            {
                cout<<"The source node is not available"<<endl;
                return 1;
            }
    }
    else
    {
        cout<<"The source node id is not valid, it should be an integer number between 0 and the number of vertices minus 1."<<endl;
        return 1;
    }

    bool connected_graph=1;  //Start the program assuming that the graph is connected.
    int iter=0;              //Variable to control the number of iterations.

    T link_distance;       //link distance from the node being explored to the ith-node.
    T current_distance;    //current_distance of the node
    T parent_distance;     //distance from the source node to the parent node.
    T min_distance;        //Variable used to find the distance from the candidate nodes in the opened_set to be part of the closed_set.

    //decltype(open_set)::iterator min_iterator;

    typename vector< graph_node<T> >::iterator min_iterator;  //This iterator is used to find the minimum distance in a vector of nodes.


    //---------------------------------------------------------------------------------------
    //Big Loop
    //---------------------------------------------------------------------------------------
    while ((iter < (vertices-1)) && (connected_graph==1))
    {
        node_id = closed_set.at(index_closed_set).id;  //Get the id of the node that is being explored.
        node_d  = closed_set.at(index_closed_set).d;   //Get distance from source node to this node.

        parent_distance = node_d;

        for (int i=0; i<vertices; ++i)  //For all possible id.  THIS CAN BE IMPROVED AS NOT ALL VERTICES ARE CONNECTED TO CURRENT NODE.
        {
           link_distance=M[node_id][i];  //Weight between the current node and the i-th node.
           if (link_distance != 0) //If there is a connection....
           {

               if (available_in_open_set[i]==true)
               {
                   faulty_search=find_element_in_vector_from_id(open_set,i,index_in_opened_set);

                   if (faulty_search==0)
                   {
                       current_distance=open_set.at(index_in_opened_set).d;

                       if (current_distance> (parent_distance+link_distance))  //If it is possible to relax the constraint...
                       {
                           open_set.at(index_in_opened_set).d = (parent_distance+link_distance);
                           open_set.at(index_in_opened_set).p = node_id;
                           d[open_set.at(index_in_opened_set).id]= (parent_distance+link_distance);
                           p[open_set.at(index_in_opened_set).id]= node_id;
                       }
                   }
               }
           }
        }

        //-------------------------------------------------------------------------------------------------
        //Find the minimum distance from the nodes available in the open_set
        //-------------------------------------------------------------------------------------------------

        //Option 1:
        min_iterator = min_element(open_set.begin(), open_set.end(), cmp_distance_in_graph_nodes<T>);

        //Option 2:
        //auto min_iterator = min_element(open_set.begin(), open_set.end(), cmp_distance_in_graph_nodes<int>);

        //cout<<"Iter: "<<iter<<". The node "<<min_iterator->name<<" has the minimum distance of "<<min_iterator->d<<endl;
        //-------------------------------------------------------------------------------------------------

        min_distance = min_iterator->d;

        if (min_distance < inf)   //If the node is actually connected to the source node.
        {

            index_closed_set++;
            //cout<<index_closed_set<<endl;
            closed_set.at(index_closed_set)= (*min_iterator); //Add node to the closed set.

            open_set.erase(min_iterator);          //Erase node from the opened_set.
                                                   //THIS CAN BE IMPROVED USING A DATA STRUCTURE SUCH AS A
                                                   //DOUBLY LINKED LIST OR A SIMPLY LINKED LIST INSTEAD OF A VECTOR.

            available_in_open_set[closed_set.at(index_closed_set).id]=false;


            //This condition prevents the program to find a path to each node, once it has found a valid target specified by the user.
            if ((target_id!=-1) && ( (closed_set.at(index_closed_set).id) == target_id))  //if the user has specified a target and it has found it, then finish.....
            {

                if (verbose) cout<<"There is a path between source node "<<source_id<<" and target node "<<target_id<<" in the current graph"<<endl;

                return 0;
            }

            //Go to BIG LOOP
        }
        else
        {
            connected_graph = 0;


            if (verbose)
            {
                if (target_id==-1)
                {
                    cout<<"The graph is not fully connected. Not all nodes can be reached from the source node"<<endl;
                }
                else
                {
                    cout<<"There is no path between source node "<<source_id<<" and target node "<<target_id<<" in the current graph"<<endl;
                }
            }

            return 1;
        }

        iter++;  //Djikstra iterations.
    }

//    cout<<endl<<"Vector of shortest distances from all nodes to the source node: "<<endl<<d<<endl;
//    cout<<endl<<"Parents of each node: "<<endl<<p<<endl;
//
//    cout<<"The closed set presented next is displayed in the order that it was explored:"<<endl<<closed_set<<endl;   //Notice that the closed_set in general won't be sorted by id.
//
//    //Sort the closed set.
//    sort(closed_set.begin(), closed_set.end(), cmp_id_in_graph_nodes<int>);
//    cout<<"Sorting the closed set in increasing order by id, produces:"<<endl<<closed_set<<endl;


return 0; //The program won't get here (this is just to avoid warning from the compiler).

}


//---------------------------------------------------------------------------------------
//This function applies dynamic programming
//to find an optimal path from each node in a graph with a given number
//of "vertices", to a pre-specified target node identified with the "target_id".
//Each node can be labeled using the vector of strings called "node_names".
//The connectivity of the graph is defined in the matrix "M" which is built
//as a vector of vectors. The result is stored in a vector of lists called
//"dp" (dynamic programming) which is modified by reference.
//This function explores previously generated paths looking for coincidences
//to used them in new paths with different starting points. If no coincidences
//are found, then a new Dijkstra path is generated instead.
template<class T>
int dynamic_programming(const int & vertices, const int & target_id, const vector< vector<T> > & M, vector< list<int> >  & dp, const vector< string > & node_names= vector<string>(0), bool verbose=false)
{
    vector<T> d(vertices); //Vector with estimate of shortest distances to all other vertices from the root
    vector<int> p(vertices); //Vector with the parent for each node.

    for (unsigned int i=0; i<dp.size(); ++i) dp[i].clear();   //This is to make sure that dp is empty.


    //---------------------------------------------------------
    //The following section is useful if the graph is not directed.
    //---------------------------------------------------------
    bool is_directed=0;                                         //Flag that will indicate if the graph is directed or not.
    int error_in_matriz_M=0;
    error_in_matriz_M =is_a_directed_graph(M,is_directed);     //Find out if the graph is directed or not
    //cout<<"In the graph is_directed == "<<is_directed<<endl;
    if (error_in_matriz_M == 1)  //If M is not square.....
    {
        return 1;
    }
    if (is_directed==0) //If the graph is not directed, you only have to run Dijkstra's algorithm once to get paths from all nodes to a source.....
    {
        my_dijkstra(vertices,target_id,M,d,p,-1,node_names,verbose);   //Use Dijkstra's algorithm, and explore all possible nodes.
                                                 //but use the target as the source (because it is possible to go backwards later on)...
        for (int i=0; i<vertices; ++i)           //For all nodes....
        {
            get_nodes_from_source_to_target(target_id, i, d, p, dp[i]);  //Notice that the target_id is given as the source,
                                                                        //in each iteration a given node is provided as a target.
            dp[i].reverse();                                             //Now, we reverse the list, to make sure that the real target appears
                                                                         //at the end of the list.
        }
    }
    //---------------------------------------------------------
    else
    {
        typename list<int>::const_iterator my_iterator;                 //Notice that iterator will be used to iterate over "dp" which is of type:  vector< list<int> >   NOT vector< list<T> >
        int faulty_search;

        for (int i=0; i<vertices; ++i)
        {
            if (i==0)
            {
               my_dijkstra(vertices,i,M,d,p,target_id,node_names,verbose);          //Function call with a target node id (this stops when the target is reached).
               get_nodes_from_source_to_target(i, target_id, d, p, dp[i]);          //This requires a full solution of d and p.
            }
            else
            {
                for (int j=0; j<i; ++j)
                {
                    //search i in dp[j] list and return and iterator to it.
                    faulty_search=search_val_in_doubly_linked_list(dp[j],i,my_iterator);

                    if (faulty_search==0)  //If the search was successful...
                    {
                        //copy sequence and return ++i;
                        push_back_sublist(dp,i,my_iterator,dp[j].end());
                        break;
                    }
                }
                if (faulty_search==1) //If a subpath was not found, apply Djikstra....
                {
                        my_dijkstra(vertices,i,M,d,p,target_id,node_names,verbose);          //Function call with a target node id (this stops when the target is reached).
                        get_nodes_from_source_to_target(i, target_id, d, p, dp[i]);  //This requires a full solution of d and p.
                }
            }
            //print_doubly_linked_list(dp[i]);
        }
    }
    print_dp(dp,node_names); //If node_names has the appropiate length then it prints using names, otherwise it prints using the node's id.
    return 0;
}

//---------------------------------------------------------------------------------------
//Option 2: Unlike the previous approach, this function
//applies Djikstra algorithm "vertices" times,
//marking in each iteration a given node as the source node.
//---------------------------------------------------------------------------------------
//int dynamic_programming(const int & vertices, const int & target_id, const vector< vector<int> > & M, vector< list<int> >  & dp, const vector< string > & node_names= vector<string>(0), bool verbose=false)
//{
//
//    vector<int> d(vertices); //Vector with estimate of shortest distances to all other vertices from the root
//    vector<int> p(vertices); //Vector with the parent for each node.
//
//
//
//    //---------------------------------------------------------
//    //The following section is useful if the graph is not directed.
//    //---------------------------------------------------------
//    bool is_directed=0;                                         //Flag that will indicate if the graph is directed or not.
//    int error_in_matriz_M=0;
//    error_in_matriz_M =is_a_directed_graph(M,is_directed);     //Find out if the graph is directed or not
//    //cout<<"In the graph is_directed == "<<is_directed<<endl;
//    if (error_in_matriz_M == 1)  //If M is not square.....
//    {
//        return 1;
//    }
//    if (is_directed==0) //If the graph is not directed, you only have to run Dijkstra's algorithm once to get paths from all nodes to a source.....
//    {
//        my_dijkstra(vertices,target_id,M,d,p,-1,node_names,verbose);   //Use Dijkstra's algorithm, and explore all possible nodes.
//                                                 //but use the target as the source (because it is possible to go backwards later on)...
//        for (int i=0; i<vertices; ++i)           //For all nodes....
//        {
//            get_nodes_from_source_to_target(target_id, i, d, p, dp[i]);  //Notice that the target_id is given as the source,
//                                                                        //in each iteration a given node is provided as a target.
//            dp[i].reverse();                                             //Now, we reverse the list, to make sure that the real target appears
//                                                                         //at the end of the list.
//        }
//
//    }
//    //---------------------------------------------------------
//    else //If the graph is directed, use brute force...
//    {
//        for (int i=0; i<vertices; ++i)
//        {
//            my_dijkstra(vertices,i,M,d,p,target_id,node_names,verbose);          //Function call with a target node id (this stops when the target is reached).
//            get_nodes_from_source_to_target(i, target_id, d, p, dp[i]);  //This requires a full solution of d and p.
//            //print_doubly_linked_list(dp[i]);
//        }
//    }
//    print_dp(dp,node_names); //If node_names has the appropiate length then it prints using names, otherwise it prints using the node's id.
//    return 0;
//}
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

//This function implements a minimum spanning tree (MST)
template<class T>
int my_minimum_spanning_tree(const int & vertices, const int & source_id, const vector< vector<T> > & M, vector<T> & d, vector<int> & p, const int & target_id=-1, const vector< string > & node_names= vector<string>(0), bool verbose=false, T & MST_cost=0)
{
    //cout<<"The dimension of matrix M is ["<<M.size()<<"x"<<M[0].size()<<"]"<<endl<<endl;
    //cout<<"The content of Matrix M is:"<<endl<<M;

    const T inf=numeric_limits<T>::max();
    //cout<<"The largest number for int is "<<inf;

    //Make sure d and p are initialized in the correct values.
    d.assign (vertices,inf);
    p.assign (vertices,-1);


    MST_cost=0;   //Cost of the minimum spanning_tree
    //---------------------------------------------------------------------------------------

    int index_closed_set=0;
    int index_in_opened_set=0;
    int faulty_search;      //0. The search was successful. 1: The search failed.
    int node_id;            //Node identifier.
    T node_d;               //Distance from the source node to current node.
    //int node_p;           //Parent node id, in the path to the source node.

    vector<bool> available_in_open_set(vertices,true);  //A "true" in an index i, will indicate that the node with id==i is available in the open_set
                                                        //to be expanded

    vector< graph_node<int> > open_set(vertices);       // A vector, with (vertices) nodes, initialized in infinity.
    vector< graph_node<int> > closed_set(vertices);     // A vector, with (vertices) nodes, initialized in infinity.


    bool connected_graph=1;  //Start the program assuming that the graph is connected.
    int iter=0;              //Variable to control the number of iterations.

    T link_distance;       //link distance from the node being explored to the ith-node.
    T parent_distance;     //distance from the source node to the parent node.
    T min_d_to_parent;        //Variable used to find the distance from the candidate nodes in the opened_set to be part of the closed_set.

    vector< T > d_to_parent(vertices,inf);  //Vector with distances from a given node to its immediate father.

    typename vector< T >::iterator min_iterator; //This iterator is used to find the minimum

    unsigned id_of_node_to_explore_next;       //It will be used as an index later.

    //---------------------------------------------------------------------------------------
    //Graph representation.
    //---------------------------------------------------------------------------------------

    //Set a unique id and name for each node
    for (int i=0; i<vertices; ++i)
    {
        open_set[i].id = i;

        if (node_names.size()==static_cast<unsigned>(vertices))   //If the user did provide a string identifier for each node
        {
            open_set[i].name=node_names[i];
        }
    }
    //---------------------------------------------------------------------------------------

    if ((source_id>=0) && (source_id<vertices))  //If source_id is a valid index.....
    {
            faulty_search=find_element_in_vector_from_id(open_set, source_id,index_in_opened_set); //Return the index_in_opened_set if faulty_search==0

            if (faulty_search==0)
            {
                open_set[index_in_opened_set].d=0;                                 //The distance from the source node to itself is zero.
                open_set[index_in_opened_set].p=source_id;                         //The source node has no parent as such. Therefore it can be its own father.

                d[source_id]=0;
                p[source_id]=source_id;

                closed_set.at(index_closed_set)=open_set[index_in_opened_set]; //Add node to the closed set.
                open_set.erase(open_set.begin()+index_in_opened_set);          //Erase node from the opened_set.
                                                                               //THIS CAN BE IMPROVED USING A DATA STRUCTURE
                                                                               //SUCH AS A DOUBLY LINKED LIST OR A SIMPLY LINKED LIST INSTEAD OF A VECTOR.

                available_in_open_set[source_id]=false;                        //This is to mark that the node is no longer in the open_set.


                if (verbose) cout<<"Exploring node "<<source_id<<endl;

                //If the source node is the target node return.
                if ((target_id!=-1) && ( (closed_set.at(index_closed_set).id) == target_id))  //if the user has specified a target and it has found it, then finish.....
                {

                if (verbose) cout<<"There is a path between source node "<<source_id<<" and target node "<<target_id<<" in the current graph"<<endl;

                return 0;
                }
            }
            else
            {
                cout<<"The source node is not available"<<endl;
                return 1;
            }
    }
    else
    {
        cout<<"The source node id is not valid, it should be an integer number between 0 and the number of vertices minus 1."<<endl;
        return 1;
    }


    //---------------------------------------------------------------------------------------
    //Big Loop
    //---------------------------------------------------------------------------------------

    while ((iter < (vertices-1)) && (connected_graph==1))
    {
        node_id = closed_set.at(index_closed_set).id;  //Get the id of the node that is being explored.
        node_d  = closed_set.at(index_closed_set).d;   //Get distance from source node to this node.
        parent_distance = node_d;

        for (int i=0; i<vertices; ++i)  //For all possible id.  THIS CAN BE IMPROVED AS NOT ALL VERTICES ARE CONNECTED TO CURRENT NODE.
        {
           link_distance=M[node_id][i];  //Weight between the current node and the i-th node.

           if ( (link_distance != 0) && (available_in_open_set[i]==true) ) //If there is a connection, and the node requested is available in the open set.
           {
             if (link_distance<=d_to_parent[i])
             {
                 p[i]= node_id;
                 d_to_parent[i]=link_distance;
                 d[i]= parent_distance+link_distance;
             }
           }
        }

        //-------------------------------------------------------------------------------------------------
        //Find the minimum distance from each node that is reachable to its parent as long as it is in the open set.
        //-------------------------------------------------------------------------------------------------

        min_iterator = min_element(d_to_parent.begin(), d_to_parent.end(), cmp_value_in_vector<T>);
        id_of_node_to_explore_next=min_iterator-d_to_parent.begin();  //Get an index that can be used directly from a vector.
        min_d_to_parent = *min_iterator; //Minimum distance to parent.

        //-------------------------------------------------------------------------------------------------

        if ((min_d_to_parent < inf) && (available_in_open_set[id_of_node_to_explore_next]==true))  //If the node is actually connected to the the parent.
        {
                   //Now find the node.....
            faulty_search=find_element_in_vector_from_id(open_set,id_of_node_to_explore_next,index_in_opened_set);

            if (faulty_search==0)
            {

                open_set.at(index_in_opened_set).p = p[id_of_node_to_explore_next];
                open_set.at(index_in_opened_set).d = d[p[id_of_node_to_explore_next]]+ d_to_parent[id_of_node_to_explore_next];

                MST_cost = MST_cost + d_to_parent[id_of_node_to_explore_next]; //Update the cost of the minimum spanning tree.

                d_to_parent[id_of_node_to_explore_next] = inf; //In this way this node won't be considered in the next iteration when computing the minimum.

                index_closed_set++;

                //cout<<index_closed_set<<endl;
                closed_set.at(index_closed_set)= open_set.at(index_in_opened_set); //Add node to the closed set.

                open_set.erase(open_set.begin()+index_in_opened_set);   //Erase node from the opened_set.
                                                                        //THIS CAN BE IMPROVED USING A DATA STRUCTURE SUCH AS A
                                                                        //DOUBLY LINKED LIST OR A SIMPLY LINKED LIST INSTEAD OF A VECTOR.

                available_in_open_set[id_of_node_to_explore_next]=false;

                if (verbose) cout<<"Exploring node "<<id_of_node_to_explore_next<<endl;
            }
            else
            {
              return 1;
            }
            //This condition prevents the program to find a path to each node, once it has found a valid target specified by the user.
            if ((target_id!=-1) && ( (closed_set.at(index_closed_set).id) == target_id))  //if the user has specified a target and it has found it, then finish.....
            {

                if (verbose) cout<<"There is a path between source node "<<source_id<<" and target node "<<target_id<<" in the current graph"<<endl;

                return 0;
            }

            //Go to BIG LOOP
        }
        else
        {
            connected_graph = 0;

            if (verbose)
            {
                if (target_id==-1)
                {
                    cout<<"The graph is not fully connected. Not all nodes can be reached from the source node"<<endl;
                }
                else
                {
                    cout<<"There is no path between source node "<<source_id<<" and target node "<<target_id<<" in the current graph"<<endl;
                }
            }

            return 1;
        }

        iter++;  //iterations.
    }
    return 0;
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------



//This function implements a  breadth first search algorithm.
template<class T>
int my_breadth_first_search(const int & vertices, const int & source_id, const vector< vector<T> > & M, vector<T> & d, vector<int> & p, const int & target_id=-1, const vector< string > & node_names= vector<string>(0), bool verbose=false)
{
    //cout<<"The dimension of matrix M is ["<<M.size()<<"x"<<M[0].size()<<"]"<<endl<<endl;
    //cout<<"The content of Matrix M is:"<<endl<<M;

    const T inf=numeric_limits<T>::max();  //Infinite for distances (it can be int, unsigned or even double).



    //cout<<"The largest number for int is "<<inf;

    //Make sure d and p are initialized in the correct values.
    d.assign (vertices,inf);
    p.assign (vertices,-1);

    //---------------------------------------------------------------------------------------

    int index_closed_set=0;
    int index_in_opened_set=0;
    int faulty_search;      //0. The search was successful. 1: The search failed.
    int node_id;            //Node identifier.

    vector<bool> available_in_open_set(vertices,true);  //A "true" in an index i, will indicate that the node with id==i is available in the open_set
                                                        //to be expanded

    vector< graph_node<int> > open_set(vertices);       // A vector, with (vertices) nodes, initialized in infinity.
    vector< graph_node<int> > closed_set(vertices);     // A vector, with (vertices) nodes, initialized in infinity.

    bool connected_graph=1;  //Start the program assuming that the graph is connected.
    int iter=0;              //Variable to control the number of iterations.

    T link_distance;       //link distance from the node being explored to the ith-node.
    T parent_distance;     //distance from the source node to the parent node.

    unsigned parent_depth;
    unsigned min_depth;
    const unsigned inf_depth=numeric_limits<unsigned>::max(); //Infinite for depth (always >=0). Notice that depth is a unsigned integer category....
    vector< unsigned > depth_level(vertices,inf_depth);  //Vector with depth from each node to the source node.
    typename vector< unsigned >::iterator min_iterator;   //This iterator is used to find the minimum

    unsigned id_of_node_to_explore_next;           //It will be used as an index later.

    //---------------------------------------------------------------------------------------
    //Graph representation.
    //---------------------------------------------------------------------------------------

    //Set a unique id and name for each node
    for (int i=0; i<vertices; ++i)
    {
        open_set[i].id = i;

        if (node_names.size()==static_cast<unsigned>(vertices))   //If the user did provide a string identifier for each node
        {
            open_set[i].name=node_names[i];
        }
    }
    //---------------------------------------------------------------------------------------

    if ((source_id>=0) && (source_id<vertices))  //If source_id is a valid index.....
    {
            faulty_search=find_element_in_vector_from_id(open_set, source_id,index_in_opened_set); //Return the index_in_opened_set if faulty_search==0

            if (faulty_search==0)
            {
                open_set[index_in_opened_set].d=0;                                 //The distance from the source node to itself is zero.
                open_set[index_in_opened_set].p=source_id;                         //The source node has no parent as such. Therefore it can be its own father.

                d[source_id]=0;
                p[source_id]=source_id;
                depth_level[source_id]=0;
                parent_depth =  depth_level[source_id];

                closed_set.at(index_closed_set)=open_set[index_in_opened_set]; //Add node to the closed set.
                open_set.erase(open_set.begin()+index_in_opened_set);          //Erase node from the opened_set.
                                                                               //THIS CAN BE IMPROVED USING A DATA STRUCTURE
                                                                               //SUCH AS A DOUBLY LINKED LIST OR A SIMPLY LINKED LIST INSTEAD OF A VECTOR.

                available_in_open_set[source_id]=false;                        //This is to mark that the node is no longer in the open_set.

                if (verbose) {cout<<"Exploring node "<<source_id<<" with depth "<<depth_level[source_id];
                    cout<<endl;
                    //cout<<". distance:"; print_vector(d,false); cout<<endl;
                    }

                //If the source node is the target node return.
                if ((target_id!=-1) && ( (closed_set.at(index_closed_set).id) == target_id))  //if the user has specified a target and it has found it, then finish.....
                {

                if (verbose) cout<<"There is a path between source node "<<source_id<<" and target node "<<target_id<<" in the current graph"<<endl;

                return 0;
                }
            }
            else
            {
                cout<<"The source node is not available"<<endl;
                return 1;
            }
    }
    else
    {
        cout<<"The source node id is not valid, it should be an integer number between 0 and the number of vertices minus 1."<<endl;
        return 1;
    }


    //---------------------------------------------------------------------------------------
    //Big Loop
    //---------------------------------------------------------------------------------------


    while ((iter < (vertices-1)) && (connected_graph==1))
    {

        node_id         = closed_set.at(index_closed_set).id;  //Get the id of the node that is being explored.
        parent_distance = closed_set.at(index_closed_set).d;   //Get distance from source node to this node.


        for (int i=0; i<vertices; ++i)  //For all possible id.  THIS CAN BE IMPROVED AS NOT ALL VERTICES ARE CONNECTED TO CURRENT NODE.
        {
           link_distance=M[node_id][i];  //Weight between the current node and the i-th node.

           if ( (link_distance != 0) && (available_in_open_set[i]==true) ) //If there is a connection, and the node requested is available in the open set.
           {
             if (   ((parent_depth + 1) <  depth_level[i])    ||     (((parent_depth + 1) == depth_level[i] ) && ((parent_distance+link_distance) < d[i]))   )     //The part after || handles tie conditions. //get the index to the node with minimum depth (and if possible with minimum distance)
             {
                 p[i]= node_id;
                 d[i]= parent_distance      +link_distance;
                 depth_level[i]=parent_depth+1;


             }
           }
        }

        depth_level.at(node_id )=inf_depth;   //In this way the depth of the previous level of expansion is not taken into account when finding the new minimum.

        //-------------------------------------------------------------------------------------------------
        //Find the minimum depth from each node that is reachable, in case of a tie, get the node with the minimum distance to the source.
        //-------------------------------------------------------------------------------------------------

        //Option 2:


        find_index_of_smallest_element_in_a_vector_and_use_a_secondary_tie_breaker_vector(depth_level, id_of_node_to_explore_next, d, false); //get the index to the node with minimum depth (and if possible with minimum distance)


        //-------------------------------------------------------------------------------------------------

        min_depth = depth_level.at(id_of_node_to_explore_next); //Minimum depth


        if ((min_depth < inf_depth) && (available_in_open_set[id_of_node_to_explore_next]==true))  //If the node is actually connected to the the parent.
        {
            //Now find the node.....
            faulty_search=find_element_in_vector_from_id(open_set,id_of_node_to_explore_next,index_in_opened_set);

            if (faulty_search==0)
            {
                open_set.at(index_in_opened_set).p = p[id_of_node_to_explore_next];
                open_set.at(index_in_opened_set).d = d[id_of_node_to_explore_next];
                index_closed_set++;

                //cout<<index_closed_set<<endl;
                closed_set.at(index_closed_set)= open_set.at(index_in_opened_set); //Add node to the closed set.

                open_set.erase(open_set.begin()+index_in_opened_set);   //Erase node from the opened_set.
                                                                        //THIS CAN BE IMPROVED USING A DATA STRUCTURE SUCH AS A
                                                                        //DOUBLY LINKED LIST OR A SIMPLY LINKED LIST INSTEAD OF A VECTOR.

                parent_depth                                     = min_depth;
                depth_level[id_of_node_to_explore_next]          = inf_depth; //In this way this node won't be considered in the next iteration when computing the minimum.
                available_in_open_set[id_of_node_to_explore_next]= false;

                if (verbose) {cout<<"Exploring node "<<id_of_node_to_explore_next<<" with depth "<<min_depth;
                              cout<<endl;
                              //cout<<". distance:"; print_vector(d,false); cout<<endl;
                             }
            }
            else
            {
              return 1;
            }

            //This condition prevents the program to find a path to each node, once it has found a valid target specified by the user.
            if ((target_id!=-1) && ( (closed_set.at(index_closed_set).id) == target_id))  //if the user has specified a target and it has found it, then finish.....
            {
                if (verbose) cout<<"There is a path between source node "<<source_id<<" and target node "<<target_id<<" in the current graph"<<endl;
                return 0;
            }

            //Go to BIG LOOP
        }
        else
        {
            connected_graph = 0;

            if (verbose)
            {
                if (target_id==-1)
                {
                    cout<<"The graph is not fully connected. Not all nodes can be reached from the source node"<<endl;
                }
                else
                {
                    cout<<"There is no path between source node "<<source_id<<" and target node "<<target_id<<" in the current graph"<<endl;
                }
            }
            return 1;
        }
        iter++;  //iterations.
    }
    return 0;
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------



//This function implements a  depth-first search algorithm
template<class T>
int my_depth_first_search(const int & vertices, const int & source_id, const vector< vector<T> > & M, vector<T> & d, vector<int> & p, const int & target_id=-1, const vector< string > & node_names= vector<string>(0), bool verbose=false)
{
    //cout<<"The dimension of matrix M is ["<<M.size()<<"x"<<M[0].size()<<"]"<<endl<<endl;
    //cout<<"The content of Matrix M is:"<<endl<<M;

    const T inf=numeric_limits<T>::max();  //Infinite for distances (it can be int, unsigned or even double).


    //cout<<"The largest number for int is "<<inf;

    //Make sure d and p are initialized in the correct values.
    d.assign (vertices,inf);
    p.assign (vertices,-1);

    //---------------------------------------------------------------------------------------

    int index_closed_set=0;
    int index_in_opened_set=0;
    int faulty_search;      //0. The search was successful. 1: The search failed.
    int node_id;            //Node identifier.

    vector<bool> available_in_open_set(vertices,true);  //A "true" in an index i, will indicate that the node with id==i is available in the open_set
                                                        //to be expanded

    vector< graph_node<int> > open_set(vertices);       // A vector, with (vertices) nodes, initialized in infinity.
    vector< graph_node<int> > closed_set(vertices);     // A vector, with (vertices) nodes, initialized in infinity.

    bool connected_graph=1;  //Start the program assuming that the graph is connected.
    int iter=0;              //Variable to control the number of iterations.

    T link_distance;       //link distance from the node being explored to the ith-node.
    T parent_distance;     //distance from the source node to the parent node.

    unsigned parent_depth;
    unsigned max_depth;
    const unsigned min_depth=0; //Notice that depth is a unsigned integer category....
    vector< unsigned > depth_level(vertices,min_depth);  //Vector with depth from each node to the source node.
    typename vector< unsigned >::iterator max_iterator;   //This iterator is used to find the node with the maximum depth.

    unsigned id_of_node_to_explore_next;           //It will be used as an index later.

    //---------------------------------------------------------------------------------------
    //Graph representation.
    //---------------------------------------------------------------------------------------

    //Set a unique id and name for each node
    for (int i=0; i<vertices; ++i)
    {
        open_set[i].id = i;

        if (node_names.size()==static_cast<unsigned>(vertices))   //If the user did provide a string identifier for each node
        {
            open_set[i].name=node_names[i];
        }
    }
    //---------------------------------------------------------------------------------------

    if ((source_id>=0) && (source_id<vertices))  //If source_id is a valid index.....
    {
            faulty_search=find_element_in_vector_from_id(open_set, source_id,index_in_opened_set); //Return the index_in_opened_set if faulty_search==0

            if (faulty_search==0)
            {
                open_set[index_in_opened_set].d=0;                                 //The distance from the source node to itself is zero.
                open_set[index_in_opened_set].p=source_id;                         //The source node has no parent as such. Therefore it can be its own father.

                d[source_id]=0;
                p[source_id]=source_id;
                depth_level[source_id]=0;
                parent_depth =  depth_level[source_id];

                closed_set.at(index_closed_set)=open_set[index_in_opened_set]; //Add node to the closed set.
                open_set.erase(open_set.begin()+index_in_opened_set);          //Erase node from the opened_set.
                                                                               //THIS CAN BE IMPROVED USING A DATA STRUCTURE
                                                                               //SUCH AS A DOUBLY LINKED LIST OR A SIMPLY LINKED LIST INSTEAD OF A VECTOR.

                available_in_open_set[source_id]=false;                        //This is to mark that the node is no longer in the open_set.

                if (verbose) {cout<<"Exploring node "<<source_id<<" with depth "<<depth_level[source_id];
                    cout<<endl;
                    //cout<<". distance:"; print_vector(d,false); cout<<endl;
                    }

                //If the source node is the target node return.
                if ((target_id!=-1) && ( (closed_set.at(index_closed_set).id) == target_id))  //if the user has specified a target and it has found it, then finish.....
                {

                if (verbose) cout<<"There is a path between source node "<<source_id<<" and target node "<<target_id<<" in the current graph"<<endl;

                return 0;
                }
            }
            else
            {
                cout<<"The source node is not available"<<endl;
                return 1;
            }
    }
    else
    {
        cout<<"The source node id is not valid, it should be an integer number between 0 and the number of vertices minus 1."<<endl;
        return 1;
    }


    //---------------------------------------------------------------------------------------
    //Big Loop
    //---------------------------------------------------------------------------------------


    while ((iter < (vertices-1)) && (connected_graph==1))
    {
        node_id         = closed_set.at(index_closed_set).id;  //Get the id of the node that is being explored.
        parent_distance = closed_set.at(index_closed_set).d;   //Get distance from source node to this node.


        for (int i=0; i<vertices; ++i)  //For all possible id.  THIS CAN BE IMPROVED AS NOT ALL VERTICES ARE CONNECTED TO CURRENT NODE.
        {
           link_distance=M[node_id][i];  //Weight between the current node and the i-th node.

           if ( (link_distance != 0) && (available_in_open_set[i]==true) ) //If there is a connection, and the node requested is available in the open set.
           {
                 p[i]= node_id;                                           //Update the parent of node i
                 d[i]= parent_distance      +link_distance;               //Update the distance from source to node i.
                 depth_level[i]=parent_depth+1;                           //Update the dept level of node i.
           }
        }

        depth_level.at(node_id )=min_depth;   //In this way the depth of the previous level of expansion is not taken into account when finding the new maximum

        //-------------------------------------------------------------------------------------------------
        //Find the maximum depth from each node that is reachable, in case of a tie, get the node with the minimum distance to the source.
        //-------------------------------------------------------------------------------------------------

        find_index_of_largest_element_in_a_vector_and_use_a_secondary_tie_breaker_vector(depth_level, id_of_node_to_explore_next, d, false); //get the index to the node with maximum depth (and if possible with minimum distance)

        //-------------------------------------------------------------------------------------------------

        max_depth = depth_level.at(id_of_node_to_explore_next); //Maximum depth

        if ((max_depth > min_depth) && (available_in_open_set[id_of_node_to_explore_next]==true))  //If the node is actually connected to the the parent.
        {
            //Now find the node.....
            faulty_search=find_element_in_vector_from_id(open_set,id_of_node_to_explore_next,index_in_opened_set);

            if (faulty_search==0)
            {
                open_set.at(index_in_opened_set).p = p[id_of_node_to_explore_next];
                open_set.at(index_in_opened_set).d = d[id_of_node_to_explore_next];
                index_closed_set++;

                //cout<<index_closed_set<<endl;
                closed_set.at(index_closed_set)= open_set.at(index_in_opened_set); //Add node to the closed set.

                open_set.erase(open_set.begin()+index_in_opened_set);   //Erase node from the opened_set.
                                                                        //THIS CAN BE IMPROVED USING A DATA STRUCTURE SUCH AS A
                                                                        //DOUBLY LINKED LIST OR A SIMPLY LINKED LIST INSTEAD OF A VECTOR.

                parent_depth                                     = max_depth;
                depth_level[id_of_node_to_explore_next]          = min_depth; //In this way this node won't be considered in the next iteration when computing the maximum
                available_in_open_set[id_of_node_to_explore_next]= false;

                if (verbose) {cout<<"Exploring node "<<id_of_node_to_explore_next<<" with depth "<<max_depth;
                              cout<<endl;
                              //cout<<". distance:"; print_vector(d,false); cout<<endl;
                             }
            }
            else
            {
              return 1;
            }

            //This condition prevents the program to find a path to each node, once it has found a valid target specified by the user.
            if ((target_id!=-1) && ( (closed_set.at(index_closed_set).id) == target_id))  //if the user has specified a target and it has found it, then finish.....
            {
                if (verbose) cout<<"There is a path between source node "<<source_id<<" and target node "<<target_id<<" in the current graph"<<endl;
                return 0;
            }

            //Go to BIG LOOP
        }
        else
        {
            connected_graph = 0;

            if (verbose)
            {
                if (target_id==-1)
                {
                    cout<<"The graph is not fully connected. Not all nodes can be reached from the source node"<<endl;
                }
                else
                {
                    cout<<"There is no path between source node "<<source_id<<" and target node "<<target_id<<" in the current graph"<<endl;
                }
            }
            return 1;
        }
        iter++;  //iterations.
    }
    return 0;
}


//---------------------------------------------------------------------------------------




#endif // SEARCH_ALGORITHMS_H_INCLUDED
