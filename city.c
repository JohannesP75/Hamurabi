#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "city.h"
#include "io.h"

void creating_city(t_city* city){
    int i;

    city->acresLand=STARTING_LAND;
    city->grainStock=STARTING_GRAIN;
    city->immigrants=STARTING_IMMIGRANTS;
    city->population=STARTING_POPULATION+STARTING_IMMIGRANTS;
    city->ending=ENDING_NONE;
    city->year=STARTING_YEAR;
    city->starved=STARTING_STARVED;
    city->totalDeaths=STARTING_TOTAL_DEATH;
    city->price=STARTING_PRICE;
    city->yield=STARTING_YIELD;
    city->harvest=STARTING_HARVEST;
    city->eatenByRats=STARTING_HARVEST-STARTING_GRAIN;

    for(i=0;i<TERM_LENGTH;i++){
        city->percentDead[i]=0;
    }
}

void updating_city(t_city* city){

    // The ladger is updated
    city->harvest=city->yield*city->landSown;
    city->totalDeaths+=city->starved;

    city->yield=calculating_yields(*city);
    city->starved=calculating_starvings(*city);
    city->eatenByRats=calculating_grain_eaten_by_rats(*city);
    city->immigrants=calculating_immigrants(*city);
    city->price=calculating_prices(*city);

    city->percentDead[city->year-STARTING_YEAR]=city->starved/(double)city->population;
    ending_assessment(city);
    city->grainStock+=city->harvest-city->eatenByRats;
    city->population+=city->immigrants-city->starved;
    // Plague

    city->year++;
}

void ending_assessment(t_city* city){
    if(city->year<TERM_LENGTH+STARTING_YEAR){
        if(city->percentDead[city->year-STARTING_YEAR]>MIN_STARVING_INPEACHMENT){
            city->ending=ENDING_FAILURE; // You suck
        }
    }
    else{
        if(calculating_average_starved(*city)>MIN_AVERAGE_STARVING_ENDING_FAILURE
           ||calculating_land_per_citizen(*city)<MAX_AVERAGE_LAND_PER_CITIZEN_FAILURE){
            city->ending=ENDING_FAILURE; // Reconsider your career in politics
        }
        if(calculating_average_starved(*city)>MIN_AVERAGE_STARVING_ENDING_CRUELTY
           ||calculating_land_per_citizen(*city)<MAX_AVERAGE_LAND_PER_CITIZEN_CRUELTY){
            city->ending=ENDING_CRUELTY; // Nero's spiritual son
        }
        if(calculating_average_starved(*city)>MIN_AVERAGE_STARVING_ENDING_AVERAGE
           ||calculating_land_per_citizen(*city)<MAX_AVERAGE_LAND_PER_CITIZEN_AVERAGE){
            city->ending=ENDING_AVERAGE; // You were an average ruler
        }
        else{
            city->ending=ENDING_VICTORY; // Congratulations for your fine management !
        }
    }
}

int calculating_immigrants(t_city city){
    /*
    The original formula was : "533 I=INT(C*(20*A+S)/P/100+1)",
    with "800 C=INT(RND(1)*5)+1", A=city->acresLand, S=city->grainStock
    and P=city->population
    */
    return (roll_dice()*(AMOUNT_FOOD_CITIZEN*city.acresLand+city.grainStock))/(100*city.population)+1;
}

int calculating_prices(t_city city){
    /*
    Original formula:
    "310 C=INT(10*RND(1)): Y=C+17"
    */
    return rand_ab(PRICE_GRAIN_MIN,PRICE_GRAIN_MAX);
}

int calculating_yields(t_city city){
    // The original formula was "C=INT(RND(1)*5)+1" and Y=C, 'Y' standing for "Yield"
    return roll_dice();
}

int calculating_grain_eaten_by_rats(t_city city){
    /*
    The original formula was :
    522 IF INT(C/2)<>C/2 THEN 530
    523 REM *** RATS ARE RUNNING WILD!!
    525 E=INT(S/C)
    */

    return ((roll_dice()%2)?city.grainStock/rand_ab(YIELD_FIELDS_MIN,YIELD_FIELDS_MAX):0);
}

int calculating_starvings(t_city city){
    // Self-evident result
    return ((city.grainFedToSubjects/AMOUNT_FOOD_CITIZEN)<city.population)?city.population-(city.grainFedToSubjects/AMOUNT_FOOD_CITIZEN):0;
}

void calculating_plague(t_city* city){
    if(rand_ab(1,100)<PLAGUE_CHANCE){ // PLAGUE_CHANCE% of chances to have plague
        city->population/=2;
        announcing_plague();
    }
}

double calculating_average_starved(t_city city){
    double S=0;
    int i;

    for(i=0;i<TERM_LENGTH;i++){
        S+=city.percentDead[i];
    }

    return S/TERM_LENGTH;
}

int calculating_land_per_citizen(t_city city){
    return city.acresLand/city.population;
}

int rand_ab(int min,int max){
	srand(time(NULL));
    return rand()%(max+1-min)+min;
}

int roll_dice(){
    return rand_ab(YIELD_FIELDS_MIN,YIELD_FIELDS_MAX);
}
