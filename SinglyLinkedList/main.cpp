#include <iostream>

#include "singly_linked_list.h"

using namespace std;


int main()
{


//------------------------------------------------------------
//List 1
//------------------------------------------------------------
int extracted_value;


my_list<int> L1;

cout<<"The list has "<<L1.get_number_of_elements()<<" elements"<<endl;

L1.add_prior_element(5);
L1.add_prior_element(4);
L1.add_prior_element(3);
L1.add_prior_element(2);
L1.add_prior_element(1);  //Head.

cout<<"Content of List L1 using built-in method"<<endl;
L1.print_list_elements();
cout<<"The list has "<<L1.get_number_of_elements()<<" elements"<<endl<<endl;

cout<<"Content of list L1 using overloaded operator << "<<endl;
cout<<L1<<endl<<endl;
cout<<"The list L1 has "<<L1.get_number_of_elements()<<" elements"<<endl<<endl;
//---------------------------------------------------------------

my_list<int> L2;
L2.add_posterior_element(5); //Head
L2.add_posterior_element(4);
L2.add_posterior_element(3);
L2.add_posterior_element(2);
L2.add_posterior_element(1);

cout<<"Content of list L2 using overloaded operator << "<<endl;
cout<<L2;
cout<<"The list L2 has "<<L2.get_number_of_elements()<<" elements"<<endl<<endl;

//----------------------------------------

cout<<"Removing the head"<<endl;
L1.remove_head(extracted_value);   //extracted_value is meaningful if the method returns 0;
cout<<"Content of List L1"<<endl;
L1.print_list_elements();
cout<<"The list L1 has "<<L1.get_number_of_elements()<<" elements"<<endl<<endl;

cout<<"Removing the tail"<<endl;
L1.remove_tail(extracted_value);    //extracted_value is meaningful if the method returns 0;
cout<<"Content of List L1"<<endl;
L1.print_list_elements();
cout<<"The list L1 has "<<L1.get_number_of_elements()<<" elements"<<endl<<endl;

cout<<"Deleting all elements"<<endl;
L1.delete_list_elements();

cout<<"Print empty list L1"<<endl;
L1.print_list_elements();
cout<<"The list L1 has "<<L1.get_number_of_elements()<<" elements"<<endl;

//----------------------------------------
//Testing deep copy constructor
//----------------------------------------
my_list<int> L3(L2);

cout<<endl<<endl<<"Content of List L3"<<endl;
L3.print_list_elements();
cout<<"The list L3 has "<<L3.get_number_of_elements()<<" elements"<<endl;

//----------------------------------------
//Testing overloaded assignment operator.
//----------------------------------------
my_list<int> L4;
L4=L2;             //This calls the overloaded assignment operator.
cout<<endl<<endl<<"Content of List L4"<<endl;
L4.print_list_elements();
cout<<"The list L4 has "<<L4.get_number_of_elements()<<" elements"<<endl;



return 0;
}

