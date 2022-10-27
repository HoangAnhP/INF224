#pragma once

#include <iostream>
#include <string>

using namespace std;

class Multimedia {
    protected :
        string nom{};
        string ndf{};
    public :
                       Multimedia    ();
                       Multimedia    (string, string);
        virtual       ~Multimedia    ();

        virtual string getNom        () const;    
        virtual string getNDF        () const;
        virtual void   setNom        (string _nom);
        virtual void   setNDF        (string _ndf);
        virtual void   printToFile   (ostream&) const;
        virtual void   printToStream (ostream&) const;
        virtual void   run           () const;
        virtual void   writeSerie    (ostream&) const;
        virtual void   readSerie     (istream&);
};
