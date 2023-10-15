#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Definiciones de pines
const int waterLevelPin = A1;     // Pin del sensor de nivel de agua
const int waterQualityPin = A0;   // Pin del sensor de calidad de agua
const int phSensorPin = A3;       // Pin del sensor de pH
const int photoresistorPin = A2;  // Pin del fotorresistor

// Inicialización de sensores
OneWire oneWire(4);  // Pin de datos para el sensor DS18B20
DallasTemperature sensors(&oneWire);

// Inicialización de la pantalla LCD I2C
LiquidCrystal_I2C lcd(0x3f, 16, 2);  // Dirección I2C y dimensiones de la pantalla

int photoresistorValue = 0; // Variable para almacenar el valor del fotorresistor

void setup() {
  lcd.init();       // Inicializa la pantalla LCD
  lcd.backlight();  // Enciende la retroiluminación
  sensors.begin();   // Inicializa el sensor DS18B20

  // Configura la velocidad de comunicación serie
  Serial.begin(9600);
}

void loop() {
  // Lectura de sensores
  float waterLevel = analogRead(waterLevelPin);
  float waterQuality = analogRead(waterQualityPin);
  float phValue = analogRead(phSensorPin);
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);
  photoresistorValue = analogRead(photoresistorPin); // Lectura del fotorresistor

  // Muestra los datos de los sensores en la pantalla LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Nivel: ");
  lcd.print(waterLevel);

  delay(5000); // Espera 5 segundos antes de cambiar a los otros sensores

  // Cambia a mostrar los datos de los otros sensores
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Luz: ");
  lcd.print(photoresistorValue);

  lcd.setCursor(0, 1);
  lcd.print("Calidad: ");
  lcd.print(waterQuality);

  delay(5000); // Espera 5 segundos antes de cambiar a los otros sensores

  // Cambia a mostrar los datos de los otros sensores
  lcd.setCursor(0, 1);
  lcd.print("pH: ");
  lcd.print(phValue);  
  
delay(5000); // Espera 5 segundos antes de volver a mostrar los primeros sensores
}
