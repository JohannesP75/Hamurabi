#ifndef CITY_H_INCLUDED
#define CITY_H_INCLUDED
// Game mode
#define CLASSIC_MODE
// Constants
#define AMOUNT_LAND_CITIZEN 10 /* How much land can be tilled by one citizen */
#define AMOUNT_FOOD_CITIZEN 20 /* How much food your citizens must eat */
#define YIELD_FIELDS_MIN 1
#define YIELD_FIELDS_MAX 6
#define STARTING_POPULATION 95
#define STARTING_IMMIGRANTS 5
#define STARTING_GRAIN 2800
#define TERM_LENGTH 10
#define STARTING_YEAR 0
#define STARTING_PRICE 3
#define STARTING_HARVEST 3000
#define STARTING_STARVED 0
#define STARTING_TOTAL_DEATH 0
#define STARTING_YIELD 3
#define PLAGUE_CHANCE 15 /* Defined on 100 */
#define STARTING_LAND STARTING_HARVEST/STARTING_PRICE
#define GRAIN_BUSHELS_BY_ACRES 2 /* Amount of bushels needed to sow an acre of land */
#define PRICE_GRAIN_MIN 17
#define PRICE_GRAIN_MAX 27
// Ceilings for getting endings
#define MIN_STARVING_INPEACHMENT 0.45
#define MIN_AVERAGE_STARVING_ENDING_FAILURE 0.33
#define MAX_AVERAGE_LAND_PER_CITIZEN_FAILURE 7
#define MIN_AVERAGE_STARVING_ENDING_CRUELTY 0.10
#define MAX_AVERAGE_LAND_PER_CITIZEN_CRUELTY 9
#define MIN_AVERAGE_STARVING_ENDING_AVERAGE 0.03
#define MAX_AVERAGE_LAND_PER_CITIZEN_AVERAGE 10

typedef struct t_city{
    int population; /* How many citizens inhabit the city */
    unsigned int acresLand; /* How much land does your city possess */
    int grainStock; /* How much bushels of grain does your city possess */
    int immigrants; /* How many immigrants come to the city this year */
    int ending; // Which ending you got; by default, ENDING_NONE
    int starved; // Dead from hunger during the year
    int totalDeaths; // Total deaths from hunger
    int year; // Self-evident
    int price; /* Price of an acre of land, expressed in buchels of grain */
    unsigned int yield; // Yield of the fields
    unsigned int landSown; // Land sown
    int eatenByRats;
    int harvest;
    int grainFedToSubjects;
    double percentDead[TERM_LENGTH]; // Where the percentage of dead per year is stocked
} t_city;

void creating_city(t_city* city);

void updating_city(t_city* city);

void ending_assessment(t_city* city);

int calculating_immigrants(t_city city);

int calculating_prices(t_city city);

int calculating_yields(t_city city);

int calculating_grain_eaten_by_rats(t_city city);

int calculating_starvings(t_city city);

void calculating_plague(t_city* city);

double calculating_average_starved(t_city city);

int calculating_land_per_citizen(t_city city);

int rand_ab(int a,int b);

int roll_dice();

#endif // CITY_H_INCLUDED
