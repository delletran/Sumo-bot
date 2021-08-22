/*For National SumoBot Competition 
 *************************************
 ********** [DHVTSUmoBOT] *************
 *************************************
 * Program Written by: 
 *    Rodel Letran
 * Hardware built by:
 *    Rex Miranda
 *    Jorge Lauro Usman
 * 
 * Especial mention to: 
 *    Ethel Joy Manalo & IECEP Officers
 *    Engr. Karl Gamboa, Team Supervisor
 * 
 * ********CopyRight_Of_2018**********
 */
#include <elapsedMillis.h>
#include "FastLED.h"
#define NUM_LEDS 2
#define DATA_PIN 49
#define CLOCK_PIN 51
CRGB leds[NUM_LEDS];
CRGB colour[8] = {0x000000,0xFF0000,0x00FF00,0x0000FF,0xFFFF00,0x00FFFF,0xFF00FF,0xFFFFFF};
const int lineTrace[8] = {30,32,34,36,A0,A1,48,50}; //Line Tracing {line1[front-leftside], line2[front-left]... ,line8[back-leftside}
const int pingEcho[6] = {2,4,6,12,40,47}; //Ultrasonic Sensor Array Echo {FL,F,FR,BR,B,BL}
const int pingTrig[6] ={3,5,7,13,42,45}; //Ultrasonic Sensor Array Trigger{FL,F,FR,BR,B,BL}
const int enLeft = 27;
const int enRight = 10;
const int MotorLF = 25; // Left motor Forward
const int MotorLB = 23; // Left motor Backward
const int MotorRF = 9; // Right motor Forward
const int MotorRB = 8; // Right motor Backward
long dur[6]; //Ultrasonic Sensor Front Duration
int dis[6]; //Ultrasonic Sensor Front Distance
int line[8] = {0};
int dly[9] = {200,320,135,180,800,1000,10,390,300};
int traced = 0, prevTraced = 0, foeDetect = 0;
int foeRange[3] = {55,25,10};

int pwmL = A7; //PWM left
int pwmR = A6; //PWM Right
int pulse = 255, pulse2 = 150, pulse3 = 210;
int prevSearch = 0;
int sumoL = 0, sumoR = 0;
int startRight=41, startLeft=43;
int skill=0;
elapsedMillis timeElapsed;

void setup(){
  pinMode(enLeft, OUTPUT);
  pinMode(enRight, OUTPUT);
  pinMode(MotorRF, OUTPUT);
  pinMode(MotorRB, OUTPUT);
  pinMode(MotorLF, OUTPUT);
  pinMode(MotorLB, OUTPUT);
  pinMode(startRight, INPUT);
  pinMode(startLeft, INPUT);
  for(int i=0; i<6;i++){
    pinMode(lineTrace[i], INPUT_PULLUP);
  }
  for(int i=0; i<6;i++){
    pinMode(pingEcho[i], INPUT);
    pinMode(pingTrig[i], OUTPUT);
  }
  Serial.begin(9600);
  digitalWrite(enLeft, HIGH);
  digitalWrite(enRight, HIGH);
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  Serial.print("Initialization Complete.\n");
  Serial.print("Press [Right button] to set initial Search Right, \n[Left button] to search Left\n");
}

void loop(){
  initial();
  if(sumoL==1){
      Serial.print("Initial Search Left.\n");
    while(sumoL==1){
      for(int i=0;i<8;i++){
        leds[0] = colour[i];
        leds[1] = colour[i+1];
        FastLED.show();
        if(sumoL==0){
          break;
        }
        else{
          delay(100);
        }
      initial();
      }
    }
    prevSearch=1;
    Serial.print("Ready...\n");
    for(int i=5; i>=1; i--){
      Serial.println(i);
      delay(dly[5]);
    }
    FullForward();
    delay(dly[8]);
//    Serial.end();
    while(1){
      Start(); 
    } 
  }
  if(sumoR==1){
      Serial.print("Initial Search Right.\n");
    while(sumoR==1){
      for(int i=0;i<8;i++){
        leds[0] = colour[i];
        leds[1] = colour[i+1];
        FastLED.show();
        if(sumoR==0){
          break;
        }
        else{
          delay(100);
        }
      initial();
      }
    }
    prevSearch=0;
    Serial.print("Ready...\n");
    for(int i=5; i>=1; i--){
      Serial.println(i);
      delay(dly[5]);
    }
    FullForward();
    delay(dly[8]);
//    Serial.end();
    while(1){
      Start();      
    }
  }
    
}

void Start() {
  detectLine();
  while((line[0] != 0) && (line[1]!= 0) && (line[2]!= 0) && (line[3]!= 0) && (line[4]!= 0) && (line[5]!= 0) && (line[6]!= 0) && (line[7]!= 0)){
    detectEnemy();
    timeElapsed = 0;
    Thruster();
    Rearer();
    Search();
    Perspective();
    detectLine();
  }
  LastStand();
}

void Thruster(){
    while((line[0] != 0) && (line[1]!= 0) && (line[2]!= 0) && (line[3]!= 0) && (line[4]!= 0) && (line[5]!= 0) && (line[6]!= 0) && (line[7]!= 0) && (dis[1]<=foeRange[0])){ // Head Enemy within range
        Serial.print("Thrust Ahead!!!\n");
        pulse = 255;
        FullForward();
        detectLine();
        FrontSkillSet();
        detectEnemyFront();
    }
}

void Rearer(){
    while((line[0] != 0) && (line[1]!= 0) && (line[2]!= 0) && (line[3]!= 0) && (line[4]!= 0) && (line[5]!= 0) && (line[6]!= 0) && (line[7]!= 0) && (dis[4]<=foeRange[0])){ // Rear Enenmy within range
        Serial.print("Press Rear!!!\n");
        pulse = 255;
        FullBackward();
        detectLine();
        RearSkillSet();
        detectEnemyBack();
    }
  
}

