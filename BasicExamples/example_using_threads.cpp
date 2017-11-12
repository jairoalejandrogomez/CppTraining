#include <iostream>
#include <vector>


#include <thread>
#include <mutex>


using namespace std;

//-----------------------------------------

void capture_key(char & key)
{
    cin >> key;
}

//-----------------------------------------

int main(void)
{

   char k='\0';  //Null character.

   //Start thread calling the function capture_key, passing by reference the variable k.
   std::thread my_thread(capture_key, std::ref(k));

   cout<<"Entering an infinite loop in the main program."<<endl;
   cout<<"The only way to leave the loop is pressing a key that will be captured by a thread." <<endl;

   while (k=='\0')
   {
        //wait
   }
   cout<<"Leaving the loop" <<endl<<endl;

   cout<<"The key captured in the thread was: "<<k<<endl<<endl;

   my_thread.join();  //This is to wait for the thread to finish.

   return 0;
}
