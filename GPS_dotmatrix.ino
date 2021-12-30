#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();
#include <Adafruit_GPS.h>
#include <HardwareSerial.h>
//SoftwareSerial mySerial(3, 2);
//HardwareSerial mySerial = Serial;
Adafruit_GPS GPS(&Serial1);
#define GPSECHO  false
boolean usingInterrupt = false;
void useInterrupt(boolean); // Func prototype keeps Arduino 0023 happy
byte pos = 0;
int angle = 500;
int speed = 00;
int avg = 0;
uint8_t spones, sptens, sphund;

//Light Variables
int sensorPin = A0; // select the input pin for LDR
int light = 0;
int backl = 20;

int lux = 0;
float rawRange = 1024;
float logRange = 5.0; // 3.3v = 10^5 lux


void setup()  
{
    //Wire.begin(4, 5);
    Wire.begin();

  
  matrix.begin();
  matrix.clear();


  //zero();

//  Serial.begin(19200);


  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
//  GPS.begin(9600);
  GPS.begin(19200);
  
  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
 // GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time
  
  GPS.sendCommand("$PMTK251,19200*22");

 
  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_10HZ);   // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz

  // Request updates on antenna status, comment out to keep quiet
  //GPS.sendCommand(PGCMD_ANTENNA);

  // the nice thing about this code is you can have a timer0 interrupt go off
  // every 1 millisecond, and read data from the GPS for you. that makes the
  // loop code a heck of a lot easier!
  //useInterrupt(true);

  delay(1000);
  // Ask for firmware version
  Serial1.println(PMTK_Q_RELEASE);
matrix.clear();
 working();
}


// Interrupt is called once a millisecond, looks for any new GPS data, and stores it



uint32_t timer = millis();


void loop()                     // run over and over again
{
  //working();
   // read data from the GPS in the 'main loop'
    char c = GPS.read();
    // if you want to debug, this is a good time to do it!

  
  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences! 
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    //Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false
  
    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
  }
  // if millis() or timer wraps around, we'll just reset it
  if (timer > millis())  timer = millis();
  // approximately every 2 seconds or so, print out the current stats
  if (millis() - timer > 100) { 
    timer = millis(); // reset the timer

//Light calculation
light = analogRead(sensorPin);
//old value -  backl = map(constrain(light, 350, 1250),350, 2000, 5, 255);
//backl = map(constrain(light, 50, 1024), 50, 750, 3, 255);
 avg = map(constrain(light, 350, 1024),350, 1024, 3, 255);
 //averaging backlight values to fix streetlight issue
backl = (avg + (backl)) / 2;
//avg = avg / 2;



//lux = RawToLux(light);
//backl = map(constrain(lux, 3000, 55000), 3, 55000, 3, 255);
  


     //  GPS.angle = (int) angle;
                 
  
 
   sphund = speed/100;
   sptens = speed%100/10;
   spones = speed%10;
   
          
   
  matrix.clear();
  
  // ~~~SPEED ONES DISPLAY~~~
  
   pos = 9;

 if (spones == 1){
one();
  }
  else if (spones == 2){
two();
  }
  else if (spones == 3){
three();
  }
  else if (spones == 4){
four();
  }
  else if (spones == 5){
five();
  }
  else if (spones == 6){
six();
  }
  else if (spones == 7){
seven();
  }
  else if (spones == 8){
eight();
  }
  else if (spones == 9){
nine();
  }
  else if (spones == 0){
zero();
  }
  else {
;
  }
  
  
  // ~~~SPEED TENS DISPLAY~~~
  
   pos = 5;
 
           
     
   
 if (sptens == 1){
one();
  }
  else if (sptens == 2){
two();
  }
  else if (sptens == 3){
three();
  }
  else if (sptens == 4){
four();
  }
  else if (sptens == 5){
five();
  }
  else if (sptens == 6){
six();
  }
  else if (sptens == 7){
seven();
  }
  else if (sptens == 8){
eight();
  }
  else if (sptens == 9){
nine();
  }
  else if (sptens == 0){
zero();
  }
  else {
;
  }
  

  // ~~~SPEED HUNDRED DISPLAY~~~
  
pos = 1;

  if (sphund == 0){
;
  }
  else if (sphund == 1){
one();
  }
  else if (sphund == 2){
two();
  }
  else {
;
  }
  
 // ~~~DIRECTION DISPLAY~~~
  if (speed == 00){
  ;
  }
  else if (angle < 23){
  pos = 1;
  north();
  }

  else if (angle < 68){
  pos = 1;
  north();
  pos = 8;
  east();   
  }

  else if (angle < 113){
  pos = 1;
  east();   
  }
 
  else if (angle < 158){
  pos = 1;
  south();  
  pos = 8;
  east();   
  }
 
  else if (angle < 202){
  pos = 1;
  south();  
  }
  
  else if (angle < 247){
  pos = 1;
  south();  
  pos = 8;
  west();
  }

  else if (angle < 293){
  pos = 1;
  west(); 
  }

  else if (angle < 338){
  pos = 1;
  north();  
  pos = 8;
  west();
  }

  else if (angle < 361){
  pos = 1;
  north();
  }
  else {
   pos = 1;
   east();
   pos = 8;
   arr();
   pos = 11;
   arr();
  }
  
//    Serial.print("\nTime: ");
//    Serial.print(GPS.hour, DEC); Serial.print(':');
//    Serial.print(GPS.minute, DEC); Serial.print(':');
//    Serial.print(GPS.seconds, DEC); Serial.print('.');
 //   Serial.println(GPS.milliseconds);
//    Serial.print("Arduino Angle: "); Serial.println(angle);
//    Serial.print("Date: ");
//    Serial.print(GPS.day, DEC); Serial.print('/');
//    Serial.print(GPS.month, DEC); Serial.print("/20");
//    Serial.println(GPS.year, DEC);
//    Serial.print("Fix: "); Serial.println((int)GPS.fix);
//    Serial.print("quality: "); Serial.println((int)GPS.fixquality); 
//    Serial.print("Raw value: ");Serial.println(light); //prints the values coming from the sensor on the screen
//    Serial.print("lux: ");Serial.println(lux); //prints the values coming from the sensor on the screen
//    Serial.print("Backlight Value: ");Serial.println(backl); //prints the values coming from the sensor on the screen
//    Serial.print("hundreds:  "); Serial.println(sphund);
//    Serial.print("tens:  "); Serial.println(sptens);
//    Serial.print("ones:  "); Serial.println(spones);
  
  
    if (GPS.fix) {
      angle = (int)GPS.angle;  
      speed = (GPS.speed) * 1.15078;
      
//      Serial.print("Speed (knots): "); Serial.println(GPS.speed); Serial.println(speed);
//      Serial.print("Angle: "); Serial.println((int)GPS.angle);
//      Serial.print("Altitude: "); Serial.println(GPS.altitude);
//      Serial.print("Satellites: "); Serial.println((int)GPS.satellites); 
//      Serial.println(" . "); Serial.println(" ");


    }
    

  }
}

