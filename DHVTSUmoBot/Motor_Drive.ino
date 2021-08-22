
//*********************************************************//
//                   Left&Right Motor Drive                //
//*********************************************************//
void RForward(){ //move right motors forward
digitalWrite(MotorRB, LOW);
digitalWrite(MotorRF, HIGH); 
}
void RBackward(){ //move right motors backward
digitalWrite(MotorRF, LOW);
digitalWrite(MotorRB, HIGH);
}
void LForward(){ //move left motors forward
digitalWrite(MotorLB, LOW);
digitalWrite(MotorLF, HIGH);
}
void LBackward(){ //move left motors backward
digitalWrite(MotorLF, LOW);
digitalWrite(MotorLB, HIGH);
}
void LStop(){ //Left Stop
digitalWrite(MotorLF, LOW);
digitalWrite(MotorLB, LOW);
}
void RStop(){ //Right Stop
digitalWrite(MotorRF, LOW);
digitalWrite(MotorRB, LOW);
}
void varyPWM(){
  for(int i=200; i>50;i--){
     analogWrite(pwmL, i);
  }
  for(int i=50; i<200;i++){
     analogWrite(pwmL, i);
  }
}
void PWM(){
  analogWrite(pwmL, pulse);
  analogWrite(pwmR, pulse);
  
}
void RotateRight(){
  PWM();
  LForward();
  RBackward();
  leds[0] = CRGB(0x0000FF);
  leds[1] = CRGB(0x0000FF);
  FastLED.show();
}
void RotateLeft(){
  PWM();
  RForward();
  LBackward();
  leds[0] = CRGB(0x00FF00);
  leds[1] = CRGB(0x00FF00);
  FastLED.show();
}
void FullForward(){
  PWM();
  RForward();
  LForward();
  leds[0] = CRGB(0xFFFFFF);
  leds[1] = CRGB(0xFFFFFF);
  FastLED.show();
}
void FullBackward(){
  PWM();
  RBackward();
  LBackward();
  leds[0] = CRGB(0xFF0000);
  leds[1] = CRGB(0xFF0000);
  FastLED.show();
}
void FullStop(){
  LStop();
  RStop();
  for(int i=0; i<8;i++){
    leds[0] = colour[i];
    leds[1] = colour[i];
    delay(200);
    FastLED.show();
  }
  
}

