#include <iostream>
//-----------------------------------------------
using namespace std;
//-----------------------------------------------
class point{
private:
    double x, y;
public:
    //-------------------------------------------
	//Examples of Constructors:
    //-------------------------------------------
	//    point(){ x = y = 0.0;}

	//    point(){
	//           this -> x = 0.0;
	//           this -> y = 0.0;
	//           }

	//    point(double a, double b){
	//           this -> x = a;
	//           this -> y = b;
	//           }

	//    point(double a=0, double b=0){
	//           x = a;
	//           y = b;
	//           }

    point(double a=0.0,double b=0.0):x(a),y(b){}

    //-------------------------------------------
    //class functions
    //-------------------------------------------
    void set(double a, double b) {x=a; y=b;}
    double getx(void) {return x;}
    double gety(void) {return y;}
};
//-----------------------------------------------
//Overload operator +
point operator+ (point& p1, point& p2){
    point sum(p1.getx() + p2.getx(), p1.gety() + p2.gety());
return sum;
}
//-----------------------------------------------
//Overload << operator to use cout.
ostream& operator<< (ostream& out, point& p){
out << "( " << p.getx() << ", " << p.gety() <<" )";
return out;
}
//-----------------------------------------------
int main()
{
	point P1;
	point P2, P3;
	P1.set(3,4);    
	P2.set(2,3);

	cout<<"P1"<<P1<<endl;
	cout<<"P2"<<P2<<endl;
	cout<<"P3"<<P3<<endl;
	P3=P1+P2;
	cout<<"P3"<<P3<<endl;

	return 0;
}
//-----------------------------------------------