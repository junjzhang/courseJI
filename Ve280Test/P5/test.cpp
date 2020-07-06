 #include <iostream>
 #include <cstdlib>
 #include <string>
 #include <fstream>
 using namespace std;

int main(){
    string calc = "calc";
    string call = "call";
    string input = "_input";
    string ans = "_ans";
    string my_a = "_myans";
    string diff = "diff -s ";
    string line;
    string temp;
    const char* command;
    int ii = 0;
    ifstream ifile;

    // Changed the system call from compile to copy, so that we can put
    // the P5 test files in a separate folder.
    system("cp ../calc ./");
    system("cp ../call ./");
    // system("g++ -std=c++11 -o calc calc.cpp");
    // system("g++ -std=c++11 -o call call.cpp");

    cout<<"********begin to test calculator********"<<endl;
    for (ii=1;ii<=4;ii++){

        cout<<"test "+calc+to_string(ii)<<"--------"<<endl;//please cout the file u test
        temp = "./calc <"+calc+to_string(ii)+" > "+calc+my_a+to_string(ii);
        command = temp.c_str();
        system(command);

        temp = diff+calc+ans+to_string(ii)+" "+calc+my_a+to_string(ii);
        command = temp.c_str();
        system(command);
    }
    // Add empty line.
    cout<<"\n*********begin to test leak of memory of calculator"<<endl;
    for (ii=1;ii<=3;ii++){
        cout<<"test "+calc+to_string(ii)<<"--------"<<endl;//please cout the file u test
        // Add ">/dev/null" to suppress stdout output.
        temp = "valgrind --leak-check=full ./calc >/dev/null < "+calc+to_string(ii);
        command = temp.c_str();
        system(command);
        cout<<"**Please check whether above information to see if there's memory leak**"<<endl;
        cout<<"Type any key to continue testing"<<endl;
        getchar();
    }
    cout<<"********End testing calculator********"<<endl;
    cout<<'\n'<<endl;
    cout<<"********begin to test call********"<<endl;
    for (ii=1;ii<=4;ii++){

        cout<<"test "+call+to_string(ii)<<"--------"<<endl;//please cout the file u test
        temp = "./call <"+call+to_string(ii)+" > "+call+my_a+to_string(ii);
        command = temp.c_str();
        system(command);

        temp = diff+call+ans+to_string(ii)+" "+call+my_a+to_string(ii);
        command = temp.c_str();
        system(command);
    }
    // Add empty line.
    cout<<"\n*********begin to test leak of memory of call"<<endl;
    for (ii=1;ii<=4;ii++){
        cout<<"test "+call+to_string(ii)<<"--------"<<endl;//please cout the file u test
        temp = "valgrind --leak-check=full ./call >/dev/null < "+call+to_string(ii);
        command = temp.c_str();
        system(command);
        cout<<"**Please check whether above information to see if there's memory leak**"<<endl;
        cout<<"Type any key to continue testing"<<endl;
        getchar();
    }
    cout<<"********End testing call********"<<endl;
    
    return 0;
}

