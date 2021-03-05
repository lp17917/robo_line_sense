#ifndef _LINESENSOR_H
#define _LINESENSOR_H

class lineSensor_c {
  
  public:

    int pin;
    float biasvalue;

    // Constructor, accepts a pin number as
    // argument and sets this as input.
    lineSensor_c( int which_pin ) {

       // Record which pin we used.
       pin = which_pin;
       biasvalue = 0;
       // Set this pin to input.
       pinMode( pin, INPUT );
    };


    // Write your calibration routine here
    // to remove bias offset
    void calibrate() {
      float value;
      value = analogRead( pin ) / 64;
      for (int i = 0; i <= 63; i++) {
        biasvalue += value;
        delay(10);
      }
      
    }


    int getbias(){
      return biasvalue;
    }

    int getlevel(){
      return (analogRead( pin ) - biasvalue);
    }
    
    // Write a routine here to check if your
    // sensor is on a line (true or false).
    boolean onLine( float threshold ) {

      if (getlevel() > threshold) {
         return true;
      }
             
      return false;
    }


};

#endif
