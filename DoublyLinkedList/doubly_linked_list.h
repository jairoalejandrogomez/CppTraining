#ifndef DOUBLY_LINKED_LIST_H_INCLUDED
#define DOUBLY_LINKED_LIST_H_INCLUDED


//--------------------------------------------------------
//Author: Jairo Alejandro Gómez.
//Date:   15th August 2015.
//Description: this library implements a basic doubly linked
//list data structure using templates in C++.
//--------------------------------------------------------


#include <iostream>

using namespace std;

//---------------------------------------------------------
//Class 1.
//---------------------------------------------------------

template<class T>
class dlle  //doubly linked list element
{
private:
     T val;
     dlle<T> * next_ptr;  //next pointer.
     dlle<T> * prev_ptr;  //previous pointer.
 public:
     dlle();                 //Default constructor.
     dlle(T);                //Constructor with value.
     dlle(const dlle<T> &);  //Copy constructor.

     ~dlle();                //Destructor.

     T get_value(void) const;
     void print_value(void);
     dlle<T> * get_next_ptr(void) const;
     dlle<T> * get_prev_ptr(void) const;


     void set_value(T);
     void set_next_ptr(dlle<T> *);
     void set_prev_ptr(dlle<T> *);

     dlle<T> & operator=(const dlle<T> &);

};

//---------------------------------------------------------------

//Default constructor
template<class T>
dlle<T>::dlle():val(static_cast<T>(0)),next_ptr(nullptr),prev_ptr(nullptr){}


//Constructor when a value is given.
template<class T>
dlle<T>::dlle(T val2)
{
    val=val2;
    next_ptr=nullptr;
    prev_ptr=nullptr;
}


//Copy constructor
template<class T>
dlle<T>::dlle(const dlle<T> & source_node)
{
    val= source_node.get_value();
    next_ptr=nullptr;
    prev_ptr=nullptr;
}

//Destructor.
template<class T>
dlle<T>::~dlle(){}


template<class T>
T dlle<T>::get_value(void) const
{
    return val;
}

template<class T>
void dlle<T>::print_value(void)
{
    cout<<get_value();
}


template<class T>
dlle<T> * dlle<T>::get_next_ptr(void) const
{
    return next_ptr;
}


template<class T>
dlle<T> * dlle<T>::get_prev_ptr(void) const
{
    return prev_ptr;
}

template<class T>
void dlle<T>::set_value(T val2)
{
  val = val2;
}


template<class T>
void dlle<T>::set_next_ptr(dlle<T> * next_ptr_given)
{
   next_ptr = next_ptr_given;
}


template<class T>
void dlle<T>::set_prev_ptr(dlle<T> * prev_ptr_given)
{
   prev_ptr=prev_ptr_given;
}

//Overload assignment operator
template<class T>
dlle<T> & dlle<T>::operator=(const dlle<T> & source_node)
{
    if (this == &source_node)
    {
        return *this;
    }
    else
    {
       val= source_node.get_value();
       next_ptr=nullptr;
       prev_ptr=nullptr;

       return *this;
    }

}


//---------------------------------------------------------
//Oveload operator <<

template<class T>
ostream & operator <<  (ostream &out,const dlle<T> & source_node)
{
    out<<source_node.get_value();
    return out;
}


//---------------------------------------------------------
//Class 2.
//---------------------------------------------------------

template<class T>
class dl_list:dlle<T> //doubly linked list
{
private:
        int num_elements;
        dlle<T> * head;
        dlle<T> * tail;


public:
        dl_list();                      //Constructor
        dl_list(const dl_list<T> &);    //Copy constructor
        ~dl_list();                     //Destructor

        void add_prior_element(T);
        void add_posterior_element(T);


        dlle<T> * get_head_ptr(void) const;
        dlle<T> * get_tail_ptr(void) const;
        int get_number_of_elements(void) const;

        void print_list(void);

        void delete_head_element(void);
        void delete_tail_element(void);

        void delete_list_elements(void);

        dl_list<T> & operator=(const dl_list<T> &);

        //insert_node
        //remove_node
        //find_value
};



//---------------------------------------------------------



template<class T>
dl_list<T>::dl_list():num_elements(0),head(nullptr),tail(nullptr){}  //Constructor

//---------------------------------------------------------

template<class T>
dl_list<T>::dl_list(const dl_list<T> & source_list)    //Copy constructor
{
    num_elements=0;
    head=nullptr;
    tail=nullptr;

    dlle<T> *cursor=source_list.get_head_ptr();

    while (cursor!=nullptr)
    {
        this->add_posterior_element(cursor->get_value());  //add_posteior_element creates the node and update the pointers.
        cursor = cursor->get_next_ptr();
    }

}

