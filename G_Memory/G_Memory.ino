/*************************************************** 
 * 
 * 
 * Designed specifically to work with the Adafruit Trellis 
 * ----> https://www.adafruit.com/products/1616
 * ----> https://www.adafruit.com/products/1611
 * 
 ****************************************************/

#include <Wire.h>
#include <Adafruit_Trellis.h>
#include <Adafruit_Trellis_XY.h>

Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_Trellis matrix1 = Adafruit_Trellis();
Adafruit_Trellis matrix2 = Adafruit_Trellis();
Adafruit_Trellis matrix3 = Adafruit_Trellis();

Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0, &matrix1, &matrix2, &matrix3);

#define NUMTRELLIS 4
#define NKEYS (NUMTRELLIS * 16)

Adafruit_Trellis_XY trellisXY = Adafruit_Trellis_XY();

#define INTPIN A2

const uint8_t map1 [8][8]={ {1,1,1,1,1,2,2,0},
                      {1,0,0,0,1,2,2,2},
                      {1,0,0,0,1,2,2,2},
                      {1,0,0,0,1,2,2,2},
                      {1,1,1,1,1,2,2,2},
                      {2,2,2,2,2,2,2,2},
                      {2,2,2,2,2,2,2,2},
                      {0,2,2,2,2,2,2,0} };
                      
const uint8_t map2 [8][8]={ {1,1,1,1,1,1,2,0},
                      {1,0,0,0,0,1,2,2},
                      {1,0,0,0,0,1,2,2},
                      {1,0,0,0,0,1,2,2},
                      {1,1,1,1,1,1,2,2},
                      {2,2,2,2,2,2,2,2},
                      {2,2,2,2,2,2,2,2},
                      {0,2,2,2,2,2,2,0} };
                      
const uint8_t map3 [8][8]={ {1,1,1,1,1,1,2,0},
                      {1,0,0,0,0,1,2,2},
                      {1,0,0,0,0,1,2,2},
                      {1,0,0,0,0,1,2,2},
                      {1,0,0,0,0,1,2,2},
                      {1,1,1,1,1,1,2,2},
                      {2,2,2,2,2,2,2,2},
                      {0,2,2,2,2,2,2,0} };
                      
const uint8_t map4 [8][8]={ {1,1,1,1,1,1,1,0},
                      {1,0,0,0,0,0,1,2},
                      {1,0,0,0,0,0,1,2},
                      {1,0,0,0,0,0,1,2},
                      {1,0,0,0,0,0,1,2},
                      {1,1,1,1,1,1,1,2},
                      {2,2,2,2,2,2,2,2},
                      {0,2,2,2,2,2,2,0} };
                      
const uint8_t map5 [8][8]={ {1,1,1,1,1,1,1,0},
                      {1,0,0,0,0,0,1,2},
                      {1,0,0,0,0,0,1,2},
                      {1,0,0,0,0,0,1,2},
                      {1,0,0,0,0,0,1,2},
                      {1,0,0,0,0,0,1,2},
                      {1,1,1,1,1,1,1,2},
                      {0,2,2,2,2,2,2,0} };
                      
const uint8_t map6 [8][8]={ {1,1,1,1,1,1,1,0},
                      {1,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,1},
                      {1,1,1,1,1,1,1,1},
                      {0,2,2,2,2,2,2,0} };
                      
const uint8_t map7 [8][8]={ {1,1,1,1,1,1,1,0},
                      {1,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,1},
                      {1,0,0,0,0,0,0,1},
                      {0,1,1,1,1,1,1,0} };
uint8_t mapS=0;        
uint8_t maps [7][8][8]; 
boolean freeze=false;
boolean mute=false;
uint8_t playMap[8][8];
uint8_t win=3;
uint8_t levels[16] = {0,0,1,1,2,2,3,3,4,4,4,5,5,5,5,6};