void one(){
matrix.drawPixel(pos, 4, backl);
matrix.drawPixel(pos, 7, backl);
matrix.drawPixel(pos + 1, 4, backl);
matrix.drawPixel(pos + 1, 5, backl);
matrix.drawPixel(pos + 1, 6, backl);
matrix.drawPixel(pos + 1, 7, backl);
matrix.drawPixel(pos + 1, 8, backl);
matrix.drawPixel(pos + 2, 4, backl);
}

void two(){
matrix.drawPixel(pos, 4, backl);
matrix.drawPixel(pos, 5, backl);
matrix.drawPixel(pos, 6, backl);
matrix.drawPixel(pos, 8, backl);
matrix.drawPixel(pos + 1, 4, backl);
matrix.drawPixel(pos + 1, 6, backl);
matrix.drawPixel(pos + 1, 8, backl);
matrix.drawPixel(pos + 2, 4, backl);
matrix.drawPixel(pos + 2, 6, backl);
matrix.drawPixel(pos + 2, 7, backl);
matrix.drawPixel(pos + 2, 8, backl);
}

void three(){
matrix.drawPixel(pos, 8, backl);
matrix.drawPixel(pos, 6, backl);
matrix.drawPixel(pos, 4, backl);
matrix.drawPixel(pos + 1, 8, backl);
matrix.drawPixel(pos + 1, 6, backl);
matrix.drawPixel(pos + 1, 4, backl);
matrix.drawPixel(pos + 2, 8, backl);
matrix.drawPixel(pos + 2, 7, backl);
matrix.drawPixel(pos + 2, 6, backl);
matrix.drawPixel(pos + 2, 5, backl);
matrix.drawPixel(pos + 2, 4, backl);
}

void four(){

matrix.drawPixel(pos, 6, backl);
matrix.drawPixel(pos, 7, backl);
matrix.drawPixel(pos, 8, backl);
matrix.drawPixel(pos + 1, 6, backl);
matrix.drawPixel(pos + 2, 7, backl);
matrix.drawPixel(pos + 2, 4, backl);
matrix.drawPixel(pos + 2, 5, backl);
matrix.drawPixel(pos + 2, 6, backl);
}

