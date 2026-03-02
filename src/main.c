#include <DFMicrobit_Radio.h>
#include <Microbit_Matrix.h>
#include <Microbit_Sensors.h>

void joy_stick() {

}

void onRadioReceive(String radio_message) {
}

void setup() {
    uint8_t a = 0;
    dfrobotRandomSeed();
    Radio.setCallback(onRadioReceive);
	Radio.turnOn();
	Radio.setGroup(7);
	Serial.begin(9600);
	MMatrix.drawPixel(random(0l), 0, LED_ON);
	MMatrix.show(MMatrix.EMPTYHEART);
	random(0l);
	String("0").toInt();
	analogRead(1);
	Button_A.isPressed();
}

void loop() {
    if (Button_A.isPressed()) {
        Radio.send("A");
    }
}