const uint8_t numbers [10][13][2]={ { {1,1},{1,2},{1,3},{2,3},{3,3},{4,3},{2,1},{3,1},{4,1},{5,1},{5,2},{5,3},{8,8} },
                              { {2,1},{1,2},{2,2},{3,2},{4,2},{5,1},{5,2},{5,3},{8,8},{8,8},{8,8},{8,8},{8,8} },
                              { {1,1},{1,2},{1,3},{2,3},{3,3},{3,2},{3,1},{4,1},{5,1},{5,2},{5,3},{8,8},{8,8} },
                              { {1,1},{1,2},{1,3},{2,3},{3,3},{3,2},{3,1},{4,3},{5,3},{5,2},{5,1},{8,8},{8,8} },
                              { {1,1},{2,1},{3,1},{3,2},{3,3},{1,3},{2,3},{4,3},{5,3},{8,8},{8,8},{8,8},{8,8} },
                              { {1,3},{1,2},{1,1},{2,1},{3,1},{3,2},{3,3},{4,3},{5,3},{5,2},{5,1},{8,8},{8,8} },
                              { {1,3},{1,2},{1,1},{2,1},{3,1},{4,1},{5,1},{5,2},{5,3},{4,3},{3,3},{3,2},{8,8} },
                              { {1,1},{1,2},{1,3},{5,2},{4,2},{3,2},{2,3},{8,8},{8,8},{8,8},{8,8},{8,8},{8,8} },
                              { {1,1},{1,2},{1,3},{2,3},{3,3},{3,2},{3,1},{2,1},{4,1},{5,1},{5,2},{5,3},{4,3} },
                              { {1,1},{1,2},{1,3},{2,3},{3,3},{2,1},{3,1},{3,2},{4,3},{5,3},{5,2},{5,1},{8,8} } };
                              
const uint8_t muteSymbol [2][25][2] = { { {2,3},{3,3},{3,2},{3,1},{4,3},{5,3},{4,2},{4,1},{1,4},{2,4},{3,4},{4,4},{5,4},{6,4},{8,8},{8,8},{8,8},{8,8},{8,8},{8,8},{8,8},{8,8},{8,8},{8,8} },
                                  { {1,3},{2,3},{3,3},{2,2},{3,2},{3,1},{3,0},{4,3},{5,3},{6,3},{4,2},{5,2},{4,1},{4,0},{3,7},{2,6},{1,5},{3,5},{2,4},{4,7},{5,6},{4,5},{6,5},{5,4} } };
uint8_t nu=0;
uint8_t points=0;

//-----------------------------------------------------------
void setup() {
  Serial.begin(9600);
  Serial.println("Trellis Memory Game");
  randomSeed(analogRead(0));
  // define number of keys
  trellisXY.begin(NKEYS);
  // set up x/y offsets
  trellisXY.setOffsets(0, 0, 0);
  trellisXY.setOffsets(1, 4, 0);
  trellisXY.setOffsets(2, 0, 4);
  trellisXY.setOffsets(3, 4, 4);

  // INT pin requires a pullup
  pinMode(INTPIN, INPUT);
  digitalWrite(INTPIN, HIGH);
  
  memcpy(maps[0], map1, sizeof(map1));
  memcpy(maps[1], map2, sizeof(map2));
  memcpy(maps[2], map3, sizeof(map3));
  memcpy(maps[3], map4, sizeof(map4));
  memcpy(maps[4], map5, sizeof(map5));
  memcpy(maps[5], map6, sizeof(map6));
  memcpy(maps[6], map7, sizeof(map7));

  trellis.begin(0x72, 0x73, 0x70, 0x71);

  updateMap();
}

