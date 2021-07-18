// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// set up a constant for the tilt switch pin
const int switchPin = 6;

// variable to hold the value of the switch pin
int switchState = 0;

// variable to hold previous value of the switch pin
int prevSwitchState = 0;

// a variable to choose which reply from the crystal ball
int reply;

//RandomHat global variables
#define randomHatStartNum 0       //Starting number in hat
#define randomHatEndNum 7         //Ending number in hat - end has to be larger than the start
#define numberInHat (randomHatEndNum - randomHatStartNum) +1

void setup() {
  // set up the number of columns and rows on the LCD
  lcd.begin(16, 2);

  // set up the switch pin as an input
  pinMode(switchPin, INPUT);

  // Print a message to the LCD.
  lcd.print("Ask the");
  // set the cursor to column 0, line 1
  // line 1 is the second row, since counting begins with 0
  lcd.setCursor(0, 1);
  // print to the second line
  lcd.print("Crystal Ball!");

  //Serial setup for randomHat function
  Serial.begin(9600);
  Serial.println("start ");
}

void loop() {
  // check the status of the switch
  switchState = digitalRead(switchPin);

  // compare the switchState to its previous state
  if (switchState != prevSwitchState) {
    // if the state has changed from HIGH to LOW you know that the ball has been
    // tilted from one direction to the other
    if (switchState == LOW) {
      // randomly chose a reply
      reply = randomHat();
      // clean up the screen before printing a new reply
      lcd.clear();
      // set the cursor to column 0, line 0
      lcd.setCursor(0, 0);
      // print some text
      lcd.print("the ball says:");
      // move the cursor to the second line
      lcd.setCursor(0, 1);

      // choose a saying to print based on the value in reply
      switch (reply) {
        case 0:
          lcd.print("YEE YEE");
          break;

        case 1:
          lcd.print("Maybe ya will, Maybe ya won't");
          break;

        case 2:
          lcd.print("Prolly...Maybe...");
          break;

        case 3:
          lcd.print("At your own risk");
          break;

        case 4:
          lcd.print("DO NOT DO IT");
          break;

        case 5:
          lcd.print("Shoot your shot");
          break;

        case 6:
          lcd.print("The Lottery has better odds");
          break;

        case 7:
          lcd.print("Nah Fam");
          break;
      }
    }
  }
  // save the current switch state as the last state
  prevSwitchState = switchState;
}

//THE randomHat() FUNCTION
int randomHat()
{
  int thePick;
  int theIndex;
  static int currentNumInHat = 0;
  static int randArray[numberInHat];

  if (currentNumInHat ==0)
  {
    for (int i = 0; i < numberInHat; i++)
    {
      if (randomHatStartNum < randomHatEndNum)
      {
        randArray[i] = randomHatStartNum + i;
      }
    }
    currentNumInHat = abs(randomHatEndNum - randomHatStartNum) + 1;
  }
  theIndex = random(currentNumInHat);
  thePick = randArray[theIndex];
  randArray[theIndex] = randArray[currentNumInHat - 1];
  currentNumInHat--;
  return thePick;
  delay(100);
}
