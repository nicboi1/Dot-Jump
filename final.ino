  #include <PCD8544.h>
 PCD8544 lcd;
// Array of Output Pin variables, set to the pins being used
const int rs = 4, en = 5, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int lvl=1;
int tag=0;
int loser=0;
int winner=0;
int counter=0;
bool lose=false;
bool pSong=false;
bool pLsong=false;
bool pWsong=false;
bool buttonHeld=true;
bool buttonHeld2=true;
bool buttonHeld3=true;
bool buttonHeld4=true;
bool keepG=true;
bool startG=false;
int i=0;
int k=0;
int del=155;
bool re=true;
bool here=false;
long int t=0;
int up=0;
int startS=0;

const char sound_pattern_size = 5;
const double sound_pattern[sound_pattern_size] = { 659.25, 523.25, 493.88, 392.00, 329.63};
const double sound_pattern2[sound_pattern_size] = { 359.25, 323.25, 393.88, 332.00, 339.63};
const double sound_pattern3[sound_pattern_size] = { 759.25, 723.25, 793.88, 732.00, 739.63};
const int buzzer = 2;
const int speedPin = 11;
const int dir1= 12;
const int dir2=13;
int speeder=20;


typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
    
} task;

int delay_gcd;
const unsigned short tasksNum = 4;
task tasks[tasksNum];

enum SM1_States { SM1_INIT, SM1_S0, SM1_S1,SM1_S2};
int SM1_Tick(int state){
    //GAME
    switch(state){ // State transitions
      case SM1_INIT:
           if((digitalRead(8)==LOW)&&(!buttonHeld3)){
           // Start Game
            lcd.clear();
            buttonHeld3=true;
            pSong=true;
            state = SM1_S0; 
           }
           if(digitalRead(8)==HIGH){
            buttonHeld3=false;
           }
        break;
      case SM1_S0:
         if(!keepG){
          //won
           state=SM1_S1;
          }
          if(lose){
            //lose
            state=SM1_S2;
          }
         //State Transition
        break;
      case SM1_S1:
        //reset from win
          if((digitalRead(9)==LOW)&&(!buttonHeld)){
            lcd.clear();
            lvl=0;
            winner=0;
            pWsong=false;
            buttonHeld=true;
            state=SM1_S0;
            keepG=true;
            counter=0;
          }
          if(digitalRead(9)==HIGH){
            buttonHeld=false;
          }
             //State Transition
        break;
      case SM1_S2:
      //reset from Lose
          if((digitalRead(9)==LOW)&&(!buttonHeld2)){
            lcd.clear();
            lvl=0;
            loser=0;
            pLsong=false;
            buttonHeld2=true;
            state=SM1_S0;
            lose=false;
            counter=0;
          }
          if(digitalRead(9)==HIGH){
            buttonHeld2=false;
          }
             //State Transition
        break;
    }
    switch(state){ // State Action
      case SM1_INIT:
      //start screen
         lcd.setCursor(20,2);
         lcd.print("DOT JUMP");
         Serial.println("ONE");
        break;

      case SM1_S0:
      Serial.println("TWO");
      //main page
            //State Action
            if(startG){
              //clear the dot from behind as it moves up
            lcd.setCursor(k-1,3);
            lcd.print(" ");
            if(k>=84){
              //dot gets to end start from beg
              k=0;
              counter++;
              if(lvl<=10){
                //in game obj at end means update lvl, motor speed, and obj speed
              lvl++;
              speeder+=50;
              del=del-10;
              }
             }
            if((counter<15)){
            //when not at end of time limit keep updating obj to move forward
            lcd.setCursor(k,3);
            lcd.print(".");
            t++;
            k++;
            Serial.println(del);
            delay(del);
            }
            if(counter>=15){
             //at the end of game limit game is won
              lcd.clear();
              keepG=false;
              pWsong=true;
            }
            if((here)&&(k==39)){
              //obj and dot collide
              lose=true;
              lcd.clear();
             
            }
         }   
        break;
    case SM1_S1:
    Serial.println("THREE");
    //win screen
            del=175;
            k=0;
          //  keepG=true;
          //  lose=false;
            speeder=20;
            t=0;
        lcd.setCursor(0,0);
        lcd.print("YOU WIN");
        lcd.setCursor(0,1);
        lcd.print("HIGHSCORE: ");
        lcd.print("11");
        break;
        
        case SM1_S2:
        //lose screen
          del=175;
           // keepG=true;
            t=0;
            k=0;
           // lose=false;
            speeder=20;
        lcd.setCursor(0,0);
        lcd.print("YOU LOSE");
        lcd.setCursor(0,1);
        lcd.print("SCORE: ");
        lcd.print(lvl);
        pLsong=true;

        break;
    }
    
    return state;
}

