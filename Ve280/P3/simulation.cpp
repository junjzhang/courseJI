#include "simulation.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

bool has_adrs(const string& instruction);
//EFFECTS: Justify that if a insturction need a address input
enum opcode_t convert_inst(const string& instruction);
//EEFECTS: Convert instruction into enum type
enum direction_t convert_dir(const string& dir);
//EFFECTS: Conver diretion into enum type


World::World(const string& summary,const string& world_file){
    ifstream file, prog_file;
    string prog_dir,temp_species,temp_prog,temp_inst,line,temp_dir;
    int ii = 0, jj =0, r, c;
    stringstream temp;

    //Initialize specie part

    file.open(summary);
    if(!file.is_open()) throw summary;
    getline(file,prog_dir);
    while(getline(file,temp_species)){
        if (temp_species.length()==0) break;
        if(ii>=int(MAXSPECIES)) throw 4;
        world.species[ii].name=temp_species;
        prog_file.open(prog_dir+"/"+temp_species);
        if(!prog_file.is_open()) throw (prog_dir+"/"+temp_species);
        //Initalize one specie
        jj = 0;
        while(getline(prog_file,temp_prog)){
            if (temp_prog.length()==0) break;
            if (jj>=int(MAXPROGRAM)) {
                cout<< "Error: Too many instructions for species "<<temp_species<<"!"<<endl;
                cout<< "Maximal number of instructions is "<<MAXPROGRAM<<"."<<endl;
                throw 5;
            }
            temp.str(temp_prog);
            temp>>temp_inst;
            world.species[ii].program[jj].op=convert_inst(temp_inst);
            if (has_adrs(temp_inst)) temp>>world.species[ii].program[jj].address;
            else world.species[ii].program[jj].address = 0;
            temp.str("");
            temp.clear();
            jj++;
        }
        world.species[ii].programSize = jj;
        prog_file.close();
        ii++;
    }
    world.numSpecies = ii;
    file.close();

    //Initalize grid:
    file.open(world_file);
    if(!file.is_open()) throw world_file;
    getline(file,line);
    temp.str(line);
    temp>>world.grid.height;
    if (world.grid.height>MAXHEIGHT||world.grid.height<=0) throw 10;
    getline(file,line);
    temp.clear();
    temp.str(line);
    temp>>world.grid.width;
    if (world.grid.width>MAXWIDTH||world.grid.width<=0) throw 11;
    temp.str("");
    temp.clear();
    for (ii = 0; ii<int(MAXHEIGHT); ii++){
        for(jj = 0; jj<int(MAXWIDTH);jj++)
           world.grid.squares[ii][jj] = NULL;
    }
    //Initialize creatures and grid's squares

    ii = 0;
    while(getline(file,line)){
        if(line.length()==0) break;
        if (ii>int(MAXCREATURES)) throw 7;
        temp.str(line);
        temp>>temp_species>>temp_dir>>r>>c;
        temp.str("");
        temp.clear();
        if (!bound_check(r,c)){
                cout<<"Error: Creature ("<<temp_species<<" "<<temp_dir<<" "<<r<<" "<<c<<") is out of bound!"<<endl;
                cout<<"The grid size is "<<to_string(int(world.grid.height))<<"-by-"<<to_string(int(world.grid.width))<<"."<<endl;
                throw 12;
        }
        if (world.grid.squares[r][c]!=NULL) {
            cout<<"Error: Creature ("<<temp_species<<" "<<temp_dir<<" "<<r<<" "<<c<<") overlaps with creature "<<World::print_creature(r,c)<<"!"<<endl;
            throw 13;
        }
        world.grid.squares[r][c] = &world.creatures[ii];
        world.creatures[ii].location.r = r;
        world.creatures[ii].location.c = c;
        world.creatures[ii].direction = convert_dir(temp_dir);
        set_specie1(ii,temp_species);
        world.creatures[ii].programID = 1;
        ii++;
    }
    world.numCreatures = ii;
    file.close();
}

