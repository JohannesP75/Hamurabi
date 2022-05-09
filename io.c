#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "io.h"
#include "city.h"

void greetings(){
    printf("Try your hand at governing Ancient Sumeria\n");
    printf("for a ten-year term of office\n");
    printf("\n");
}

#ifndef CLASSIC_MODE
char** get_line(char* line[512],char* tokens[3]){


    tokens=strtok(line," ");

}


void get_grain_amount_to_sell(int amount,t_city* city){
    if(amount>t_city->grainStock){
        printf("")
    }else{}
}
#endif // CLASSIC_MODE

void ending_management(t_city city){

    if(/*city.ending!=ENDING_NONE&&*/city.year>=TERM_LENGTH+STARTING_YEAR){
            final_bilan(city);
    }

    switch(city.ending){
        case ENDING_VICTORY:
            printf("A fantastic performance!!!  Charlemagne, Disraeli, and\n");
            printf("Jefferson combined could not have done better!\n");
            break;
        case ENDING_CRUELTY:
            printf("Your heavy-handed performance smacks of nero and Ivan IV.\n");
            printf("The people (remaining) find you an unpleasant ruler, and,\n");
            printf("frankly, hate your guts!!\n");
            break;
        case ENDING_AVERAGE:
            printf("Your performance could have been somewhat better, but\n");
            printf("really wasn't to bad at all. %d people\n",rand_ab(0,(4*city.population)/5)); // Original : "INT(P*.8*RND(1))"
            printf("would dearly like to see you assassinated but we all have our\n");
            printf("trivial problems.\n");
            break;
        case ENDING_FAILURE:
            if(city.year<=TERM_LENGTH+STARTING_YEAR){printf("You starved %d prople in one year!!!\n",city.starved);}
            printf("Due to this extreme mismanagement you have not only\n");
            printf("been impeached and thrown out of office but you have\n");
            printf("also been declared national fink!!!!\n");
            break;
        case ENDING_NONE:
        default:
            break;
    }
}

#ifndef CLASSIC_MODE
void tokens_management(char* token[3],t_city* city){
    int numToken;
    int amount;

    if(token[0]=="help"||token[0]=="?"){ /* The player want help on the game */
        if(token[1]=="grain"){
            printf("Grain is produced in fields by your citizens.\n");
            printf("They have to eat %d bushels of grain to live.\n",AMOUNT_FOOD_CITIZEN);
            printf("You can also buy land with it.\n");
        }
        if(token[1]=="land"||token[1]=="acres"){
            printf("Land is worked by your citizens.\n")
            printf("It produces bushels of grain at a variable yield.\n")
            printf("You can buy and sold land.\n");
        }
        if(token[1]=="citizens"||token[1]=="citizen"){
            printf("Your citizens work for you in the city fields.\n")
            printf("They have to eat %d bushels of grain to live.\n",AMOUNT_FOOD_CITIZEN);
            printf("They can work until %d acres.\n",AMOUNT_LAND_CITIZEN);
        }
    printf("END\n")
    }
    if(token[0]=="quit"){ /* You quit the game */
        goodbye_message();
    }
    if(token[0]=="endturn"){ /* You end the turn */

    }
    if(token[0]=="info"){ /* You ask information on your play */
        if(token[1]=="grain"){
            printf("You have %d bushels of grain.\n",city->grainStock);
        }
        if(token[1]=="land"||token[1]=="acres"){
            printf("You have %d acres of land.\n",city->acresLand);
            printf("Land sell and is brought for %d bushels of grain.\n",);
        }
        if(token[1]=="citizens"||token[1]=="citizen"){
            printf("There is %d inhabitants in your city\n",city->population);
        }
        if(token[1]=="city"){
            printf("You have %d bushels of grain.\n",city->grainStock);
            printf("You have %d acres of land.\n",city->acresLand);
            printf("There is %d inhabitants in your city\n",city->population);
        }
        printf("END\n");
    }

    if(token[0]=="sell"){
        amount=atoi(token[1]);
        if(amount<0){
            steward_quits();
        }else{
            city->acresLand-=amount;
            city->grainStock+=amount*(city->price);
        }
    }

    if(token[0]=="buy"){
        amount=atoi(token[1])
        if(amount<0){
                steward_quits();
        }else{
            city->acresLand+=amount;
            city->grainStock-=amount*(city->price);
        }
    }

    if(token[0]=="feed"){
        amount=atoi(token[1])
        if(amount<0){
                steward_quits();
        }else{
        }
    }
}
#endif // CLASSIC_MODE

