int buttonState[20];         // variable for reading the pushbutton status
int sumState;
bool button3 = false;
int checkTicks = 10;       
double accuracy = 0.6;        //need checkTicks*accuracy ticks

void buttonUpd() {

  /*buttonState = digitalRead(3);
    Serial.println(buttonState);*/

  sumState = 0;
  for (int i = 0; i < (checkTicks - 1); i++) {
    buttonState [checkTicks - 1 - i] = buttonState [checkTicks - 2 - i];
    sumState += buttonState[checkTicks - 1 - i];
  }
  buttonState[0] = 1 - digitalRead(3);
  //Serial.println(buttonState[0]);
  sumState += buttonState[0];
  //Serial.println(sumState);
  if (sumState < checkTicks * accuracy)
    button3 = false;
  else
    button3 = true;
}
