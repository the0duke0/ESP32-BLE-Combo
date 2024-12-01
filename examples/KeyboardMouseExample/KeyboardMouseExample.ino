/**
 * This example turns the ESP32 into a Bluetooth LE keyboard and mouse that writes 
 * some words, presses Enter, presses a media key and then Ctrl+Alt+Delete,
 * then moves and the scrolls the mouse and clicks it.
 */
 
#include <BleCombo.h>

#define DEVICE_NAME "ESP32 Keyboard/Mouse"
#define DEVICE_MANUFACTURER "Espressif"

void setup() {
  Serial.begin(115200);
  Serial.println("Starting work!");
  Keyboard.deviceName = DEVICE_NAME;
  Keyboard.deviceManufacturer = DEVICE_MANUFACTURER;

  // bleConnectionMode allows providing different HID reports. For example, MEDIA allows for creating a media only device.
  // For mobile (at least Android) this prevents the mobile device from showing a mouse cursor and hiding the vitual keyboard.
  // The default is KEYBOARD_MEDIA_MOUSE_MODE
  //Keyboard.bleConnectionMode = MEDIA_MODE;
  
  Keyboard.begin();
  Mouse.begin();
}

void loop() {
  if(Keyboard.isConnected()) {
    Serial.println("Sending 'Hello world'");
    Keyboard.println("Hello World");

    delay(1000);
    Serial.println("Sending Enter key...");
    Keyboard.write(KEY_RETURN);

    delay(1000);
  
    Serial.println("Sending Play/Pause media key...");
    Keyboard.write(KEY_MEDIA_PLAY_PAUSE);

    delay(1000);

    Serial.println("Sending Ctrl+Alt+Delete...");
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_DELETE);
    delay(100);
    Keyboard.releaseAll();

    unsigned long startTime;

    Serial.println("Move mouse pointer up");
    startTime = millis();
    while(millis()<startTime+1000) {
      Mouse.move(0,-1);
      delay(5);
    }
    Serial.println("Move mouse pointer left");
    startTime = millis();
    while(millis()<startTime+1000) {
      Mouse.move(-1,0);
      delay(5);
    }

    Serial.println("Move mouse pointer down");
    startTime = millis();
    while(millis()<startTime+1000) {
      Mouse.move(0,1);
      delay(5);
    }

    Serial.println("Move mouse pointer right");
    startTime = millis();
    while(millis()<startTime+1000) {
      Mouse.move(1,0);
      delay(5);
    }
    
    Serial.println("Scroll Down");
    Mouse.move(0,0,-1);

    Serial.println("Left click");
    Mouse.click(MOUSE_LEFT);
    delay(500);

    Serial.println("Right click");
    Mouse.click(MOUSE_RIGHT);
    delay(500);

    Serial.println("Scroll wheel click");
    Mouse.click(MOUSE_MIDDLE);
    delay(500);

    Serial.println("Back button click");
    Mouse.click(MOUSE_BACK);
    delay(500);

    Serial.println("Forward button click");
    Mouse.click(MOUSE_FORWARD);
    delay(500);

    Serial.println("Click left+right mouse button at the same time");
    Mouse.click(MOUSE_LEFT | MOUSE_RIGHT);
    delay(500);

    Serial.println("Click left+right mouse button and scroll wheel at the same time");
    Mouse.click(MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE);
    delay(500);


  }
  
  Serial.println("Waiting 2 seconds...");
  delay(2000);
}
