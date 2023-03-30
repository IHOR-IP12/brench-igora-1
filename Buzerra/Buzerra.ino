const int trigPin = 9;
const int echoPin = 8;
const int motor = 5;
const int buzzerPin = 3;
const int batteryPin = A0; 
long duration = 0;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motor, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

long distance(long time)
{
  long distanceCalc;
  distanceCalc = ((time * 0.034) / 2); // centimeters
  return distanceCalc;
}

bool isBatteryLow()
{
  int batteryReading = analogRead(batteryPin);
  float batteryVoltage = batteryReading * (5.0 / 1023.0) * 2; 
  return batteryVoltage < 6.0; // необхідно буде змінити в залежності від того яка батарея

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(1);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(3);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  long distanceCm = distance(duration);
  if (distanceCm <= 160 && distanceCm > 50)
  {
    digitalWrite(motor, HIGH);
    if (isBatteryLow())
    {
      for (int i = 0; i < 30; i++)
      {
        tone(buzzerPin, 1000, 500);
        delay(500);
      }
    }
    else
    {
      tone(buzzerPin, 1000, 500);
    }
  }
  else
  {
    digitalWrite(motor, LOW);
    noTone(buzzerPin);
  }
  Serial.print("Distance = ");
  Serial.print(distanceCm);
  Serial.println(" cm");
  delay(500);
}
