#include <DHT11.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display


DHT11 dht11(2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  
}

void loop() {
    int temperature = 0;
    int humidity = 0;
    
    // Attempt to read the temperature and humidity values from the DHT11 sensor.
    int result = dht11.readTemperatureHumidity(temperature, humidity);
    int temp = temperature;
    int H = humidity;
    // Check the results of the readings.
    // If the reading is successful, print the temperature and humidity values.
    // If there are errors, print the appropriate error messages.
    if (result == 0) {
        //delay(2000); //reads the temp and humidity every 2 seconds
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C\tHumidity: ");
        Serial.print(humidity);
        Serial.println(" %");

        // Print a message to the LCD.
        lcd.setCursor(0,0);
        lcd.print("Temp: ");
        lcd.print(temperature);
        lcd.print((char)223); //degrees symbol for lcd screen
        lcd.print("C ");
        lcd.setCursor(0,1);
        lcd.print("Humidity: ");
        lcd.print(humidity);
        lcd.print("% ");
        
    } else {
        // Print error message based on the error code.
        Serial.println(DHT11::getErrorString(result));
    }
    
    if (humidity > 80) {
      digitalWrite(3, HIGH);
      delay(250);
      digitalWrite(3,LOW);
      delay(250);
    }
}
