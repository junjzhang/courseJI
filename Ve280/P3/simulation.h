#ifndef SIMULATION_H
#define SIMULATION_H

#include "world_type.h"

class World{
    //overview: a simulation world
    struct world_t world;
    void set_specie1(int order_c,const string& specie);
    //REQUIRES: Legal order_c (0-numCreatures-1), legal species name
    //MODIFIES: no. order_c creature's species
    //EFFECTS: Change creature's species with specific name
    string print_creature(int r, int c);
    //REQUIRES: 0<r<height, 0<c<width
    //EFFECTS: Return a string that describes the location and name of a creature
    void move(int order_c, int address);
    //REQUIRES: Legal order_c (0-numCreatures-1), legal address
    //MODIFIES: no. order_c creature's programID and its'location and grid
    //EFFECTS: Do hop instruction of no. order_c creature if adress is 0, do if empty if the adress is not 0
    int facing_pos_r(int order_c);
    //REQUIRES: Legal order_c (0-numCreatures-1)
    //EFFECTS: Return the rows of the facing posiion of no. order_c creature.
    int facing_pos_c(int order_c);
    //REQUIRES: Legal order_c (0-numCreatures-1)
    //EFFECTS: Return the columns of the facing posiion of no. order_c creature.
    bool bound_check(int r,int c);
    //REQUIRES: 0<r<height, 0<c<width
    //EFFECTS: Check position if r,c are out of bound
    void set_loc(int r, int c, int order_c);
    //REQUIRES: 0<r<height, 0<c<width, Legal order_c (0-numCreatures-1), legal species name
    //MODIFIES: no. order_c creature's programID and its'location and grid
    //EFFECTS: Set the location of creature no. oder_c
    void next_step(int order_c, int address);
    //REQUIRES: Legal order_c (0-numCreatures-1), leagal address
    //MODIFIES: no. order_c creature's programID
    //EFFECTS: Update the programID of creature no. order_c
    void turn(int order_c, int flag);
    //REQUIRES: Legal order_c (0-numCreatures-1), flag 0 or 1, 1 for left and 0 for right
    //MODIFIES: no. order_c creature's direction
    //EFFECTS: Let creature of no. order_c turn
    void infect(int order_c);
    //REQUIRES: Legal order_c (0-numCreatures-1)
    //MODIFIES: no. order_c creature's species
    //EFFECTS: Do infect instrucion on creature no. order_c
    void ifwall(int order_c, int adress);
    //REQUIRES: Legal order_c (0-numCreatures-1), leagal address
    //MODIFIES: no. order_c creature's programID
    //EFFECTS: Do inwall instruction on creature no. order_c with adress n
    void ifsame(int order_c, int adress, int flag);
    //REQUIRES: Legal order_c (0-numCreatures-1), leagal address, flag 0 or 1, if flag is 1, do if enemy if flag is 0
    //MODIFIES: no. order_c creature's programID
    //EFFECTS: Do ifsame instructon on creature no. order_c with adress n
    void do_instruction(int order_c, enum opcode_t instruction, int address);
    //REQUIRES: Legal order_c (0-numCreatures-1), leagal address
    //MODIFIES: no. order_c creature and grid
    //EFFECTS: Let creatrue no. order_c do specific instruction;
    void run_step(int order_c, int print_flag);
    //REQUIRES: Legal order_c (0-numCreatures-1), leagal address, flag 0 or 1, 1 for v, 0 for concise
    //MODIFIES: world
    //EFFECTS: Let order_c run a step and print
    void print_instruction(int order_inst, enum opcode_t instruction, int address);
    //REQUIRES: Legal order_c (0-numCreatures-1), leagal address
    //EFFECTS: Print no. order_inst instruction of no. oder_c creature
public:
    void print_world();
    //EFFECTS: Print the world
    World(const string& summary,const string& world_file);
    //MODIFIES: world
    //EFFECTS: Constructor
    void run_round(int print_flag);
    //REQUIRES: flag 0 or 1, 1 for v, 0 for concise
    //MODIFIES: world
    //EFFECTS: Run a round
};

void run_simulation(World &wd,int rounds,int print_flag);
//REQUIRES: legal rounds, flag 0 or 1, 1 for v, 0 for concise
//MODIFIES: wd
//EFFECTS: Simulation for n rounds and print simulation results

#endif
