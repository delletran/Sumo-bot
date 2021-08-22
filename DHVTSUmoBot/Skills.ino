/***********************************************************************
 ******************************** Skills  ******************************
 **********************************************************************/
 void Search(){
      detectEnemy();
      while((line[0] != 0) && (line[1]!= 0) && (line[2]!= 0) && (line[3]!= 0) && (line[4]!= 0) && (line[5]!= 0) && (line[6]!= 0) && (line[7]!= 0) &&(dis[0]>foeRange[0])&&(dis[1]>foeRange[0])&&(dis[2]>foeRange[0])&&(dis[3]>foeRange[0])&&(dis[4]>foeRange[0])&&(dis[5]>foeRange[0])){
        pulse = 150;
        analogWrite(pwmL, pulse);
        analogWrite(pwmR, pulse);
        if(prevSearch==1){
          RotateLeft();
          Serial.print("Searching Left \n");
        }
        else{
          RotateRight();
          Serial.print("Searching Right \n");
        }
        detectEnemy();
      }
 }
 void Perspective(){
    if((line[0] != 0) && (line[1]!= 0) && (line[2]!= 0) && (line[3]!= 0) && (line[4]!= 0) && (line[5]!= 0) && (line[6]!= 0) && (line[7]!= 0) && dis[1]<=foeRange[0] && dis[1]!=0){
        pulse=255;
        FullForward();
    }
    else if((line[0] != 0) && (line[1]!= 0) && (line[2]!= 0) && (line[3]!= 0) && (line[4]!= 0) && (line[5]!= 0) && (line[6]!= 0) && (line[7]!= 0) && dis[4]<=foeRange[0] && dis[4]!=0){ 
        pulse=255;
        FullBackward();
    }
    else if(dis[0]<=foeRange[0] && dis[0]!=0){       //rotate Left
        Serial.print("Enemy Front-Left!!!\n");
        prevSearch=1;
        pulse = 255;
        RotateLeft();
        delay(dly[2]);
          detectLine();  LastStand();
        RotateRight();
        delay(dly[6]);
          detectLine();  LastStand();
        FullForward();
        delay(dly[2]);
          detectLine();  LastStand();
    }
    else if(dis[2]<=foeRange[0] && dis[2]!=0){  //rotate Right
        Serial.print("Enemy Front-Right!!!\n");
        prevSearch=0;
        pulse = 255;
        RotateRight();
        delay(dly[2]);
          detectLine();  LastStand();
        RotateLeft();
        delay(dly[6]);
          detectLine();  LastStand();
        FullForward();
        delay(dly[2]);
          detectLine();  LastStand();
      
    }
    else if(dis[3]<=foeRange[0] && dis[3]!=0){  //rotate Left
        Serial.print("Enemy Back-Left!!!\n");
        prevSearch=1;
        pulse = 255;
        RotateLeft();
        delay(dly[2]);
          detectLine();  LastStand();
        RotateRight();
        delay(dly[6]);
          detectLine();  LastStand();
        FullBackward();
        delay(dly[2]);
          detectLine();  LastStand();
      
    }
    else if(dis[5]<=foeRange[0] && dis[5]!=0){  //rotate Right
        Serial.print("Enemy Back-Right!!!\n");
        prevSearch=0;
        pulse = 255;
        RotateRight();
        delay(dly[2]);
          detectLine();  LastStand();
        RotateLeft();
        delay(dly[6]);
          detectLine();  LastStand();
        FullBackward();
        delay(dly[2]);
          detectLine();  LastStand();
      
    }
    else{ 
        Search();
    }
 }
 void Shake(){
    Serial.print(", Shake enemy!!!\n");
    if(prevSearch==1){
      RotateLeft();
      delay(dly[3]);
       detectLine();  LastStand();
      RotateRight();
      delay(dly[3]);
       detectLine();  LastStand();
      RotateLeft();
      delay(dly[3]);
       detectLine();  LastStand();
      prevSearch=0;
    }
    else{
      RotateRight();
      delay(dly[3]);
       detectLine();  LastStand();
      RotateLeft();
      delay(dly[3]);
       detectLine();  LastStand();
      RotateLeft();
      delay(dly[3]);
       detectLine();  LastStand();
      prevSearch=1;    
    }
  
 }
 void Sway(){
    Serial.print(", Sway!!!\n");
    if(prevSearch==1){
      RotateLeft();
      delay(dly[7]);
       detectLine();  LastStand();
      RotateLeft();
      delay(dly[7]);
       detectLine();  LastStand();
    }
    else{
      RotateRight();  
      delay(dly[7]);      
       detectLine();  LastStand();   
      RotateRight();  
      delay(dly[7]); 
       detectLine();  LastStand();
    }
 }

 void BumpFront(){
    Serial.print(", Bump!!!\n");
    for(int i=0; i<2;i++){
       FullBackward();
       delay(dly[3]);
       detectLine();  LastStand();
       FullForward();
       delay(dly[7]);
       detectLine();  LastStand();
    }
 }
 
 void BumpRear(){
    Serial.print(", Bump!!!\n");
    for(int i=0; i<2;i++){
       FullForward();
       delay(dly[3]);
       detectLine();  LastStand();
       FullBackward();
       delay(dly[7]);
       detectLine();  LastStand();
    }
 }
 void FrontSkillSet(){
        if(timeElapsed >= 1000 && dis[1]<=foeRange[2]){
          switch(skill){
            case 0: 
                BumpFront();
                skill=1;
            break;
            case 1: 
//                Shake();
                BumpFront();
                skill=0;
            break;
          }
          timeElapsed=0;
        }
 }
 void RearSkillSet(){
        if(timeElapsed > 1000  && dis[4]<=foeRange[2]){
          switch(skill){
            case 0: 
                BumpRear();
                skill=1;
            break;
            case 1: 
//                Shake();
                BumpRear();
//                Search();
//                Perspective();
//                if(dis[1]<=foeRange[2]){
//                  BumpFront();
//                }
//                else if(dis[4]<=foeRange[2]){ 
//                  BumpRear();
//                }
                skill=0;
            break;
          }
          timeElapsed=0;
        }
 }
 
 void SuperSkill(){
  
 }

