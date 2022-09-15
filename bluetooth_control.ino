/*   
    L = Left 
    R = Right 
    F = forward 
    B = backward
    S = stop
*/
int pinLB   = 12;     
int pinLF   = 3;      
int pinRB   = 13;    
int pinRF   = 11;    
int echoPin = 4;    // define pin for sensor echo
int trigPin = 5;    // define pin for sensor trig
int val;

void setup()
 {
  Serial.begin(9600);   
  // define pin for motor output 
  pinMode(pinLB,OUTPUT); // pin 12
  pinMode(pinLF,OUTPUT); // pin 3 (PWM)
  pinMode(pinRB,OUTPUT); // pin 13
  pinMode(pinRF,OUTPUT); // pin 11 (PWM) 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
 }
void advance()       // move forward
    { 
    digitalWrite(pinLB,LOW);    // right wheel moves forward
    digitalWrite(pinRB, LOW);   // left wheel moves forward
    analogWrite(pinLF,255);   
    analogWrite(pinRF,255);
    }
void stopp()         // stop
    {
     digitalWrite(pinLB,HIGH);
     digitalWrite(pinRB,HIGH);
     analogWrite(pinLF,0);
     analogWrite(pinRF,0); 
    }
void right()        // turn right 
    {
     digitalWrite(pinLB,HIGH);  // left wheel moves forward
     digitalWrite(pinRB,LOW);   // right wheel moves backward
     analogWrite(pinLF, 255);
     analogWrite(pinRF,255);   
    }
void left()         // turn left 
    {
     digitalWrite(pinLB,LOW);  // left wheel moves forward
     digitalWrite(pinRB,HIGH); // right wheel moves backward
     analogWrite(pinLF, 255);
     analogWrite(pinRF,255);  
    }
  void back()       // move backward
    {
     digitalWrite(pinLB,HIGH);  // motor moves to left rear
     digitalWrite(pinRB,HIGH);  // motor moves to right rear
     analogWrite(pinLF,255);  
     analogWrite(pinRF,255);     
    }

void directionInput()
    { 
      val=Serial.read(); 
      if(val=='F')advance();
      if(val=='B')back();
      if(val=='L'){left(); delay(200);stopp();}
      if(val=='R'){right();delay(200);stopp();}
      if(val=='S')stopp();
}

void loop()
    { 
      // detect collision
      long duration, Distance;
      digitalWrite(trigPin, LOW); 
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      Distance = (duration/2) / 74;     // Distance in Inches
      if (Distance < 10) { 
        stopp();
        delay(200);
        left();
        delay(800);
        stopp();
      }
      directionInput();
    }
