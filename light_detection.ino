#include <Wire.h>
#include <SoftwareSerial.h>
#define ADDR 0x23
int bluetoothTx = 11; // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 12; // RX-I pin of bluetooth mate, Arduino D3
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
#define PIN 13
int time = millis();
#define LEDR 5
#define LEDG 6
#define LEDB 9
void turnoff(){
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, LOW);
}

void setup()
{
Serial1.begin(9600); 
Serial.begin(9600);
pinMode(PIN, OUTPUT);
//
Wire.begin();
Wire.beginTransmission(ADDR);
Wire.write(0b00000001);
Wire.endTransmission();


bluetooth.begin(115200); // Start bluetooth serial at 9600

 //pinMode(LEDR, 255);
 // pinMode(LEDG, 255);
 // pinMode(LEDB, 255);
  //turnoff();
Serial1.print(0);
}



void loop()
{
int val = 0;
 
// reset
  Wire.beginTransmission(ADDR);
  Wire.write(0b00000111);
  Wire.endTransmission();
  digitalWrite(PIN, LOW);
  delay(100);

  Wire.beginTransmission(ADDR);
  Wire.write(0b00100000);
  Wire.endTransmission();
  // typical read delay 120ms
  delay(120);
  Wire.requestFrom(ADDR, 2); // 2byte every time
  for (val=0; Wire.available()>=1; )
  {
  char c = Wire.read();
  val = (val << 8) + (c & 0xFF);
  }
  val = val / 1.2;
// Serial.print("lx: ");
 // Serial.println(val);
 // Serial.println("OK");
 // digitalWrite(PIN, HIGH);
 delay(500);


Serial1.print((char)Serial.read());
//Serial.println(bluetooth.read());

  byte cmmd[20];
  int insize; 
  int x;
   
   
       int sendData = (int)val;
	byte packet[3]; 
        packet[0] = 97; //key send to phone
	packet[1] = sendData/256 ; //divides sendData to two 1 byte packets
	packet[2] = sendData % 256;  
  if(bluetooth.available() > 0) //check BT is succeed
		if(char(bluetooth.read()) == 100) //check recieve key from phone
		{
			//Serial.println("succeed!");
			for(int i = 0; i < 3; i++) 
				bluetooth.write(packet[i]); //send packet to phone
		}
 if ((insize=(bluetooth.available()))>0){ //讀取藍牙訊息
  //   Serial.print("input size = ");
   //  Serial.println(insize);
      for (int i=0; i<insize; i++){
        Serial.println(cmmd[i]=char(bluetooth.read()));
    //    Serial.print(" ");
   // delay(100);
      }//此段請參考上一篇解釋
 }
    switch (cmmd[0]) { //讀取第一個字
  //  delay(500);
    case 97: //97為"a"的ASCII CODE
      Serial.println("on");
      Serial1.print(5); //點亮LED
      break;

    case 98://98為"b"的ASCII CODE
      Serial.println("off");
     Serial1.print(0); //熄滅LED
     
      break;
/*     case 100: //d
    // Serial.println("succeed!");
  	
      for(int i = 0; i < 3; i++) {
	   bluetooth.write(packet[i]); 
      }   
     break;*/
      case 101://e
      Serial1.print(4);//臥房
      break;
      case 102://f
      Serial1.print(6);//書房
      break;
      case 103://g
      Serial1.print(3);//廚房
      break;
      case 104://h
      Serial1.print(4);//客廳
      break;
      case 105://i
      Serial1.print(2);//廁所
      break;
      case 106://j
      Serial1.print(1);//走廊樓梯
      break;
      case 107://k
      Serial1.print(8);//　縫紉
      break;
      case 108://l
      Serial1.print(7);//化妝
      break;
      case 109://　m
      Serial1.print(5);//
      break;
      case 65://RED
      analogWrite(LEDR,0);
      analogWrite(LEDG,255);
      analogWrite(LEDB,255);
      break;
       case 66://ORANGE
      analogWrite(LEDR,10);
      analogWrite(LEDG,230);
      analogWrite(LEDB,255);
      break;
       case 67://YELLOW
      analogWrite(LEDR,80);
      analogWrite(LEDG,199);
      analogWrite(LEDB,255);
      break;
       case 68://GREEN
      analogWrite(LEDR,255);
      analogWrite(LEDG,0);
      analogWrite(LEDB,255);
      break;
      case 69://BLUE
      analogWrite(LEDR,255);
      analogWrite(LEDG,0);
      analogWrite(LEDB,0);
      break;
      case 70://靛
      analogWrite(LEDR,255);
      analogWrite(LEDG,255);
      analogWrite(LEDB,0);
      break;
       case 71://紫
      analogWrite(LEDR,0);
      analogWrite(LEDG,255);
      analogWrite(LEDB,0);
      break;
        case 72://NONE
      analogWrite(LEDR,255);
      analogWrite(LEDG,255);
      analogWrite(LEDB,255);
      break;
    } //Switch 
    
 
  String s = "";
    while (Serial1.available()) {
        char c = Serial1.read();
        if(c!='\n'){
            s += c;
        }
        //delay(500);    // 沒有延遲的話 UART 串口速度會跟不上Arduino的速度，會導致資料不完整
    }
   if(s == "1")  Serial.println("led is ok");

}

