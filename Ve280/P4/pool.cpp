#include "pool.h"

using namespace std;

int to_index(Height h, Color c, Shape s, Top t);
//EFFECTS: Return the index of the piece with given attributes

Pool::Pool(){
    for(int ii=0; ii<NP; ii++){
        this->pieces[ii]=Piece(Height(int(ii/8)),Color(int(ii/4)%2),Shape(int(ii/2)%2),Top(ii%2));
        this->pieces[ii].setUsed(false);
    }
}

Piece & Pool:: getUnusedPiece(int index){
    if (this->pieces[index].isUsed()) throw UsedPieceException(this->pieces[index]);
    return this->pieces[index];
}

int to_index(Height h, Color c, Shape s, Top t){
    return 8*h+4*c+2*s+t;
}

Piece & Pool::getUnusedPiece(Height h, Color c, Shape s, Top t){
    return this->getUnusedPiece(to_index(h,c,s,t));
}

Piece & Pool::getUnusedPiece(const std::string &in){
    Height temp_h = Height(in.substr(0,1)=="T");
    Color temp_c = Color(in.substr(1,1)=="E");
    Shape temp_s = Shape(in.substr(2,1)=="Q");
    Top temp_t = Top(in.substr(3,1)=="O");
    return this->getUnusedPiece(to_index(temp_h,temp_c,temp_s,temp_t));
}

string Pool::toString() const{
    int count = 0;
    ostringstream temp1, temp2;
    for(int ii=0; ii<16; ii++){
        if (!this->pieces[ii].isUsed()){
            temp1<<pieces[ii].toString().substr(0,2)<<" ";
            temp2<<pieces[ii].toString().substr(2,2)<<" ";
            count++;
        }
    }
    if (count==0) return "";
    return "Available:\n"+temp1.str()+"\n"+temp2.str()+"\n";
}
