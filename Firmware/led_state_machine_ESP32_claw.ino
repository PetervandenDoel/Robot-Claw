#define LED 32
#define LIMIT_SWITCH 22
#define STOCCO_RESET 12
// defines pins numbers
volatile float desired_position = 0.0;
#define RESET 21
int settled_flag = 0;

const int trigPin = 33;
const int echoPin = 34;
// defines variables
long duration;
int distance;

volatile int LEDcounter=0;

volatile char state[20];
#include <Timer.h>
//#define ENCA 4 //YELLOW
//#define ENCB 2 //WHITE
#define IN1 4  //H-bridge
#define IN2 15  //H-bridge
#define EN 19 //PWM
#define OE 13
#define SEL1 2
#define SEL2 27
#define RST 26
#define A 25
#define B 5
#define C 18
#define MUXIN 35
#include <math.h>


//variables
Timer timer;


//THIS NEEDS TO BE GLOBAL OR VOLATILE ???THIS PREVT VARIABLE 


long prevT = 0;
float eprev = 0;
volatile float eintegral = 0;
//int Flag = 0;
int i;
int byte11[8];
int byte21[8];
int byte31[8];
int byte41[8];
int bytetot[32];
int ppr=0;
volatile long totalcount=0;






void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(LED,OUTPUT);
  Serial.begin(115200); // Starts the serial communication
  pinMode(RESET,INPUT); 
  pinMode(LIMIT_SWITCH, INPUT);



  // configure ISR to run every 100 milliseconds
  timer.every(100, timerISR);
  //pinMode(ENCA, INPUT_PULLUP);
  //pinMode(ENCB, INPUT_PULLUP);
  pinMode(EN, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  //analogWriteFrequency(5000);

  pinMode(OE,OUTPUT);
  pinMode(SEL1,OUTPUT);
  pinMode(SEL2,OUTPUT);
  pinMode(RST,OUTPUT);

  //MULTIPLEXER I/O DEFINITIONS
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(MUXIN,INPUT);

  pinMode(STOCCO_RESET,INPUT);

 //RESET
 
 reset_decoder();
 /*
  digitalWrite(RST,LOW);
  delayMicroseconds(10);
  digitalWrite(RST,HIGH);
*/
}


void reset_decoder(){
  digitalWrite(RST,LOW);
  delayMicroseconds(10);
  digitalWrite(RST,HIGH);
  
  }

// interfacing with multiplexers on PCB to get one byte of data from decoder pins

byte getByte(){
  byte by1=0;
  byte by2=0;
  while(1){
    
    //read first byte

    digitalWrite(C,LOW);
    digitalWrite(B,LOW);
    digitalWrite(A,LOW);    
    delayMicroseconds(1);
    by1 |= (digitalRead(MUXIN)<<0);
    digitalWrite(C,LOW);
    digitalWrite(B,LOW);
    digitalWrite(A,HIGH);    
    delayMicroseconds(1);
    by1 |= (digitalRead(MUXIN)<<1);
    digitalWrite(C,LOW);
    digitalWrite(B,HIGH);
    digitalWrite(A,LOW); 
    delayMicroseconds(1);   
    by1 |= (digitalRead(MUXIN)<<2);
    digitalWrite(C,LOW);
    digitalWrite(B,HIGH);
    digitalWrite(A,HIGH);
    delayMicroseconds(1);    
    by1 |= (digitalRead(MUXIN)<<3);
    digitalWrite(C,HIGH);
    digitalWrite(B,LOW);
    digitalWrite(A,LOW); 
    delayMicroseconds(1);   
    by1 |= (digitalRead(MUXIN)<<4);
    digitalWrite(C,HIGH);
    digitalWrite(B,LOW);
    digitalWrite(A,HIGH);
    delayMicroseconds(1);    
    by1 |= (digitalRead(MUXIN)<<5);
    digitalWrite(C,HIGH);
    digitalWrite(B,HIGH);
    digitalWrite(A,LOW); 
    delayMicroseconds(1);   
    by1 |= (digitalRead(MUXIN)<<6);
    digitalWrite(C,HIGH);
    digitalWrite(B,HIGH);
    digitalWrite(A,HIGH);
    delayMicroseconds(1);    
    by1 |= (digitalRead(MUXIN)<<7);
      

    //READ BYTE SECOND TIME TO SEE IF ITS STABLE

    digitalWrite(C,LOW);
    digitalWrite(B,LOW);
    digitalWrite(A,LOW);    
    delayMicroseconds(1);
    by2 |= (digitalRead(MUXIN)<<0);
    digitalWrite(C,LOW);
    digitalWrite(B,LOW);
    digitalWrite(A,HIGH);    
    delayMicroseconds(1);
    by2 |= (digitalRead(MUXIN)<<1);
    digitalWrite(C,LOW);
    digitalWrite(B,HIGH);
    digitalWrite(A,LOW); 
    delayMicroseconds(1);   
    by2 |= (digitalRead(MUXIN)<<2);
    digitalWrite(C,LOW);
    digitalWrite(B,HIGH);
    digitalWrite(A,HIGH);
    delayMicroseconds(1);    
    by2 |= (digitalRead(MUXIN)<<3);
    digitalWrite(C,HIGH);
    digitalWrite(B,LOW);
    digitalWrite(A,LOW); 
    delayMicroseconds(1);   
    by2 |= (digitalRead(MUXIN)<<4);
    digitalWrite(C,HIGH);
    digitalWrite(B,LOW);
    digitalWrite(A,HIGH);
    delayMicroseconds(1);    
    by2 |= (digitalRead(MUXIN)<<5);
    digitalWrite(C,HIGH);
    digitalWrite(B,HIGH);
    digitalWrite(A,LOW); 
    delayMicroseconds(1);   
    by2 |= (digitalRead(MUXIN)<<6);
    digitalWrite(C,HIGH);
    digitalWrite(B,HIGH);
    digitalWrite(A,HIGH);
    delayMicroseconds(1);    
    by2 |= (digitalRead(MUXIN)<<7);
      
      
       
    
    //only break loop if equal

    if(by1==by2){
      break;
        }
    
    }
    //we know its stable
    return by1;
  
}


