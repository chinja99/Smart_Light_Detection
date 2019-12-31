#include <SoftwareSerial.h> 

  int led =10;
  // the setup routine runs once when you press reset:
  // 關閉LED

     
  char c;
void setup() {
// initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  Serial.begin(9600); // Begin the serial monitor at 9600bps
  Serial1.begin(9600); // Begin the hardware serial at 9600bps for UART
analogWrite(led,255);


}
  // the loop routine runs over and over again forever:
void loop() {

  if(Serial1.available()) // If stuff was typed in the serial monitor
  {
  // Send any characters the Serial monitor prints to the hardware serial
   c = (char)Serial1.read();
    Serial.print(c);
          LED(c);        
          delay(100);     
  }
} 
void LED(char c) {

          switch(c)
          {
            case '0':    analogWrite(led,255); Serial1.print(1);   break;
            case '1':    analogWrite(led,205); Serial1.print(1);   break;//65 LX
            case '2':    analogWrite(led,175); Serial1.print(1);   break; //437 LX
            case '3':    analogWrite(led,180); Serial1.print(1);   break;//346 LX
            case '4':    analogWrite(led,185); Serial1.print(1);    break; //252LX
            case '5':    analogWrite(led,190); Serial1.print(1);    break; //187LX
            case '6':    analogWrite(led,160);  Serial1.print(1);   break; //590 LX
            case '7':    analogWrite(led,155);  Serial1.print(1);   break; //634 LX
            case '8':    analogWrite(led,0);  Serial1.print(1);   break;//1108 LX
          }
}
