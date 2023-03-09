

void setup() {
       
  // put your setup code here, to run once:
  pinMode(13,OUTPUT); 
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
String readString;
String Q;

//-------------------------------Check Serial Port---------------------------------------
 while (Serial.available()) {
      delay(1);
    if (Serial.available() >0) {
      char c = Serial.read();  //gets one byte from serial buffer
    if (isControl(c)) {
      //'Serial.println("it's a control character");
      break;
    }
      readString += c; //makes the string readString    
    }
 }   

 Q = readString;
//--------Checking Serial Read----------
      if(Q=="1"){         
        digitalWrite(13,HIGH);               
      }
      if(Q=="2"){         
        digitalWrite(13,LOW);             
      }



}
