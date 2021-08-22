
//*********************************************************//
//                   Detect Enemy & Ring Tan               //
//*********************************************************//
void detectEnemy(){
  detectEnemyFront();
  detectEnemyBack();
}

void detectEnemyFront(){
 // Serial.print("     Front Ping  \n"); 
//  Serial.print("#   ");
  for(int i=0; i<3;i++){
    digitalWrite(pingTrig[i], LOW);
    delayMicroseconds(2);
    digitalWrite(pingTrig[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(pingTrig[i], LOW);
    dur[i] = pulseIn(pingEcho[i], HIGH);     //duration of the echo back and fort
    dis[i] = dur[i] * 0.034 / 2;        //ultrasonic feedback distance conversion to cm
//    Serial.print(dis[i]); Serial.print("   #   ");
    detectLine();  LastStand();
  }
  Serial.print("\n");
}

void detectEnemyBack(){
//  Serial.print("      Back Ping  \n"); 
//  Serial.print("||   ");
  for(int i=3; i<6;i++){
    digitalWrite(pingTrig[i], LOW);
    delayMicroseconds(2);
    digitalWrite(pingTrig[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(pingTrig[i], LOW);
    dur[i] = pulseIn(pingEcho[i], HIGH);     //duration of the echo back and fort
    dis[i] = dur[i] * 0.034 / 2;        //ultrasonic feedback distance conversion to cm
//    Serial.print(dis[i]); Serial.print("   ||   ");
    detectLine();   LastStand();
  }
  Serial.print("\n");
}

void detectLine(){
  for(int i=0; i<8;i++){
     line[i] = digitalRead(lineTrace[i]);
     line[3]=1;
     line[7]=1;
     if(line[i]!=1){
      traced=i+1;
      prevTraced=traced;
     }
     else{
      traced=0;
     }
  }
}
void LastStand(){
  for(int i=0; i<8;i++){
     line[i] = digitalRead(lineTrace[i]);
     line[3] = 1;                                    //proximity sensor unavailable
     line[7] = 1;                                    //proximity sensor unavailable
  }
  if((line[3]!=1)&&(line[4]!=1)){
     Serial.print("*** 04 # 05 *** \n"); //steady left; backward right hard
     pulse=255; PWM();
     RBackward();
     LStop();
     delay(dly[7]);
     delay(dly[7]);
     delay(dly[7]);
     FullBackward();
     delay(dly[7]);
     Search();
  }
  else if((line[7]!=1)&&(line[0]!=1)){
     Serial.print("*** 08 # 01 *** \n"); //steady right; forward left hard
     pulse=255; PWM();
     LBackward();
     RStop();
     delay(dly[7]);
     delay(dly[7]);
     delay(dly[7]);
     FullBackward();
     delay(dly[7]);
     Search();
  }
  else if((line[0]!=1)&&(line[1]!=1)){
     Serial.print("*** 01 # 02 *** \n"); //steady right; backward left hard
     analogWrite(pwmR, pulse2);
     analogWrite(pwmL, 255);
     LBackward();
     RStop();
     delay(dly[7]);
     delay(dly[7]);
     pulse=255;
     FullBackward();
     delay(dly[7]);   
     Search();
  }
     
  else if((line[1]!=1)&&(line[2]!=1)){
     Serial.print("*** 02 # 03 *** \n"); //FullBackward
     pulse=255; PWM();
     FullBackward();
     delay(dly[1]);
     Search();
  }
     
  else if((line[2]!=1)&&(line[3]!=1)){
     Serial.print("*** 03 # 04 *** \n"); //steady left; backward right light
     pulse=255; PWM();
     RBackward();
     LStop();
     delay(dly[0]);
     delay(dly[0]);
     pulse=255;
     FullBackward();
     delay(dly[0]);
     Search();
  }
          
  else if((line[4]!=1)&&(line[5]!=1)){
     Serial.print("*** 05 # 06 *** \n"); //steady left; forward right hard
     analogWrite(pwmL, pulse2);
     analogWrite(pwmR, 255);
     LForward();
     RForward();
     delay(dly[1]);
     LStop();
     delay(dly[7]);
     pulse=255;
     FullForward();
     delay(dly[7]);
     Search();
  }
     
  else if((line[5]!=1)&&(line[6]!=1)){
     Serial.print("*** 06 # 07 *** \n"); //FullForward
     pulse=255; PWM();
     FullForward();
     delay(dly[0]);
     Search();
  }
     
  else if((line[6]!=1)&&(line[7]!=1)){
     Serial.print("*** 07 # 08 *** \n"); //steady right; forward left light
     analogWrite(pwmR, pulse3);
     analogWrite(pwmL, 255);
     LForward();
     RForward();
     delay(dly[0]);
     RStop();
     delay(dly[0]);
     pulse=255;
     FullForward();
     delay(dly[0]);
  }
     
  else if((line[0]!=1)){
     Serial.print("*** 01 *** \n"); //steady right; backward left hard
     analogWrite(pwmR, pulse2);
     analogWrite(pwmL, 255);
     FullBackward();
     RBackward();
     LBackward();
     delay(dly[1]);
     RStop();
     delay(dly[7]);
     pulse=255;
     FullBackward();
     delay(dly[7]);   
     Search();
  }
     
  else if((line[1]!=1)){
     Serial.print("*** 02 *** \n"); //steady right; backward left light
     analogWrite(pwmR, pulse3);
     analogWrite(pwmL, 255);
     pulse=255;
     LBackward();
     RStop();
     delay(dly[0]);
     FullBackward();
     delay(dly[0]);
  }
     
  else if((line[2]!=1)){
     Serial.print("*** 03 *** \n"); //steady left; backward right light
     analogWrite(pwmL, pulse3);
     analogWrite(pwmR, 255);
     RBackward();
     LStop();
     delay(dly[0]);
     pulse=255;
     FullBackward();
     delay(dly[0]);
     Search();
  }
     
  else if((line[3]!=1)){
     Serial.print("*** 04 *** \n"); //steady left; backward right hard
     analogWrite(pwmL, pulse2);
     analogWrite(pwmR, 255);
     FullBackward();
     delay(dly[0]);
     LStop();
     delay(dly[7]);
     pulse=255;
     FullBackward();
     delay(dly[7]);
  }
     
  else if((line[4]!=1)){
     Serial.print("*** 05 *** \n"); //steady left; forward right hard
     analogWrite(pwmL, pulse2);
     analogWrite(pwmR, 255);
     FullForward();
     delay(dly[0]);
     LStop();
     delay(dly[7]);
     pulse=255;
     FullForward();
     delay(dly[7]);
     Search();
  }
     
  else if((line[5]!=1)){
     Serial.print("*** 06 *** \n"); //steady left; forward right light
     analogWrite(pwmL, pulse3);
     analogWrite(pwmR, 255);
     RForward();
     LStop();
     delay(dly[0]);
     pulse=255;
     FullForward();
     delay(dly[0]);
  }
     
  else if((line[6]!=1)){
     Serial.print("*** 07 *** \n"); //steady right; forward left light
     analogWrite(pwmR, pulse3);
     analogWrite(pwmL, 255);
     LForward();
     RStop();
     delay(dly[0]);
     pulse=255;
     FullForward();
     delay(dly[0]);
     Search();
  }
     
  else if((line[7]!=1)){
            
     Serial.print("*** 08 # 01 *** \n"); //steady right; forward left hard
     analogWrite(pwmR, pulse2);
     analogWrite(pwmL, 255);
     LForward();
     RForward();
     delay(dly[1]);
     RStop();
     delay(dly[7]);
     pulse=255;
     FullForward();
     delay(dly[7]);
     Search();
  }
  
}
  
void initial(){
  sumoL = digitalRead(startLeft);
  sumoR = digitalRead(startRight);
  
}


