#include <iostream>
#include <string>

#include "src/Multimedia.h"

using namespace std;

Multimedia::Multimedia ()
{}

Multimedia::Multimedia ( string _nom, string _ndf )
    : nom(_nom),
      ndf(_ndf)
{}

Multimedia::~Multimedia () 
{}

string Multimedia::getNom () const {
    return nom;
}

string Multimedia::getNDF () const {
    return ndf;
}

void Multimedia::setNom ( string _nom ) {
    nom = _nom;
}

void Multimedia::setNDF ( string _ndf ) {
    ndf = _ndf;
}

void Multimedia::printToFile ( ostream& os ) const {
    os << "Nom de l'objet     : " << nom << endl
       << "Path               : " << ndf << endl;
    os << endl;
}

void Multimedia::printToStream ( ostream& os ) const {
    os << "Nom de l'objet     : " << nom << ";"
       << "Path               : " << ndf;
}

void Multimedia::run () const
{}

void Multimedia::writeSerie ( ostream& os ) const {
    os << "Multimedia" << endl
       << nom          << endl
       << ndf          << endl;
}

void Multimedia::readSerie ( istream& is ) {
    string str;
    getline(is, str);
    setNom(str);
    getline(is, str);
    setNDF(str);
}
