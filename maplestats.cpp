#include "maplestats.h"

void mapleChar::levelUp(){
    lvl++;

    //Add mp from int.  The conversion to int will automatically floor.
    int gearCoef = 0;
    if (lvl >= intGearStartLvl){
        gearCoef = 1;
    }
    mp += static_cast<int>((static_cast<double>(intBase) + static_cast<double>(intGear*gearCoef) + static_cast<double>(intBase)*static_cast<double>(mwLvl)/10*0.05)/10.0);

    //Mp wash 5 sp.
    if (mpWashing && lvl >= mpWashStartLvl && lvl <= mpWashStopLvl && intBase > 400){
        //If mage assume max improved mp, 10 per ap * 5.
        if (mapleClass == MAGE){
            mp += 50;
        }
        //Mp from washing.  Formula: https://mapleroyals.com/forum/threads/question-about-mp-washing.117452/
        mp += 5*(intBase/10 - 30);


        //Used aprs.
        aprUsed += 5;
    }

    //Add sp to int.
    if (lvl < addBaseIntUntilLvl){
        intBase += 5;
    }

    if (mapleClass == FIGHTER || mapleClass == SPEARMAN){
        hp += 66;
        mp += 5;
        if (lvl == 70){
            hp += 1025;
            intBase += 3;
            if (mapleClass != FIGHTER){
                mp += 125;
            }
        }
        if (lvl == 120){
            hp += 1825;
            intBase += 3;
            if (mapleClass != FIGHTER){
                mp += 125;
            }
        }
    }

    if (mapleClass == ARCHER || mapleClass == THEIF){
        hp += 22;
        mp += 15;

        if (lvl == 70){
            intBase += 3;
            hp += 625;
            mp += 125;
        }
        if (lvl == 120){
            intBase += 3;
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
            intBase += 3;
            hp += 625;
            mp += 125;
        }
        if (lvl == 120){
            intBase += 3;
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
            intBase += 3;
            hp += 625;
            mp += 125;
        }
        if (lvl == 120){
            intBase += 3;
            hp += 925;
            mp += 125;
        }
    }

    if (mapleClass == MAGE){
        hp += 12;
        mp += 43;
        if (lvl == 70 || lvl == 120){
            intBase += 3;
            mp += 475;
        }
    }

    //Wash base int out for non mage classes.
    if (mapleClass != MAGE && lvl >= washBaseIntLvl){
        aprUsed = intBase - 4;
        intBase = 4;
    }
}
