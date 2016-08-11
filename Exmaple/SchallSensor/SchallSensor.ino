/*
                      ***SatixCommunity***
                    http://www.satixcommunity.de
Autor:     Felix
Beschreibung: In diesem Progeamm wollen wir einen HC - SR04 Ultraschallsensor
              auslesen und uns den Wert im SeriellenMoitor anzeigen lassen.

Bei Fragen, Anregungen, oder Verbesserungsvorschlaegen schreibt einfach bei uns ins Forum,
oder meldet euch bei mir unter: felix@satixcommunity.de

Wenn ihr schnell mehr ueber Funktionen o.ae. wissen wollt, schaut einfach hier vorbei: https://www.arduino.cc/en/Reference/HomePage
*/

// Der Trigger Pin sendet das Signal.
#define TRIGGER_PIN 9
// Der Echo Pin 'lauscht' auf das Signal
#define ECHO_PIN 8

// Hier berechnen wir die Schallgeschwindigkeit mit 20°C.
// Wenn die Temperatur bei euch stark abweicht, ersetzt sie einfach
// durch den Celsius Wert.
float schallGeschwindigkeit  = 331.5 + 0.6 * 20;

void setup()
{
  Serial.begin(9600);

  // Da der Trigger Pin sendet, ist es ein output.
  pinMode(TRIGGER_PIN, OUTPUT);
  // Da der Echo Pin auf das Signal 'lauscht' ist es ein input.
  pinMode(ECHO_PIN, INPUT);
}

void loop()
{
  Serial.println(distanceInCm());

  delay(500);
}

float distanceInCm()
{
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(3);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(TRIGGER_PIN, LOW);

  // Hier erfassen wir den Impuls, den der Trigger Pin gesendet hat.
  float tInMs = pulseIn(ECHO_PIN, HIGH); // Der Impuls wird in Microsekunden ausgegeben.

  // Diese Zeit rechnen wir jetzt in Sekunden um
  // Mikrosekunden / 1000 = Millisekunden / 1000 = Sekunden.
  // Dann teilen wir das ganze durch 2, da wir ja nur den halbe Strecke wollen.
  // Also die Entfernung vom Schallsensor bis zum Objekt, das angepingt wird.
  float tInS = tInMs / 1000.0 / 1000.0 / 2;
  
  // Nun Multiplizieren wir das ganze mit unserer Schallgeschwindigkeit
  // um die distanz in Metern zu bekommen.
  float distance = tInS * schallGeschwindigkeit;

  // Die Distanz mit 100 multiplizieren, damit wir
  // die Distanz in cm ausgegeben bekommen.
  return distance * 100;
}

