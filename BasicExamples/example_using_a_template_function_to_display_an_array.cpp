#include <iostream>
//---------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------
template <class T>
inline void display_vector_values(const T vec1[], int n)
{
    for (int i=0;i<n;i++)
    {
        cout<<"["<<vec1[i]<<"]"<<endl;
    }

}
//---------------------------------------------------------------
int main()
{
	int v[]={1,2,3,4};
	double v2[]={1.1,2.2,3.3,4.4};
	int n=4;

	cout<<"The elements of vector v are: "<<endl;
	display_vector_values(v,n);

	cout<<"The elements of vector v2 are: "<<endl;
	display_vector_values(v2,n);

	return 0;
}
//---------------------------------------------------------------