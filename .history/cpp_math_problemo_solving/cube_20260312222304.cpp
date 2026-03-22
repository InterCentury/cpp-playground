#include<iostream>
#include <cmath>
using namespace std;

//main formula = 
//! (a+b+c)^3 = a^3 + b^3 + c^3 + 3a^2b + 3a^2c + 3ab^2 +  
//!             3b^2c + 3ac^2 + 3bc^2 + 6abc    

void step_1_printing_process_fn()
    {
      cout << "The main formula: ";
			 cout << "(a+b+c)^3 = a^3 + b^3 + c^3 + 3a^2b + 3a^2c + 3ab^2 +  3b^2c + 3ac^2 + 3bc^2 + 6abc  ";
    }
void step_2_printing_process_fn(int a,int b,int c,int a_square,int b_square, int c_square, int a_cube,int b_cube,int c_cube,int main_result)
    {

		 cout << endl << "step 2 printing process,"<<endl;	
     cout<<"(a+b+c)^3 ="<<a<<"^"<<"3"<<  "+"   <<b<<"^"<<"3"<<  "+"  <<c<<"^"<<"3"; cout << endl;
		 cout << "  +  " <<" 3*"<<a<<" ^2"<<" * "<<b<<"   +   "<<"3*"<<a<<"    *   "<<b<<"^2";      cout << endl;
		 cout << "  +  " <<" 3*"<<b<<" ^2"<<" * "<<c<<"   +   "<<"3*"<<b<<"    *   "<<c<<"^2";      cout << endl;
		 cout << "  +  " <<" 3*"<<a<<" ^2"<<" * "<<c<<"   +   "<<"3*"<<a<<"    *   "<<c<<"^2";      cout << endl;
		 cout << "  +  " <<" 6*"<<a<<"*"<<b<<"*"<<c  <<"  =  "<< main_result;
     
		}
void step_3_printing_process_fn(int a,int b,int c,int a_square,int b_square, int c_square, int a_cube,int b_cube,int c_cube,int main_result)
    {
     cout << endl<< endl << "step 3 printing process,"<<endl;	
     cout <<"("<<a<<"^3"<<"  + "<<a<<"^3"<<"  + "<<b<<"^3"<<"  + "<<c<<"^3"<<"  + "<<")"<<endl;
		 cout << "  +  " <<" (3*"<<a<<" ^2"<<" * "<<b<<")   +   ("<<"3*"<<a<<"    *   "<<b<<"^2)";      cout << endl;
     cout << "  +  " <<" (3*"<<b<<" ^2"<<" * "<<c<<")   +   ("<<"3*"<<b<<"    *   "<<c<<"^2)";      cout << endl;
     cout << "  +  " <<" (3*"<<a<<" ^2"<<" * "<<c<<")   +   ("<<"3*"<<a<<"    *   "<<c<<"^2)";      cout << endl;
     cout << "  +   (" <<" 6*"<<a<<"*"<<b<<"*"<<c<<")"  <<"  =  "<< main_result;
		}
void step_4_printing_process_fn(int a,int b,int c,int a_square,int b_square, int c_square, int a_cube,int b_cube,int c_cube,int main_result)
    {
     cout << endl << endl << "step 4 printing process,"<<endl;	
     cout <<"("<<a<<"^3"<<"  + "<<a<<"^3"<<"  + "<<b<<"^3"<<"  + "<<c<<"^3"<<"  + "<<")"<<endl;
		 cout << "  +  " <<" (3*"<<a_square<<"*"<<b<<")   +   ("<<"3*"<<a<<"*"<<b_square <<")";      cout << endl;
     cout << "  +  " <<" (3*"<<b_square<<"*"<<c<<")   +   ("<<"3*"<<b<<"*"<<c_square <<")";      cout << endl;
     cout << "  +  " <<" (3*"<<a_square<<"*"<<c<<")   +   ("<<"3*"<<a<<"*"<<c_square <<")";      cout << endl;
     cout << "  +  (" <<"6*"<<a<<"*"<<b<<"*"<<c<<")" <<")" <<"  =  "<< main_result;
     
		}
void step_5_printing_process_fn(int a,int b,int c,int a_square,int b_square, int c_square, int a_cube,int b_cube,int c_cube,int main_result)
    {
     cout << endl << endl << "step 5 printing process,"<<endl;	
    cout <<"("<<a_cube+b_cube+c_cube<<")";
		 cout << "  + (" <<3*a_square*b<<")  +  ("<<3*a*b_square <<")";    
     cout << "  + (" <<3*b_square*c<<")  +  ("<<3*b*c_square <<")";    
     cout << "  + (" <<3*a_square*c<<")  +  ("<<3*a*c_square <<")";    
     cout << "  +  (" <<6*a*b*c<<")" <<"  =  "<< main_result;
		}
void step_6_printing_process_fn(int main_result)
    {
			cout << endl << endl << "Finally, result = " << main_result;
		}										

int main()
{
	int a; int b; int c;
	// ask user for the value of abc 
	cout << "Enter the value of abc," << endl;
	cout << "Enter :"; cin >> a >> b >> c;
  
  //generate power as cube
	  int a_cube = a*a*a;int b_cube = b*b*b; int c_cube = c*c*c;
	//generate power as square
	  int a_square = a*a; int b_square = b*b; int c_square = c*c;	
  
	int main_ans = (a+b+c)*(a+b+c)*(a+b+c);
	cout << endl;
	step_1_printing_process_fn();
	cout << endl;
  step_2_printing_process_fn(a,b,c,a_square,b_square,c_square,a_cube,b_cube,c_cube,main_ans);
	step_3_printing_process_fn(a,b,c,a_square,b_square,c_square,a_cube,b_cube,c_cube,main_ans);
	step_4_printing_process_fn(a,b,c,a_square,b_square,c_square,a_cube,b_cube,c_cube,main_ans);
	step_5_printing_process_fn(a,b,c,a_square,b_square,c_square,a_cube,b_cube,c_cube,main_ans);
	step_6_printing_process_fn(main_ans);
  return 0;
}


