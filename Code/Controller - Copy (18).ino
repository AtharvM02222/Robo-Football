#include "arduino_secrets.h"


#include <PS2X_lib.h>

//to motor driver
#define m1 9 //data1
#define m2 8 //data2
#define m3 7 //data3
#define m4 6 //data4

#define ir 4 //right indicator
#define il 3 //left indicator
#define hl 2 //head light
#define bl 1 //Brack light




PS2X ps2x; 
int i=0; 
int k=0;
int d=100; 
int d1=200;

int error = 0; 
byte type = 0;
byte vibrate = 0;

void setup(){


 pinMode(m1, OUTPUT);
 pinMode(m2, OUTPUT);
 pinMode(m3, OUTPUT);
 pinMode(m4, OUTPUT);

 pinMode(ir, OUTPUT);
 pinMode(il, OUTPUT);
 pinMode(hl, OUTPUT);
 pinMode(bl, OUTPUT);


 digitalWrite(ir,0);
 digitalWrite(il,0);
 digitalWrite(hl,0);
 digitalWrite(bl,0);

 digitalWrite(m1,0);
 digitalWrite(m2,0);
 digitalWrite(m3,0);
 digitalWrite(m4,0);
 




  
 error = ps2x.config_gamepad(13,11,10,12, false, false);   
                          //(clock, command, attention, data)

 if(error == 0){
  Serial.println("Found Controller, configured successful");
 }
   
 else if(error == 1)
  Serial.println("No controller found, check wiring or reset the Arduino");
   
 else if(error == 2)
  Serial.println("Controller found but not accepting commands");
  
 else if(error == 3)
  Serial.println("Controller refusing to enter Pressures mode, may not support it.");  
 type = ps2x.readType();
 switch(type) {
  case 0:
    break;
  case 1:
    break;
  case 2:
    break;
  }
}


void loop(){
   
 if(error == 1) 
  return; 
  
 else { //DualShock Controller
  
    ps2x.read_gamepad(false, vibrate); // disable vibration of the controller

    

     int rightstickry = (ps2x.Analog(PSS_RY)); // Right stickry
     int rightstickrx = (ps2x.Analog(PSS_RX));
     
    
     if(ps2x.Button(PSB_PAD_UP)|| rightstickry<50)  // MOVE FORWARD
     {
        digitalWrite(m1,1);
        digitalWrite(m2,0);
        digitalWrite(m3,0);
        digitalWrite(m4,1);
       
       
      }
      
      if(ps2x.Button(PSB_PAD_RIGHT)|| rightstickrx>200)// TURN RIGHT
      {
        digitalWrite(m1,1);
        digitalWrite(m2,0);
        digitalWrite(m3,1);
        digitalWrite(m4,0);
        digitalWrite(ir,1);
        
      }
      
      if(ps2x.Button(PSB_PAD_LEFT)|| rightstickrx<50)// TURN LEFT
      {
        digitalWrite(m1,0);
        digitalWrite(m2,1);
        digitalWrite(m3,0);
        digitalWrite(m4,1);
        digitalWrite(il,1);
      
      
      }
      
      if(ps2x.Button(PSB_PAD_DOWN)|| rightstickry>200)// MOVE BACK
      {
        digitalWrite(m1,0);
        digitalWrite(m2,1);
        digitalWrite(m3,1);
        digitalWrite(m4,0);
               
       
      }  
      if (!ps2x.Button(PSB_PAD_DOWN) && !ps2x.Button(PSB_PAD_UP) && !ps2x.Button(PSB_PAD_RIGHT) && !ps2x.Button(PSB_PAD_LEFT) && rightstickry>50 && rightstickry<200 && rightstickrx>50 && rightstickrx<200 ) 
      {
        digitalWrite(m1,0);
        digitalWrite(m2,0);
        digitalWrite(m3,0);
        digitalWrite(m4,0);
        digitalWrite(ir,0);
        digitalWrite(il,0);
      }

      if (ps2x.Button(PSB_GREEN))
      {
      
      digitalWrite(hl,1);
     }

     if (ps2x.Button(PSB_RED))            
      {
       
        digitalWrite(bl,1);
        
     
      }

    if (ps2x.Button(PSB_PINK))   
    {

      i=1;
      
      
    }
    
    if (ps2x.Button(PSB_BLUE))            
    { 
      digitalWrite(ir,0);
      digitalWrite(il,0);
      digitalWrite(hl,0);
      digitalWrite(bl,0);

      i=0;
    }
 if (i==1)  
 {digitalWrite(ir,1);
  digitalWrite(il,1);
  delay(500);
  digitalWrite(ir,0);
  digitalWrite(il,0);
  delay(500);
  k++;
  }

  if (k==3)  
 {i=0;
  }          
 delay(50);
 }    
}
