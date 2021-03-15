# Read moisture

Ok great! if you are here you have set up your working environment properly and you have a blinking NODE MCU. If not go back :D.

## Wire up the moisture sensor

ok its time to wire up our moisture sensor. en start reading the information what comes trough.
in the table you can see where to connect what Or just look at the image :D

| Sensor        | NODEMCU       |
| ------------- |:-------------:|
| A0            | A0            |
| D0            | D1            |
| GND           | GND           |
| VCC           | 3.3V          |

![alt text](https://raw.githubusercontent.com/svenvs/socialPlant/main/pictures/MCUandMoistSensor_bb.png "Logo Title Text 1")

## Add the code

The thing what we need todo is basically read the sensor data from the Sensor. we have 2 ways of doing trough the Analog pin A0 or the Digital pin D1.

To start using these pins in our code we need to define them and make them as input pins. In the example code below you can see an example.

[Example file](https://github.com/svenvs/socialPlant/blob/main/codeExamples/ReadMoisture/plantMood.ino)

```C++
#define SOILSENSORA A0 // define the pins
#define SOILSENSORD D1 // define the pins


//Some vars to store values
double analogSoil = 0.0;
int digitalSoil = 0;


void setup() {
  // put your setup code here, to run once:
  
  // setting the mode of the pins
  pinMode(SOILSENSORA, INPUT);
  pinMode(SOILSENSORD, INPUT);

  //We set the Serial for debugging we can use it to log
  Serial.begin(115200);
  Serial.println("start");  
}
void loop() {
  // read values from the sensor
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
```