enum SM2_States { SM2_INIT, SM2_S0, SM2_S1};
int SM2_Tick(int state){
    //jump
    switch(state){ // State transitions
      case SM2_INIT:
         //State Transition
            state = SM2_S0;
        break;
      case SM2_S0:
      //jump
      if((digitalRead(10)==LOW)&&(re)){
        tag=0;
            re=false;
            state = SM2_S1;  
          }

        //State Transition
        break;
      case SM2_S1:
      //on ground level
      if(tag>=4){
        //has to go through entire jump sequence b4 going back to ground state (to then jump again)
            re=true;
            state = SM2_S0;   
      }
        //State Transition
        break;
    }

    
    switch(state){ // State Action
      case SM2_INIT:
         //State Action
        break;
      case SM2_S0:
      Serial.println("FOUR");
      //bottom
           lcd.setCursor(39,2);
          lcd.print(" ");
          // Serial.println("SM2_S0");
          lcd.setCursor(39,3);
          lcd.print(".");
          here=true;

         //State Action
        break;
      case SM2_S1:
      Serial.println("FIVE");
      //jump sequence
            //State Action
            if(tag<3){
              if(tag==2){
              tag++;
              }
                if(tag==1){
                //top
                lcd.setCursor(39,2);
                lcd.print(" ");
                lcd.setCursor(39,1);
                lcd.print(".");
                here=false;
                tag++;
                tone(buzzer, 659.25);
                delay(150);
            }
              if((tag==0)||(tag>=3)){
                //middle
                noTone(buzzer);
                 lcd.setCursor(39,3);
                  lcd.print(" ");
                  lcd.setCursor(39,1);
                  lcd.print(" ");
                  lcd.setCursor(39,2);
                   lcd.print(".");
                   here=false;
                   up=0;
                  tag++;
                  delay(150);
              }

           }
            
           // tone(buzzer, sound_pattern[1]);
         //State Action
        break;
     
        
    }
    

    return state;
}

enum SM3_States { SM3_INIT, SM3_S0, SM3_S1, SM3_S2, SM3_S3};
int SM3_Tick(int state){
    //buzzer songs
    switch(state){ // State transitions
      case SM3_INIT:
         //State Transition
            state = SM3_S0;
        break;
      case SM3_S0:
      Serial.println("SIX");
      //play songs
          if(pSong){
            //start song
            state = SM3_S1;  
          }
          if(pLsong){
            //lose song
            state = SM3_S2;  
          }
          if(pWsong){
            //win song
            state = SM3_S3;  
          }
        //State Transition
        break;
      case SM3_S1:
      Serial.println("SEVEN");
      //end of Start song
        if(!pSong){
          state=SM3_S0;
        }
        //State Transition
        break;
       case SM3_S2:
       Serial.println("EIGHT");
        if(!pLsong){
          //end of lose song
          state=SM3_S0;
        }
        //State Transition
        break;
       case SM3_S3:
       Serial.println("NINE");
        if(!pWsong){
          //end of win song
          state=SM3_S0;
        }
        //State Transition
        break;
    }

    
    switch(state){ // State Action
      case SM3_INIT:
         //State Action
        break;
      case SM3_S0:
      Serial.println("TEN");
    //No song plays
        break;
      case SM3_S1:
      
      //Start song
      if(startS>=5){
        //start game after start song
        lcd.clear();
        startG=true;
        tone(buzzer,0);
        pSong=false;
      }else{
        //start screen w/ start song
        lcd.setCursor(20,2);
        lcd.print("DOT JUMP");
        tone(buzzer,sound_pattern[startS]);
       // Serial.println("outer");
         startS++;
      }
        break;
     case SM3_S2:
     //lose song
        if (loser<5){
        tone(buzzer,sound_pattern2[loser]);
        loser++;
        }
        if(loser>=5){
          //only play once
          noTone(buzzer);
          pLsong=false;
        }
     break;
     case SM3_S3:
     //win song
        if (winner<5){ 
        tone(buzzer,sound_pattern3[winner]);
        winner++;
        }
        if(winner>=5){
          //only play once
          noTone(buzzer);
          pWsong=false;
        }
     break;
    }
    

    return state;
}

enum SM4_States { SM4_INIT, SM4_S0, SM4_S1};
int SM4_Tick(int state){
  //fan speed
    //Read thing
    switch(state){ // State transitions
      case SM4_INIT:
         //State Transition
            state = SM4_S1;
         
        break;
      case SM4_S0:
      //game ends fan off
        if((!keepG)||(lose)){
          state=SM4_S1;
        }
        //State Transition
        break;
      case SM4_S1:
      //game is being played fan on
        if((keepG)&&(!lose)&&(startG)){
          state=SM4_S0;
        }
          
        
        //State Transition
        break;

    }

    
    switch(state){ // State Action
      case SM4_INIT:
         //State Action
        break;
      case SM4_S0:
      //Fan ON
            digitalWrite(dir1,HIGH);
            digitalWrite(dir2,LOW);
            //Serial.println(speeder);
            digitalWrite(speedPin,speeder);
        break;
      case SM4_S1:
     //Fan OFF
      digitalWrite(speedPin,0);
        break;

    }
    

    return state;
}


void setup() {
    //some set up (Default Arduino Function)

    // LEDs
     pinMode(buzzer, OUTPUT);
    pinMode(speedPin, OUTPUT);
    pinMode(dir1, OUTPUT);
    pinMode(dir2, OUTPUT);
   pinMode(8,INPUT_PULLUP);
   pinMode(9,INPUT_PULLUP);
   pinMode(10,INPUT_PULLUP);
    Serial.begin(9600);


  unsigned char i = 0;
  tasks[i].state = SM1_INIT;
  tasks[i].period = 25;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM1_Tick;
  i++;
  tasks[i].state = SM2_INIT;
  tasks[i].period = 50;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM2_Tick;
   i++;
  tasks[i].state = SM3_INIT;
  tasks[i].period = 250;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM3_Tick;
  i++;
  tasks[i].state = SM4_INIT;
  tasks[i].period = 250;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM4_Tick;
  delay_gcd = 500; // GCD
  lcd.begin(84,48);

}


void loop() {
  // put your main code here, to run repeatedly:
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
     if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = millis(); // Last time this task was ran
      
     }
   }
}
