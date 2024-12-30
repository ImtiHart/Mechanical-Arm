// C code
#include <Servo.h>
Servo s1, s2, s3, s4;
float v1, v2, v3, v4, posv1;
int buttonState = HIGH;  // Current state of the button
int lastButtonState = HIGH; // Previous state of the button
bool isGripping = false;   // Tracks claw state (grip/release)
unsigned long lastDebounceTime = 0; // Timestamp for debouncing
unsigned long debounceDelay = 50;  // Debounce delay in milliseconds
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A1, INPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);

  s1.attach(13);
  s2.attach(12);
  s3.attach(11);
  s4.attach(10);
}


void loop(){
  v1 = digitalRead(A2);
  posv1 = analogRead(A1);
  posv1 = map(posv1,0,1023,0,180);
  v2 = analogRead(A3);
  v3 = analogRead(A4);
  v4 = analogRead(A5);

  
  v2 = map(v2, 0,1023,0,180);
  s2.write(v2);
  
  v3 = map(v3, 0,1023,0,180);
  s3.write(v3);
  
  v4 = map(v4, 0,1023,0,180);
  s4.write(v4);

    if (v1 != lastButtonState) {
    lastDebounceTime = millis(); // Reset debounce timer
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Check if button state has changed
    if (v1 != buttonState) {
      buttonState = v1;

      // Toggle state only on button press (LOW)
      if (buttonState == LOW) {
        isGripping = !isGripping; // Toggle grip/release state

        if (isGripping) {
          s1.write(90); // Grip position
          Serial.println("Claw is gripping.");
        } else {
          s1.write(0); // Release position
          Serial.println("Claw is released.");
        }
      }
    }
  }

  lastButtonState = v1; // Save the current state
}
