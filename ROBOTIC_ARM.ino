#include <Servo.h>

#define numofValsRec 5
#define digitsPerValRec 1

Servo Thumb;
Servo Index;
Servo Middle;
Servo Ring;
Servo Pinky;


int valsRec[numofValsRec];
int stringLength = numofValsRec * digitsPerValRec + 1;
int counter = 0;
bool counterStart = false;
String receivedString;




void setup() {
  Serial.begin(9600);
  Thumb.attach(11);
  Index.attach(5);
  Middle.attach(6);
  Ring.attach(9);
  Pinky.attach(10);
}

void receiveData(){
  while(Serial.available()){
    char c = Serial.read();
    if(c == '$'){
      counterStart = true;
    }
    if(counterStart){
      if(counter < stringLength){
        receivedString = String(receivedString + c);
        counter++;
      }
      if(counter >= stringLength){
        for(int i = 0; i < numofValsRec; i++){
          int num = (i * digitsPerValRec) + 1;
          valsRec[i] = receivedString.substring(num, num + digitsPerValRec).toInt();
        }
        receivedString = "";
        counter = 0;
        counterStart = false;
      }
    }
  }
}
void loop() {
    Serial.println();
  receiveData();
  Serial.print(valsRec[0]);
    Serial.print(valsRec[1]);
    Serial.print(valsRec[2]);
    Serial.print(valsRec[3]);
    Serial.print(valsRec[4]);
  if(valsRec[0] == 1){
    Thumb.write(180);
  }
  else{
    Thumb.write(140);
  }

if(valsRec[1] == 1){
      Index.write(0);
  }
  else{
      Index.write(180);
  }

  if(valsRec[2] == 1){
      Middle.write(0);
  }
  else{
      Middle.write(180);
  }

  if(valsRec[3] == 1){
      Ring.write(180);
  }
  else{
      Ring.write(0);
  }

  if(valsRec[4] == 1){
      Pinky.write(180);
  }
  else{
      Pinky.write(0);
  }
}
