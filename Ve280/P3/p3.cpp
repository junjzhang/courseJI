#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "simulation.h"


using namespace std;

int main (int argc, char *argv[]){
    int rounds, print_flag = 0;//1 for v
    string species_sum,world_file,print_mode;
    stringstream temp;

    //Handle argument
    try{
        if (argc<4) throw 1;
        for(int ii=1 ;ii<argc ;ii++){
            temp<<argv[ii]<<" ";
        }
        temp>>species_sum>>world_file>>rounds;
        if (argc == 5) temp>>print_mode;
        temp.str("");
        temp.clear();
        if (rounds <0) throw 2;
        if (print_mode == "v" || print_mode == "verbose") print_flag = 1;
        World wd(species_sum,world_file);
        run_simulation(wd,rounds,print_flag);
    }

    //Handle possible error
    catch(int v){
        if (v == 1){
            cout<<"Error: Missing arguments!"<<endl;
            cout<<"Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]"<<endl;
        }
        if (v == 2){
            cout<<"Error: Number of simulation rounds is negative!"<<endl;
        }
        if (v == 4){
            cout<<"Error: Too many species!"<<endl;
            cout<<"Maximal number of species is "<<MAXSPECIES<<"."<<endl;
        }
        if (v == 7){
            cout<<"Error: Too many creatures!"<<endl;
            cout<<"Maximal number of creatures is "<<MAXCREATURES<<"."<<endl;
        }
        if (v == 10){
            cout<<"Error: The grid height is illegal!"<<endl;
        }
        if (v == 11){
            cout<<"Error: The grid width is illegal!"<<endl;
        }
        return 0;
    }
    catch(string v){
        cout<<"Error: Cannot open file "<<v<<"!"<<endl;
        return 0;
    }
    return 0;
}
