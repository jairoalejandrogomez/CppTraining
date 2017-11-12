#include <iostream>
#include <vector>

using namespace std;

int main()
{
    double data[]={1.0,2.0,3.0};
        
    cout<<"Original data"<<endl;
    for (double d : data)
    {
      cout<<d<<" ";
    }
        
    for (auto &element : data)  //&element is a reference declaration
    {
     element = element +2;      //This will increase the content of the vector by 2.
    }
    
    cout<<endl<<endl<<"Processed data"<<endl;
    for (auto d : data)
    {
      cout<<d<<" ";
    }
        
    return 0;
}
