#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//Author:            Jairo Alejandro Gómez.
//Last modified on:  25th August 2015.


//Description: This class implements a basic "graph_node" used
//to handle Dijkstra algorithm. The "id" is conceived as an
//index and therefore it has to be an integer >=0.
//"name" is an optional string identifier for each node.
//"d" is the current estimated distance from a source node to this node.
//This class implements a default constructor, and it overloads
//the assignment operator.

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

#include <iostream>
#include <vector>        //vector from STL.
#include <limits>        //This is to use  numeric_limits<type>::max()()   in c++11

using namespace std;


//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

template<class T>
class graph_node
{
public:

    //---------------------------------------------------------------------------------------
    //Attributes
    //---------------------------------------------------------------------------------------
    int id;       //vertex id.
    string name;  //vertex name.
    T d;          //Current estimated distance from a source node to this node.
    int p;        //Parent's id in the solution (path to the source node).
    //---------------------------------------------------------------------------------------

    //notice that a valid id has to be >=0 therefore the program knows that anything below 0 has not been used and treat it accordingly.
    graph_node(int given_id=-1,string given_name="none",T given_d=numeric_limits<T>::max(), int given_p=-1):id(given_id),name(given_name),d(given_d),p(given_p){}
    ~graph_node(){}       //destructor

    graph_node<T> & operator=(const graph_node<T> & source_node)
    {
      if (this==&source_node)
      {
          return *this;
      }
      else
      {
          this->id  =source_node.id;
          this->name=source_node.name;
          this->d   =source_node.d;
          this->p   =source_node.p;

          return *this;
      }
    }
};

//---------------------------------------------------------------------------------------
//Overload operator to use << with objects from "graph_node" class.
template<class T>
ostream & operator<<(ostream & out, const graph_node<T> & node)
{
   out<<"id="<<node.id<<", name="<<node.name<<", d="<<node.d<<", p="<<node.p;
   return out;
}

//---------------------------------------------------------------------------------------
//This is function compares the attribute "d" of two graph_node objects.
//It is called by the function std::min_element.
template<class T>
bool cmp_distance_in_graph_nodes(const graph_node<T> & left_arg, const graph_node<T> & right_arg)
{
  return left_arg.d < right_arg.d;
}

//---------------------------------------------------------------------------------------
//This is function compares the attribute "id" of two graph_node objects.
//It is called by the function std::sort
template<class T>
bool cmp_id_in_graph_nodes(const graph_node<T> & left_arg, const graph_node<T> & right_arg)
{
  return left_arg.id < right_arg.id;
}

//---------------------------------------------------------------------------------------
//This function searches a graph_node with an attribute
//equal to "id" in the vector of graph_nodes "v". If the function
//finds the node it returns 0 and modifies by reference the "index"
//of its location, otherwise the function returns 1.
template<class T>
int find_element_in_vector_from_id(vector< graph_node<T> > v, int id, int &index)
{
    for (unsigned int i=0;i<v.size(); ++i)
    {
        if (v[i].id==id)
        {
            index = i;
            return 0;  //success
        }

    }

    return 1; //Could not find the node with the specified id.
}

//---------------------------------------------------------------------------------------


#endif // NODE_H_INCLUDED
