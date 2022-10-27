#pragma once

#include <iostream>
#include <string>

#include "Video.h"

using namespace std;

class Film : public Video {
    private :
        int     nChaps{};
        float* durChaps = nullptr;
    public :
                     Film        (){};
                     Film        (string, string, float, int);
                    ~Film        ();

              int    getNChaps   ()         const;
        const float* getDurChaps ()         const;
              void   setDurChaps (float*, int);
              void   printToFile (ostream&) const override;
              void   run         ()         const override;
};
