#pragma once

#include <iostream>
#include <string>
#include <list>
#include <memory>

#include "Multimedia.h"

using namespace std;

class Groupe : public list<shared_ptr<Multimedia>> {
    private :
        string nomGroupe;
    public :
               Groupe        (){};
               Groupe        ( string _nomGroupe )
                : list<shared_ptr<Multimedia>> ()
                , nomGroupe(_nomGroupe)
               {}
              ~Groupe        (){};

        string getNomGroupe  ()              const
        {
            return nomGroupe;
        }

        void   printToFile   ( ostream& os ) const
        {
            os << "Printing groupe    : " << nomGroupe << endl;
            for ( auto i = this->begin(); i != this->end(); i++ ) {
                (*i)->printToFile(os);
            }
            os << endl;
        }

        void   printToStream ( ostream& os ) const
        {
            os << "Printing groupe    : " << nomGroupe << endl;
            for ( auto i = this->begin(); i != this->end(); i++ ) {
                (*i)->printToStream(os);
            }
            os << endl;
        }
};
