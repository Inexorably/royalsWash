#include "maplestats.h"

void mapleChar::levelUp(){
    lvl++;

    //Add mp from int.  The conversion to int will automatically floor.
    mp += (intBase + intGear)/10;

    if (mapleClass == FIGHTER || mapleClass == SPEARMAN){
        hp += 66;
        mp += 5;
        if (lvl == 70){
            hp += 1025;
            if (mapleClass != FIGHTER){
                mp += 125;
            }
        }
        if (lvl == 120){
            hp += 1825;
            if (mapleClass != FIGHTER){
                mp += 125;
            }
        }
    }

    if (mapleClass == ARCHER || mapleClass == THEIF){
        hp += 22;
        mp += 15;

        if (lvl == 70){
            hp += 625;
            mp += 125;
        }
        if (lvl == 120){
            hp += 925;
            mp += 125;
        }
    }

    if (mapleClass == SAIR){
        hp += 25;
        if (rand() % 1){
            mp += 21;
        }
        else{
            mp += 20;
        }

        if (lvl == 70){
            hp += 625;
            mp += 125;
        }
        if (lvl == 120){
            hp += 925;
            mp += 125;
        }
    }

    if (mapleClass == BUCC){
        hp += 55;
        if (rand() % 1){
            mp += 21;
        }
        else{
            mp += 20;
        }

        if (lvl == 70){
            hp += 625;
            mp += 125;
        }
        if (lvl == 120){
            hp += 925;
            mp += 125;
        }
    }

    if (mapleClass == MAGE){
        hp += 12;
        mp += 43;
        if (lvl == 70 || lvl == 120){
            mp += 475;
        }
    }
}
