//
// main.cpp
// Created on 21/10/2018
//

#include <iostream>
#include <string>
#include <sstream>
#include "src/Multimedia.h"
#include "src/Photo.h"
#include "src/Video.h"
#include "src/Film.h"
#include "src/Groupe.h"
#include "src/Manageur.h"
#include "src/tcpserver.h"

//#define  VERSION_1

using namespace std;

int main(int argc, const char* argv[])
{

#ifdef VERSION_1
    // Test pour Photos, séparément
    std::cout << "Hello brave new world" << std::endl;

    string f1 = "~/PHAM/INF224/TD1/Images/mt1.jpeg";
    Multimedia* m1 = new Multimedia("m1", f1);
    cout << "Nom de l'objet     : " << m1->getNom() << endl
         << "Path               : " << m1->getNDF() << endl;
    cout << endl;
    
    string f2 = "~PHAM/INF224/TD1/Images/mt2.jpeg";
    Multimedia* m2 = new Multimedia();
    m2->setNom("m2");
    m2->setNDF(f2);
    cout << "Nom de l'objet     : " << m2->getNom() << endl
         << "Path               : " << m2->getNDF() << endl;
    cout << endl;

    string f3 = "~/PHAM/INF224/TD1/Images/mt3.jpeg";
    Multimedia* m3 = new Multimedia("m3", f3);
    m3->printToFile(cout);

    // Test pour Photo et Video en utilisant array
    Multimedia* tableau[2];
    tableau[0] = new Photo("Photo1", f1, 10, 10);

    string fv = "~/PHAM/INF224/TD1/Vids/vid1.mp4";
    tableau[1] = new Video("Video1", fv, 0);
    
    for ( int k = 0; k < 2; k++ ) {
        tableau[k]->printToFile(cout);
//        tableau[k]->run();
    }

    // Test pour Film
    float chaps[4] = {3, 5, 4, 2};
    Film* film = new Film("Film1", fv, 14, 4);
    film->setDurChaps(chaps, 4);
    film->printToFile(cout);

    // Test pour Groupe
    Groupe* gr = new Groupe("Groupe1");
    shared_ptr<Multimedia> photo1 ( new Photo("photo1", f1, 10, 10) );
    shared_ptr<Multimedia> video1 ( new Video("video1", fv, 0) );
    gr->push_back(photo1);
    gr->push_back(video1);
    gr->printToFile(cout);
    gr->pop_back();
    gr->pop_back();

    // Test Manageur
    Manageur * mng = new Manageur();
    mng->creerPhoto("photo2", f2, 10, 10);
//    shared_ptr<Photo> p(mng->creerPhoto("photo1", f1, 10, 10));
    mng->creerVideo("video2", fv, 0);
    mng->creerGroupe("groupe2");
    mng->getMultimedia("photo2", cout);
    mng->getMultimedia("video2", cout);

//    mng->addToGroupe("groupe2", p);
    mng->addToGroupe("groupe2", video1);
    mng->getGroupe("groupe2", cout);

    mng->delMultimedia("photo1");

    mng->getGroupe("groupe2", cout);
 
    delete m1;
    delete m2;
    delete m3;
    for ( int i = 0; i < 2; i++ ) {
        delete tableau[i];
    }
    delete film;
    delete gr;
    delete mng;
#endif
    Manageur* mngS = new Manageur();

//    string f1S = "~/PHAM/INF224/TD1/Images/mt1.jpeg";
//    string fvS = "~/PHAM/INF224/TD1/Vids/vid1.mp4";
//    mngS->creerPhoto("photo", f1S, 20, 20);
//    mngS->creerVideo("video", fvS, 10);

    // Serialisation
    mngS->readFromSerie("Serialisation.txt");
    mngS->writeToSerie("ResultSerie.txt");


    const int PORT = 3331;
    auto* server = new TCPServer( [&](string const& request, string& response) {
        cout << "request : " << request << endl;

        // Découper la requête
        stringstream strm;
        strm << request;
        string todo;
        string typeTodo;
        string objTodo;
        strm >> todo;
        strm >> typeTodo;
        strm >> objTodo;

        stringstream res;

        // Traiter la requête
        if ( todo == "find" ) {
            if ( typeTodo == "photo" || typeTodo == "video" || typeTodo == "multimedia" ) {
                if ( mngS->getMultiToStr(objTodo, res) )
                    cout << "Found " << typeTodo << " " << objTodo << ", sending to clien" << endl;
                else
                    cout << typeTodo << " " << objTodo << " not found" << endl;
            }
            else if ( typeTodo == "groupe" ) {
                if ( mngS->getGroupToStr(objTodo, res) )
                    cout << "Found " << typeTodo << " " << objTodo << ", sending to clien" << endl;
                else
                    cout << typeTodo << " " << objTodo << " not found" << endl;
            }
            else
                res << "No object of type " << typeTodo << " exists";
        }
        else if ( todo == "play" ) {
            if ( typeTodo == "photo" || typeTodo == "video" || typeTodo == "multimedia" ) {
                if ( mngS->runMultimedia(objTodo) )
                    res << "Playing " << typeTodo << " " << objTodo;
            }
            else
                res << "Can't play object of type " << typeTodo;
        }
        else if ( todo == "quit" ) {
            return false;
        }

        if ( res.str().empty() )
            response = "No response for this request;";
        else
            response = res.str() + ";";

          return true;
    });

    cout << "Starting Server on port " << PORT << endl;
    int status = server->run(PORT);

    if ( status < 0 ) {
        cerr << "Cout not start Server on port " << PORT << endl;
        return 1;
    }

    delete mngS;
    delete server;

    return 0;
}
