#include "board.h"

using namespace std;

Board::Board(){
    for(int ii=0; ii<4; ii++){
        for(int jj=0; jj<4; jj++){
            this->grid[ii][jj] = (Square(Vaxis(ii),Haxis(jj))); 
        }
    }
}

Square& Board::getSquare(Vaxis v, Haxis h){
    return this->grid[v][h];
}

Square& Board::getEmptySquare(Vaxis v, Haxis h){
    if(!grid[v][h].isEmpty()) throw SquareException(grid[v][h],"not empty");
    return grid[v][h];
}

Square& Board::getEmptySquare(const std::string &s){
    Vaxis temp_v = Vaxis(int(*(s.substr(0,1).c_str())-'A'));
    Haxis temp_h = Haxis(stoi(s.substr(1,1))-1);
    return this->getEmptySquare(temp_v,temp_h);
}

void Board::place(Piece &p, Square &sq){
    sq.setPiece(&p);
    p.setUsed(true);
    return;
}

bool Board::isWinning(const Piece &p, const Square &sq){
    Vaxis v = sq.getV();
    Haxis h = sq.getH();
    bool flag_h = true, flag_c = true, flag_s = true, flag_t = true;

    //check vertical line
    for(int ii=0; ii<4; ii++){
        if (ii!=v){
            try{
                this->grid[ii][h].getPiece();
            }
            catch(SquareException& error){
                flag_h = flag_c = flag_s = flag_t = false;
                break;
            }
            const Piece & temp_p = this->grid[ii][h].getPiece();
            flag_h = flag_h&&p.compareHeight(temp_p);
            flag_c = flag_c&&p.compareColor(temp_p);
            flag_s = flag_s&&p.compareShape(temp_p);
            flag_t = flag_t&&p.compareTop(temp_p);
        }
    }
    if(flag_h||flag_c||flag_s||flag_t) return true;

    //check horizental line
    flag_h = flag_c = flag_s = flag_t = true;
    for(int ii=0; ii<4; ii++){
        if (ii!=h){
            try{
                this->grid[v][ii].getPiece();
            }
            catch(SquareException& error){
                flag_h = flag_c = flag_s = flag_t = false;
                break;
            }
            const Piece & temp_p = this->grid[v][ii].getPiece();
            flag_h = flag_h&&p.compareHeight(temp_p);
            flag_c = flag_c&&p.compareColor(temp_p);
            flag_s = flag_s&&p.compareShape(temp_p);
            flag_t = flag_t&&p.compareTop(temp_p);
        }
    }
    if(flag_h||flag_c||flag_s||flag_t) return true;

    //check first diagnol
    if(sq.isOnFirstDiagonal()){
        flag_h = flag_c = flag_s = flag_t = true;
        for(int ii=0; ii<4; ii++){
            if (ii!=v){
                try{
                    this->grid[ii][ii].getPiece();
                }
                catch(SquareException& error){
                    flag_h = flag_c = flag_s = flag_t = false;
                    break;
                }
                const Piece & temp_p = this->grid[ii][ii].getPiece();
                flag_h = flag_h&&p.compareHeight(temp_p);
                flag_c = flag_c&&p.compareColor(temp_p);
                flag_s = flag_s&&p.compareShape(temp_p);
                flag_t = flag_t&&p.compareTop(temp_p);
            }
        }
        if(flag_h||flag_c||flag_s||flag_t) return true;
    }

    //check second diagnol
    if(sq.isOnSecondDiagonal()){
        flag_h = flag_c = flag_s = flag_t = true;
        for(int ii=0; ii<4; ii++){
            if (ii!=v){
                try{
                    this->grid[ii][3-ii].getPiece();
                }
                catch(SquareException& error){
                    flag_h = flag_c = flag_s = flag_t = false;
                    break;
                }
                const Piece & temp_p = this->grid[ii][3-ii].getPiece();
                flag_h = flag_h&&p.compareHeight(temp_p);
                flag_c = flag_c&&p.compareColor(temp_p);
                flag_s = flag_s&&p.compareShape(temp_p);
                flag_t = flag_t&&p.compareTop(temp_p);
            }
        }
        if(flag_h||flag_c||flag_s||flag_t) return true;
    }
    return false;
        
}

string Board::toString() const{
    string result = "    1    2    3    4    \n";
    ostringstream temp1,temp2;
    string line="  +----+----+----+----+\n";
    result += line;
    for(int ii=0; ii<4; ii++){
        temp1<<char(ii+'a')<<" ";
        temp2<<"  ";
        for (int jj=0; jj<4; jj++){
            if(this->grid[ii][jj].isEmpty()){
                temp1<<"|    ";
                temp2<<"|    ";
            }        
            else{
                string attribute = this->grid[ii][jj].getPiece().toString();
                temp1<<"| "<<attribute.substr(0,2)<<" ";
                temp2<<"| "<<attribute.substr(2,2)<<" ";
            }
        }
        temp1<<"|\n";
        temp2<<"|\n";
        result += temp1.str()+temp2.str()+line;
        temp1.str("");
        temp2.str("");
        temp1.clear();
        temp2.clear();
    }
    return result;
}
