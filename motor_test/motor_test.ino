//Motor testing

#define L_PWM_PIN 10
#define L_DIR_PIN 16
#define R_PWM_PIN  9
#define R_DIR_PIN 15
#define BUTTON_A 14
#define BUTTON_B 30
#define BUTTON_C 17
#define L_DIR_FWD LOW
#define L_DIR_BWD HIGH
#define R_DIR_FWD LOW
#define R_DIR_BWD HIGH

// Variables to remember our
// motor power for Left and Right.
// Byte stores 0 to 255
byte l_power;
byte r_power;


// Setup, only runs once when powered on.
void setup() {

  // Set our motor driver pins as outputs.
  pinMode( L_PWM_PIN, OUTPUT );
  pinMode( L_DIR_PIN, OUTPUT );
  pinMode( R_PWM_PIN, OUTPUT );
  pinMode( R_DIR_PIN, OUTPUT );
  pinMode( BUTTON_A, INPUT );
  pinMode( BUTTON_B, INPUT );
  pinMode( BUTTON_C, INPUT );

  // Set initial direction for l and r
  // Which of these is foward, or backward?
  digitalWrite( L_DIR_PIN, L_DIR_FWD  );
  digitalWrite( R_DIR_PIN, R_DIR_FWD );

  // Set initial l_power and r_power values.
  l_power = 0;
  r_power = 0;

  // Start up the Serial for debugging.
  Serial.begin(9600);
  delay(1000);
  // Print reset so we can catch any reset error.
  Serial.println(" ***Reset*** ");

}


// put your main code here, to run repeatedly:
void loop() {

  // Adjust power. e.g., increment by 4 on every loop()
  //l_power = l_power + 4;
  //r_power = r_power + 4;

  // Send power PWM to pins, to motor drivers.
  analogWrite( L_PWM_PIN, l_power );
  analogWrite( R_PWM_PIN, r_power );
  Serial.println(r_power);
  Serial.println(l_power);
  //Serial.println(digitalRead(BUTTON_C));
  if ((digitalRead(BUTTON_B) == LOW)){
    l_power = 0;
    r_power = 0;
  }
  if ((digitalRead(BUTTON_C) == LOW)){
    l_power++;
    r_power++;
  }
  /*
  if (l_power > 150){
    r_power = 0;
    l_power = 0;
    digitalWrite( L_DIR_PIN, L_DIR_BWD  );
    digitalWrite( R_DIR_PIN, R_DIR_BWD );
  }
  */
  // Brief pause
  delay(500);

}
