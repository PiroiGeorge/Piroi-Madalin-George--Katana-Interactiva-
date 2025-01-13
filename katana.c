#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

// Configurare MPU6050 și LED-uri
Adafruit_MPU6050 mpu;
#define LED_PIN 8 // Pinul la care este conectată banda de LED-uri NeoPixel
#define NUMPIXELS 50 // Numărul de LED-uri din banda NeoPixel
Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Configurare SoftwareSerial pentru DY-SV5W
#define MP3_RX_PIN 3  // Pinul RX al DY-SV5W conectat la D3
#define MP3_TX_PIN 4  // Pinul TX al DY-SV5W conectat la D4
SoftwareSerial mySerial(MP3_RX_PIN, MP3_TX_PIN);

// Configurare buton
#define BUTTON_PIN 10 // Pinul conectat la buton
bool currentMode = false;  // Modul curent: false = MPU6050, true = Joc de lumini
unsigned long buttonPressStart = 0;  // Momentul când butonul a fost apăsat
bool buttonState = LOW; // Starea curentă a butonului
bool lastButtonState = LOW; // Starea anterioară a butonului

// Praguri pentru apăsarea butonului
const unsigned long LONG_PRESS_THRESHOLD = 5000; // Prag pentru apăsare lungă (5 secunde)
const unsigned long DEBOUNCE_DELAY = 50; // Întârziere pentru debouncing
unsigned long lastDebounceTime = 0; // Momentul ultimei schimbări a stării butonului

// Variabile globale pentru MPU6050
float prevAngleY = 0; // Ultimul unghi măsurat pe axa Y
const float threshold = 70.0; // Prag pentru detectarea schimbărilor bruste de unghi (în grade)
unsigned long lastChangeTime = 0; // Ultimul moment când a fost detectată o schimbare
const unsigned long MIN_CHANGE_INTERVAL = 1000; // Interval minim între schimbări (1 secundă)

// Variabile DY-SV5W
byte commandLength; // Lungimea comenzii trimise către DY-SV5W
byte command[6]; // Comanda DY-SV5W
int checkSum = 0; // Suma de control pentru comanda DY-SV5W

// Funcție pentru a trimite comenzi către DY-SV5W
void sendCommand() {
  for (int q = 0; q < commandLength; q++) {
    mySerial.write(command[q]);
    Serial.print("Comandă trimisă: 0x");
    Serial.println(command[q], HEX);
  }
  Serial.println("Final comanda.");
}

// Funcție pentru redarea unei melodii specifice
void playTrack(int soundTrack) {
  command[0] = 0xAA; // Prefixul comenzii
  command[1] = 0x07; // Comandă pentru redare
  command[2] = 0x02; // Dimensiunea datelor
  command[3] = highByte(soundTrack); // Octetul superior al ID-ului melodiei
  command[4] = lowByte(soundTrack); // Octetul inferior al ID-ului melodiei
  checkSum = 0;

  // Calcularea sumei de control
  for (int q = 0; q < 5; q++) {
    checkSum += command[q];
  }
  command[5] = lowByte(checkSum); // Adăugarea sumei de control la comandă
  commandLength = 6;
  sendCommand(); // Trimiterea comenzii
  Serial.print("Redă melodia: ");
  Serial.println(soundTrack);
}

// Funcție pentru setarea volumului pe DY-SV5W
void playbackVolume(int vol) {
  if (vol > 30) vol = 30; // Limitează volumul la maxim 30
  command[0] = 0xAA; // Prefixul comenzii
  command[1] = 0x13; // Comandă pentru setarea volumului
  command[2] = 0x01; // Dimensiunea datelor
  command[3] = vol; // Nivelul volumului
  checkSum = 0;

  // Calcularea sumei de control
  for (int q = 0; q < 4; q++) {
    checkSum += command[q];
  }
  command[4] = lowByte(checkSum); // Adăugarea sumei de control
  commandLength = 5;
  sendCommand(); // Trimiterea comenzii
  Serial.print("Setează volumul la: ");
  Serial.println(vol);
}

