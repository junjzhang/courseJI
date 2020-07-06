#include "piece.h"

using namespace std;

Piece::Piece(Height h, Color c, Shape s, Top t): h(h), c(c), s(s), t(t), used(false){}

bool Piece::compareHeight(const Piece &p) const{
    return (this->h==p.h);
}

bool Piece::compareColor(const Piece &p) const{
    return (this->c==p.c);
}

bool Piece::compareShape(const Piece &p) const{
    return (this->s==p.s);
}

bool Piece::compareTop(const Piece &p) const{
    return (this->t==p.t);
}

bool Piece::isUsed() const{
    return this->used;
}

void Piece::setUsed(bool u){
   this->used = u;
   return;
}

string Piece::toString() const{
   ostringstream temp;
   temp<<HCODE[this->h];
   temp<<CCODE[this->c];
   temp<<SCODE[this->s];
   temp<<TCODE[this->t];
   return temp.str();
}