//---------------------------------------------------------

template<class T>
dl_list<T>::~dl_list()
{
    delete_list_elements();
}

//---------------------------------------------------------

template<class T>
void dl_list<T>::add_prior_element(T val)
{
    dlle<T> *ptr;
    ptr=new dlle<T>;

    ptr->set_value(val);
    num_elements++;

    if (head==nullptr)  //If the list is empty
    {
     //List
     head=ptr;
     tail=ptr;

     //There is no need to set next and prev pointers as they already are nullptr

    }
    else  //If there is a single element or if the list has more than one element.
    {
        ptr->set_next_ptr(head);
        ptr->set_prev_ptr(nullptr);
        head->set_prev_ptr(ptr);
        head=ptr;
    }
}


//---------------------------------------------------------

template<class T>
void dl_list<T>::add_posterior_element(T val)
{
    dlle<T> *ptr;
    ptr=new dlle<T>;

    ptr->set_value(val);
    num_elements++;

    if (head==nullptr)  //If the list is empty
    {
     //List
     head=ptr;
     tail=ptr;

     //There is no need to set next and prev pointers as they already are nullptr

    }
    else  //If there is a single element or if the list has more than one element.
    {
        ptr->set_next_ptr(nullptr);
        ptr->set_prev_ptr(tail);

        tail->set_next_ptr(ptr);
        tail=ptr;
    }

}

//---------------------------------------------------------

template<class T>
dlle<T> * dl_list<T>::get_head_ptr(void) const
{
    return head;
}

//---------------------------------------------------------

template<class T>
dlle<T> * dl_list<T>::get_tail_ptr(void) const
{
    return tail;
}

//---------------------------------------------------------
template<class T>
int dl_list<T>::get_number_of_elements(void) const
{
   return num_elements;
}

//---------------------------------------------------------
template<class T>
void dl_list<T>::print_list(void)
{
    dlle<T> * ptr_i=head;

    while (ptr_i!=nullptr)
    {
        cout<<"("<<ptr_i->get_value()<<")"<<endl;
        ptr_i=ptr_i->get_next_ptr();
    }

}
//---------------------------------------------------------

template<class T>
void dl_list<T>::delete_head_element(void)
{
   dlle<T> * cursor;

   if (head!=nullptr) //If there is at least one element, there is something to delete
   {
       cursor = head->get_next_ptr();

       delete head;

       num_elements--;

       if (cursor==nullptr)  //if there is a single element
       {
           tail = nullptr;
           head = nullptr;
       }
       else  //If there is at least another element.
       {
           cursor ->set_prev_ptr(nullptr); //Disconnect the node pointed by the head.
           head = cursor;
       }
   }
}


//---------------------------------------------------------

template<class T>
void dl_list<T>::delete_tail_element(void)
{
   dlle<T> * cursor;

   if (tail!=nullptr) //If there is at least one element, there is something to delete
   {
       cursor = tail->get_prev_ptr();

       delete tail;

       num_elements--;

       if (cursor==nullptr)  //if there is a single element
       {
           tail = nullptr;
           head = nullptr;
       }
       else  //If there is at least another element.
       {
           cursor ->set_next_ptr(nullptr); //Disconnect the node pointed by the head.
           tail = cursor;
       }
   }
}

//---------------------------------------------------------

template<class T>
void dl_list<T>::delete_list_elements(void)
{
    dlle<T> * cursor=head;

    while (head!=nullptr)
    {
        cursor=cursor->get_next_ptr();
        delete head;
        head = cursor;
    }
}

//---------------------------------------------------------


template<class T>
dl_list<T> & dl_list<T>::operator=(const dl_list<T> & source_list)
{
    if (this== &source_list)
    {
        return *this;
    }
    else
    {
        //delete any existing nodes.
        delete_list_elements();

        //Reset target list
        num_elements=0;
        head=nullptr;
        tail=nullptr;

        //Now perform a deep copy of the source_list:
        dlle<T> *cursor=source_list.get_head_ptr();
        while (cursor!=nullptr)
        {
            add_posterior_element(cursor->get_value());  //add_posteior_element creates the node and update the pointers.
            cursor = cursor->get_next_ptr();
        }
        return *this;
    }
}

//---------------------------------------------------------

//Overload << operator external to the class.
template<class T>
ostream & operator<<(ostream & out, const dl_list<T> & source_list)
{
    dlle<T> * cursor=source_list.get_head_ptr();

    while (cursor!=nullptr)
    {
        out<<"("<<cursor->get_value()<<")"<<endl;
        cursor=cursor->get_next_ptr();
    }

    return out;
}


//---------------------------------------------------------

#endif // DOUBLY_LINKED_LIST_H_INCLUDED
