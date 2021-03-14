#define SOILSENSORA A0
#define SOILSENSORD D1

double analogSoil = 0.0;
int digitalSoil = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(SOILSENSORA, INPUT);
  pinMode(SOILSENSORD, INPUT);
setupLedMatrix();
  Serial.begin(115200);
  Serial.println("start");  
}
void loop() {

  analogSoil = analogRead(SOILSENSORA);
  digitalSoil = digitalRead(SOILSENSORD);
  Serial.println(analogSoil);
  Serial.println(digitalSoil);

  if(digitalSoil == 1){
    setSad();
    Serial.println("I am thirsty");
  } else {
    setSmiley();
    Serial.println("I am happy");
  }


  delay(1000); // slow down for a second
}
