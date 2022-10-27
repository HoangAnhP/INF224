#pragma once

#include <iostream>
#include <string>

#include "Multimedia.h"

using namespace std;

class Photo : public Multimedia {
    private :
              float  latitude  {};
              float  longitude {};
    public :
               Photo       () {};
               Photo       ( string _nom, string _ndf, float _lat, float _long ) 
                   : Multimedia(_nom, _ndf)
                   , latitude  (_lat)
                   , longitude (_long)
               {}
              ~Photo       ()
               {
                   cout << "Delete photo       : " << nom << endl;
               }

        float  getLat      () const 
        { 
            return latitude; 
        } 
        float  getLong     () const
        {
            return longitude;
        }
        void   setLat      ( float _lat )
        {
            latitude = _lat;
        }
        void   setLong     ( float _long )
        {
            longitude = _long;
        }
        void   printToFile ( ostream& os ) const override
        {
            os << "Nom de l'objet     : " << nom << endl
               << "Path               : " << ndf << endl
               << "latitude           : " << latitude << endl
               << "longitude          : " << longitude << endl;
            os << endl;
        }
        void   printToStream ( ostream& os ) const
        {
            os << "Nom de l'objet     : " << nom << ";"
               << "Path               : " << ndf << ";" 
               << "latitude           : " << latitude << ";"
               << "longitude          : " << longitude;
        }
        void   run         () const override
        {
            cout << "Running photo      : " << getNom() << " from " << getNDF() << endl;
            string commd = "imagej " + getNDF() + " &"; 
            system(commd.data());
        }
        void   writeSerie  ( ostream& os ) const override
        {
            os << "Photo"   << endl
               << nom       << endl
               << ndf       << endl
               << latitude  << endl
               << longitude << endl;
        }
        void   readSerie   ( istream& is ) override
        {
            string str;
            getline(is, str);
            setNom(str);
            getline(is, str);
            setNDF(str);
            getline(is, str);
            setLat(stof(str));
            getline(is, str);
            setLong(stof(str));
        }
};
