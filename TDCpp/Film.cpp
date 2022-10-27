#include <iostream>
#include <string>

#include "src/Film.h"

using namespace std;

Film::Film ( string _nom, string _ndf, float _duree, int _nChaps ) 
            : Video(_nom, _ndf, _duree)
            , nChaps(_nChaps)
{
    if ( nChaps != 0 )
        durChaps = new float[nChaps];
}

Film::~Film() {
    delete[] durChaps;
}

int Film::getNChaps () const {
    return nChaps;
}

const float* Film::getDurChaps () const {
    return durChaps;
}

void Film::setDurChaps ( float* _durChaps, int _n ) {
    if ( nChaps != _n ) {
        nChaps = _n;
        delete durChaps;
    }
    copy(_durChaps, _durChaps+nChaps, durChaps);
}

void Film::printToFile ( ostream& os ) const {
    os << "Nom de l'objet     : " << nom << endl
       << "Path               : " << ndf << endl
       << "durée              : " << duree << endl
       << "nombre de chapitre : " << nChaps << endl
       << "dur de chaque chap : ";
    for (int i = 0; i < nChaps; i++) {
        os << "-> " << durChaps[i];
    }
    os << endl << endl;
}

void Film::run () const {
    cout << "Running film : " << nom << endl
         << "Duree total  : " << duree << endl
         << "With         : " << nChaps << endl;
    for (int i = 0; i < nChaps; i++) {
         cout << "Chap" << i+1 << "       : " << durChaps[i] << endl;
    }
    string commd = "mpv " + getNDF() + " &";
    system(commd.data());
}