//interfacing with decoder's internal multiplexers to get stored position value from motor decoder
float get_position(){
  byte byte1=0;
  byte byte2=0;
  byte byte3=0;
  byte byte4=0;
  
  //data

  //store in latches

 
 digitalWrite(OE,HIGH);
 delay(25);

  digitalWrite(SEL1,LOW);
  digitalWrite(SEL2,HIGH);
  
 digitalWrite(OE,LOW);
 //now we ready
//-------------------------------------------------Capturing MSB 
  //select byte 1

  //ready to get MSB

  byte1=getByte();
  
//-------------------------------------------------Capturing 2 byte 

  digitalWrite(SEL1,HIGH);
  digitalWrite(SEL2,HIGH);
  //delayMicroseconds(10);    

  
  //ready to get 2nd byte
  byte2=getByte();
  
//-------------------------------------------------Capturing 3 byte 
  digitalWrite(SEL1,LOW);
  digitalWrite(SEL2,LOW);   

  //ready to get 3rd byte
  byte3=getByte();
    
//-------------------------------------------------Capturing 4 byte 
  digitalWrite(SEL1,HIGH);
  digitalWrite(SEL2,LOW);   
  
  //ready to get LSB
  
  byte4=getByte();
 
 digitalWrite(OE,HIGH);
 delay(25);
    //print

long total=0;


//combining bytes with proper place values
total=((long)byte1<<24)|((long)byte2<<16)|((long)byte3<<8)|((long)byte4<<0);

totalcount = total;

float revolutions = 0;

revolutions=(totalcount)/(4.0*34.0*360.0);



Serial.println(revolutions);
return revolutions ;
}


void setMotorPos(int flag, int pwmVal, int pwm, int in1, int in2) {
  
  if (flag == 1) {
    motor_forwards();
  } else if (flag == -1) {
    motor_backwards();
  } else {
    motor_stop();
  }
  
  analogWrite(EN, pwmVal);
}


