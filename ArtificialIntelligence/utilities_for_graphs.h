#ifndef UTILITIES_FOR_GRAPHS_H_INCLUDED
#define UTILITIES_FOR_GRAPHS_H_INCLUDED


//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//Author:           Jairo Alejandro Gómez.
//Last modified on: 18th September 2015.
//Description:      Basic utilities used in search_algorithms.h
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------


#include <iostream>
#include <vector>
#include <list>
#include <limits>        //This is to use  numeric_limits<type>::max()()   in c++11
#include <iomanip>      //To use std::setfill, std::setw  (for formatting strings in cout).

using namespace std;

//---------------------------------------------------------------------------------------
//This function prints the content of a vector v, using cout.
template<class T>
void print_vector(const vector<T> &v, bool as_column=true)
{
    string c;

    if (as_column)
    {c="\n";}
    else {c=" ";}

        for (unsigned i=0; i<v.size(); ++i)
        {
         cout <<"["<<v.at(i)<<"]"<<c;
        }
}



//---------------------------------------------------------------------------------------


//This function prints the content of a vector v, using cout.
template<class T>
void print_vector_of_parents(const vector<T> &v, const vector< string > & v_names= vector<string>(0), bool as_column=true)
{
    string c;

    if (as_column)
    {c="\n";}
    else {c=" ";}

    if (v_names.size()==0)  //If there are no names to look up in a secondary vector v_names....
    {
        for (unsigned i=0; i<v.size(); ++i)
        {
         cout <<"[Node: "<<i<<", Parent: "<<v.at(i)<<"]"<<c;
        }
    }
    else
    {
        for (unsigned i=0; i<v.size(); ++i)
        {
         cout <<"[Node: "<<v_names.at(i)<<", Parent: "<<v_names.at(v.at(i))<<"]"<<c;
        }
    }

}

//---------------------------------------------------------------------------------------


//This operator overload allows the user to pass a vector
//as an ostream which is useful for using cout<<
template<class T>
ostream & operator<<(ostream & out,const vector<T> &v)
{
    for (unsigned i=0; i<v.size(); ++i)
    {
         out <<"["<<v.at(i)<<"]"<<endl;
    }

    return out;
}


//---------------------------------------------------------------------------------------
//This function compares the value of two vector elements
//It is called by the function std::min_element.
template<class T>
bool cmp_value_in_vector(const T & left_arg, const T & right_arg)
{
  return left_arg < right_arg;
}

//---------------------------------------------------------------------------------------

//if condition == false, it finds index with the minimum v value, and if possible with the smallest v2 value.
//if condition == true, it finds index with the minimum v value, and if possible with the largest v2 value.
template< class T1, class T2 >
int find_index_of_smallest_element_in_a_vector_and_use_a_secondary_tie_breaker_vector(const vector< T1 > &v,  unsigned & v_index_to_return, const vector< T2 > & v2, const bool condition=false)
{
       if (v.size() == v2.size())
       {
           v_index_to_return        = 0;
           T1  min_val              = v[0];
           T2 auxiliar_condition    = v2[0];

           for (unsigned i=0; i < v.size(); i++)
           {
             if ((v[i] < min_val) || ((v[i] == min_val) && ((condition==false) && (v2[i] < auxiliar_condition))) || ((v[i] == min_val) && ((condition==true)  && (v2[i] > auxiliar_condition))))
             {
                v_index_to_return  = i;
                min_val            = v[i];
                auxiliar_condition = v2[i];
             }
           }
       }
       else
       {
            cout<<"vectors v and v2 should have the same number of elements";
            return 1;
       }

       return 0;
}


//---------------------------------------------------------------------------------------

//if condition == false, it finds index with the largest v value, and if possible with the smallest v2 value.
//if condition == true,  it finds index with the largest v value, and if possible with the largest v2 value.
template< class T1, class T2 >
int find_index_of_largest_element_in_a_vector_and_use_a_secondary_tie_breaker_vector(const vector< T1 > &v,  unsigned & v_index_to_return, const vector< T2 > & v2, const bool condition=false)
{
       if (v.size() == v2.size())
       {
           v_index_to_return        = 0;
           T1  min_val              = v[0];
           T2 auxiliar_condition    = v2[0];

           for (unsigned i=0; i < v.size(); i++)
           {
             if ((v[i] > min_val) || ((v[i] == min_val) && ((condition==false) && (v2[i] < auxiliar_condition))) || ((v[i] == min_val) && ((condition==true)  && (v2[i] > auxiliar_condition))))
             {
                v_index_to_return  = i;
                min_val            = v[i];
                auxiliar_condition = v2[i];
             }
           }
       }
       else
       {
            cout<<"vectors v and v2 should have the same number of elements";
            return 1;
       }

       return 0;
}


//---------------------------------------------------------------------------------------
//This operator overload allows the user to pass a matrix
//built as a vector of vectors as an ostream which is useful
//for using cout<<
template<class T>
ostream & operator<<(ostream & out,const vector< vector<T> > &M)
{
    for(unsigned i = 0 ; i < M.size() ; ++i)
    {
        out<<"["<<'\t';  //'\t' is a tab.
		for(unsigned j = 0; j < M[0].size(); ++j)
		{
		 //std::cout << std::setfill (' ') << std::setw (3);   //The ' ' is to set fill character. setw(2) is to use at least two characters
		 out << M[i][j] << '\t'  ;
		}
		out <<"]"<<endl;
	}
	out << endl;

	return out;
}



//---------------------------------------------------------------------------------------

