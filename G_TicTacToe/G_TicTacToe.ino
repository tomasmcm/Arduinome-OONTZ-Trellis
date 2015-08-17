/*************************************************** 
 * This is a test example for the Adafruit Trellis w/HT16K33 
 * Added Adafruit_Trellis_XY library
 * Print out X/Y values...
 * 
 * G. Kuetemeyer
 * 03/20/2014
 * gk@pobox.com
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

/*************************************************** 
 * This example shows reading buttons and setting/clearing buttons in a loop
 * Also sending X/Y values to serial port.
 * 
 * Up to 8 matrices can be used but this example will use 4
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

uint8_t stripes [8][8]={ 
  {
    0,0,1,0,0,1,0,0   }
  ,
  {
    0,0,1,0,0,1,0,0   }
  ,
  {
    1,1,1,1,1,1,1,1   }
  ,
  {
    0,0,1,0,0,1,0,0   }
  ,
  {
    0,0,1,0,0,1,0,0   }
  ,
  {
    1,1,1,1,1,1,1,1   }
  ,
  {
    0,0,1,0,0,1,0,0   }
  ,
  {
    0,0,1,0,0,1,0,0   }
};

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

  for (byte y = 0; y < 8; y++) {
    for (byte x = 0; x < 8; x++) {
      if(stripes[x][y]==1){
        trellis.setLED(trellisXY.getTrellisId(x, y));
      }
    }
  }
  trellis.writeDisplay();
}

void loop() {
  delay(30);  
  // If a button was just pressed or released...
  if (trellis.readSwitches()) {
    // go through every button
    for (byte i=0; i < trellisXY.numKeys; i++) {
      byte xValue;
      byte yValue;
      byte xyTrellisID;
      if (trellis.justPressed(i)) {

        xValue = trellisXY.getTrellisX(i);
        yValue = trellisXY.getTrellisY(i);
        if(stripes[xValue][yValue]!=1){
          // Alternate the LED
          if (trellis.isLED(i)) 
            trellis.clrLED(i);
          else
            trellis.setLED(i);
        }
      }
    } 
  }
  trellis.writeDisplay();
}





