//includes the libraries needed
#include <DHT11.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// creating variables for temp and humidity
int temperature = 0;  
int humidity = 0;


unsigned long lastButton = 0;  //create variable for the button timer. This variable cannot have negative numbers, and can hold a lot of data.
const int interruptPin = 2;   //makes the variable for the pin that is connected to the interrupt. Is read-only.

DHT11 dht11(6);  //makes pin for DHT11 sensor


//function for the interrupt
void InterruptFunction() {
    lastButton = millis();  //makes the variable lastButton == the function millis()
}


//function to set up everything, runs once.
void setup() {
  // put your setup code here, to run once:
  
  pinMode(interruptPin, INPUT_PULLUP);     //makes inerruptPin an input
  attachInterrupt(digitalPinToInterrupt(interruptPin), InterruptFunction, FALLING);  //sets up the interrupt with all the settings (digitalPinToInterrupt(pin), function, mode)
  
  Serial.begin(9600);      // sets the data rate in baud(bits per second)
  
  pinMode(4, OUTPUT);      // makes pin 4 an output
  
  lcd.init();              // initialize the lcd 
  lcd.backlight();         // turns on the backlight
  
}


//the main function that continously loops
void loop() {
  
    // Attempt to read the temperature and humidity values from the DHT11 sensor.
    int result = dht11.readTemperatureHumidity(temperature, humidity);
    lcd.noBacklight();  //turns off the backlight
    
    // Check the results of the readings.
    // If the reading is successful, print the temperature and humidity values.
    if (result == 0) {
        //reads the temp and humidity
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C\tHumidity: ");
        Serial.print(humidity);
        Serial.println(" %");

        // Prints the temp and humidity on the LCD.
        lcd.setCursor(0,0);
        lcd.print("Temp: ");
        lcd.print(temperature);
        lcd.print((char)223); //degrees symbol for lcd screen
        lcd.print("C ");
        lcd.setCursor(0,1);
        lcd.print("Humidity: ");
        lcd.print(humidity);
        lcd.print("% ");
        
// If there are errors, print the appropriate error messages.
    } else {
        // Print error message based on the error code.
        Serial.println(DHT11::getErrorString(result));
    }

    //if the button was pressed in the last 5 seconds it runs the code
    if(lastButton+5000 > millis()){ 
      lcd.backlight(); //turns on backlight
    }
    else{
      lcd.noBacklight(); //turns off backlight
    }

    
    if (humidity > 79) {
      digitalWrite(4, HIGH); //turns on relay
    }
    else{
      digitalWrite(4,LOW); //turns off relay
    }
}