//This function analyses the connectivity matrix of a graph, to find out if the
//graph is_directed or not.
template<class T>
int is_a_directed_graph(const vector< vector<T> > & M, bool & is_directed=0)
{


    if (M.size() == M[0].size())  //If the Matrix M is square....
    {
        is_directed = false;  //Initially, assume that it is not a directed graph

        for(unsigned i = 0 ; i < M.size() ; ++i)
        {
            for(unsigned j = 0; j <=i; ++j)
            {
                if (M[i][j] != M[j][i])           //If the matrix is not symmetric....
                {
                    is_directed = true ;
                    return 0;                      // Success.
                }
            }
        }

    }
    else
    {
        return 1;                                  //Failure.
    }

    return 0;                                      // Success.
}

//---------------------------------------------------------------------------------------

//This function prints the content of a doubly linked
//list on the screen using cout<<
template< class T >
void print_doubly_linked_list(const list<T> & mylist)
{
  if (mylist.empty()==0)   //If the list is not empty.
  {
      for (typename list<T>::const_iterator it = mylist.begin(); it != mylist.end(); ++it)
      {
            cout<<"["<<(*it)<<"] ";
      }
      cout<<endl;
  }
  else
  {
      cout<<"[Empty list]"<<endl;
  }

}




//---------------------------------------------------------------------------------------
//This function prints the output "dp" generated by the function dynamic_programming.
//(i.e: it prints optimal paths from each node in a graph, to a  pre-selected target node).
//If the vector "node_names" has the same number of elements that the number of vertices in the graph (i.e if it
//has the same number of elements than dp), it prints each node sequence using name strings,
//otherwise it prints the node sequence using the node's id.
void print_dp(const vector< list<int> > & dp, const vector< string > & node_names= vector<string>(0) )
{
  int index;
  if (dp.size()>=0)    //If the vector of lists is not empty....
  {
     if (node_names.size()==dp.size()) //Print the sequence using node_names.
     {
         for (unsigned i=0; i<dp.size(); ++i)
         {
             for (typename list< int >::const_iterator it = dp[i].begin(); it != dp[i].end(); ++it)
             {
                index=(*it);
                cout<<"["<<node_names[index]<<"] ";
             }

             cout<<endl;
         }
     }
     else   //Print the sequence using the node's id.
     {
         for (unsigned i=0; i<dp.size(); ++i)
         {
             for (typename list<int>::const_iterator it = dp[i].begin(); it != dp[i].end(); ++it)
             {

                cout<<"["<<(*it)<<"] ";
             }

             cout<<endl;
         }
     }
  }
  else
  {
      cout<<"It is impossible to print the content of the vector of lists.";
  }

}

//---------------------------------------------------------------------------------------
//This function searches the value "val" in the doubly
//linked list mylist, and if the element is found
//an iterator passed by reference is modified and the
//function returns 0, otherwise the function returns 1.
template< class T >
int search_val_in_doubly_linked_list(const list<T> & mylist, T val, typename list<T>::const_iterator &it)
{
  if (mylist.empty()==0)   //If the list is not empty.
  {
      for (it = mylist.begin(); it != mylist.end(); ++it)
      {
            if ((*it)==val) //If the element has been found...
            {
               return 0;  //successful search
            }
      }


  }

  return 1; //faulty search;
}

//---------------------------------------------------------------------------------------
//This function receives a vector "dp" containing doubly
//linked lists and copies a sublist defined by the
//iterators "it_begin" and "it_end" into the position
//"dest_index" of the vector "dp"
void push_back_sublist(vector< list<int> >  & dp, int dest_index, list<int>::const_iterator it_begin, list<int>::const_iterator it_end)
{
  list<int>::const_iterator it;

  for (it = it_begin; it != it_end; ++it)
  {
     dp[dest_index].push_back((*it));
  }

}

//---------------------------------------------------------------------------------------
//This function reconstruct the optimal path between
//a source node identified by its "source_id" and
//the target node identified by its "target_id", given
//Dijkstra's solution in vectors "d" (cost) and "p" (parent),
//The sequence of nodes is returned in a doubly linked list
//called "node_sequence" that is modified by reference.
//an optional arguments corresponds to "inf" which is
//the value used to represent infinity in Dijkstra's algorithm.
template<class T>
int get_nodes_from_source_to_target(const int & source_id,const int & target_id, const vector<T> & d, const vector<int> & p, list<int> & node_sequence, bool empty_node_sequence=true, const T inf=numeric_limits<T>::max())
{

    if (empty_node_sequence==true)   //This is to start from a clean node_sequence by default.
    {

        node_sequence.clear();
    }


    if ( (target_id>=0) && (static_cast<unsigned>(target_id)<d.size())  && (source_id>=0) && (static_cast<unsigned>(source_id)<d.size()) )
    {
        if (d[target_id]!=inf)                      //If there is a path from the source.
        {

            node_sequence.push_front(target_id);     //Back trace the path from the target to the source....

            if (target_id==source_id)               //If the the algorithm reached its goal....
            {
                return 0;
            }
            else                                    //Get the next node recursively.
            {
               // cout<<source_id<<" "<<target_id<<endl;
                if (p[target_id]!=-1)
                {
                   return get_nodes_from_source_to_target(source_id,p[target_id],d,p,node_sequence, false);  //the false, is to avoid clearing up the node_sequence.
                }
                else
                {
                   node_sequence.clear(); //Clean as there is no path
                   //cout<<"There is no path from target to source"<<endl;
                   return 1;
                }

            }
        }
        else
        {

            //cout<<"There is no path from target to source"<<endl;
            return 1;
        }
    }

    return 1; //The program won't get here (this is just to avoid warning from the compiler).
}

//---------------------------------------------------------------------------------------


#endif // UTILITIES_FOR_GRAPHS_H_INCLUDED