void managing_start_of_turn(t_city* city){
    printf("Hamurabi:  I beg to report to you,\n");
    printf("in year %d, %d people starved, %d came to the city,\n",city->year,city->starved,city->immigrants);

    calculating_plague(city);

    printf("Population is now %d\n",city->population);
    printf("The city now owns %d acres.\n",city->acresLand);
    printf("You harvested %d bushels per acre.\n",city->yield);
    printf("The rats ate %d bushels.\n",city->eatenByRats);
    printf("You now have %d bushels in store.\n",city->grainStock);
    printf("\n");
}

void final_bilan(t_city city){
    printf("In your %d-year term of office, %lf percent of the\n",TERM_LENGTH,calculating_average_starved(city));
    printf("population starved per year on the average, i.e. a total of\n");
    printf("%d people died!!\n",city.totalDeaths);
    printf("You started with %d acres per person and ended with\n",STARTING_LAND/(STARTING_POPULATION+STARTING_IMMIGRANTS));
    printf("%d acres per person.\n",calculating_land_per_citizen(city));
    printf("\n");
}

void steward_quits(){
    printf("Hamurabi:  I cannot do what you wish.\n");
    printf("Get yourself another steward!!!!!\n");
    goodbye_message();

    exit(0);
}

void announcing_plague(){
    printf("A horrible plague struck!  Half the people died.\n");
}

void not_enough_grain(t_city city){
    printf("Hamurabi:  think again.  You have only\n");
    printf("%d bushels of grain.  Now then,\n",city.grainStock);
}

void not_enough_land(t_city city){
    printf("Hamurabi:  think again.  You own only %d acres.  Now then,\n",city.acresLand);
}

void not_enough_pop(t_city city){
    printf("But you have only %d people to tend the fields!  Now then,\n",city.population);
}

void goodbye_message(){
    char c;
    printf("So long for now.\n");

    do{
    c=getchar();
    //scanf("%c",&c);
    }while(c!='q');
}

#ifdef CLASSIC_MODE

void classic_turn_management(t_city* city){

    // First, the land is bought
    classic_land_management_buy(city);

    // Now, the land is sold
    classic_land_management_sell(city);

    // The people is then fed
    classic_grain_management_feed(city);

    // ..and the cultures are finally managed
    classic_culture_management(city);
}

void classic_grain_management_feed(t_city* city){
    int amount;
    int sortie=0;

    do{
        printf("How many bushels do you wish to feed your people\n");
        scanf("%d",&amount);

        if(amount<0){
            steward_quits();
        }else if(amount>city->grainStock){
        not_enough_grain(*city);
        }else{
            city->grainStock-=amount;
            city->grainFedToSubjects=amount;
            sortie=1;
        }
    }while(!sortie);
}

void classic_culture_management(t_city* city){
    int landAmount=0;
    int sortie=0;

    do{
    printf("How many acres do you wish to plant with seed\n");
    scanf("%d",&landAmount);

    if(landAmount<0)steward_quits();
    if(landAmount>city->acresLand){
            not_enough_land(*city);
    }else{
        if((landAmount/GRAIN_BUSHELS_BY_ACRES)<=city->grainStock){
                if(landAmount<=AMOUNT_LAND_CITIZEN*city->population){
                        city->grainStock-=landAmount/GRAIN_BUSHELS_BY_ACRES;
                        city->landSown=landAmount;
                        sortie=1;
                }else{
                    not_enough_pop(*city);
                }
        }else{
            not_enough_grain(*city);
        }
    }
    }while(!sortie);

    city->landSown=landAmount;
}

void classic_land_management_buy(t_city* city){
    int landAmount;
    int sortie=0;

    printf("Land is trading at %d bushels per acre.\n",city->price);

    do{
        printf("How many acres do you want to buy\n");
        scanf("%d",&landAmount);

        if(landAmount<0){
            steward_quits();
        }else if(landAmount*(city->price)>city->grainStock){
            not_enough_grain(*city);
        }else{
            city->acresLand+=landAmount;
            city->grainStock-=landAmount*(city->price);
            sortie=1;
        }
    }while(!sortie);
}

void classic_land_management_sell(t_city* city){
    int landAmount=0;
    int sortie=0;

    do{
        printf("How many acres do you wish to sell\n");
        scanf("%d",&landAmount);

        if(landAmount<0){
                steward_quits();
        }else if(landAmount>city->acresLand){
                not_enough_land(*city);
        }else{
                city->grainStock+=(city->price)*landAmount;
                city->acresLand-=landAmount;
                sortie=1;
            }
    }while(!sortie);
}

#endif // CLASSIC_MODE
