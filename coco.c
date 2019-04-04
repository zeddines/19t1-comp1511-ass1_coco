/*
Coco assignment by Bertram Lee (z5210146), written in 27th March 2019.

Description:
The program legally plays coco using information received from stdin, cards that
can be played are then stored in an array. The program then makes decision using
optimizing functions to select the best card possible from the array.

Additional info:
## For clarity, numbers are used to indicate the decision tree for deciding 
   playable cards (refer to 'finding cards playable' module in main function):
    (1) playing first card in round
        (1.1) playing first card in round. primes had been played. [play any cards]
        (1.2) playing first card in round. primes hadn't been played. 
            (1.2.1) playing first card in round. primes hadn't been played. 
                    have a non-prime cards in hand. [play non-prime cards]
            (1.2.2) playing first card in round. primes hadn't been played. 
                    don't have non-prime card. [play any cards]
    (2) not playing first card in round
        (2.1) not playing first card in round. the first card was prime
            (2.1.1) not playing first card in round. the first card was prime. 
                    have a prime card in hand. [play prime cards]
            (2.1.2) not playing first card in round. the first card was prime. 
                    don't have a prime card in hand. [play any cards]
        (2.2) not playing first card in round. the first card was not prime.
            (2.2.1) not playing first card in round. the first card was not prime. 
                    have cocomposite cards. [play cocomposite cards]
            (2.2.2) not playing first card in round. the first card was not prime. 
                    don't have cocomposite cards. [play any cards]


*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define DOUGLAS 42

//***function declaration***//

//return 1 if prime, else return 0
int is_prime(int number); 

//return 1 if cocomposite, else return 0
int is_cocomposite(int number1, int number2); 

int calculate_penalty_points(int num_cards_played_this_round, int cards_played_this_round[3]); 

//return the maximum value card which follows with the first card played before me this round
int max_num(int num_cards_played_this_round, int cards_played_this_round[3]); 

int optimize(int player, int num_cards_playable, int cards_playable[10], 
             int cards_played_this_round[3], int num_cards_played_previous_rounds,
             int cards_played_previous_rounds[40], int cards_discarded[3], 
             int cards_received[3], int num_cards_in_hand, int cards_in_hand[10], int get_trick);  
                
int first_card_in_round(int num_cards_playable, int cards_playable[10], 
                        int num_cards_prediction, int cards_prediction[40]); 
                                    
int fourth_card_in_round(int num_cards_playable, int cards_playable[10],
                         int cards_played_this_round[3]);
                         
//return 1 if the array contains douglas, else return 0                         
int have_douglas(int num_cards_playable, int cards_playable[10]); 

//***function declaration end***//

