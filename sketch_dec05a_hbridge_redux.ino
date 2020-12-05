#include <IRremote.h>

//------------------------------------------------------------
//Codes for Infrared Remote Control
//COM-11759 https://www.sparkfun.com/products/retired/11759
//Note: Uncomment out this section if you are using this w/ the older remote.


#define POWER 0x10EFD827
#define A 0x10EFF807
#define B 0x10EF7887
#define C 0x10EF58A7
#define UP 0x10EFA05F
#define DOWN 0x10EF00FF
#define LEFT 0x10EF10EF
#define RIGHT 0x10EF807F
#define SELECT 0x10EF20DF

//------------------------------------------------------------

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

//Keyboard Controls:
//
// 1 -Motor 1 Left
// 2 -Motor 1 Stop
// 3 -Motor 1 Right
//
// 4 -Motor 2 Left
// 5 -Motor 2 Stop
// 6 -Motor 2 Right

// Motor 1
int dir1PinA = 2;
int dir2PinA = 3;
int speedPinA = 9; // Needs to be a PWM pin to be able to control motor speed
int speed1 = 255;

// Motor 2
int dir1PinB = 4;
int dir2PinB = 5;
int speedPinB = 10; // Needs to be a PWM pin to be able to control motor speed
int speed2 = 255;

// Misc. Pins
int irTestPin = 12;


void setup() {
  Serial.begin(9600);

  pinMode(dir1PinA,OUTPUT);
  pinMode(dir2PinA,OUTPUT);
  pinMode(speedPinA,OUTPUT);
  pinMode(dir1PinB,OUTPUT);
  pinMode(dir2PinB,OUTPUT);
  pinMode(speedPinB,OUTPUT);

  pinMode(irTestPin, OUTPUT);

  // Enable IR inputs
  irrecv.enableIRIn();

  Serial.println("System initialized");

  /*
   * Test Program
  motorAFwd();
  motorBFwd();

  delay(2000);

  motorAFwd();
  motorBRev();

  delay(1000);

  motorAFwd();
  motorBFwd();

  delay(5000);

  motorAStop();
  motorBStop();
  */
}

void loop() {
  handleIRControls();
  
  //handleSerialControls();
}

/*
 * IR Remote Controls Handler
 */
void handleIRControls()
{
  if (irrecv.decode(&results))
  {
    if (results.value == POWER)
    {
      Serial.println("POWER");
      // Blink the LED
      digitalWrite(irTestPin, HIGH);
      delay(100);
      digitalWrite(irTestPin, LOW);
    }
    else if (results.value == A)
    {
      Serial.println("A");
    }
    else if (results.value == B)
    {
      Serial.println("B");
    }
    else if (results.value == C)
    {
      Serial.println("C");
    }
    else if (results.value == UP)
    {
      Serial.println("Forward (UP)");
      motorAFwd();
      motorBFwd();
    }
    else if (results.value == DOWN)
    {
      Serial.println("Reverse (DOWN)");
      motorARev();
      motorBRev();
    }
    else if (results.value == LEFT)
    {
      Serial.println("Turn Left (LEFT)");
      motorARev();
      motorBFwd();
    }
    else if (results.value == RIGHT)
    {
      Serial.println("Turn Right (RIGHT)");
      motorAFwd();
      motorBRev();
    }
    else if (results.value == SELECT)
    {
      Serial.println("Stop (SELECT)");
      motorAStop();
      motorBStop();
    }
    else {
      Serial.println("IR RECV Code Value Not Defined or Button was Held Down");
    }

    Serial.print("IR RECV Code = 0x ");
    Serial.println(results.value, HEX);
    irrecv.resume();
  }
}

/*
 * Reset Helpers
 */

void resetAInputs() {
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, LOW);
  digitalWrite(speedPinA, LOW);
  digitalWrite(speed1, LOW);
}

void resetBInputs() {
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, LOW);
  digitalWrite(speedPinB, LOW);
  digitalWrite(speed2, LOW);
}

/*
 * Motor A Controls
 */

void motorAFwd() {
  resetAInputs();
  analogWrite(speedPinA, 255);//Sets speed variable via PWM 
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);
  Serial.println("Motor 1 Forward"); // Prints out â€œMotor 1 Forwardâ€ on the serial monitor
  Serial.println("   "); // Creates a blank line printed on the serial monitor
}

void motorAStop() {
  resetAInputs();
  analogWrite(speedPinA, 0);
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);
  Serial.println("Motor 1 Stop");
  Serial.println("   ");
}

void motorARev() {
  resetAInputs();
  analogWrite(speedPinA, 255);
  digitalWrite(dir1PinA, HIGH);
  digitalWrite(dir2PinA, LOW);
  Serial.println("Motor 1 Reverse");
  Serial.println("   ");
}

/*
 * Motor B Controls
 */

void motorBFwd() {
  resetBInputs();
  analogWrite(speedPinB, 255);//Sets speed variable via PWM 
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
  Serial.println("Motor 2 Forward");
  Serial.println("   "); // Creates a blank line printed on the serial monitor
}

void motorBStop() {
  resetBInputs();
  analogWrite(speedPinB, 0);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
  Serial.println("Motor 2 Stop");
  Serial.println("   ");
}

void motorBRev() {
  resetBInputs();
  analogWrite(speedPinB, 255);
  digitalWrite(dir1PinB, HIGH);
  digitalWrite(dir2PinB, LOW);
  Serial.println("Motor 2 Reverse");
  Serial.println("   ");
}

/*
 * OBSELETE, but may be useful for testing purposes
 * 
void handleSerialControls() {
  if (Serial.available() > 0) {
    int inByte = Serial.read();

    // Now, set our new ones
    switch (inByte) {
      case '1': // Motor 1 Forward
        motorAFwd();
        break;

      case '2': // Motor 1 Stop (Freespin)
        motorAStop();
        break;

      case '3': // Motor 1 Reverse
        motorARev();
        break;

      //______________Motor 2______________

      case '4': // Motor 2 Forward
        motorBFwd();
        break;

      case '5': // Motor 1 Stop (Freespin)
        motorBStop();
        break;

      case '6': // Motor 2 Reverse
        motorBRev();
        break;
    }
  }
}
*/
