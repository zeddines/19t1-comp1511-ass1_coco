#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//function declaration
int is_prime(int number); //return 1 if prime, else return 0
int is_cocomposite(int number1, int number2); //return 1 if cocomposite, else return 0



//functions
int main(){
   int game_state=0; //present name 0, discard cards 1, play a card 2
   int num_cards_in_hand=0;
   int cards_in_hand[10]={0}; 
   int num_cards_played_this_round=0;
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
      while(counter<10){
         scanf("%d",&cards_in_hand[counter]);
         counter++;
      }
      counter=0;
      printf("%d %d %d",cards_in_hand[9],cards_in_hand[8],cards_in_hand[7]);
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
//      printf("retrieved information\n");
      //***finding cards playable***//
      
      int cards_playable[10]={0};
      int num_cards_playable=0;
      int num_primes_played=0; //show number of prime cards played previously
      int num_primes_in_hand=0; //
      int num_cocomposites_in_hand=0; //number of cocomposite cards with the first card in this round in hand, do not need to use it when you're playing the first card in round
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
            counter=0;
            if(num_primes_in_hand==num_cards_in_hand){ //you only have prime cards, can play any cards     mod 3
               while(counter<num_cards_in_hand){
                  cards_playable[num_cards_playable]=cards_in_hand[counter];
                  counter++;
                  num_cards_playable++;
               }
               counter=0;
//               printf("runned module 1\n");
            }
            else{ //you have non prime cards, play non prime cards    mod 2
               while(counter<num_cards_in_hand){
                  if(is_prime(cards_in_hand[counter])==0){  
                     cards_playable[num_cards_playable]=cards_in_hand[counter];
                     num_cards_playable++;
                  }
                  counter++;
               }
               counter=0;
//               printf("runned module 3\n");
            }
         }
         else{ //prime cards are played, can play any cards   mod 1
            while(counter<num_cards_in_hand){
               cards_playable[num_cards_playable]=cards_in_hand[counter];
               counter++;
               num_cards_playable++;
            }
            counter=0;
//            printf("runned module 1\n");
         }
      }
      else{ //not playing first card in round
         if(is_prime(cards_played_this_round[0])==1){ //the first card is a prime card
            while(counter<num_cards_in_hand){ //check numbers of prime cards you have
               if(is_prime(cards_in_hand[counter])==1)
                  num_primes_in_hand++;
               counter++;
            }
            counter=0;
            if(num_primes_in_hand==0){ //you don't have a prime card, play any card    mod 5
               while(counter<num_cards_in_hand){
                  cards_playable[num_cards_playable]=cards_in_hand[counter];
                  counter++;
                  num_cards_playable++;
               }
               counter=0;  
//               printf("runned module 5\n");          
            }
            else{ //you have prime cards, play prime cards   mod 4
               while(counter<num_cards_in_hand){
                  if(is_prime(cards_in_hand[counter])==1){
                     cards_playable[num_cards_playable]=cards_in_hand[counter];
                     num_cards_playable++;
                  }
                  counter++;
               }
               counter=0;
//               printf("runned module 4\n");
            }
         }
         else{ //the first card is not a prime card   
            while(counter<num_cards_in_hand){ //check the number of cocomposite cards you have
               if(is_cocomposite(cards_in_hand[counter],cards_played_this_round[0])==1){
                  num_cocomposites_in_hand++;
               }
               counter++;
            }
            counter=0;
            if(num_cocomposites_in_hand==0){ //don't have cocomposite cards, play any cards   mod 7
               while(counter<num_cards_in_hand){
                  cards_playable[num_cards_playable]=cards_in_hand[counter];
                  counter++;
                  num_cards_playable++;
               }
               counter=0; 
//               printf("runned module 7\n");                 
            }
            else{ //have cocomposite cards, play cocomposite cards   mod 6
//               printf("counter= %d,num_cards_in_hand= %d\n",counter,num_cards_in_hand);
               while(counter<num_cards_in_hand){
                  if(is_cocomposite(cards_in_hand[counter],cards_played_this_round[0])==1){
                     cards_playable[num_cards_playable]=cards_in_hand[counter];
                     num_cards_playable++;
//                     printf("module 6: %d and %d are cocomposite\n",cards_in_hand[counter],cards_played_this_round[0]);
                  }
//                  else //delete
//                     printf("module 6: %d and %d are not cocomposite\n",cards_in_hand[counter],cards_played_this_round[0]);
                  counter++;
               }
               counter=0;
//               printf("runned module 6\n");
            }
         
         }
      }
//      printf("finding cards module end\n");
      
      //***finding cards playable end***//

      //***optimize***// pick the best card from the playble_card array
/*      printf("cards playable = ");
      while(counter<num_cards_playable){
         printf("%d  ",cards_playable[counter]);
         counter++;
      }
      counter=0;
      printf("\n");*/
      printf("%d\n",cards_playable[0]);
      
      //***optimize end***//
      
      
   }
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

int is_cocomposite(int number1, int number2){ //return 1 if cocomposite, else return 0
   int counter=2;
   while(counter<number1){
      if(number1%counter==0&&number2%counter==0&&counter!=number2)
         return 1;
      counter++;
   }
   return 0;
}





