#include <iostream>
#include <iomanip>      // std::setfill, std::setw

#include <vector>
#include<list>



using namespace std;



//------------------------------------------------------

template<class T>
void print_vector(const vector<T> &v)
{
    for (unsigned i=0; i<v.size(); ++i)
    {
         cout <<"["<<v.at(i)<<"]"<<endl;
    }

}

//------------------------------------------------------
template<class T>
ostream & operator<<(ostream &out,vector<T> v)
{
    for (unsigned i=0; i<v.size(); ++i)
    {
         out <<"["<<v.at(i)<<"]"<<endl;
    }
}

//------------------------------------------------------



template<class T>
ostream & operator<<(ostream &out,vector< vector<T> > M)
{




    for(unsigned i = 0 ; i < M.size() ; ++i)
    {
        out<<"[ ";
		for(unsigned j = 0; j < M[0].size(); ++j)
		{
		 std::cout << std::setfill (' ') << std::setw (3);   //The ' ' is to set fill character. setw(2) is to use at least two characters
		 out << M[i][j] << " " ;
		}
		out <<" ]"<<endl;
	}
	out << endl;

    return out;
}

//------------------------------------------------------

int main(void)
{
    const int rows=3;
    const int cols=2;
    vector< vector<int> > M(rows, vector<int>(cols) ) ;
	M[0][0] = 0;
	M[0][1] = 1;
	M[1][0] = 10;
	M[1][1] = 11;
	M[2][0] = 20;
	M[2][1] = 21;


    cout<<"The dimension of matrix M is ["<<M.size()<<"x"<<M[0].size()<<"]"<<endl;
    cout<<"The content of Matrix M is:"<<endl<<M;



    vector< vector<int> > M2{{0, 3, 9, 0, 0, 0},
                             {3, 0, 2, 1, 7, 0},
                             {9, 2, 0, 0, 6, 4},
                             {0, 1, 0, 0, 3, 0},
                             {0, 7, 6, 3, 0, 1},
                             {0, 0, 4, 0, 1, 0}};


    cout<<"The dimension of matrix M2 is ["<<M2.size()<<"x"<<M2[0].size()<<"]"<<endl;
    cout<<"The content of Matrix M2 is:"<<endl<<M2;


    return 0;
}


//------------------------------------------------------