int main(){
    //***variables***//
    
    //position of the player, varies from 0-3
    int t_pos = 0; 
    //present name 0, discard cards 1, play a card 2
    int game_state = 0; 
    
    int num_cards_in_hand = 0;
    int cards_in_hand[10] = {0}; 
    
    int num_cards_played_this_round = 0;
    int cards_played_this_round[3] = {0};
    
    //num_cards_played_previous rounds = (10 - num_cards_in_hand) * 4
    int cards_played_previous_rounds[36] = {0}; 
    
    int cards_discarded[3] = {0};
    int cards_received[3] = {0};
    
    //number of cards playable in this round   
    int num_cards_playable = 0; 
    //array of cards playable this round	
    int cards_playable[10] = {0}; 
    
    //counter for loops, everytime a loop is executed, reset counter to 0
    int counter = 0; 

    //number of prime cards played in previous rounds, only need to use this 
    //when playing the first card in round
    int num_primes_played = 0; 
    //number of prime cards in hand
    int num_primes_in_hand = 0; 
    //number of cocomposite cards with the first card in this round in hand,
    //do not need to use it when playing the first card in round
    int num_cocomposites_in_hand = 0; 
    
    //if get_trick = 0, you can pick any card and you will not win the round as
    //you didn't follow the first card (used if not first card)
    int get_trick = 1; 
    
    //***variables end***//
    
    scanf("%d", &game_state);
    
    //***present name***//
    
    if(game_state == 0){ 
        printf("zeddines\n");
        return 0;
    }
    
    //***present name end***//
    
    //***discard cards***//
    
    if(game_state == 1){
        while(counter < 10){
            scanf("%d", &cards_in_hand[counter]);
            counter++;
        }
        counter = 0;
        printf("%d %d %d", cards_in_hand[9], cards_in_hand[8], cards_in_hand[7]);
    }
    
    //***discard cards end***//
    
    //***play a card***//
    if(game_state == 2){ 
     
        //***retrieving information from stdin***//
        scanf("%d %d %d", &num_cards_in_hand, &num_cards_played_this_round, &t_pos);
        
        //receive cards in hand
        while(counter < num_cards_in_hand){  
            scanf("%d", &cards_in_hand[counter]);
            counter++;
        }
        counter = 0;
        
        //receive cards played this round
        while(counter < num_cards_played_this_round){ 
            scanf("%d", &cards_played_this_round[counter]);
            counter++;
        }
        counter = 0;
        
        //receive cards played previous rounds
        while(counter < (10 - num_cards_in_hand) * 4){ 
            scanf("%d", &cards_played_previous_rounds[counter]);
            counter++;
        }
        counter = 0;
        
        //receive cards discarded before the game starts
        while(counter < 3){ 
            scanf("%d", &cards_discarded[counter]);
            counter++;
        }
        counter = 0;
        
        //receive cards received before the game starts
        while(counter < 3){ 
            scanf("%d",&cards_received[counter]);
            counter++;
        }
        counter = 0;
        
        //***retrieving information from stdin ends***//

        //***finding cards playable***// (Check the header comment for clarity ##)
        
        //playing first card in round (1)
        if(num_cards_played_this_round == 0){
            //check whether a prime card is played in previous rounds
            while(counter < (10 - num_cards_in_hand) * 4){ 
                if(is_prime(cards_played_previous_rounds[counter]) == 1)
                    num_primes_played++;
                counter++;
            }
            counter = 0;
            
            //no prime cards are played in previous rounds (1.2)
            if(num_primes_played == 0){ 
                //check numbers of prime cards you have
                while(counter < num_cards_in_hand){ 
                    if(is_prime(cards_in_hand[counter]) == 1)
                        num_primes_in_hand++;
                    counter++;
                }
                counter = 0;
                
                //you only have prime cards, can play any cards (1.2.2)
                if(num_primes_in_hand == num_cards_in_hand){ 
                    while(counter < num_cards_in_hand){
                        cards_playable[num_cards_playable] = cards_in_hand[counter];
                        counter++;
                        num_cards_playable++;
                    }
                    counter = 0;
                }
                
                //you have non prime cards, play non prime cards (1.2.1)
                else{ 
                    while(counter < num_cards_in_hand){
                        if(is_prime(cards_in_hand[counter]) == 0){  
                            cards_playable[num_cards_playable] = cards_in_hand[counter];
                            num_cards_playable++;
                        }
                        counter++;
                    }
                    counter = 0;
                }
            }
            
            //prime cards are played, can play any cards (1.1)
            else{ 
                while(counter < num_cards_in_hand){
                    cards_playable[num_cards_playable] = cards_in_hand[counter];
                    counter++;
                    num_cards_playable++;
                }
                counter = 0;
            }
        }
        
        //not playing first card in round (2)
        else{ 
            //the first card is a prime card (2.1)
            if(is_prime(cards_played_this_round[0]) == 1){ 
                //check numbers of prime cards you have
                while(counter < num_cards_in_hand){ 
                    if(is_prime(cards_in_hand[counter]) == 1)
                        num_primes_in_hand++;
                    counter++;
                }
                counter = 0;
                
                //you don't have a prime card, play any card (2.1.2), and won't win
                if(num_primes_in_hand == 0){ 
                    while(counter < num_cards_in_hand){
                        cards_playable[num_cards_playable] = cards_in_hand[counter];
                        counter++;
                        num_cards_playable++;
                    }
                    counter = 0;
                    get_trick = 0;           
                }
                
                //you have prime cards, play prime cards (2.1.1)
                else{ 
                    while(counter < num_cards_in_hand){
                        if(is_prime(cards_in_hand[counter]) == 1){
                            cards_playable[num_cards_playable] = cards_in_hand[counter];
                            num_cards_playable++;
                        }
                        counter++;
                    }
                    counter = 0;
                }
            }
            
            //the first card is not a prime card (2.2)
            else{ 
                //check the number of cocomposite cards you have 
                while(counter < num_cards_in_hand){ 
                    if(is_cocomposite(cards_in_hand[counter],cards_played_this_round[0]) == 1){
                        num_cocomposites_in_hand++;
                    }
                    counter++;
                }
                counter = 0;
                
                //don't have cocomposite cards, play any cards (2.2.2)
                if(num_cocomposites_in_hand == 0){ 
                    while(counter < num_cards_in_hand){
                        cards_playable[num_cards_playable] = cards_in_hand[counter];
                        counter++;
                        num_cards_playable++;
                    }
                    counter = 0;      
                    get_trick = 0;          
                }
                
                //have cocomposite cards, play cocomposite cards (2.2.1)
                else{ 
                    while(counter < num_cards_in_hand){
                        if(is_cocomposite(cards_in_hand[counter],cards_played_this_round[0]) == 1){
                            cards_playable[num_cards_playable] = cards_in_hand[counter];
                            num_cards_playable++;
                        }
                        counter++;
                    }
                    counter = 0;
                }
            }
        }
        
        //***finding cards playable end***//

        //***optimize***// pick the best card from the playble_card array
        
        printf("%d",optimize(num_cards_played_this_round, num_cards_playable, cards_playable, 
                cards_played_this_round,  (10 - num_cards_in_hand) * 4,
                cards_played_previous_rounds, cards_discarded, cards_received, num_cards_in_hand,       
                cards_in_hand, get_trick));        
//        printf("%d\n", cards_playable[0]);

        //***optimize end***//
        
    //***play a card end***//
    }
    

    return 0;
}

