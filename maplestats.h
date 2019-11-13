#ifndef MAPLESTATS_H
#define MAPLESTATS_H

#include "globals.h"

#include <QString>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

struct mapleChar{
    int hp;
    int mp;
    int intBase;
    int intGear;
    int lvl;

    int mwLvl;

    //Lvl to stop adding base int.
    int addBaseIntUntilLvl;

    //Level at which we wash base int out.
    int washBaseIntLvl;

    QString mapleClass;

    //Note: Upon hitting lvl 70 / 120 hp is added for job advancement.
    void levelUp();
};


#endif // MAPLESTATS_H
