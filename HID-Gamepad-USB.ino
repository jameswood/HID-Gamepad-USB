#include "HID-Project.h"
#include <EasyTransfer.h>
EasyTransfer ET;
int numberOfButtons = 32;

struct RECEIVE_DATA_STRUCTURE{
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t joyx;
  int16_t joyy;
  int8_t joyz;
  int16_t joyxr;
  int16_t joyyr;
  int8_t joyzr;
  uint32_t buttonState;
};

RECEIVE_DATA_STRUCTURE controllerState;

void setup() {
  Gamepad.begin();
  Serial1.begin(2000000);
  ET.begin(details(controllerState), &Serial1);
  Gamepad.releaseAll();
}

void loop() {
  if(ET.receiveData()){
    Gamepad.xAxis(controllerState.joyx);
    Gamepad.yAxis(controllerState.joyy);
    Gamepad.zAxis(controllerState.joyz);
    Gamepad.rxAxis(controllerState.joyxr);
    Gamepad.ryAxis(controllerState.joyyr);
    Gamepad.rzAxis(controllerState.joyzr);
    for (int i=0; i<numberOfButtons; i++){
      if(bitRead(controllerState.buttonState, i)){
        Gamepad.press(i+1);
      } else {
        Gamepad.release(i+1);
      }
    }
    Gamepad.write();
  }
}