//***optimizing functions***//
            //player = num_cards_played_this_round
int optimize(int player, int num_cards_playable, int cards_playable[10], 
             int cards_played_this_round[3], int num_cards_played_previous_rounds,
             int cards_played_previous_rounds[40], int cards_discarded[3], 
             int cards_received[3], int num_cards_in_hand, int cards_in_hand[10], 
             int get_trick){        
             
    //***variables***//             
             
    //total cards-cards in previous round-cards played this round-cards in hand
    //-(cards discarded, depending on my position)       
    int cards_potentially_played_this_round[40] = {0};  
    int num_cards_potentially_played_this_round = 0;
    
    //counters for loops
    int counter = 0;
    int counter2 = 0;
    
/*    int cards_played_previous_rounds_index = 0;
    int cards_played_this_round_index = 0;
    int cards_in_hand_index = 0;*/
    
    //if flag = 1, the number checking for the cards_potentially_played_this_round
    //array is in other arrys, which means that the number will not get assigned into
    //the cards_potentially_played_this_round array. if flag = 0, the number will
    //get assigned
    int flag = 0; 
    
    //***variables end***//
    
    printf("\n");
    printf("cards_playable: "); 
    while(counter < num_cards_playable){
        printf("%d ", cards_playable[counter]);
        counter++;
    }
    printf("\n\n");
    counter = 0;
    
    //if get_trick == 0, you cannot follow the first card, you won't receive 
    //trick and can play any card
    //play the douglas, if don't have douglas play largest card
    if(get_trick == 0){ 
        printf("get trick is 0\n");
        if(have_douglas(num_cards_playable,cards_playable) == 1){
            return DOUGLAS;
        }
        else{
            return cards_playable[num_cards_playable-1];
        }
    }
    
    
//    printf("num_cards_played_previous_rounds = %d\n", num_cards_played_previous_rounds);

    //***assign values to cards_potentially_played_this_round array***// 
    
    //counter initialize from 10 as cards range from 10-49
    counter = 10;
    while(counter <= 49){ 
        while(counter2 < num_cards_played_previous_rounds && flag == 0){
            if(counter == cards_played_previous_rounds[counter2]){
                flag = 1;
                //printf("card_played_previously = %d\n", counter);                
            }
            counter2++;;
        }
        counter2 = 0;
        
        while(counter2 < player && flag == 0){
            if(counter == cards_played_this_round[counter2]){
                flag = 1;            
            }
            counter2++;
        }        
        counter2 = 0;
        
        while(counter2<num_cards_in_hand && flag == 0){
            if(counter == cards_in_hand[counter2]){
                flag = 1;
            }
            counter2++;
        }
        counter2 = 0;
        
        /*
        if the player next to me has already played a card in round before us, we can exclude the cards I discarded initially        
        */    
//        printf("flag = %d\n",flag);
        if(flag == 0){
            cards_potentially_played_this_round[num_cards_potentially_played_this_round] = counter;
            num_cards_potentially_played_this_round++;            
        }
        else
            flag = 0;
        counter++;
    }
    counter = 0;
    
    //***assign values to cards_potentially_played_this_round array end***//
    

    while(counter < num_cards_potentially_played_this_round){
        printf("%d ", cards_potentially_played_this_round[counter]);
        counter++;
    }    
    printf("\n");
    printf("start of function\n");
    
    //***strats***//
    
    //playing the first card in round
    if(player == 0){ 
        printf("playing as first card\n");
        return first_card_in_round(num_cards_playable, cards_playable, num_cards_potentially_played_this_round, cards_potentially_played_this_round);
    }
    
    //playing the fourth card in round
    else if(player == 3){ 
        printf("playing as fourth card\n");
        return fourth_card_in_round(num_cards_playable, cards_playable, cards_played_this_round);
    }
    
    else if(player == 1 || player == 2){
    
    }
    
    //***strats end***//
    
    //usually doesn't run this return command, for safety measures
    return cards_playable[0];
}


