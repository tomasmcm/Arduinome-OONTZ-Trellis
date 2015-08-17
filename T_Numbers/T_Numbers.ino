/*
Numbers Testing

Use lower most left and most right buttons to change number

*/

#include <Wire.h>
#include <Adafruit_Trellis.h>
#include <Adafruit_Trellis_XY.h>

/*************************************************** 
  This example shows reading buttons and setting/clearing buttons in a loop
  Also sending X/Y values to serial port.

  Up to 8 matrices can be used but this example will use 4
 ****************************************************/

Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_Trellis matrix1 = Adafruit_Trellis();
Adafruit_Trellis matrix2 = Adafruit_Trellis();
Adafruit_Trellis matrix3 = Adafruit_Trellis();

Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0, &matrix1, &matrix2, &matrix3);

#define NUMTRELLIS 4
#define NKEYS (NUMTRELLIS * 16)

Adafruit_Trellis_XY trellisXY = Adafruit_Trellis_XY();

#define INTPIN A2

uint8_t numbers [10][13][2]={ { {1,1},{1,2},{1,3},{2,3},{3,3},{4,3},{2,1},{3,1},{4,1},{5,1},{5,2},{5,3},{8,8} },
                              { {2,1},{1,2},{2,2},{3,2},{4,2},{5,1},{5,2},{5,3},{8,8},{8,8},{8,8},{8,8},{8,8} },
                              { {1,1},{1,2},{1,3},{2,3},{3,3},{3,2},{3,1},{4,1},{5,1},{5,2},{5,3},{8,8},{8,8} },
                              { {1,1},{1,2},{1,3},{2,3},{3,3},{3,2},{3,1},{4,3},{5,3},{5,2},{5,1},{8,8},{8,8} },
                              { {1,1},{2,1},{3,1},{3,2},{3,3},{1,3},{2,3},{4,3},{5,3},{8,8},{8,8},{8,8},{8,8} },
                              { {1,3},{1,2},{1,1},{2,1},{3,1},{3,2},{3,3},{4,3},{5,3},{5,2},{5,1},{8,8},{8,8} },
                              { {1,3},{1,2},{1,1},{2,1},{3,1},{4,1},{5,1},{5,2},{5,3},{4,3},{3,3},{3,2},{8,8} },
                              { {1,1},{1,2},{1,3},{5,2},{4,2},{3,2},{2,3},{8,8},{8,8},{8,8},{8,8},{8,8},{8,8} },
                              { {1,1},{1,2},{1,3},{2,3},{3,3},{3,2},{3,1},{2,1},{4,1},{5,1},{5,2},{5,3},{4,3} },
                              { {1,1},{1,2},{1,3},{2,3},{3,3},{2,1},{3,1},{3,2},{4,3},{5,3},{5,2},{5,1},{8,8} } };
int nu=1;

//-----------------------------------------------------------
void setup() {
  Serial.begin(9600);
  Serial.println("Trellis X/Y Demo");

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
  
  // Order is important here!! Start with tile address you want to
  // use as the first one, etc. Note that this will vary depending
  // on how you/ve set up addressing.
  trellis.begin(0x72, 0x73, 0x70, 0x71);

  updateNumber();
  
}

void loop() {
  delay(30);  

  if (trellis.readSwitches()) {
    for (byte i=0; i < trellisXY.numKeys; i++) {
      byte xValue;
      byte yValue;
      byte xyTrellisID;

      if (trellis.justPressed(i)) {
        xValue = trellisXY.getTrellisX(i);
        yValue = trellisXY.getTrellisY(i);
        if(xValue==7 && yValue==0){
          if(nu>0)nu--;
          updateNumber();
        }
        if(xValue==7 && yValue==7){
          if(nu<99)nu++;
          updateNumber();
        }
      }
     } 
  }
  trellis.writeDisplay();
}

void updateNumber(){
  clearAll();
  if(nu<10){
    for (int i = 0; i < 13; i++) {
      if(numbers[nu][i][0]!=8) trellis.setLED(trellisXY.getTrellisId(numbers[nu][i][0], numbers[nu][i][1]));
    }
  }else{
    int digOne = nu/10, digTwo = nu%10;
    for (int i = 0; i < 13; i++) {
      if(numbers[digOne][i][0]!=8) trellis.setLED(trellisXY.getTrellisId(numbers[digOne][i][0], numbers[digOne][i][1]));
    }
    for (int i = 0; i < 13; i++) {
      if(numbers[digTwo][i][0]!=8) trellis.setLED(trellisXY.getTrellisId(numbers[digTwo][i][0], numbers[digTwo][i][1] + 3));
    }
  }
  trellis.writeDisplay();
}

void clearAll(){
  for (byte y = 0; y < 8; y++) {
    for (byte x = 0; x < 8; x++) {
      trellis.clrLED(trellisXY.getTrellisId(x, y));
    }
  }
}

