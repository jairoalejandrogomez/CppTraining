//For more information on the importance of good pseudo random number generators, 
//please visit: https://channel9.msdn.com/Events/GoingNative/2013/rand-Considered-Harmful


//Feel free to comment/uncomment the version that you want to try.

//--------------------------------------------------
//Option 1
//--------------------------------------------------
#include <iostream>
#include <random>

using namespace std;

int main()
{   												  //The Mersenne Twister is a pseudorandom number generator (PRNG). 
	std::mt19937 mt(1729);                            //Engine [0,2^32). Deterministic 32-bit seed.
	                                                  //Very fast, but NOT cryptographically secure.
	                                                  //Seedable with more than 32 bits if you want.
	                                                  //Reproducible.
	std::uniform_int_distribution<int> dist(0,99);    //Distribution [0,99], inclusive on both ends. 
	                                                  //Preserves perfect uniformity.
	                                                  //Deterministic, but NOT invariant. (It will vary across platforms, may vary across versions)
	for (int i=0; i<16; ++i)
	{
		cout<<dist(mt)<<" ";                          //dist runs the engine, viewed through distribution.
	}		

	cout<<endl;
}

////--------------------------------------------------
////Option 2
////--------------------------------------------------
//
//#include <iostream>
//#include <random>
//
//using namespace std;
//
//int main()
//{
//	std::random_device rd;  //Non-deterministic 32-bit seed.
//	                        //Possible slow.
//	                        //Strongly platform-dependent.
//	                        //Possibly crypto-secure.
//	                        //Non-seedable, non-reproducible.
//	std::mt19937 mt(rd());                             
//	std::uniform_int_distribution<int> dist(0,99);     
//	for (int i=0; i<16; ++i)
//	{
//		cout<<dist(mt)<<" ";                         
//	}		
//
//	cout<<endl;
//}
////--------------------------------------------------