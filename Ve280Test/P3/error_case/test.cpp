 #include <iostream>
 #include <cstdlib>
 #include <string>
 #include <fstream>
 using namespace std;
 
int main(){
    string cop = "cannotopen";
    string mis = "miss_argument";
    string ans = "_ans";
    string spi = "spi_error";
    string my_a = "myans";
    string txt = ".txt";
    string diff = "diff -s ";
    string line; 
    string temp;
    const char* command;
    int ii = 0;
    ifstream ifile;
     
    system("g++ -o p3 simulation.cpp p3.cpp");

    for (ii=1;ii<3;ii++){
        ifile.open(cop+to_string(ii)+txt);
        getline(ifile,line);
        ifile.close();
        cout<<"test "+cop+to_string(ii)+txt<<"--------"<<endl;//please cout the file u test
        temp = line+" > "+my_a+to_string(ii)+txt;//command line is Csting, so first create a string
        command = temp.c_str();//Then, convert it into cstring type by .c_str()
        system(command); 
        temp = diff+cop+to_string(ii)+ans+txt+" "+my_a+to_string(ii)+txt;
        command = temp.c_str();
        system(command);
    }
    for (ii=1;ii<5;ii++){
        ifile.open(mis+to_string(ii)+txt);
        getline(ifile,line);
        ifile.close();
        cout<<"test "+mis+to_string(ii)+txt<<"--------"<<endl;
        temp = line+" > "+my_a+to_string(ii)+txt;
        command = temp.c_str();
        system(command); 
        temp = diff+mis+to_string(ii)+ans+txt+" "+my_a+to_string(ii)+txt;
        command = temp.c_str();
        system(command);
    }
    for (ii=1;ii<4;ii++){
        cout<<"test "+spi+to_string(ii)+txt<<"--------"<<endl;
        temp = "./p3 "+spi+to_string(ii)+txt+" world"+" 10"+" > "+my_a+to_string(ii)+txt;
        command = temp.c_str();
        system(command); 
        temp = diff+spi+to_string(ii)+ans+txt+" "+my_a+to_string(ii)+txt;
        command = temp.c_str();
        system(command);
    }
    return 0;
}
