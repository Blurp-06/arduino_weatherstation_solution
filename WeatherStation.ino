/*
	Note to the people reading this:
		TMP36 will get VERY hot when  plugged in backwards!!!
		This may happen to other models too!
*/

// The pins used in the program.
#define TEMP_PIN A0
#define LDR_PIN A1

/* 
	The value of the LDR will be mapped to be between 0-255, this macro will define when it will be night. 
	The higher the values is how more light there is.
*/
#define DAY_THRESHOLD 100

void setup() {
	// Starting the serial port.
	Serial.begin(9600);
}

void loop() {
	if (isDay()) {
		Serial.println("It is " + String(getTemp()) + " degrees Celcius, it also is day.");
	} else{
		Serial.println("It is " + String(getTemp()) + " degrees Celcius, it also is night.");
	}
	delay(500);
}

/*
	The function 'getTemp -> float' returns the temperature in celcius.
	Values in this function is made for 3.3V, for 5V the values should be changed from:
	3.3 -> 5.0
	0.33 -> 0.5

	Calculations from https://learn.adafruit.com/tmp36-temperature-sensor/using-a-temp-sensor.
*/
float getTemp() {
	int tempReading = analogRead(TEMP_PIN);
	float voltage = tempReading * 3.3 / 1024;
	float tempInCelcius = (voltage - 0.33) * 100;
	return tempInCelcius;
}

bool isDay() {
	int ldrReading = analogRead(LDR_PIN);
	int mappedReading = map(ldrReading, 0, 1024, 255, 0);
	return mappedReading > DAY_THRESHOLD;
}