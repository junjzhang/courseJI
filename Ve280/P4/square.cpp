#include "square.h"

using namespace std;

Square::Square(Vaxis v_a, Haxis h_a): v(v_a),h(h_a),p(NULL){
} 

Vaxis Square::getV() const{
    return this->v;
}

Haxis Square::getH() const{
    return this->h;
}

void Square::setV(Vaxis v){
    this->v = v;
    return;
}

void Square::setH(Haxis h){
    this->h = h;
    return;
}

const Piece& Square::getPiece() const{
    if (this->p==NULL) throw SquareException(*this,"empty");
    return *this->p;
}

void Square::setPiece(const Piece *p){
    this->p = p;
    return;
}

bool Square::isEmpty() const{
    return (this->p==NULL);
}

bool Square::isOnFirstDiagonal() const{
    return (int(this->v)==int(this->h));
}

bool Square::isOnSecondDiagonal() const{
    return (3-int(this->v)==int(this->h));
}

string Square::toString() const{
    string result;
    switch (this->v){
    case 0:
        result = "A";
        break;
    case 1:
        result = "B";
        break;
    case 2:
        result = "C";
        break;
    case 3:
        result = "D";
        break;
    }
    return result+to_string(this->h+1);
}
