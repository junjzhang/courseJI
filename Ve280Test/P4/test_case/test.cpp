 #include <iostream>
 #include <cstdlib>
 #include <string>
 #include <fstream>
 using namespace std;

int main(){
    string wc = "winning_condition";
    string pc = "PVC";
    string cp = "CVP";
    string pp = "PVP";
    string cc = "CVC";
    string input = "_input";
    string ans = "_ans";
    string my_a = "myans";
    string txt = ".txt";
    string diff = "diff -b ";
    string line;
    string temp;
    const char* command;
    int ii = 0;
    ifstream ifile;

    for (ii=1;ii<=6;ii++){

        cout<<"test "+wc+to_string(ii)<<"--------"<<endl;//please cout the file u test



        temp = "./game h h <"+wc+to_string(ii)+txt+" > "+my_a+to_string(ii)+txt;
        command = temp.c_str();
        system(command);


        temp = diff+wc+to_string(ii)+ans+txt+" "+my_a+to_string(ii)+txt;
        command = temp.c_str();
        system(command);
    }
    for (ii=1;ii<=3;ii++){
        ifile.open(pc+to_string(ii)+input+txt);
        getline(ifile,line);
        ifile.close();
        cout<<"test "+pc+to_string(ii)+txt<<"--------"<<endl;

        temp = line + " < "+pc+to_string(ii)+txt+" > "+my_a+to_string(ii)+txt;
        command = temp.c_str();
        system(command);

        temp = diff+pc+to_string(ii)+ans+txt+" "+my_a+to_string(ii)+txt;
        command = temp.c_str();
        system(command);
    }
    for (ii=1;ii<=3;ii++){
        ifile.open(cc+to_string(ii)+input+txt);
        getline(ifile,line);
        ifile.close();
        cout<<"test "+cc+to_string(ii)+txt<<"--------"<<endl;

        temp = line + " > "+my_a+to_string(ii)+txt;
        command = temp.c_str();
        system(command);

        temp = diff+cc+to_string(ii)+ans+txt+" "+my_a+to_string(ii)+txt;
        command = temp.c_str();
        system(command);
    }
      for (ii=1;ii<=2;ii++){
        ifile.open(cp+to_string(ii)+input+txt);
        getline(ifile,line);
        ifile.close();
        cout<<"test "+cp+to_string(ii)+txt<<"--------"<<endl;

        temp = line + " < "+cp+to_string(ii)+txt+" > "+my_a+to_string(ii)+txt;
        command = temp.c_str();
        system(command);

        temp = diff+cp+to_string(ii)+ans+txt+" "+my_a+to_string(ii)+txt;
        command = temp.c_str();
        system(command);
    }
      for (ii=1;ii<=3;ii++){
        ifile.open(pp+to_string(ii)+input+txt);
        getline(ifile,line);
        ifile.close();
        cout<<"test "+pp+to_string(ii)+txt<<"--------"<<endl;

        temp = line + " < "+pp+to_string(ii)+txt+" > "+my_a+to_string(ii)+txt;
        command = temp.c_str();
        system(command);

        temp = diff+pp+to_string(ii)+ans+txt+" "+my_a+to_string(ii)+txt;
        command = temp.c_str();
        system(command);
    }
    return 0;
}

