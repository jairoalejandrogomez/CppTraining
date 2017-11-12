#include <iostream>
//---------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------
template<class T1, class T2>
void copy(const T1 source[], T2 destination[],int size)
{
 //Note: This loop assumes that both arrays have exactly the same size !!!.
 for (int i=0;i<size;++i)
 {
   destination[i]=static_cast<T2>(source[i]);
 }
}
//---------------------------------------------------------------------
template <class T>
inline void display_vector_values(const T vec1[], int n)
{
    for (int i=0;i<n;++i)
    {
        cout<<"["<<vec1[i]<<"]"<<endl;
    }

}
//---------------------------------------------------------------------
int main()
{
    const int i1[]={1,2,3,4};
    int i2[]={0,0,0,0};

    const double d1[]={1.1,2.2,3.3,4.4};
    double d2[]={0.0,0.0,0.0,0.0};

    int n=4;

    copy(i1,i2,n);
    copy(d1,d2,n);


    cout<<"The elements of vector v are: "<<endl;
    display_vector_values(i1,n);

    cout<<"The elements of vector v2 are: "<<endl;
    display_vector_values(d2,n);

    return 0;
}
//---------------------------------------------------------------------