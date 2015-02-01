// MasterCaution.ino
// Reads two digital button inputs for Master Caution button
// and light testing.  This code (or parts of it) will
// ultimately be inserted into an entire cockpit code.

const byte MCled = 8;                 // Master Caution (MC) LED
const unsigned long MCinterval = 200; // LED blinking interval
unsigned long MCtimer;                // MC timer to prevent delay(x) use
unsigned long MChack;                 // Hack clock designed to end MC illumination with .9 sec delay
byte onState[3] = { 0, 0, 0 };        // save the state of each pin

void setup() {
 Serial.begin(115200);     // Open serial connection
 pinMode(2, INPUT);        // Set these three pins for reading
 pinMode(3, INPUT);        // Each have a 10k pullup externally
 pinMode(4, INPUT);        // so a trigger is LOW
 pinMode(MCled, OUTPUT);   // Master Caution LED
 MCtimer = millis ();      // set MC timer to equal current clock
}

void MCflash() {           // sub-program that loops to blink MC LED
  if (digitalRead (MCled) == LOW)
      digitalWrite (MCled, HIGH);
  else
      digitalWrite (MCled, LOW);
  MCtimer = millis (); 
} 


void ReadCockpit() {                // sub-program that sends button pins (when pressed) to RPi
  for (int i=0; i<3; i++) {         // Iterate over pins
   if (digitalRead(i+2) == LOW) {   // Check if triggered
     if (onState[i] == 0) {         // Just triggered?
       Serial.write(i+2);           // Send the pin number
       onState[i] = 1;              // but just once
     } 
   } else {
     onState[i] = 0;                // Not triggered
   }
 }
 delay(20);}


void loop() { 
  ReadCockpit();                          // read button stati (statuses?)
  if (Serial.available()) {
   char MC = Serial.read();
   if (MC == 'H') {                       // RPi sends Arduino 'H' if MC triggered
     delay(900);                          // delay for RPi sound to start
     MChack=-1001;                        // set hack to start at -1001
     while (millis()-MChack != 1000) {    // current time minus hack... starts at 1001 and gets larger until MC button press resets
       if ( (millis () - MCtimer) >= MCinterval) {
       MCflash(); 
       if ( digitalRead(4)==LOW) {
         MChack=millis();                 // MC button reset, starting .9sec delay
         Serial.write(4);                 // send MC Pin to RPi to shut down sound
         }
       }}
       digitalWrite(MCled, LOW);
       }
    }
  }
