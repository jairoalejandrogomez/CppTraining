#include <iostream>
#include <random>
//------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------
std::random_device rd;
std::mt19937 mt(rd());      //Non-deterministic 32-bit seed.
	                        //Possible slow.
	                        //Strongly platform-dependent.
	                        //Possibly crypto-secure.
	                        //Non-seedable, non-reproducible.
//------------------------------------------------------------------
double prob()
{
   std::uniform_real_distribution<> dist(0, 1);   //Distribution [0,1], inclusive on both ends.
                                                  //Preserves perfect uniformity.
                                                  //Deterministic, but NOT invariant. (It will vary across platforms, may vary across versions)
   return dist(mt);                               //dist runs the engine, viewed through distribution.
}
//------------------------------------------------------------------
void create_matrix_representing_a_random_graph(bool** &graph, int graph_size, double density)
{
	//Dynamically create a 2D matrix of type bool

	graph = new bool*[graph_size];
	for(int i = 0; i <graph_size; ++i)
	{
		graph[i] = new bool[graph_size];
	}
	//heap created 2 D array of Bool


	for (int i = 0; i < graph_size; i++)
	{
	 for(int j = i; j < graph_size; j++)
	 {
	   if (i == j)
	   {
		graph[i][j]= false; //no loops
	   }
	   else
	   {
	   	graph[i][j] = graph[j][i] = (prob() < density);
	   }

	 }
	}
}
//------------------------------------------------------------------
template <class T>
inline void print_matrix(T ** matrix, int m, int n)
{
    for (int i=0;i<m; ++i)
    {
        cout << "[ ";
        for (int j=0; j<n; ++j)
        {
            cout<<matrix[i][j]<<" ";
        }
        cout<<"]"<<endl;
    }

}
//------------------------------------------------------------------
int main()
{
	int graph_size=5;    //graph represented by a connectivity matrix of 5 x 5.
	double density=0.19; //Probability that an edge exists between two nodes. (it can be a number between 0.0 and 1.0)
	bool** graph;

	create_matrix_representing_a_random_graph(graph,graph_size,density);

	print_matrix(graph,graph_size,graph_size);

	return 0;
}
//------------------------------------------------------------------
