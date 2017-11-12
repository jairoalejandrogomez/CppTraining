#include <iostream>
//-------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------
template <class T>
inline T sum_vector(T* vec1, int n)
{
    T sum1=0;
    for (int i=0;i<n;i++)
    {
        sum1=sum1+vec1[i];
    }

    return sum1;
}
//-------------------------------------------------------------------
int main()
{
	int v[]={1,2,3,4};
	int n=4;
	int tsum;

	tsum=sum_vector(v,n);

	cout<<"The sum of the elements of vector v is: "<<tsum<<endl;

	return 0;
}
//-------------------------------------------------------------------