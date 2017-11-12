#ifndef SINGLY_LINKED_LIST_H_INCLUDED
#define SINGLY_LINKED_LIST_H_INCLUDED
 

#include <iostream>

using namespace std;


//------------------------------------------------------------------------
// Author: Jairo Alejandro Gómez.
// Date:   14th August 2015.
// Description: This library implements a single list element class and a list
// class with basic methods using templates.


// Single list element representation
//                       _________
//     list_head     -> |  value  |  --> next_ptr
//                      |_________|
//


//Note: if you get an error that says 'nullptr' was not declared in this scope. Do as follows:
//code blocks -> settings -> compiler
//Select Have g++ follow the c++11 ISO c++ language standard [-std=c++11]
//------------------------------------------------------------------------





//------------------------------------------------------------------------
// Class 1
//------------------------------------------------------------------------

template<class T>
class sle   //Single List Element (sle)
{
protected:
    sle *next_ptr;
    T value;

public:
    sle(T);       //Constructor
    ~sle();       //Destructor

    //-------------------------------------------------------------------
    //Methods
    //-------------------------------------------------------------------
    void set_value(T);
    T get_value();

    sle<T>* get_next_ptr_addr();
    void set_next_ptr_addr(sle<T>*);
    //-------------------------------------------------------------------
 };
//------------------------------------------------------------------------


template<class T>
std::ostream& operator<< (std::ostream&, sle<T> &);  //Overload operator <<





//------------------------------------------------------------------------
// Class 2
//------------------------------------------------------------------------

template<class T>
class my_list:sle<T>
{
protected:
    sle<T> *head;
    int n;               //number of elements in the list.

public:
    my_list();                    //Constructor.
    my_list(const my_list<T> &);  //Deep copy constructor.
    ~my_list();                   //Destructor

    my_list<T> & operator=(const my_list<T> &); //Overloading operator =

    sle<T> * get_head(void) const;            //This is called a "const function", and it had to be defined this way, so that a method receiving a const argument can call it.
    int get_number_of_elements (void) const;

    void add_prior_element(T);
    void add_posterior_element(T);
    void print_list_elements(void);
    void delete_list_elements(void);

    bool remove_head(T&);
    bool remove_tail(T&);

    //Pending:
    //Find an element by value.
    //Sort the list in increasing or decreasing order
 };
//------------------------------------------------------------------------


template<class T>
std::ostream& operator<< (std::ostream&, my_list<T> &);   //Overload operator <<

//------------------------------------------------------------------------







//------------------------------------------------------------------------
// Implementation of the classes
//------------------------------------------------------------------------
////To force the compiler to compile templates
////that are likely to be used, here the content of of the
////implementation (usually stored in a .cpp file) was copied into
////this .h file. Otherwise
////you will get an error when building your project saying something
////like "undefined reference to AN_TYPE_INSTANTIATION_OF_THIS_TEMPLATE".
////------------------------------------------------------------




//------------------------------------------------------------------------
//------------------------------------------------------------------------
//Class1 - Single list element (sle) class.
//------------------------------------------------------------------------
//------------------------------------------------------------------------
template<class T>
sle<T>::sle(T val=0):next_ptr(nullptr),value(val){}         //Constructor. Notice you could use 0 instead of nullptr. but nullptr is type safe in c++11.

template<class T>
sle<T>::~sle(){}                                            //Destructor

//-------------------------------------------------------------------
//Methods
//-------------------------------------------------------------------
template<class T>
void sle<T>::set_value(T val){value=val;}

template<class T>
T sle<T>::get_value(){return value;}

template<class T>
sle<T>* sle<T>::get_next_ptr_addr(){return next_ptr;}

template<class T>
void sle<T>::set_next_ptr_addr(sle<T>* new_ptr){next_ptr=new_ptr;}
//------------------------------------------------------------
//Overload operators outside the class.
//------------------------------------------------------------

//Overloading << operator to enable its use when calling cout
template<class T>
std::ostream& operator<< (std::ostream& out, sle<T> &node){
out << "( " << node.get_value() <<" )";
return out;
}



//------------------------------------------------------------------------
//------------------------------------------------------------------------
// Class 2. my_list class
//------------------------------------------------------------------------
//------------------------------------------------------------------------

//Constructor. Notice you could use 0 instead of nullptr. but nullptr is type safe in c++11.
template<class T>
my_list<T>::my_list()
{
 head=nullptr;
 n=static_cast<int>(0);
}


//Deep copy constructor.
template<class T>
my_list<T>::my_list(const my_list<T> &  source_list)  //In this way the argument is given without copying its content to the stack, but it cannot be changed.
{
  n=0;
  head=nullptr;

  sle<T> *cursor;
  cursor = source_list.get_head();

  while (cursor != nullptr)
  {
    this->add_posterior_element(cursor->get_value());   //This line update the head as well.
    cursor = cursor -> get_next_ptr_addr();
  }
}

//---------------------------------------------------------------------

