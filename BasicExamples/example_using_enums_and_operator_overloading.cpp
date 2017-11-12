#include <iostream>
//----------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------
typedef enum days{SUN, MON, TUE, WED, THU, FRI, SAT} days;
//----------------------------------------------------------------
inline days operator+ (days d)
{
    return static_cast<days>((static_cast<int>(d) + 1) % 7);
}
//----------------------------------------------------------------
ostream & operator<<(ostream& out, days d)
{
	switch (d)
	{
		case SUN: out << "Sunday"; break;
		case MON: out << "Monday"; break;
		case TUE: out << "Tuesday"; break;
		case WED: out << "Wednesday"; break;
		case THU: out << "Thursday"; break;
		case FRI: out << "Friday"; break;
		case SAT: out << "Saturday"; break;
	}
    
    return out;
}

//----------------------------------------------------------------
int main()
{
	days a=FRI, b;
	b= (+a);

	cout<<"The day after "<<a<<" is "<<b<<endl;

	return 0;
}
//----------------------------------------------------------------