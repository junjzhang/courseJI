#include <chrono>
#include <fstream>
#include <iostream>
#include <math.h>

using namespace std;

int main() 
{
    //const char* command;
    //string temp;
    //string t1 = "./test -i BINARY < test";
    //string t11 = "./test -i UNSORTED < test";
    //string t111 = "./test -i FIBONACCI < test";
    //string t2 = " > out";
    ofstream outf;
    for (int ii = 2; ii < 13; ii++) {
    //    cout<<ii<<"********************"<<endl;
    //    cout<<"test for binary"<<endl;
    //    temp = t1 + to_string(ii) + t2 + to_string(ii);
    //    command = temp.c_str();
    //    auto start1 = chrono::steady_clock::now();
    //    system(command);
    //    auto end1 = chrono::steady_clock::now();
    //    chrono::duration<double, std::micro> elapsed = end1 - start1;
    //    cout << elapsed.count() << endl;

    //    cout<<"test for us"<<endl;
    //    temp = t1 + to_string(ii) + t2 + to_string(ii);
    //    command = temp.c_str();
    //    start1 = chrono::steady_clock::now();
    //    system(command);
    //    end1 = chrono::steady_clock::now();
    //    elapsed = end1 - start1;
    //    cout << elapsed.count() << endl;
        
    //    cout<<"test for fib"<<endl;
    //    temp = t1 + to_string(ii) + t2 + to_string(ii);
    //    command = temp.c_str();
    //    start1 = chrono::steady_clock::now();
    //    system(command);
    //    end1 = chrono::steady_clock::now();
    //    elapsed = end1 - start1;
    //    cout << elapsed.count() << endl;
        int num = pow(2, ii);
        outf.open("test"+to_string(ii));
        outf<<num<<endl;
        outf<<num<<endl;
        outf<<"0 0"<<endl;
        outf<<num-1<<" "<<num-1<<endl;
   for (int jj = 0; jj < num; jj++) {
        for (int jj = 0; jj <num ;jj++){
        outf<<abs(mrand48())%1000<<" ";
        }
        outf<<endl;
    }
    outf.close();
    }
  //auto start1 = chrono::steady_clock::now();
  //auto end1 = chrono::steady_clock::now();
  //chrono::duration<double, std::micro> elapsed = end1 - start1;
  //cout << elapsed.count() << endl;
  return 0;
}