int fourth_card_in_round(int num_cards_playable, int cards_playable[10], int cards_played_this_round[3]){
    int i = 0;
    printf("cards_playable: ");
    while(i < num_cards_playable){
        printf("%d ", cards_playable[i]);
        i++;
    }
    printf("\n");
    //penalty points for this round before my play
    int penalty_points = calculate_penalty_points(3, cards_played_this_round);
    
    //counter = num_cards_playble-1 and counter-- 
    //as I search from the largest value to smallest 
    int counter = num_cards_playable-1;
    
    printf("penalty points = %d\n",penalty_points);
    
    //no penalty points this round
    if(penalty_points == 0){ 
        //douglas is playable
        if(have_douglas(num_cards_playable, cards_playable) == 1){ 
            //the highest num that wins this round < DOUGLAS
            if(max_num(3, cards_played_this_round) < DOUGLAS){ 
                //play largest card that isn't douglas 
                while(counter >= 0){ 
                    if(cards_playable[counter] != DOUGLAS){
                        printf("module 4\n");
                        printf("counter = %d, cards_playable[%d] = %d\n",counter, counter, cards_playable[counter]);
                        return cards_playable[counter];
                    }
                    counter--;
                }
                counter = num_cards_playable-1;
                //you only have douglas playable
                printf("module 4.1\n"); 
                return DOUGLAS;
            }
            //highest card which wins this round > DOUGLAS, give douglas
            else{ 
                printf("module 5\n");
                return DOUGLAS;
            }
        }
        //douglas is not playable, play largest card
        else{ 
            printf("module 6\n");
            return cards_playable[num_cards_playable-1];
        }
    }
    //have penalty marks this round
    else{ 
        //douglas is playable
        if(have_douglas(num_cards_playable, cards_playable) == 1){ 
            //highest card which wins this round  < douglas
            if(max_num(3, cards_played_this_round) < DOUGLAS){
                //play largest card that is < highest card which wins this round 
                while(counter >= 0){
                    if(cards_playable[counter] < max_num(3, cards_played_this_round)){
                        printf("module 1\n");
                        return cards_playable[counter];
                    }
                    counter--;
                }
                counter = num_cards_playable-1;
                
                //you only have one card and it is douglas
                if(num_cards_playable == 1){ 
                    printf("module 1.1\n");
                    return DOUGLAS;
                }
                //don't have a card < highest card which wins this round
                //you get the trick this round anyways, pick the largest card that isn't a douglas
                //(can be further improved to not pick prime)                
                else{ 
                    printf("module 1.2\n");
                    while(counter >= 0){
                        if(cards_playable[counter] != DOUGLAS){
                            return cards_playable[counter];
                        }
                    }
                }
            }
            //highest value which wins this round > DOUGALS
            else{ 
                printf("module 2\n");
                return DOUGLAS;
            }
        }
        //douglas is not playable
        else{ 
            while(counter >= 0){
                //play largest card that is < highest number which wins this round
                if(cards_playable[counter] < max_num(3, cards_played_this_round)){
                    printf("module 3, max_num = %d\n",max_num(3, cards_played_this_round));
                    return cards_playable[counter];
                }
                counter--;
            }
            counter = num_cards_playable-1; 
            
            //largest card > max_num, you get the trick anyways, pick the largest number 
            //(can be further improved for not picking prime)
            printf("module 3.1\n");
            return cards_playable[num_cards_playable-1]; 
        }
    }
    printf("no module is runned\n");
    
    //return smallest number if all cases fail
    return cards_playable[0];
}