// Funcție pentru a clipi LED-urile roșii de 3 ori
void blinkRedLEDs() {
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(255, 0, 0)); // Setează culoarea LED-urilor la roșu
    }
    pixels.show(); // Afișează culoarea pe LED-uri
    delay(500);
    pixels.clear(); // Stinge LED-urile
    pixels.show();
    delay(500);
  }
}

// Funcție pentru verificarea stării butonului
void checkButton() {
  bool reading = digitalRead(BUTTON_PIN); // Citește starea curentă a butonului

  if (reading != lastButtonState) {
    lastDebounceTime = millis(); // Resetează timpul de debounce
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        buttonPressStart = millis(); // Înregistrează momentul apăsării butonului
      } else if (buttonState == LOW) {
        unsigned long pressDuration = millis() - buttonPressStart; // Durata apăsării

        if (!currentMode && pressDuration >= LONG_PRESS_THRESHOLD) {
          currentMode = true; // Schimbă modul la "Joc de lumini"
          Serial.println("Modul schimbat: Joc de lumini.");
          playbackVolume(30); // Setează volumul maxim
          blinkRedLEDs();
          playTrack(1); // Redă prima melodie
        } else if (currentMode && pressDuration < LONG_PRESS_THRESHOLD) {
          currentMode = false; // Schimbă modul la "Detectare mișcări"
          Serial.println("Modul schimbat: Detectare mișcări.");
          playbackVolume(30); // Setează volumul normal
          blinkRedLEDs();
        }
      }
    }
  }

  lastButtonState = reading; // Actualizează starea butonului
}

// Funcție pentru un joc de lumini continuu
void lightShow() {
  uint32_t color = pixels.Color(random(0, 256), random(0, 256), random(0, 256)); // Generează o culoare aleatorie
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, color); // Setează fiecare LED la culoarea generată
  }
  pixels.show();
  delay(200); // Întârziere pentru efect
}

void setup() {
  Serial.begin(115200); // Inițializează comunicarea serială
  mySerial.begin(9600); // Inițializează comunicarea cu DY-SV5W

  pinMode(BUTTON_PIN, INPUT_PULLUP); // Configurează butonul ca intrare cu rezistență pull-up

  if (!mpu.begin()) {
    Serial.println("Nu s-a putut inițializa MPU-6050. Verifică conexiunile!");
    while (1) delay(10); // Oprește execuția dacă MPU-6050 nu este conectat
  }

  // Configurarea MPU6050
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // Configurarea NeoPixel
  pixels.begin();
  pixels.clear();
  pixels.show();

  playbackVolume(25); // Setează volumul inițial
  Serial.println("Sistem pregătit!");
}

void loop() {
  checkButton(); // Verifică starea butonului

  if (!currentMode) {
    // Modul "Detectare mișcări"
    sensors_event_t accel, gyro, temp;
    if (mpu.getEvent(&accel, &gyro, &temp)) {
      unsigned long currentTime = millis();
      if (currentTime - lastChangeTime > MIN_CHANGE_INTERVAL) {
        float angleY = atan2(accel.acceleration.y, accel.acceleration.z) * 180 / PI; // Calculează unghiul pe axa Y

        if (abs(angleY - prevAngleY) > threshold) {
          uint32_t color = pixels.Color(random(0, 256), random(0, 256), random(0, 256)); // Generează o culoare aleatorie
          for (int i = 0; i < NUMPIXELS; i++) {
            pixels.setPixelColor(i, color); // Setează culoarea LED-urilor
          }
          pixels.show();

          playTrack(2); // Redă piesa 2

          Serial.println("Schimbare detectată!");
          Serial.print("Unghi anterior: ");
          Serial.print(prevAngleY);
          Serial.print(" | Unghi curent: ");
          Serial.println(angleY);

          lastChangeTime = currentTime; // Actualizează timpul ultimei schimbări
        }

        prevAngleY = angleY; // Actualizează unghiul anterior
      }
    } else {
      Serial.println("Eroare la citirea datelor de la MPU6050.");
    }

    delay(100);
  } else {
    // Modul "Joc de lumini"
    lightShow();
  }
}