void motor_forwards() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void motor_backwards(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void motor_stop(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}



//using ultrasonic sensor to get distance from ground
float get_distance(float prev_d) {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  //Serial.print("Distance: ");
  //Serial.println(distance);
  if(distance>200){ //it spiked
    return (float) prev_d;
    }
    //Serial.println( distance);
  return (float)distance;
}


// different states for the robot claw's state machine

void object_origin(){
  desired_position = 0.11;
  timer.update();

  if (LEDcounter %10 == 0){
    digitalWrite(LED,HIGH);
  }
  
  //delay(700);
  if (LEDcounter % 10 == 7){
    digitalWrite(LED,LOW);
  }
  //delay(300);
  Serial.println("object origin");

}
void closing_object(){
  
  desired_position = 0.2;
  timer.update();
  //Serial.print("LED counter is ");
  //Serial.println(LEDcounter);
  if(LEDcounter%10==0){
    digitalWrite(LED, HIGH);
  }
  //delay(100);
  if (LEDcounter % 10 == 1){
    digitalWrite(LED, LOW);
  }
  //delay(900);
  Serial.println("closing");

}

void grasping_object(){
  
  desired_position = 1;
  timer.update();
  //Serial.print("LED counter is ");
  //Serial.println(LEDcounter);
  if(LEDcounter%10==0){
    digitalWrite(LED, HIGH);
  }
  //delay(100);
  if (LEDcounter % 10 == 1){
    digitalWrite(LED, LOW);
  }
  //delay(900);
  Serial.println("grasping");

}

void object_destination(){
  desired_position = 1;
  timer.update();  //MAYBE??????
  if(LEDcounter%10 == 0){
    digitalWrite(LED, HIGH);
  }
  //delay(400);
  if(LEDcounter %10 == 4){
    digitalWrite(LED, LOW);
  }
  //delay(600);
  Serial.println("destination");

}

void releasing_object(){
  desired_position = 0.11;
  timer.update();
  
  digitalWrite(LED, HIGH);
  //delay(1000);
  Serial.println("releasing");

}


// PID control loop that is triggered by a timer ISR at the control frequency
void timerISR()
{
 
    
    //delay(1);

    // this LED counter variable uses the control frequency to control the duty cycle of a blinking LED without having to use another one of the arduino IDE's limited configurable 
    //interrupts
    LEDcounter++;
    
    float pos = get_position();

    //PID constants
    float kp = 1050;
    float kd = 100;
    //float kd=0.0;
    float ki = 2.8;
    int start_time = micros();
    settled_flag = 0;

    //time difference
    //long currT = micros();
    //long et = currT - prevT;
    float deltaT = 10;
    //float deltaT = ((float)(currT - prevT))/1.0E4;
//    Serial.print("CurrT: ");
//    Serial.println(currT);
//    Serial.print("PRevT is: ");
//    Serial.println(prevT);
//    Serial.print("delta T value: ");
//    Serial.println(deltaT);
//    prevT = currT;
    //Serial.print("Calculation time difference");
    //Serial.println(micros()-start_time);
 

    //error
    start_time = micros();
    float e = pos - desired_position;
    if (fabs(e) > 0.016) {
    //finite difference derivative
    float dedt = (e - eprev)/deltaT;

    //integral
    eintegral = eintegral + e*deltaT;

    //control signal
    float u = kp*e + kd*dedt + ki*eintegral;

    //motor power
    float pwr = fabs(u);
    //Serial.print("Error calculation time");
   // Serial.println(micros()-start_time);

    start_time = micros();

    //Locking our duty cycle between 60 and 220
    if (pwr > 220) {
      pwr = 220;    } 
    if (pwr<60){
      pwr=60;
      }

    //motor direction
    int dir = 1;
    if (u < 0) {
      dir = -1;
    }
    
    //signal the motor
    setMotorPos(dir, pwr, EN, IN1, IN2);

    //store previous error
    eprev = e;


    // lots of debug print statements
    Serial.print("Desired position is: ");
    Serial.println(desired_position);
    Serial.print(" ");
    Serial.print("position is: ");
    Serial.println(pos);
    Serial.print(" ");
    Serial.print("Power motor is getting: ");
    Serial.println(pwr);
    Serial.print("error is ");
    Serial.println(e);
    Serial.print("proportional contiburtion ");
    Serial.println(kp*e);
    Serial.print("derivitave contributoin ");
    Serial.println(kd*dedt);
    Serial.print("integral contribution ");
    Serial.println(ki*eintegral);
    Serial.print("control signal is ");
    Serial.println(u);

//    Serial.print("Rest of program");
//    Serial.println(micros()-start_time);
   
    }
    else{
      settled_flag = 1;
    }
    Serial.print("settled flag is: ");
    Serial.println(settled_flag);
}




//State machine based on distance sensor

void loop() {
  float d=70;
  d=get_distance(d);

  Serial.println(distance);

  while(1){
    Serial.println("waitng for stocco");
//    this is for stocco pressing the reset button on his computer
    if(digitalRead(STOCCO_RESET)==1){
      break;
      
      }
  }

  while(1){               //this is for the calibration state, move until limit switch is hit
    
    analogWrite(EN,150);
    //150/255 duty cycle

    motor_forwards();
     d = get_distance(d);
     Serial.println(d);
     Serial.print("Eintegral is: ");
     Serial.println(eintegral);

    if (digitalRead(LIMIT_SWITCH)){
      // making sure limit switch has been pressed for some time
      delay(10);
      if (digitalRead(LIMIT_SWITCH)){
        Serial.println("stopping motor");
        motor_stop();
        reset_decoder();
        Serial.println("decoder reset");
        //delay(1000);
        break;
      }
    }
  }
  eintegral=0.0;
       Serial.print("Eintegral is: ");
     Serial.println(eintegral);

  //label for gotostatement
  open:
  while(1){
    d = get_distance(d);
    Serial.println(d);
    //eintegral = 0;
    Serial.print("Eintegral is: ");
    Serial.println(eintegral);
    

    if (d > 20){
      
      object_origin();
    }
    else break;
  }

  Serial.println("ready to start closing");
  delay(5000);
  //reset integral for new PID target
  eintegral=0.0;
  
  while(1){
    d = get_distance(d);
    Serial.println(d);
    closing_object();
    if (settled_flag == 1){
      delay(500);
      break; 
    }
  }

Serial.println(5);
delay(1000);
for(int index=1;index<5;index++){
    Serial.println(5-index);
    delay(1000);
}
//reset integral for new PID target
eintegral=0.0;  
  
  while(1){
    d = get_distance(d);
      //Serial.println(d);
    if (d < 70){ //this is holding the object on the ground
      grasping_object();
    }
    else break;
  }
  
  while(1){
    d = get_distance(d);
          Serial.println(d);
    if (d > 20){ //this is holding it in the air
      object_destination();
    }
    else break;
  }

//reset integral for new PID target
eintegral=0.0;
  
  while(1){
    d = get_distance(d);
          Serial.println(d);
    if (d < 70){ //ready to release on the ground
      releasing_object();
    }
    else{
      
    goto open;
    break;
    }
  }



  
}