void five(){
matrix.drawPixel(pos, 4, backl);
matrix.drawPixel(pos, 6, backl);
matrix.drawPixel(pos, 7, backl);
///matrix.drawPixel(pos, 8, backl);
matrix.drawPixel(pos + 1, 4, backl);
matrix.drawPixel(pos + 1, 6, backl);
matrix.drawPixel(pos + 1, 8, backl);
matrix.drawPixel(pos + 2, 4, backl);
matrix.drawPixel(pos + 2, 5, backl);
matrix.drawPixel(pos + 2, 6, backl);
matrix.drawPixel(pos + 2, 8, backl);
}

void six(){
matrix.drawPixel(pos, 4, backl);
matrix.drawPixel(pos, 5, backl);
matrix.drawPixel(pos, 6, backl);
matrix.drawPixel(pos, 7, backl);
//matrix.drawPixel(pos, 8, backl);
matrix.drawPixel(pos + 1, 4, backl);
matrix.drawPixel(pos + 1, 6, backl);
matrix.drawPixel(pos + 1, 8, backl);
matrix.drawPixel(pos + 2, 4, backl);
matrix.drawPixel(pos + 2, 5, backl);
matrix.drawPixel(pos + 2, 6, backl);
matrix.drawPixel(pos + 2, 8, backl);
}

void seven(){
matrix.drawPixel(pos, 8, backl);
matrix.drawPixel(pos + 1, 6, backl);
matrix.drawPixel(pos + 1, 8, backl);
matrix.drawPixel(pos + 2, 4, backl);
matrix.drawPixel(pos + 2, 5, backl);
matrix.drawPixel(pos + 2, 6, backl);
matrix.drawPixel(pos + 2, 7, backl);
matrix.drawPixel(pos + 2, 8, backl);
}

void eight(){
matrix.drawPixel(pos, 4, backl);
matrix.drawPixel(pos, 5, backl);
matrix.drawPixel(pos, 6, backl);
matrix.drawPixel(pos, 7, backl);
matrix.drawPixel(pos, 8, backl);
matrix.drawPixel(pos + 1, 4, backl);
matrix.drawPixel(pos + 1, 6, backl);
matrix.drawPixel(pos + 1, 8, backl);
matrix.drawPixel(pos + 2, 4, backl);
matrix.drawPixel(pos + 2, 5, backl);
matrix.drawPixel(pos + 2, 6, backl);
matrix.drawPixel(pos + 2, 7, backl);
matrix.drawPixel(pos + 2, 8, backl);
  
 
}void nine(){
matrix.drawPixel(pos, 4, backl);
matrix.drawPixel(pos, 6, backl);
matrix.drawPixel(pos, 7, backl);
matrix.drawPixel(pos, 8, backl);
matrix.drawPixel(pos + 1, 4, backl);
matrix.drawPixel(pos + 1, 6, backl);
matrix.drawPixel(pos + 1, 8, backl);
matrix.drawPixel(pos + 2, 5, backl);
matrix.drawPixel(pos + 2, 6, backl);
matrix.drawPixel(pos + 2, 7, backl);
matrix.drawPixel(pos + 2, 8, backl);
}

void zero(){
matrix.drawPixel(pos, 4, backl);
matrix.drawPixel(pos, 5, backl);
matrix.drawPixel(pos, 6, backl);
matrix.drawPixel(pos, 7, backl);
matrix.drawPixel(pos, 8, backl);
matrix.drawPixel(pos + 1, 4, backl);
matrix.drawPixel(pos + 1, 8, backl);
matrix.drawPixel(pos + 2, 4, backl);
matrix.drawPixel(pos + 2, 5, backl);
matrix.drawPixel(pos + 2, 6, backl);
matrix.drawPixel(pos + 2, 7, backl);
matrix.drawPixel(pos + 2, 8, backl);
}

//void east(){
//matrix.drawPixel(pos + 0, 0, backl);
//matrix.drawPixel(pos + 0, 1, backl);
//matrix.drawPixel(pos + 0, 2, backl);
//matrix.drawPixel(pos + 1, 0, backl);
//matrix.drawPixel(pos + 1, 1, backl);
//matrix.drawPixel(pos + 1, 2, backl);
//matrix.drawPixel(pos + 2, 0, backl);
//matrix.drawPixel(pos + 2, 2, backl);
//}
//void north(){
//matrix.drawPixel(pos + 0, 0, backl);
//matrix.drawPixel(pos + 0, 1, backl);
//matrix.drawPixel(pos + 0, 2, backl);
//matrix.drawPixel(pos + 1, 1, backl);
//matrix.drawPixel(pos + 2, 0, backl);
//matrix.drawPixel(pos + 2, 1, backl);
//matrix.drawPixel(pos + 2, 2, backl);
//}
//
//void south(){
//matrix.drawPixel(pos + 0, 0, backl);
//matrix.drawPixel(pos + 0, 2, backl);
//matrix.drawPixel(pos + 1, 0, backl);
//matrix.drawPixel(pos + 1, 1, backl);
//matrix.drawPixel(pos + 1, 2, backl);
//matrix.drawPixel(pos + 2, 0, backl);
//matrix.drawPixel(pos + 2, 2, backl);
//}
//
//void west(){
//matrix.drawPixel(pos + 0, 0, backl);
//matrix.drawPixel(pos + 0, 1, backl);
//matrix.drawPixel(pos + 0, 2, backl);
//matrix.drawPixel(pos + 1, 0, backl);
//matrix.drawPixel(pos + 1, 1, backl);
//matrix.drawPixel(pos + 2, 0, backl);
//matrix.drawPixel(pos + 2, 1, backl);
//matrix.drawPixel(pos + 2, 2, backl);
//}