void loop() {
  delay(30);  
  // If a button was just pressed or released...
  if(!freeze){
    if (trellis.readSwitches()) {
      // go through every button
      for (byte i=0; i < trellisXY.numKeys; i++) {
        byte xValue;
        byte yValue;
        byte xyTrellisID;
        if (trellis.justPressed(i)) {
  
          xValue = trellisXY.getTrellisX(i);
          yValue = trellisXY.getTrellisY(i);
          if(maps[mapS][xValue][yValue]==0){
            // Alternate the LED
            if(win==0){
              if (trellis.isLED(i)) 
                trellis.clrLED(i);
              else
                trellis.setLED(i);
            }
            
            if(xValue==7 && yValue==7){
              trellis.clrLED(i);
              if(mapS<6) mapS++;
              updateMap();
            } 
            else if(xValue==7 && yValue==0){
              trellis.clrLED(i);
              if(mapS>0) mapS--;
              updateMap();
            }
            else if(xValue==0 && yValue==7){
              trellis.clrLED(i);
              trellis.writeDisplay();
              play();
            }else{
              if(win==3) blinkStart();
            }
          }
          if(xValue==1 && yValue==7) muteSwitch();
        }
      }
      
      switch(mapS){
        case 0:
          countLEDS(3, 3, 3);
        break;
        case 1:
          countLEDS(4, 4, 3);
        break;
        case 2:
          countLEDS(5, 4, 4);
        break;
        case 3:
          countLEDS(6, 5, 4);
        break;
        case 4:
          countLEDS(7, 5, 5);
        break;
        case 5:
          countLEDS(8, 6, 5);
        break;
        case 6:
          countLEDS(9, 6, 6);
        break;
        default:
        break;
  }
    }
  }
//  trellis.setLED(trellisXY.getTrellisId(1,1));
  trellis.writeDisplay();
}

void updateMap(){
  trellis.clear();
  for (byte y = 0; y < 8; y++) {
    for (byte x = 0; x < 8; x++) {
      if(maps[mapS][x][y]==1){
        trellis.setLED(trellisXY.getTrellisId(x, y));
      }
    }
  }
  trellis.writeDisplay();
}

void play(){
  freeze=true;
  win=0;
  memset(playMap, 0, sizeof(playMap));
  switch(mapS){
    case 0:
      randomChoose(3, 3, 3, 1000);
    break;
    case 1:
      randomChoose(4, 4, 3, 1500);
    break;
    case 2:
      randomChoose(5, 4, 4, 2000);
    break;
    case 3:
      randomChoose(6, 5, 4, 2000);
    break;
    case 4:
      randomChoose(7, 5, 5, 2500);
    break;
    case 5:
      randomChoose(8, 6, 5, 2500);
    break;
    case 6:
      randomChoose(9, 6, 6, 3000);
    break;
    default:
    break;
  }
  freeze=false;
}

void randomChoose(uint8_t t, uint8_t xx, uint8_t yy, uint8_t te){
  uint8_t conta=0;
  while(conta<t){
    uint8_t x=0;
    uint8_t y=0;
    while( trellis.isLED( trellisXY.getTrellisId(x,y) ) ){
      x=int(random(1,yy+1));
      y=int(random(1,xx+1));
    }
    playMap[x][y]=1;
    trellis.setLED(trellisXY.getTrellisId(x, y)); 
    trellis.writeDisplay();
    conta++;
  }
  delay(te);
  updateMap();
}

void countLEDS(uint8_t t, uint8_t xx, uint8_t yy){
  uint8_t ledsOn=0;
  for (byte y = 1; y < xx+1; y++) {
    for (byte x = 1; x < yy+1; x++) {
      if( trellis.isLED( trellisXY.getTrellisId(x,y) ) ){
        ledsOn++;
      }
    }
  }
  if(ledsOn>=t) checkLEDS(t, xx, yy);
}

void checkLEDS(uint8_t t, uint8_t xx, uint8_t yy){
  for (byte y = 1; y < xx+1; y++) {
    for (byte x = 1; x < yy+1; x++) {
      if( trellis.isLED( trellisXY.getTrellisId(x,y) ) ){
        if( playMap[x][y]==0){
          win=2;
          Serial.println("You Lost!!!!");
        }
      }
    }
  }
  if(win==0){
    win=1;
    Serial.println("You Won!!!!");
    points=t;
    winBlink(xx, yy);
    updateMap();
  }else{
    if(nu>0)points=((t/2)-1);
    lostBlink(xx, yy);
    updateMap();
  }
  win=3;
}

