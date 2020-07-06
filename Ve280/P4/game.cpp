#include "player.h"
#include <iostream>

using namespace std;

static Board board;
static Pool pool;
 
static int check_status(Piece& ps, Square& sqr);
//EFFECTS: Check if there's a tie or winner


int main(int argc, char* argv[]){
    string first_player,second_player;
    int seed = 0;
    stringstream temp;
    temp.clear();
    Player* first;
    Player* second;
    int game_flag = 1;//1 for continue, 2 for win, 3 for tie


    for(int ii=1 ;ii<argc ;ii++){
        temp<<argv[ii]<<" ";
    }
    temp>>first_player>>second_player;
    if (argc == 4) temp>>seed;
    temp.str("");
    temp.clear();

    if(first_player=="h"){
        first = getHumanPlayer(&board,&pool);
    }
    if(second_player=="h"){
        second = getHumanPlayer(&board,&pool);
    }
    if(first_player=="m"){
        first = getMyopicPlayer(&board,&pool,seed);
    }
    if(second_player=="m"){
        second = getMyopicPlayer(&board,&pool,seed);
    }
    cout<< board.toString();
    cout<<""<<endl;
    cout<<pool.toString()<<endl;
    
    while(game_flag==1){
        cout<<"Player 1's turn to select a piece:"<<endl;
        Piece& temp_ps_1 = first->selectPiece();
        cout<<temp_ps_1.toString()<<" selected."<<endl;
        cout<<" "<<endl;
        cout<<"Player 2's turn to select a square:"<<endl;
        Square& temp_sqr_2 = second->selectSquare(temp_ps_1);
        cout<<temp_sqr_2.toString()<<" selected."<<endl;
        board.place(temp_ps_1,temp_sqr_2);
        cout<<" "<<endl;
        cout<< board.toString();
        cout<<""<<endl;
        cout<<pool.toString()<<endl;
        game_flag = check_status(temp_ps_1,temp_sqr_2);
        if (game_flag == 2) cout<<"Player 2 has won!"<<endl;
        if (game_flag == 3) cout<<"It is a draw."<<endl;
        if (game_flag != 1) break;
        cout<<"Player 2's turn to select a piece:"<<endl;
        Piece& temp_ps_2 = second->selectPiece();
        cout<<temp_ps_2.toString()<<" selected."<<endl;
        cout<<" "<<endl;
        cout<<"Player 1's turn to select a square:"<<endl;
        Square& temp_sqr_1 = first->selectSquare(temp_ps_2);
        cout<<temp_sqr_1.toString()<<" selected."<<endl;
        board.place(temp_ps_2,temp_sqr_1);
        cout<<" "<<endl;
        cout<< board.toString();
        cout<<""<<endl;
        cout<<pool.toString()<<endl;
        game_flag = check_status(temp_ps_2,temp_sqr_1);
        if (game_flag == 2) cout<<"Player 1 has won!"<<endl;
        if (game_flag == 3) cout<<"It is a draw."<<endl;
        if (game_flag != 1) break;
    }
    return 0;
}

static int check_status(Piece& ps, Square& sqr){
    if(board.isWinning(ps,sqr)) return 2;
    int count = 0;
    for(int ii=0; ii<4; ii++){
        for(int jj=0; jj<4; jj++){
            try{
                board.getEmptySquare(Vaxis(ii),Haxis(jj));
            }
            catch(SquareException error){continue;}
            count ++;
            if (count!=0) break;
        }
        if (count!=0) break;
    }
    if(count == 0) return 3;
    return 1;
}
