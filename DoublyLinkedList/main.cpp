#include <iostream>

#include "doubly_linked_list.h"


using namespace std;

int main()
{

    //--------------------------------------------------------------
    dlle<int> node1;
    dlle<int> node2(4);
    dlle<int> node3(node2);

    cout<<"Node 1 value "<<node1.get_value()<<endl;
    cout<<"Node 2 value "<<node2.get_value()<<endl;
    cout<<"Node 3 value "<<node3.get_value()<<endl;


    cout<<endl;
    node1.print_value();
    cout<<endl;
    node2.print_value();
    cout<<endl;
    node3.print_value();
    cout<<endl;

    node1.set_value(static_cast<int>(10));
    cout<<endl<<"After changing node1, its value is "<<endl;
    node1.print_value();

    dlle<int> node4(20);
    node4=node1;

    cout<<endl<<endl<<"The value of node4 is "<<node4<< endl;

    //--------------------------------------------------------------

    dl_list<double> L1;

    L1.add_posterior_element(1.9);   //Check add_posterior_element.
    L1.add_posterior_element(1.8);
    L1.add_posterior_element(1.7);
    L1.add_posterior_element(1.6);

    L1.add_prior_element(2.0);       //Check add_prior_element



    cout<<endl<<"The content of list L1 is"<<endl;
    L1.print_list();   //check print_list method
    cout<<"List L1 has "<<L1.get_number_of_elements()<<" elements"<<endl;   //To check overloading of << operator


    dl_list<double> L2(L1);  //To check copy constructor
    cout<<endl<<"The content of list L2"<<endl<<L2;   //To check overloading of << operator

    dl_list<double> L3;
    L3=L2;                    //Check overloading of assignment operator.
    cout<<endl<<"The content of list L3"<<endl<<L3;   //To check overloading of << operator


    L3.delete_head_element();
    cout<<endl<<"The content of list L3 after removing previous head"<<endl<<L3;   //To check overloading of << operator


    L3.delete_tail_element();
    cout<<endl<<"The content of list L3 after removing previous tail"<<endl<<L3;   //To check overloading of << operator

    cout<<endl<<"List L3 has now "<<L3.get_number_of_elements()<<" elements";   //To check overloading of << operator


    L3.delete_list_elements();
    cout<<endl<<"After deleting all elements list L3 has now "<<L3.get_number_of_elements()<<" elements";   //To check overloading of << operator





    //--------------------------------------------------------------


    cout << endl<<endl<<"End!" << endl;
    return 0;
}
