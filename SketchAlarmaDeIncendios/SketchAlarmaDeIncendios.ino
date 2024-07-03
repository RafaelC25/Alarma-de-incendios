#include <DHT.h>

#define DHTPIN1 A5       // Pin al que está conectado el primer sensor DHT11
#define DHTPIN2 A2       // Pin al que está conectado el segundo sensor DHT22
#define DHTTYPE1 DHT11   // Tipo de sensor DHT para el primer sensor
#define DHTTYPE2 DHT22   // Tipo de sensor DHT para el segundo sensor

#define MQ2PIN1 A1       // Pin al que está conectado el primer sensor MQ-2
#define MQ2PIN2 A0       // Pin al que está conectado el segundo sensor MQ-2

#define GREEN_LED 8      // Pin al que está conectado el LED verde
#define RED_LED 9        // Pin al que está conectado el LED rojo

DHT dht1(DHTPIN1, DHTTYPE1);
DHT dht2(DHTPIN2, DHTTYPE2);

void setup() {
  Serial.begin(9600);
  dht1.begin();
  dht2.begin();
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
}

void loop() {
  delay(2000); // Espera un momento para que el sensor se estabilice
  
  float temperature1 = dht1.readTemperature(); // Lee la temperatura del primer sensor en grados Celsius
  float humidity1 = dht1.readHumidity();       // Lee la humedad relativa del primer sensor
  
  float temperature2 = dht2.readTemperature(); // Lee la temperatura del segundo sensor en grados Celsius
  float humidity2 = dht2.readHumidity();       // Lee la humedad relativa del segundo sensor
  
  int mq2Value1 = analogRead(MQ2PIN1);         // Lee el valor analógico del primer sensor MQ-2
  int mq2Value2 = analogRead(MQ2PIN2);         // Lee el valor analógico del segundo sensor MQ-2
  
  Serial.println("Sensor DHT11:");
  Serial.print("Temperatura: ");
  Serial.print(temperature1);
  Serial.print(" °C\t");
  
  Serial.print("Humedad: ");
  Serial.print(humidity1);
  Serial.print(" %\n");

  Serial.println("Sensor DHT22:");
  Serial.print("Temperatura: ");
  Serial.print(temperature2);
  Serial.print(" °C\t");
  
  Serial.print("Humedad: ");
  Serial.print(humidity2);
  Serial.print(" %\n");
  
  Serial.println("Sensores MQ-2:");
  Serial.print("Valor sensor 1: ");
  Serial.println(mq2Value1);
  Serial.print("Valor sensor 2: ");
  Serial.println(mq2Value2);
  
  bool mq2_1_alto = mq2Value1 >= 350;
  bool mq2_2_alto = mq2Value2 >= 350;
  bool dht11_alto = temperature1 >= 45;
  bool dht22_alto = temperature2 >= 60;
  
  if ((mq2_1_alto && mq2_2_alto && dht11_alto && dht22_alto) || 
      (mq2_1_alto && mq2_2_alto && dht11_alto && !dht22_alto) ||
      (mq2_1_alto && mq2_2_alto && !dht11_alto && !dht22_alto) ||
      (mq2_1_alto && !mq2_2_alto && dht11_alto && dht22_alto) ||
      (mq2_1_alto && !mq2_2_alto && dht11_alto && !dht22_alto) ||
      (!mq2_1_alto && mq2_2_alto && dht11_alto && dht22_alto) ||
      (!mq2_1_alto && mq2_2_alto && dht11_alto && !dht22_alto) ||
      (!mq2_1_alto && !mq2_2_alto && dht11_alto && dht22_alto)) {
    digitalWrite(RED_LED, HIGH);  // Enciende el LED rojo
    digitalWrite(GREEN_LED, LOW); // Apaga el LED verde
  } else {
    digitalWrite(GREEN_LED, HIGH); // Enciende el LED verde
    digitalWrite(RED_LED, LOW);    // Apaga el LED rojo
  }
}