void winBlink(uint8_t xx, uint8_t yy){
  uint8_t counte=0;
  while(counte<3){
    for (byte y = 1; y < xx+1; y++) {
      for (byte x = 1; x < yy+1; x++) {
        if( trellis.isLED( trellisXY.getTrellisId(x,y) ) ){
          trellis.clrLED(trellisXY.getTrellisId(x, y));
        }else{
          trellis.setLED(trellisXY.getTrellisId(x, y));
        }
      }
    }
    trellis.writeDisplay();
    delay(200);
    counte++;
  }
  for (byte y = 1; y < xx+1; y++) {
      for (byte x = 1; x < yy+1; x++) {
        trellis.setLED(trellisXY.getTrellisId(x, y));
      }
  }
  trellis.writeDisplay();
  delay(300);
  for (byte x = 1; x < yy+1; x++) {
      for (byte y = 1; y < xx+1; y++) {
        trellis.clrLED(trellisXY.getTrellisId(x, y));
        trellis.writeDisplay();
        delay(100);
      }
  }
  uint8_t tempNu=nu+points;
  updateNumber();
  delay(200);
  while(nu < tempNu){
    Serial.print(tempNu);Serial.println(points);
    nu++;
    points--;
    updateNumber();
    delay(200);
  }
  if(!mute) playSound();
  delay(1000);
  //mapS++;
}

void updateNumber(){
  trellis.clear();
  for (byte x = 1; x < 7; x++) {
    trellis.setLED(trellisXY.getTrellisId(7, x));
  }
  
  if(nu<10){
    for (uint8_t i = 0; i < 13; i++) {
      if(numbers[nu][i][0]!=8) trellis.setLED(trellisXY.getTrellisId(numbers[nu][i][0], numbers[nu][i][1]));
    }
  }else{
    uint8_t digOne = nu/10, digTwo = nu%10;
    for (uint8_t i = 0; i < 13; i++) {
      if(numbers[digOne][i][0]!=8) trellis.setLED(trellisXY.getTrellisId(numbers[digOne][i][0], numbers[digOne][i][1]));
    }
    for (uint8_t i = 0; i < 13; i++) {
      if(numbers[digTwo][i][0]!=8) trellis.setLED(trellisXY.getTrellisId(numbers[digTwo][i][0], numbers[digTwo][i][1] + 3));
    }
  }
  trellis.writeDisplay();
}

void playSound(){
  uint8_t dur=125;
  if(win==2){//lose
    tone(8, 147, dur);
    delay(dur*1.3);
    tone(8, 131, dur);
    delay(dur*1.3);
    noTone(8);
  }
  if(win==1){//win
    tone(8, 220, dur);
    delay(dur*1.3);
    tone(8, 247, dur);
    delay(dur*1.3);
    noTone(8);
  }
}

void lostBlink(uint8_t xx, uint8_t yy){
  for (byte y = 1; y < xx+1; y++) {
      for (byte x = 1; x < yy+1; x++) {
        trellis.setLED(trellisXY.getTrellisId(x, y));
      }
  }
  trellis.writeDisplay();
  delay(200);
  for (byte y = 0; y < xx+2; y++) {
      for (byte x = 0; x < yy+2; x++) {
        trellis.clrLED(trellisXY.getTrellisId(x, y));
        trellis.writeDisplay();
        delay(50);
      }
  }
  updateNumber();
  delay(200);
  uint8_t tempNu=nu-points;
  while(nu > tempNu){
    Serial.print(tempNu);Serial.println(points);
    nu--;
    points--;
    updateNumber();
    delay(200);
  }
  if(!mute) playSound();
  delay(1000);
}

void blinkStart(){
  for (uint8_t i = 0; i < 4; i++) {
    if(i%2==0){
      trellis.setLED(trellisXY.getTrellisId(0, 7));
      trellis.writeDisplay();
    }else{
      trellis.clrLED(trellisXY.getTrellisId(0, 7));
      trellis.writeDisplay();
    }
    delay(100);
  }
}

void muteSwitch(){
  trellis.clear();
  uint8_t m=(mute)?1:0;
  for (uint8_t i = 0; i < 24; i++) {
      if(muteSymbol[m][i][0]!=8) trellis.setLED(trellisXY.getTrellisId(muteSymbol[m][i][0], muteSymbol[m][i][1]));
  }
  trellis.writeDisplay();
  mute=!mute;
  delay(500);
  updateMap();
}
