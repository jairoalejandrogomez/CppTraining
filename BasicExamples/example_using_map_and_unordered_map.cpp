#include <iostream>
#include <string>
#include <map>
#include <unordered_map>  

//Note: unordered_map containers are faster than map containers to access individual elements by their key, 
//although they are generally less efficient for range iteration through a subset of their elements.

using namespace std;

int main()
{
    //              KEY        , DATA
    map           <unsigned long, string  > worker;
    unordered_map <unsigned long, unsigned> payroll;
    
    unsigned total_pay =0;
    
    //Empoyer 1 (using the key 100)
    worker[100] = "Mark Tissot";
    payroll[100] = 67300;
    
    //Employer 2 (using the key 500)
    worker[500]  = "Jhosep Mag";
    payroll[500] = 87300;
    
    auto p2 = payroll.begin();
    for(auto p = worker.begin(); p != worker.end(); ++p)
    {
        cout <<"ID: " << (*p).first << ", Name: " << (*p).second <<", Salary:\t$" <<(*p2).second << endl;
        p2++;
    }
    
    cout<<endl<<"                                    ------------"<<endl;
    
    for(auto p = payroll.begin(); p != payroll.end(); ++p) 
    {
    	total_pay += (*p).second;
    }
    
    cout << "\t\t\t     Total: \t$"<< total_pay << endl;
        
    return 0;
}