bool has_adrs(const string& instruction){
    for(int ii=4; ii<9; ii++){
        if (opName[ii]==instruction){
            return true;
        }
    }
    return false;
}

enum opcode_t convert_inst (const string& instruction){
    for(int ii=0; ii<9; ii++){
        if (opName[ii]==instruction) return opcode_t(ii);
    }
    cout<< "Error: Instruction "<<instruction<<" is not recognized!"<<endl;
    throw 6;
}

enum direction_t convert_dir(const string& dir){
    for(int ii=0; ii<4; ii++){
        if(directName[ii]==dir) return direction_t(ii);
    }
    cout<< "Error: Direction "<<dir<<" is not recognized!"<<endl;
    throw 9;
}

void World::set_specie1(int order_c, const string& specie){
    for(int ii=0; ii<int(world.numSpecies); ii++){
        if (world.species[ii].name==specie) {
            world.creatures[order_c].species = &world.species[ii];
            return;
        }
    }
    cout<<"Error: Species "<<specie<<" not found!"<<endl;
    throw 8;
    return;
}

string World::print_creature(int r, int c){
    return ("("+world.grid.squares[r][c]->species->name+" "+directName[world.grid.squares[r][c]->direction]+" "+to_string(r)+" "+to_string(c)+")");
}

void World::move(int order_c,int address){
    int new_r = facing_pos_r(order_c);
    int new_c = facing_pos_c(order_c);
    if(!bound_check(new_r,new_c)){
        next_step(order_c,0);
        return;
    }
    if(world.grid.squares[new_r][new_c]!=NULL){
        next_step(order_c,0);
        return;
    }
    if(!address) set_loc(new_r,new_c,order_c);
    next_step(order_c,address);
    return;
}

int World::facing_pos_c(int order_c){
    int new_c = world.creatures[order_c].location.c;
    int dir = world.creatures[order_c].direction;
    switch (dir){
    case WEST:
        new_c--;
        break;
    case EAST:
        new_c++;
        break;
    }
    if (!(bound_check(new_c,0))) return MAXHEIGHT;
    return new_c;
}

int World::facing_pos_r(int order_c){
    int new_r = world.creatures[order_c].location.r;
    int dir = world.creatures[order_c].direction;
    switch (dir){
    case NORTH:
        new_r--;
        break;
    case SOUTH:
        new_r++;
        break;
    }
    if (!(bound_check(0,new_r))) return MAXWIDTH;
    return new_r;
}

bool World::bound_check(int r, int c){
    return (r<=int(world.grid.height)-1)&&(r>=0)&&(c<=int(world.grid.width)-1)&&(c>=0);
}

void World::set_loc(int r, int c, int order_c){
    int old_r = world.creatures[order_c].location.r;
    int old_c = world.creatures[order_c].location.c;
    world.creatures[order_c].location.r = r;
    world.creatures[order_c].location.c = c;
    world.grid.squares[r][c] = world.grid.squares[old_r][old_c];
    world.grid.squares[old_r][old_c] = NULL;
    return;
}

void World::next_step(int order_c, int address){
    if(address) world.creatures[order_c].programID = address;
    else world.creatures[order_c].programID++;
}

void World::turn(int order_c, int flag){
    int dir = world.creatures[order_c].direction;
    switch (dir){
    case EAST:
        world.creatures[order_c].direction = (flag)?NORTH:direction_t(dir+1);
        break;
    case NORTH:
        world.creatures[order_c].direction = (flag)?direction_t(dir-1):EAST;
        break;
    default:
        world.creatures[order_c].direction = (flag)?direction_t(dir-1):direction_t(dir+1);
    }
    next_step(order_c,0);
    return;
}

void World::infect(int order_c){
    int n_r = facing_pos_r(order_c);
    int n_c = facing_pos_c(order_c);
    next_step(order_c,0);
    if (!bound_check(n_r,n_c)) return;
    if (world.grid.squares[n_r][n_c] == NULL) return;
    if (world.grid.squares[n_r][n_c]->species->name == world.creatures[order_c].species->name) return;
    world.grid.squares[n_r][n_c]->species = world.creatures[order_c].species;
    world.grid.squares[n_r][n_c]->programID = 1;
    return;
}

