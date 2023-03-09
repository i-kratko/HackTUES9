

void setup() {
       
  // put your setup code here, to run once:
Serial.begin(9600);
Serial1.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
String readString;
String Q;

//-------------------------------Check Serial Port---------------------------------------
 
 while (Serial1.available()){
  delay(1);
  if(Serial1.available()>0){
  char c = Serial1.read();
    Serial.print(c);
   if (isControl(c)){
  break;
  }
   
  }
 
 }
 
 
 
 
 
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
      if(Q=="on"){         
        Serial1.print("1");
        Serial.println("Sent:On");               
      }
      if(Q=="off"){         
        Serial1.print("2");  
        Serial.println("Sent:Off");                          
      }



}