//Overload assignment operator.
template<class T>
my_list<T> & my_list<T>::operator=(const my_list<T> &source_list)
{
       if (this == &source_list)
       {
         return *this;  //*this so we can chain the assignment operator .
                        //also if we don’t need to make a copy, why make one?
       }
       else
       {
           this -> delete_list_elements();   //De allocate any previous content

           //Copy attributes

           //Perform a deep copy of the list elements.
           sle<T> *cursor;
           cursor = source_list.get_head();

           while (cursor != nullptr)
           {
               this->add_posterior_element(cursor->get_value());   //This line update the head, and n as well.
               cursor = cursor -> get_next_ptr_addr();
           }

           return *this;
       }
}

//---------------------------------------------------------------------

template<class T>
my_list<T>::~my_list() //Destructor
{
  //cout<<endl<<"Destroying a list..."<<endl;
  delete_list_elements();
}

//---------------------------------------------------------------------

template<class T>
sle<T> * my_list<T>::get_head(void) const  //This is called a const function, and it had to be defined this way, so that a method receiving a const argument can call it.
{
  return head;
};

//---------------------------------------------------------------------

template<class T>
int my_list<T>::get_number_of_elements (void) const
{
  return n;
};

//---------------------------------------------------------------------

template<class T>
void my_list<T>::add_prior_element(T val2)    //This creates and inserts a new element at the beginning, and updates the head of the list (also known as prepend)
{
       sle<T>* prior;
       prior = new sle<T>(val2);
       prior->set_next_ptr_addr(head);
       head=prior;

       n++;   //Add 1 to the number of elements in the list.
}

//---------------------------------------------------------------------

template<class T>
void my_list<T>::add_posterior_element(T val2)    //This creates and inserts a new element at the end, and updates the head of the list.
{
       sle<T>* posterior;
       posterior = new sle<T>(val2);

       sle<T>* tmp_ptr;
       tmp_ptr=head;

       if (head!=nullptr)  //If the list is not empty find the pointer to the last element and link the new element called posterior
       {
         while (tmp_ptr->get_next_ptr_addr()!=nullptr)
         {
             tmp_ptr=tmp_ptr->get_next_ptr_addr();
         }

         tmp_ptr->set_next_ptr_addr(posterior);
       }
       else   //If the list was empty, update the head of the list.
       {
         head=posterior;
       }

       n++;   //Add 1 to the number of elements in the list.
}

//---------------------------------------------------------------------



template<class T>
bool my_list<T>::remove_head(T& val)
{
     sle<T>* tmp_ptr;

     if (head != nullptr)
        {
              val = head -> get_value();           //Retrieve the value pointed by the head

              tmp_ptr = head->get_next_ptr_addr(); //get the address to the next element.
              delete head;                         //Delete current element
              head = tmp_ptr;                      //update head point

              n--;                                 //Subtract 1 from the number of elements in the list.

              return 0;                            //Success
       }
    else
       {
              return 1;                            //Failure (the list is empty).
       }

}

//---------------------------------------------------------------------


template<class T>
bool my_list<T>::remove_tail(T& val)
{

     if  (head!=nullptr)            //If the list is not empty...
     {
         sle<T> * cursor = head;
         sle<T> * prev_cursor = head;

         while (cursor->get_next_ptr_addr()!=nullptr)
         {
             prev_cursor = cursor;                    //Pointer to the previous list element
             cursor = cursor->get_next_ptr_addr();

         }

         val=cursor->get_value();     //Get the value from the tail of the list.

         if (prev_cursor == cursor)   //If there is a single element in the list....
         {
            head = nullptr;           //Now, it is an empty list.
         }
         else
         {
             prev_cursor->set_next_ptr_addr(nullptr);   //The previous element will be now the new last element.
             delete cursor;                             //delete the unconnected node.
         }

         n--;   //Decrement the number of elements within the list.

         return 0;  //Success.
     }
    else //if the list is empty
    {
         return 1; //Failure.
    }


}

//---------------------------------------------------------------------

template<class T>
void  my_list<T>::delete_list_elements(void)
{
    sle<T>* next_ptr;

     if (head != nullptr)
     {
              next_ptr=head->get_next_ptr_addr();
              delete head;                        //Delete current element
              head = next_ptr;                    //update head point

              n--;                                //Subtract 1 from the number of elements in the list.

              delete_list_elements();             //Recursively destroy all list elements.
     }
}

//------------------------------------------------------------


template<class T>
void  my_list<T>::print_list_elements(void)  //default value =head.
{
            sle<T> * cursor = head;

            while (cursor != nullptr)
            {
              cout<<"("<<cursor->get_value()<<") "<<endl;
              cursor=cursor->get_next_ptr_addr();
            }

}


//------------------------------------------------------------
//Overload operators outside the classes.
//------------------------------------------------------------

//Overloading << operator to enable its use when calling cout

template<class T>
std::ostream& operator<< (std::ostream& out, my_list<T> &list_of_interest){
    sle<T> * cursor = list_of_interest.get_head();
    while (cursor != nullptr)
    {
      out<<"("<<cursor->get_value()<<") "<<endl;
      cursor=cursor->get_next_ptr_addr();
    }

return out;
}






//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------


#endif // SINGLY_LINKED_LIST_H_INCLUDED


