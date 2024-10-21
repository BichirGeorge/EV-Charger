#include <Arduino.h>

// Definesc pinii pentru butoanele de start si stop
int startButton = 2;
int stopButton = 3;

// Definesc pinii pentru LED-urile rgb: albastru, verde si rosu
int rgbblue = 4;
int rgbgreen = 5;
int rgbred = 6;

// Definesc pinii pentru LED-urile care simuleaza incarcarea bateriei
int led1 = 10;
int led2 = 9;
int led3 = 8;
int led4 = 7;

// Variabilele prin care tin minte starea de incarcare si daca s-a apasat butonul de stop
bool isCharging = false;
bool stopRequested = false;

void startCharging();
void stopCharging();
void simulateCharging();
void resetStation();
void checkStopButton();


unsigned long stopButtonPressTime = 0; // Variabila care stocheaza timpul in care a fost apasat botonul de stop, tine minte cat timp a fost apasat
const unsigned long stopButtonLongPressDuration = 1000; // Variabila care stocheaza cat timp trebuie apsat butonul de stop
unsigned long lastStartDebounceTime = 0; // Variabila care stocheaza timpul in care a fost apasat botonul de start, tine minte cat timp a fost apasat
unsigned long debounceDelay = 50; // Variabila care stocheaza cat timp trebuie apsat butonul de start 
int lastStartButtonState = HIGH; // Variabila care stocheaza starea anterioara a butonului de start

const unsigned long LED_BLINK_DELAY = 500;

void setup()
{
  pinMode(startButton, INPUT);
  pinMode(stopButton, INPUT);

  pinMode(rgbgreen, OUTPUT);
  pinMode(rgbred, OUTPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  // Pornesc starea initiala in care LED-ul rgb este culoarea verde
  digitalWrite(rgbgreen, HIGH);
  digitalWrite(rgbred, LOW);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  // Citesc starea butonului de start
  int currentStartButtonState = digitalRead(startButton);

    // Daca butonul de start si-a schimbat starea, atunci resetam timer-ul pentru debounce
    if (currentStartButtonState != lastStartButtonState) {
      lastStartDebounceTime = millis();
    }

    // Daca timpul de bounce a trecut si butonul de start a fost apasat, atunci incepem animatia de incarcare
    if ((millis() - lastStartDebounceTime) > debounceDelay) {
      if (currentStartButtonState == LOW && !isCharging) {
        startCharging();
      }
    }
  // Updatam ultima stare a butonul de start 
  lastStartButtonState = currentStartButtonState;

  // Verific starea butonul de stop
  checkStopButton();

  // Daca trebuie sa se incarce, atunci incepem simularea incarcarii
  if (isCharging) {
    simulateCharging();
  }
}

// Functia pentru inceperea incarcarii
void startCharging() {
  isCharging = true;
  stopRequested = false;

  // Opresc  RGB-ul verde si aprind RGB-ul rosu pentru a arata ca incarcarea a inceput
  digitalWrite(rgbgreen, LOW);
  digitalWrite(rgbred, HIGH);
}

// Functie pentru a verifica daca butonul de stop este apasat 
void checkStopButton() {

  // Daca butonul de stop este apasat
  if (digitalRead(stopButton) == LOW) {
    if (stopButtonPressTime == 0) {

      // Incep sa contorizez cat timp a fost apasat butonul de start
      stopButtonPressTime = millis();

      // Daca acesta a fost apasat mai mult decat timp-ul prestabilit, atunci opresc simularea incarcarii
    } else if (millis() - stopButtonPressTime >= stopButtonLongPressDuration) {
      if (isCharging) {
        stopRequested = true;
      }
    }
  } else {
    stopButtonPressTime = 0; // Daca butonul nu mai este apasat, atunci resetam contorul
  }
}

// Functia pentru simularea procesului de incarcare
void simulateCharging() {
  int leds[] = {led1, led2, led3, led4};

  // Trecem prin fiecare bec
  for (int i = 0; i < 4; i++) {  
    // Fiecare LED se aprinde si se stinge de 3 ori
    for (int j = 0; j < 3; j++) {
      digitalWrite(leds[i], HIGH);
      delay(LED_BLINK_DELAY);
      digitalWrite(leds[i], LOW);
      delay(LED_BLINK_DELAY);

      // Verific daca butonul de stop a fost apasat, iar daca a fost apasat opresc incarcarea
      checkStopButton();
      if (stopRequested) {
        stopCharging();
        return;
      }
    }

    // LED-ul ramane arpins
    digitalWrite(leds[i], HIGH);

    // Verific din nou daca butonul de stop a fost apasat
    checkStopButton();
    if (stopRequested) {
      stopCharging();
      return;
    }
  }

  //Apelez functia pentru a arata ca incarcarea a fost finalizata si incarcarea se opreste
  stopCharging();
}

// Functia de animatie pentru finalizarea incarcarii 
void stopCharging() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    delay(LED_BLINK_DELAY);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    delay(LED_BLINK_DELAY);
  }

  resetStation();  // Resetam statia la starea initiala 
}

// Functia de resetare la starea initiala
void resetStation() {
  isCharging = false;
  stopRequested = false;

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);

  digitalWrite(rgbred, LOW);
  digitalWrite(rgbgreen, HIGH);
}