// ~~~BIGGER DIRECTION DISPLAYS~~~
void north(){
matrix.drawPixel(pos + 0, 0, backl);
matrix.drawPixel(pos + 0, 1, backl);
matrix.drawPixel(pos + 0, 2, backl);
matrix.drawPixel(pos + 1, 1, backl);
matrix.drawPixel(pos + 2, 0, backl);
matrix.drawPixel(pos + 3, 0, backl);
matrix.drawPixel(pos + 3, 1, backl);
matrix.drawPixel(pos + 3, 2, backl);
}

void east(){
matrix.drawPixel(pos + 0, 0, backl);
matrix.drawPixel(pos + 0, 1, backl);
matrix.drawPixel(pos + 0, 2, backl);
matrix.drawPixel(pos + 1, 0, backl);
matrix.drawPixel(pos + 1, 1, backl);
matrix.drawPixel(pos + 1, 2, backl);
matrix.drawPixel(pos + 2, 0, backl);
matrix.drawPixel(pos + 2, 2, backl);
matrix.drawPixel(pos + 3, 0, backl);
matrix.drawPixel(pos + 3, 2, backl);
}

void south(){
matrix.drawPixel(pos + 0, 0, backl);
matrix.drawPixel(pos + 0, 2, backl);
matrix.drawPixel(pos + 1, 0, backl);
matrix.drawPixel(pos + 1, 1, backl);
matrix.drawPixel(pos + 1, 2, backl);
matrix.drawPixel(pos + 2, 0, backl);
matrix.drawPixel(pos + 2, 1, backl);
matrix.drawPixel(pos + 2, 2, backl);
matrix.drawPixel(pos + 3, 0, backl);
matrix.drawPixel(pos + 3, 2, backl);
}

void west(){
matrix.drawPixel(pos + 0, 0, backl);
matrix.drawPixel(pos + 0, 1, backl);
matrix.drawPixel(pos + 0, 2, backl);
matrix.drawPixel(pos + 1, 0, backl);
matrix.drawPixel(pos + 1, 1, backl);
matrix.drawPixel(pos + 2, 0, backl);
matrix.drawPixel(pos + 3, 0, backl);
matrix.drawPixel(pos + 3, 1, backl);
matrix.drawPixel(pos + 3, 2, backl);
}

void arr(){
matrix.drawPixel(pos + 0, 0, backl);
matrix.drawPixel(pos + 0, 1, backl);
matrix.drawPixel(pos + 0, 2, backl);
matrix.drawPixel(pos + 1, 2, backl);
matrix.drawPixel(pos + 2, 2, backl);
matrix.drawPixel(pos + 3, 2, backl);
}

void working(){

  // 5
  // 9
matrix.clear();
  pos = 1;
  one();
  pos = 5;
  one();
  pos = 9;
  one();  
delay(150);
matrix.clear();
  pos = 1;
  one();
  pos = 5;
  two();
  pos = 9;
  two();  
delay(150);
matrix.clear();
  pos = 1;
  one();
  pos = 5;
  three();
  pos = 9;
  three();  
delay(150);
matrix.clear();
  pos = 1;
  one();
  pos = 5;
  four();
  pos = 9;
  four();  
delay(150);
matrix.clear();
  pos = 1;
  one();
  pos = 5;
  five();
  pos = 9;
  five();  
delay(150);
matrix.clear();
  pos = 1;
  one();
  pos = 5;
  six();
  pos = 9;
  six();  
delay(150);
matrix.clear();
  pos = 1;
  one();
  pos = 5;
  seven();
  pos = 9;
  seven();  
delay(150);
matrix.clear();
  pos = 1;
  one();
  pos = 5;
  eight();
  pos = 9;
  eight();  
delay(150);
matrix.clear();
  pos = 1;
  one();
  pos = 5;
  nine();
  pos = 9;
  nine();  
delay(150);


}

float RawToLux(int raw)
{
  float logLux = raw * logRange / rawRange;
  return pow(10, logLux);
}