void World::ifwall(int order_c, int adress){
    int n_r = facing_pos_r(order_c);
    int n_c = facing_pos_c(order_c);
    if (bound_check(n_r,n_c)){
        next_step(order_c,0);
        return;
    }
    next_step(order_c,adress);
    return;
}

void World::ifsame(int order_c, int adress, int flag){
    int n_r = facing_pos_r(order_c);
    int n_c = facing_pos_c(order_c);
    if(!bound_check(n_r,n_c)){
        next_step(order_c,0);
        return;
    }
    if(world.grid.squares[n_r][n_c]==NULL){
        next_step(order_c,0);
        return;
    }
    if(world.grid.squares[n_r][n_c]->species->name != world.creatures[order_c].species->name) adress = (flag)?0:adress;
    else adress = (flag)?adress:0;
    next_step(order_c,adress);
    return;
}

void World::print_instruction (int order_inst, enum opcode_t instruction, int address){
    string inst_name = opName[instruction];
    cout<<"Instruction "<<to_string(order_inst)<<": "<<inst_name;
    if(address) cout<< " "<<to_string(address);
    cout<<endl;
    return;
}

void World::run_step(int order_c,int print_flag){
    if (print_flag) cout<<endl;
    //cout<<world.creatures[order_c].species->name<<endl;
    int order_inst = world.creatures[order_c].programID;
    int address = world.creatures[order_c].species->program[order_inst-1].address;
    enum opcode_t instruction = world.creatures[order_c].species->program[order_inst-1].op;
    //cout<<opName[instruction]<<endl;
    while (instruction>3&&instruction<9){
        if(print_flag) print_instruction(order_inst,instruction,address);
        do_instruction(order_c,instruction, address);
        order_inst = world.creatures[order_c].programID;
        address = world.creatures[order_c].species->program[order_inst-1].address;
        instruction = world.creatures[order_c].species->program[order_inst-1].op;
    }
    if(print_flag) print_instruction(order_inst,instruction,address);
    else cout<<" "<<opName[instruction]<<endl;
    do_instruction(order_c,instruction,address);
    return;
}

void World::do_instruction(int order_c, enum opcode_t instruction, int address){
    switch (instruction){
    case HOP:
        move(order_c,0);
        break;
    case LEFT:
        turn(order_c,1);
        break;
    case RIGHT:
        turn(order_c,0);
        break;
    case INFECT:
        infect(order_c);
        break;
    case IFEMPTY:
        move(order_c,address);
        break;
    case IFWALL:
        ifwall(order_c,address);
        break;
    case IFSAME:
        ifsame(order_c,address,1);
        break;
    case IFENEMY:
        ifsame(order_c,address,0);
        break;
    case GO:
        next_step(order_c,address);
        break;
    }
    return;
}

void World::print_world(){
    int height = world.grid.height;
    int width = world.grid.height;
    for (int ii=0;ii<height;ii++){
        for(int jj=0;jj<width;jj++){
            if (world.grid.squares[ii][jj]==NULL) cout<<"____ ";
            else cout<<world.grid.squares[ii][jj]->species->name.substr(0,2)<<"_"<<directShortName[world.grid.squares[ii][jj]->direction]<<" ";
        }
        cout<<endl;
    }
    return;
}

void World::run_round(int print_flag){
    int num_c = world.numCreatures;
    for(int ii=0; ii<num_c;ii++){
        cout<<"Creature "<<print_creature(world.creatures[ii].location.r,world.creatures[ii].location.c)<<" takes action:";
        run_step(ii,print_flag);
        if (print_flag) print_world();
    }
    if(!print_flag) print_world();
    return;
}

void run_simulation(World &wd, int rounds, int print_flag){
    cout<<"Initial state"<<endl;
    wd.print_world();
    for(int ii=1; ii<=rounds; ii++){
        cout<<"Round "<<to_string(ii)<<endl;
        wd.run_round(print_flag);
    }
    return;
}
