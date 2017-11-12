#include <iostream>
#include <vector>

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


int main(void)
{

   vector<int> v(2);  //Vector with 2 elements

   v.at(0)=1;
   v.at(1)=2;

   cout<<"Content of vector v[0]    = "<<v[0]<<endl;      //This works but it doesn't check the bounds.
   cout<<"Content of vector v.at(1) = "<<v.at(1)<<endl;   //This does the same, it does check the bounds, and therfore it takes longer.

   cout<<endl<<"Content of vector v using function:"<<endl;
   print_vector(v);

   cout<<endl<<"Content of vector v using overloaded operator:"<<endl<<v;


   vector<int> v2;
   v2.push_back(1);   // Adds an element to the end of a vector
   v2.push_back(2);
   v2.push_back(3);

   v=v2;               //Deep copy !!!!

   cout<<endl<<"New content of vector v after using the deep copy"<<endl<<v;


   int my_value=v.at(v.size()-1);
   v.pop_back();                       //This only deletes the last element, it DOESN'T return the value.

   cout<<endl<<"The value removed was "<<my_value<<endl;

   cout<<endl<<"New content of vector v after doing a pop_back"<<endl<<v;


   v.clear();  // Erases all elements of the vector

   if (v.empty())  //Returns true if the vector is empty
    cout<<endl<<"the vector is now empty"<<endl;




    return 0;
}


//------------------------------------------------------

