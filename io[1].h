#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED
#include "city.h"

enum t_endings{
    ENDING_FAILURE,
    ENDING_AVERAGE,
    ENDING_VICTORY,
    ENDING_CRUELTY,
    ENDING_NONE
};

void greetings();

#ifndef CLASSIC_MODE
#define LENGTH_LINE 512

char** get_line(char* line[512],char* tokens[3]);

void get_grain_amount(int amount,t_city* city);

void get_land_amount(int amount,t_city* city);
#endif // CLASSIC_MODE

void ending_management(t_city city);

#ifndef CLASSIC_MODE
void tokens_management(char* token,t_city* city);
#endif // CLASSIC_MODE

void managing_start_of_turn(t_city* city);

void final_bilan(t_city city);

void steward_quits();

void printing_turn_infos(t_city city);

void announcing_plague();

void not_enough_grain(t_city city);

void not_enough_land(t_city city);

void not_enough_pop(t_city city);

void goodbye_message();

#ifdef CLASSIC_MODE

void classic_turn_management(t_city* city);

void classic_grain_management_feed(t_city* city);

void classic_culture_management(t_city* city);

void classic_land_management_buy(t_city* city);

void classic_land_management_sell(t_city* city);

#endif // CLASSIC_MODE

#endif // INTERFACE_H_INCLUDED