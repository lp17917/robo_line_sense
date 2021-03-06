#include "lineSensor.h"
#include "motor.h"

#define BUTTON_A 14
#define BUZZER 6

#define LINE_LEFT_PIN A2
#define LINE_CENTRE_PIN A3
#define LINE_RIGHT_PIN A4

#define L_PWM_PIN 10
#define L_DIR_PIN 16
#define R_PWM_PIN  9
#define R_DIR_PIN 15

#define standby 0
#define startup 1
#define initalise 2
#define findline 3
#define foundline 4

float threshold;
float leftlevel;
float centrelevel;
float rightlevel;
float totalread;
float propleft;
float propcentre;
float propright;
float M;
int state;

lineSensor_c line_left(LINE_LEFT_PIN); //Create a line sensor object for the left sensor
lineSensor_c line_centre(LINE_CENTRE_PIN); //Create a line sensor object for the centre sensor
lineSensor_c line_right(LINE_RIGHT_PIN); //Create a line sensor object for the right sensor
motor_c left_motor(L_DIR_PIN,L_PWM_PIN);
motor_c right_motor(R_DIR_PIN,R_PWM_PIN);

void weighted_line_sense(){
  leftlevel = line_left.getlevel();
  centrelevel = line_centre.getlevel();
  rightlevel = line_right.getlevel();
  totalread = leftlevel + centrelevel + rightlevel;
  propleft = leftlevel/totalread;
  propcentre = centrelevel/totalread;
  propright = rightlevel/totalread;
  M = propright - propleft;
  if (-0.25 < M && M < 0.25){
      left_motor.speedchange(23);
      right_motor.speedchange(25);
  }
  else {
    left_motor.speedchange(M*50*1);
    right_motor.speedchange(M*50*-1);
  }
}

void play_tone(int volume) {
    analogWrite(BUZZER, volume);
}


void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  pinMode(BUZZER, OUTPUT);
  threshold = 200;
  state = standby;
}

void loop() 
{

  switch(state){
    case(standby):
      if ((digitalRead(BUTTON_A) == LOW)){
        state = startup;
      }
    case(startup):
      for (int i = 0; i < 5; i++){
        play_tone(64);
        delay(500);
        play_tone(0);
        delay(500);
      }
      state = initalise;
    case(initalise):
      line_left.calibrate();
      line_centre.calibrate();
      line_right.calibrate();
    case(findline):
      left_motor.speedchange(23);
      right_motor.speedchange(25);
      if (line_left.getlevel() > threshold || line_right.getlevel() > threshold ||line_centre.getlevel() > threshold){
        left_motor.speedchange(0);
        right_motor.speedchange(0);
        state = foundline;
      }
    case(foundline):
      weighted_line_sense();
  }
  
  

 /*
  // To store result.
  int l_value; // left sensor
  int c_value; // centre sensor
  int r_value; // right sensor
  // Read analog voltages
  l_value = line_left.getlevel();
  c_value = line_centre.getlevel();
  r_value = line_right.getlevel();

  //Serial.print("is on :");
  //Serial.print(on);
  //Serial.print("is calibrated :"); 
  //Serial.print(calibrated);
  // To send data back to your computer.
  // You can open either Serial monitor or plotter.
  /*
  Serial.print( l_value );
  Serial.print( ", " );
  Serial.print( c_value );
  Serial.print( ", " );
  Serial.print( r_value );
  Serial.print( ", " );
  Serial.print( line_left.onLine(threshold) );
  Serial.print( ", " );
  Serial.print( line_centre.onLine(threshold) );
  Serial.print( ", " );
  Serial.print( line_right.onLine(threshold) );
  Serial.print( "\n" );
  */

  delay(25);
}
