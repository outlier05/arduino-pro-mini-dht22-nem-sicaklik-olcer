#include <LowPower.h>
#include <Wire.h>
//oled ekran ds1306 chip lib
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


//DHT 22 lib
#include <DHT.h>

//RTC libs

//oled var girişleri
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

//dht var
#define DHTPIN 2
#define DHTTYPE DHT11

//DHT
DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  //debug amaçlı
  Serial.begin(9600);
  dht.begin();
  delay(2000);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
  }
  display.clearDisplay();
}

void loop() {
  ust_kisim();
  higro_termo();
  delay(500);
  for (unsigned int i = 0; i < 4; i++) {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
  delay(2000);
}

void ust_kisim() {
  //üst sarı kısım
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 7);
  display.print("Burak Keskin");
}

void higro_termo() {
  //mavi ilk ve ikinci satır
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  display.setCursor(0, 19);
  display.print("Nem     ");
  display.setTextSize(2);
  display.print("%");
  display.print(h);
  display.setCursor(0, 40);
  display.setTextSize(1);
  display.print("Sicaklik  ");
  display.setTextSize(2);
  display.print(t);
  display.setTextSize(1);
  display.print(F("C"));
  /*display.drawPixel(86, 24, WHITE);
    display.drawPixel(87, 24, WHITE);
    display.drawPixel(86, 25, WHITE);
    display.drawPixel(87, 25, WHITE);*/
  display.display();
}
