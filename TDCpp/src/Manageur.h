#pragma once

#include <iostream>
#include <string>
#include <list>
#include <memory>
#include <map>
#include <sstream>
#include <fstream>

#include "Multimedia.h"
#include "Photo.h"
#include "Video.h"
#include "Film.h"
#include "Groupe.h"
#include "tcpserver.h"

using namespace std;

class Manageur {
    private :
        map<string, shared_ptr<Multimedia>> multimedias;
        map<string, shared_ptr<Groupe>>     groupes;
    public :
                 Manageur       ();
                ~Manageur       ();

        Photo  * creerPhoto     (string, string, float, float);
        Video  * creerVideo     (string, string, float);
        Film   * creerFilm      (string, string, float, int);
        Groupe * creerGroupe    (string);
        
        bool     getMultimedia  (string, ostream&);
        bool     getGroupe      (string, ostream&);
        bool     getMultiToStr  (string, ostream&);
        bool     getGroupToStr  (string, ostream&);

        void     addToGroupe    (string, shared_ptr<Multimedia>);

        bool     runMultimedia  (string);

        void     delMultimedia  (string);
        void     delGroupe      (string);

        void     writeToSerie   (const string& oFile);
        void     readFromSerie  (const string& iFile);
};
