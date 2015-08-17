/*

Press top-right corner to get mapping on serial monitor
Binary Mapping

*/


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
          for (byte y = 0; y < 8; y++) {
            Serial.print("{");
            for (byte x = 0; x < 8; x++) {
              if(trellis.isLED(trellisXY.getTrellisId(x, y))){
                Serial.print("1");
                if(x<7)Serial.print(",");
              }else{
                Serial.print("0");
                if(x<7)Serial.print(",");
              }
            }
            Serial.print("}");
            if(y<7)Serial.println(",");
            else Serial.println("");
          }
         Serial.println("} \n");
        }
      } 
    }
    trellis.writeDisplay();
  }
}




