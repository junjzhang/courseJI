#include <iostream>
#include "player.h"
using namespace std;

class HumanP: public Player{
public:
    HumanP(Board* b, Pool* p):Player(b,p){}
    Piece & selectPiece();
    //REQUIRES: There is an unused piece to select
    //EFFECTS: If input piece is valid, then return it, otherwise, print error information.
    Square & selectSquare(const Piece &p);
    //REQUIRES: There is an empty square to place the piece "p"
    //EFFECTS: If input square is valid, return it, otherwise, print error information.
};

class MyopicP: public Player{
public:
    MyopicP(Board* b, Pool* p):Player(b,p){}
    Piece & selectPiece();
    //REQUIRES: There is an unused piece to select
    //EFFECTS: If input piece is valid, then return it, otherwise, print error information.
    Square & selectSquare(const Piece &p);
    //REQUIRES: There is an empty square to place the piece "p"
    //EFFECTS: If input square is valid, return it, otherwise, print error information.
};

Piece& HumanP::selectPiece(){
    string input;
    while(true){
        cout<<"Enter a piece:";
        cin>>input;
        cin.ignore(2048,'\n');
        cin.clear();
        try{
            if(input.length()<4) throw InvalidInputException(input);
        }
        catch(InvalidInputException& error){
            cout<<error.what()<<endl;
            continue;
        }
        try{
            string h,c,s,t;
            h = input.substr(0,1);
            c = input.substr(1,1);
            s = input.substr(2,1);
            t = input.substr(3,1);
            if((h!="S"&&h!="T")||(c!="B"&&c!="E")||(s!="C"&&s!="Q")||(t!="H"&&t!="O")) throw InvalidInputException(input);
        }
        catch(InvalidInputException& error){
            cout<<error.what()<<endl;
            continue;
        }
        try{
            return this->pool->getUnusedPiece(input.substr(0,4));
        }
        catch(UsedPieceException& error){
            cout<<error.what()<<endl;
        }
        input = "";
    }
}

Square & HumanP::selectSquare(const Piece &p){
    string input;
    int v, h;
    while(true){
        cout<<"Enter a position:";
        cin>>input;
        cin.ignore(2048,'\n');
        cin.clear();
        try{
            if(input.length()<2) throw InvalidInputException(input);
        }
        catch(InvalidInputException& error){
            cout<<error.what()<<endl;
            continue;
        }
        v = int(*(input.substr(0,1).c_str())-'A');
        h = int(*(input.substr(1,2).c_str())-'1');
        try{
            if(v>3||v<0||h>3||h<0) throw InvalidInputException(input);
        }
        catch(InvalidInputException& error){
            cout<<error.what()<<endl;
            continue;
        }
        try{
            return this->board->getEmptySquare(input.substr(0,2));
            //this->board->place(p,result);
        }
        catch(SquareException& error){
            cout<<error.what()<<endl;
        }
        input = "";
    }
}

Piece& MyopicP:: selectPiece(){
    bool is_good = true;
    int count=0;
    int count_bad=0;
    int piece_cand[NP];
    int piece_bad[NP];

    for(int m=0; m<NP; m++){
        try{
            this->pool->getUnusedPiece(Height(m/8),Color((m/4)%2),Shape((m/2)%2),Top(m%2));
        }
        catch(UsedPieceException& error){continue;}
        Piece& candinate = this->pool->getUnusedPiece(Height(m/8),Color((m/4)%2),Shape((m/2)%2),Top(m%2));
        //see if it's bad
        is_good = true;
        for(int ii=0; ii<4; ii++){
            for(int jj=0; jj<4; jj++){
                try{
                    this->board->getEmptySquare(Vaxis(ii),Haxis(jj));
                }
                catch(SquareException& error){continue;}
                Square& temp_sqr= this->board->getEmptySquare(Vaxis(ii),Haxis(jj));
                if(this->board->isWinning(candinate,temp_sqr)){
                    is_good = false;
                    break;
                }
            }
            if(!is_good) break;
        }
        if(is_good) piece_cand[count++] = m;
        else piece_bad[count_bad++] = m;
    }
    if(count==0){
        int order = rand()%count_bad;
        int index = piece_bad[order];
        return(this->pool->getUnusedPiece(Height(int(index/8)),Color(int(index/4)%2),Shape(int(index/2)%2),Top(index%2)));
    }
    else{
        int order = rand()%count;
        int index = piece_cand[order];
        return(this->pool->getUnusedPiece(Height(int(index/8)),Color(int(index/4)%2),Shape(int(index/2)%2),Top(index%2)));
    }
}

Square& MyopicP::selectSquare(const Piece& p){
    int count=0;
    int cand_v[NP];
    int cand_h[NP];

    for(int ii=0; ii<4; ii++){
        for(int jj=0; jj<4; jj++){
            try{
                this->board->getEmptySquare(Vaxis(ii),Haxis(jj));
            }
            catch(SquareException& error){continue;}
            Square& temp_sqr = this->board->getEmptySquare(Vaxis(ii),Haxis(jj));
            if (this->board->isWinning(p,temp_sqr)) return temp_sqr;
            else{
                cand_v[count] = ii;
                cand_h[count] = jj;
                count++;
            }
        }
    }
    int index = rand()%count;
    return this->board->getEmptySquare(Vaxis(cand_v[index]),Haxis(cand_h[index]));
}


Player* getHumanPlayer (Board *b, Pool *p){
    static HumanP human(b,p);
    return &human;
}

Player* getMyopicPlayer(Board* b, Pool *p, unsigned int seed){
    static MyopicP myopic(b,p);
    srand(seed);
    return &myopic;
}
