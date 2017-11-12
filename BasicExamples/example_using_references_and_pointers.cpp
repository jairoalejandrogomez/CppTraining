#include <iostream>

using namespace std;

int main(void)
{
    int a = 10;
    int b = 20;

    cout<<"Initial value of a="<<a<<endl;
    cout<<"Initial value of b="<<b<<endl<<endl;


    //-----------------------------------------
    //Pointer
    //-----------------------------------------

    int *ptr;   //Pointer
    ptr  = &a;  //ptr points to a.
    *ptr = 5;   //The net effect is a=5;

    ptr = &b;
    *ptr= 25;  //The net effect is b=25

    cout<<"New value of a="<<a<<endl;
    cout<<"New value of b="<<b<<endl<<endl;


    //-----------------------------------------
    //References. In C++, you can't declare a reference without initialization. You must initialize it.
    //-----------------------------------------
    a=10;
    b=20;

    int &my_reference1 = a;  //The value of the memory space retrieved by a, can now be retrieved by my_reference1 as well.
    int &my_reference2 = b;  //The value of the  memory space retrieved by b, can now be retrieved by my_reference2 as well.
    int &my_reference3 = my_reference2;  //The value of the memory space retrieved by b, and my_reference2, can now be retrieved by my_reference3 as well.

    my_reference1= 0;  //The net effect is a=0

    my_reference3= 30;  //The net effect is that the value retrieved either by my_reference2, my_reference3 or by b is equal to 30.

    cout<<"New value of a            ="<<a<<endl;
    cout<<"New value of my_reference1="<<my_reference1<<endl<<endl;


    cout<<"New value of b            ="<<b<<endl;
    cout<<"New value of my_reference2="<<my_reference2<<endl;
    cout<<"New value of my_reference3="<<my_reference3<<endl<<endl;


    return 0;
}
