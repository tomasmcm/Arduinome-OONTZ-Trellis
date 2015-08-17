/*

Press top-right corner to get mapping on serial monitor
XY mapping

*/

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
  Keyboard.begin();
}

void loop() {
  delay(30);  
  if (trellis.readSwitches()) {
    for (byte i=0; i < trellisXY.numKeys; i++) {
      byte xValue;
      byte yValue;
      if (trellis.justPressed(i)) {
        xValue = trellisXY.getTrellisX(i);
        yValue = trellisXY.getTrellisY(i);
        if (trellis.isLED(i)) 
          trellis.clrLED(i);
        else
          trellis.setLED(i);

        if(xValue==7 && yValue==7){
          trellis.clrLED(i);
          
          Serial.print("{");
          for (byte i=0; i < trellisXY.numKeys; i++) {
            if (trellis.isLED(i)){
              byte x = trellisXY.getTrellisX(i);
              byte y = trellisXY.getTrellisY(i);
              Serial.print("{");
              Serial.print(x);
              Serial.print(","); 
              Serial.print(y);
              Serial.print("},");
            }
          }
          Serial.println("}");
        }
      } 
    }
    trellis.writeDisplay();
  }
}