int first_card_in_round(int num_cards_playable, int cards_playable[10], int num_cards_prediction, int cards_prediction[40]){
        
    return cards_playable[0];
}


//***optimizing functions ends***//

//***assisting functions***//

//return 1 if prime, else return 0
int is_prime(int number){ 
    int counter = 2;
    while(counter < number){
        if(number % counter == 0)
            return 0;
        counter++;
    }
    return 1;
}

//return 1 if cocomposite, else return 0
int is_cocomposite(int number1, int number2){ 
    int counter = 2;
    while(counter < number1){
        if((number1 % counter == 0) && (number2 % counter == 0) && (counter != number2))
            return 1;
        counter++;
    }
    return 0;
}

//calculate the penalty points in round before my play
int calculate_penalty_points(int num_cards_played_this_round, int cards_played_this_round[3]){
    int counter = 0;
    int penalty_points = 0;
    while(counter < num_cards_played_this_round){
        if(is_prime(cards_played_this_round[counter]) == 1){
            penalty_points++;
        }
        else if(cards_played_this_round[counter] == DOUGLAS){
            penalty_points+=7;
        }
        counter++;
    }
    return penalty_points;
}

//return 1 if have douglas in array, else return 0
int have_douglas(int num_cards_playable, int cards_playable[10]){ 
    int counter = 0;
    while(counter < num_cards_playable){
        if(cards_playable[counter] == DOUGLAS){
            return 1;
        }
        counter++;
    }
    return 0;
}

//return the maximum value card which wins the round before my play
int max_num(int num_cards_played_this_round, int cards_played_this_round[3]){ 
    int counter = 0;
    int max = 0;
    int first_is_prime = 0; //0 if first card is non prime, 1 if it is prime
    
    first_is_prime = is_prime(cards_played_this_round[0]);
    if(first_is_prime == 0){
        while(counter < num_cards_played_this_round){
            if(cards_played_this_round[counter] > max && is_cocomposite(cards_played_this_round[counter], cards_played_this_round[0]) == 1){
                max = cards_played_this_round[counter];
            }
            counter++;
        }
    }
    else{
        while(counter < num_cards_played_this_round){
            if(cards_played_this_round[counter] > max && is_prime(cards_played_this_round[counter]) == 1){
                max = cards_played_this_round[counter];
            }
            counter++;
        }
    }
    return max;
}

//***assisting functions end***//





   //***testing area***//
   /*
   int count2=0;
   printf("\n***\n");
   printf("%d %d %d\n",num_cards_in_hand,num_cards_played_this_round,t_pos);
   while(count2<num_cards_in_hand){
      printf("%d ",cards_in_hand[count2]);
      count2++;
   }
   count2=0;
   printf("\n");
    while(count2<num_cards_played_this_round){
      printf("%d ",cards_played_this_round[count2]);
      count2++;
   }
   count2=0;
   printf("\n");
   while(count2<(10-num_cards_in_hand)*4){
      printf("%d ",cards_played_previous_rounds[count2]);
      count2++;
   }
   count2=0;
   printf("\n");
   while(count2<3){
      printf("%d ",cards_discarded[count2]);
      count2++;
   }
   count2=0;
   printf("\n");
   while(count2<3){
      printf("%d ",cards_received[count2]);
      count2++;
   }
   count2=0;
   printf("\n");
//   printf("num_primes_played=%d num_primes_in_hand=%d\n",num_primes_played,num_primes_in_hand);
*/   
   
   
   
   //***testing area end***//




