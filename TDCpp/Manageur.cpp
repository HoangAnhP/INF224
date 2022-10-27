#include "src/Manageur.h"

using namespace std;

Manageur::Manageur ()
         : multimedias()
         , groupes()
{}

Manageur::~Manageur () {
    multimedias.clear();
    for ( auto gr : groupes ) {
        ((gr.second).get())->clear();
    }
    groupes.clear();
}

Photo * Manageur::creerPhoto ( string _nom, string _ndf, float _lat, float _long ) {
    shared_ptr<Photo> p(new Photo(_nom, _ndf, _lat, _long));
    (multimedias[_nom]) = p;
    return p.get();
}

Video * Manageur::creerVideo ( string _nom, string _ndf, float _dur ) {
    shared_ptr<Video> v(new Video(_nom, _ndf, _dur));
    multimedias[_nom] = v;
    return v.get();
}

Film * Manageur::creerFilm ( string _nom, string _ndf, float _dur, int _n ) {
    shared_ptr<Film> f(new Film(_nom, _ndf, _dur, _n));
    multimedias[_nom] = f;
    return f.get();
}

Groupe * Manageur::creerGroupe ( string _nomG ) {
    shared_ptr<Groupe> gr(new Groupe(_nomG));
    groupes[_nomG] = gr;
    return gr.get();
}

bool Manageur::getMultimedia ( string _nomM, ostream& os ) {
    if ( multimedias.find(_nomM) != multimedias.end() ) {
        (multimedias[_nomM])->printToFile(os);
        return true;
    }
    else {
        os << "Multimedia : " << _nomM << " not found" << endl;
        return false;
    }
}

bool Manageur::getGroupe ( string _nomG, ostream& os ) {
    if ( groupes.find(_nomG) != groupes.end() ) {
        (groupes[_nomG])->printToFile(os);
        return true;
    }
    else {
        os << "Groupe : " << _nomG << " not found" << endl;
        return false;
    }
}

bool Manageur::getMultiToStr ( string _nomM, ostream& os ) {
    if ( multimedias.find(_nomM) != multimedias.end() ) {
        (multimedias[_nomM])->printToStream(os);
        return true;
    }
    else {
        os << "Multimedia : " << _nomM << " not found";
        return false;
    }
}

bool Manageur::getGroupToStr ( string _nomG, ostream& os ) {
    if ( groupes.find(_nomG) != groupes.end() ) {
        (groupes[_nomG])->printToStream(os);
        return true;
    }
    else {
        os << "Groupe : " << _nomG << " not found" << endl;
        return false;
    }
}

void Manageur::addToGroupe ( string _nomG, shared_ptr<Multimedia> _multi ) {
    if ( groupes.find(_nomG) != groupes.end())
        (groupes[_nomG])->push_back(_multi);
    else
        cout << "Groupe : " << _nomG << " not found" << endl;  
}

bool Manageur::runMultimedia ( string _nomM ) {
    if ( multimedias.find(_nomM) != multimedias.end()) {
        (multimedias[_nomM])->run();
        return true;
    }
    else {
        cout << "Multimedia : " << _nomM << " not found" << endl;
        return false;
    }
}

void Manageur::delMultimedia ( string _nomM ) {
    if ( multimedias.find(_nomM) != multimedias.end()){
        for ( auto gr : groupes ) { 
            gr.second->remove(multimedias[_nomM]);
        }

        multimedias.erase(_nomM);
    }
    else
        cout << "Multimedia : " << _nomM << " not found" << endl;   
}

void Manageur::delGroupe ( string _nomG ) {
    if ( groupes.find(_nomG) != groupes.end()) {
        (groupes[_nomG])->clear();
        groupes.erase(_nomG);
    }
    else
        cout << "Groupe : " << _nomG << " not found" << endl;
}

void Manageur::writeToSerie ( const string& oFile ) {
    ofstream os(oFile);
    if ( os ) {
        for ( auto m : multimedias ) {
            m.second->writeSerie(os);
        }
        os.close();
    }
    else
        cout << "Can't open file " << oFile << endl;
}

void Manageur::readFromSerie ( const string& iFile ) {
    ifstream is(iFile);
    if ( is ) {
        while ( is ) {
            string str;
            getline(is, str);
            if ( str == "Photo" ) {
                getline(is, str);
                string _nom = str;
                getline(is, str);
                string _ndf = str;
                getline(is, str);
                float _lat = stof(str);
                getline(is, str);
                float _long = stof(str);
                creerPhoto(_nom, _ndf, _lat, _long);
            }
            else if ( str == "Video" ) {
                getline(is, str);
                string _nom = str;
                getline(is, str);
                string _ndf = str;
                getline(is, str);
                float _dur = stof(str);
                creerVideo(_nom, _ndf, _dur);
            }
/*            if ( str == "Film" ) {
                getline(is, str);
                string _nom = str;
                getline(is, str);
                string _ndf = str;
                getline(is, str);
                float _dur = stof(str);
                getline(is, str);
                int _nC = stoi(str);
                creerFilm(_nom, _ndf, _dur, _nC);
            }*/
        }
    }
    else
        cout << "Can't open file " << iFile << endl;
}
