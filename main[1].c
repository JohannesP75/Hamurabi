#include <stdio.h>
#include <stdlib.h>
#include "city.h"
#include "io.h"

/*

    C port of the Hamurabi game (1973) by Julien FOMO-POUALEU,
    which began on Saturday, October 25th of the year 2014, at 14:13.

    Original header :

    "HAMURABI"
    "CREATIVE COMPUTING  MORRISTOWN, NEW JERSEY"

    October 31st : the imput-outpit of this game is finished and the mechanisms are nearly finished,
            leaving only the management of the end of the turn and the win conditions -
            the command-line interface will get fixed later
        (Later, this day)
            The build has now be effectued, after some fixing of errors detected by the compiler.
            Some errors will have to be fixed, for exemple the management of cultures seems to be buggy
        (14:08)
            The game seems to be locked in an infinite loop when, during the culture phase, the grain stock is to 0
            and I thus enter 0 as the amount of land to be sown
            Also the five starting immigrants are not counted in the population and the starting number
            of bushels eaten by rats has not been initialized during coding
        (17:39)
            A bug which made, during selling land,
            removing the sold quantity 'multiplied by the price' instead of the quantity alone
            has been fixed
        (18:24)
            The only remaining task is the command line mod;
            I managed to do a 18''30' play without any bug nor glitch
        (20:00)
            The functions classic_culture_management(t_city* city) and creating_city(t_city* city) have been fixed,
            meaning the starting immigrants are now inclued in the total population and that you are now able to saw
            the maximum your pop and grain allows for
            The percentages array have also been fixed, now the percentage of death by hunger is calculated insteas
            to remaining to 0 all the play
            Finally, the final bilan which was in the original is present
    November 1st
        (11:50)
            A bug which made the impeachment for starving more than 45% not happens has been resolved, although
            the final bilan is being printed, which should't happens
    November 2nd
        (14:29)
            I finally implemented a means by which the games pauses shortly before shutting down: the game don't
            quits before you push 'q'

*/

int main(int argc,char* argv[]){
    t_city city;
#ifndef CLASSIC_MODE
    char line[LENGTH_LINE];
    char** input[3];
#endif // CLASSIC_MODE

    greetings();
    creating_city(&city);

    while((city.ending==ENDING_NONE)&&(city.year<TERM_LENGTH)){
        managing_start_of_turn(&city);
#ifndef CLASSIC_MODE
        do{
            strcpy(input,get_line());
            tokens_management(input,&city);
        }while(input[0]!="endturn"&&input[0]!="quit");
#else
        classic_turn_management(&city);
#endif
        updating_city(&city);
        ending_management(city);
    }

    goodbye_message();

    return 0;
}