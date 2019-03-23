#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//function declaration
int is_prime(int number); //return 1 if prime, else return 0




//functions
int main(){
   int game_state=0; //present name 0, discard cards 1, play a card 2
   int num_cards_in_hand=0;
   int cards_in_hand[10]={0}; 
   int num_cards_played_this_round={0};
   int cards_played_this_round[3]={0};
   int cards_played_previous_rounds[36]={0};
   int cards_discarded[3]={0};
   int cards_received[3]={0};
   int t_pos=0;
   int counter=0; //counter for loops
    
   scanf("%d",&game_state);
   if(game_state==0){ //present name
      printf("zeddines\n");
      return 0;
   }
   if(game_state==1){  //discard 3 cards
   
   
   }
   if(game_state==2){  //play a card
      //***retrieving information***//
      scanf("%d %d %d",&num_cards_in_hand,&num_cards_played_this_round,&t_pos);
      while(counter<num_cards_in_hand){  //cards in hand
         scanf("%d",&cards_in_hand[counter]);
         counter++;
      }
      counter=0;
      while(counter<num_cards_played_this_round){ //cards played this round
         scanf("%d",&cards_played_this_round[counter]);
         counter++;
      }
      counter=0;
      while(counter<(10-num_cards_in_hand)*4){ //cards played previous rounds
         scanf("%d",&cards_played_previous_rounds[counter]);
         counter++;
      }
      counter=0;
      while(counter<3){ //cards discarded
         scanf("%d",&cards_discarded[counter]);
         counter++;
      }
      counter=0;
      while(counter<3){ //cards received
         scanf("%d",&cards_received[counter]);
         counter++;
      }
      counter=0;
      //***retrieving information ends***//
      
      //***finding cards playable***//
      
      int cards_playable[10]={0};
      int num_primes_played=0; //show number of prime cards played previously, if > 0, then can play a prime card in first round
      int num_primes_in_hand=0; //
      if(num_cards_played_this_round==0){ //playing first card in round
         while(counter<(10-num_cards_in_hand)*4){ //check whether a prime card is played in previous rounds
            if(is_prime(cards_played_previous_rounds[counter])==1)
               num_primes_played++;
            counter++;
         }
         counter=0;
         if(num_primes_played==0){ //no prime cards are played in previous rounds
            while(counter<num_cards_in_hand){ //check numbers of prime cards you have
               if(is_prime(cards_in_hand[counter])==1)
                  num_primes_in_hand++;
               counter++;
            }
            if(num_primes_in_hand==num_cards_in_hand){ //you only have prime cards, can play any cards
               
            
            
            }
            else{ //you have non prime cards, play non prime cards
            
            
            
            
            }
         
         }
         else{ //prime cards are played, can play any cards
         
         
         
         
         }
            
      }
      else{ //not playing first card in round
      
      
      
      }
      
      
      //***finding cards playable end***//
      
      
   }
   //***testing area***//
   
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
   
   
   
   
   //***testing area end***//


   return 0;
}

//primary functions





//assisting functions
int is_prime(int number){ //return 1 if prime, else return 0
   int counter=2;
   while(counter<number){
      if(number%counter==0)
         return 0;
      counter++;
   }
   return 1;
}




