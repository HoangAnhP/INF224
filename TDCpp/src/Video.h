#pragma once

#include <iostream>
#include <string>

#include "Multimedia.h"

using namespace std;

class Video : public Multimedia {
    protected :
        float duree{};
    public :
                       Video         (){};
                       Video         ( string _nom, string _ndf, int _duree )
                           :Multimedia(_nom, _ndf)
                           ,duree(_duree)
                       {}
                      ~Video         ()
                       {
                           cout << "Delete video       : " << nom << endl;
                       }

        virtual float  getDur        () const
                       {
                           return duree;
                       }
                void   setDur        ( float _dur )
                       {
                           duree = _dur;
                       }
                void   printToFile   ( ostream& os ) const override
                       {
                           os << "Nom de l'objet     : " << nom << endl
                           << "Path               : " << ndf << endl
                           << "durée              : " << duree << endl;
                           os << endl;
                       }
                void   printToStream ( ostream& os ) const override
                       {
                           os << "Nom de l'objet     : " << nom << ";"
                           << "Path               : " << ndf << ";"
                           << "durée              : " << duree;
                       }
 
                void   run           () const override
                       {
                           cout << "Running video      : " << getNom() << endl;
                           string commd = "mpv " + getNDF() + " &"; 
                           system(commd.data());
                       }
                void   writeSerie  ( ostream& os ) const override
                       {
                           os << "Video" << endl
                              << nom     << endl
                              << ndf     << endl
                              << duree   << endl;
                       }
                void   readSerie   ( istream& is ) override
                       {
                           string str;
                           getline(is, str);
                           setNom(str);
                           getline(is, str);
                           setNDF(str);
                           getline(is, str);
                           setDur(stof(str));
                       }
               
};
