# The tutorial

Ok great! if you are here you have set up your working environment properly and you have a blinking NODE MCU. If not go back :D.

## The moisture sensor

Let's start with the moisture sensor. This will be the easiest part where we hook up some wire's and start reading its data.

### Wiring it up

ok its time to wire up our moisture sensor. en start reading the information what comes trough.
in the table you can see where to connect what Or just look at the image :D

| Sensor        | NODEMCU       |
| ------------- |:-------------:|
| A0            | A0            |
| D0            | D1            |
| GND           | GND           |
| VCC           | 3V3           |

![alt text](https://raw.githubusercontent.com/svenvs/socialPlant/main/pictures/MCUandMoistSensor_bb.png "Sensor wirering diagram")

### Add the code

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

What good is to know the analog pin will give a number from 0 to 1024 where 1024 is completely dry and 0 soaking wett. And the digital pin will give a 1 or 0 where the 1 is dry and the 0 is wett. You can use a screwdriver to change the intensity on the sensor module.

### Debug to see it working

If you uploaded the code and added some ``` Serial.println("I am happy"); ``` you can see those in the serial monitor inside your arduino IDE. you can find it here:

And you see some weirt charcters or just nothing please check the serial boudrate and make it the same one as in your code: ```Serial.begin(115200);```

## The LED matrix

If you have seen your logs inside your monitor. Then you are ready for the next step! Lets add a visual representation to your NODEMCU.

### Connecting the wires

Ok we are using a MAX7219 for our DOT Matrix else we had to connect allot more wires. So here again a table and an image how to connect.

![alt text](https://raw.githubusercontent.com/svenvs/socialPlant/main/pictures/MCUandMoistSensorMatrix_bb.png "Sensor wirering diagram including matrix")

| Matrix        | NODEMCU       |
| ------------- |:-------------:|
| VCC           | 3V3           |
| GND           | GND           |
| DIN           | D7            |
| CS            | D8            |
| CLK           | D5            |

### Code for the Matrix

because its allot of code we will create an extra tab to put it. To keep our main much more readable.

You can create a tab by click on the arrow down sign (:arrow_down_small:) click on new tab and give it a name does not matter which name you will give it.

When thats done you can add the following code:

```C++
unsigned char i;
unsigned char j;

int Max7219_pinCLK = D5;
int Max7219_pinCS = D8;
int Max7219_pinDIN = D7;
 
unsigned char disp1[41][8]={
{0x3C,0x42,0xA5,0x81,0xA5,0x99,0x42,0x3C},// smile
{0x3C,0x42,0xA5,0x81,0xBD,0x81,0x42,0x3C},//neutral
{0x3C,0x42,0xA5,0x81,0x99,0xA5,0x42,0x3C},//sad
{0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},//0
{0x10,0x18,0x14,0x10,0x10,0x10,0x10,0x10},//1
{0x7E,0x2,0x2,0x7E,0x40,0x40,0x40,0x7E},//2
{0x3E,0x2,0x2,0x3E,0x2,0x2,0x3E,0x0},//3
{0x8,0x18,0x28,0x48,0xFE,0x8,0x8,0x8},//4
{0x3C,0x20,0x20,0x3C,0x4,0x4,0x3C,0x0},//5
{0x3C,0x20,0x20,0x3C,0x24,0x24,0x3C,0x0},//6
{0x3E,0x22,0x4,0x8,0x8,0x8,0x8,0x8},//7
{0x0,0x3E,0x22,0x22,0x3E,0x22,0x22,0x3E},//8
{0x3E,0x22,0x22,0x3E,0x2,0x2,0x2,0x3E},//9
{0x8,0x14,0x22,0x3E,0x22,0x22,0x22,0x22},//A
{0x3C,0x22,0x22,0x3E,0x22,0x22,0x3C,0x0},//B
{0x3C,0x40,0x40,0x40,0x40,0x40,0x3C,0x0},//C
{0x7C,0x42,0x42,0x42,0x42,0x42,0x7C,0x0},//D
{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x7C},//E
{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x40},//F
{0x3C,0x40,0x40,0x40,0x40,0x44,0x44,0x3C},//G
{0x44,0x44,0x44,0x7C,0x44,0x44,0x44,0x44},//H
{0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x7C},//I
{0x3C,0x8,0x8,0x8,0x8,0x8,0x48,0x30},//J
{0x0,0x24,0x28,0x30,0x20,0x30,0x28,0x24},//K
{0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7C},//L
{0x81,0xC3,0xA5,0x99,0x81,0x81,0x81,0x81},//M
{0x0,0x42,0x62,0x52,0x4A,0x46,0x42,0x0},//N
{0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},//O
{0x3C,0x22,0x22,0x22,0x3C,0x20,0x20,0x20},//P
{0x1C,0x22,0x22,0x22,0x22,0x26,0x22,0x1D},//Q
{0x3C,0x22,0x22,0x22,0x3C,0x24,0x22,0x21},//R
{0x0,0x1E,0x20,0x20,0x3E,0x2,0x2,0x3C},//S
{0x0,0x3E,0x8,0x8,0x8,0x8,0x8,0x8},//T
{0x42,0x42,0x42,0x42,0x42,0x42,0x22,0x1C},//U
{0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18},//V
{0x0,0x49,0x49,0x49,0x49,0x2A,0x1C,0x0},//W
{0x0,0x41,0x22,0x14,0x8,0x14,0x22,0x41},//X
{0x41,0x22,0x14,0x8,0x8,0x8,0x8,0x8},//Y
{0x0,0x7F,0x2,0x4,0x8,0x10,0x20,0x7F},//Z
};

void Write_Max7219_byte(unsigned char DATA) {   
  unsigned char i;
  digitalWrite(Max7219_pinCS,LOW);    
  for(i=8;i>=1;i--){    
     digitalWrite(Max7219_pinCLK,LOW);
     digitalWrite(Max7219_pinDIN,DATA&0x80);// Extracting a bit data
     DATA = DATA<<1;
     digitalWrite(Max7219_pinCLK,HIGH);
   }                                 
}
 
 
void Write_Max7219(unsigned char address,unsigned char dat){
  digitalWrite(Max7219_pinCS,LOW);
  Write_Max7219_byte(address);           //address，code of LED
  Write_Max7219_byte(dat);               //data，figure on LED
  digitalWrite(Max7219_pinCS,HIGH);
}
 
void Init_MAX7219(void){
 Write_Max7219(0x09, 0x00);       //decoding ：BCD
 Write_Max7219(0x0a, 0x03);       //brightness
 Write_Max7219(0x0b, 0x07);       //scanlimit；8 LEDs
 Write_Max7219(0x0c, 0x01);       //power-down mode：0，normal mode：1
 Write_Max7219(0x0f, 0x00);       //test display：1；EOT，display：0
}

void setupLedMatrix(){
  pinMode(Max7219_pinCLK,OUTPUT);
  pinMode(Max7219_pinCS,OUTPUT);
  pinMode(Max7219_pinDIN,OUTPUT);
  delay(50);
  Init_MAX7219();
}

void setSmiley(){
  j=0;
   for(i=1;i<9;i++){
    Write_Max7219(i,disp1[j][i-1]);
   }
}

void setNeutral(){
  j=1;
   for(i=1;i<9;i++){
    Write_Max7219(i,disp1[j][i-1]);
   }
}

void setSad(){
  j=2;
   for(i=1;i<9;i++){
    Write_Max7219(i,disp1[j][i-1]);
   }
}

void loopAll(){
     for(j=0;j<41;j++)
  {
   for(i=1;i<9;i++)
    Write_Max7219(i,disp1[j][i-1]);
   delay(500);
  }  
}
```

Yeah I know this code can be much cleaner And ill do so in the future. But for now just take it :innocent:.

When you have the code in a TAB we can use it in our main file.

in the setup of your main add: ```setupLedMatrix();``` this will make sure the matrix is setup properly.

And you will now be able to use the methods: ```setNeutral();```, ```setSad();```, ```setSmiley();``` and as the method names tell you thats what they do to the matrix.

You can see my example code here:

```C++
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
```

All done? Great job you just ranked up to the next level! by giving you plant feelings! Going strong :D

![alt text](https://media.tenor.com/images/780e5fedbbb97b37b52c84f318f60f6a/tenor.gif "Win baby that celebrates our nice victory")

## Hook it up to the internetz

Ok now the most challangeing part off all will start lets hook up our plant to the internet.
We have a few steps to take care off. We need to give the plant a way to tell us when he or she is thirsty. We will use Telegram for that by using their BOT api so lets start there by creating a BOT.

### You need a favor from the botFather

When you opend up Telegram on the right search for a new contact and type ```BotFather``` and only click on the one with the verified by telegram icon. the rest just ignore. Now you can ask him for a favor to create a bot for you with sending our first message:

```/newbot```

Now you can give your bot a name I have used the @ sign to make a group of bots for all my plants. If I might do that in the future.

Follow the conversation with the BotFather and read carfully what he say's. My conversation did go like this:

![alt text](https://raw.githubusercontent.com/svenvs/socialPlant/main/pictures/BotFatherConversation.png  "Both father conversation")

Eventually you will get a token this is something you will need in the code eventually.

### Hook it up to your WIFI

All still alive with the conversation with the BothFather? Great! now we can start hooking up our plant to the wifi. Lets imidiatly dive into the code!

on top of your mainfile include these to libraries:

```C++
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> //For https :D
```

And define these constants.

```C++
const char* ssid = "SSID";
const char* password = "WIFIPASS";
```

And in your setup you need to include some extra things which are these:

```C++
WiFi.begin(ssid, password); // Start the WIFI connection
  while (WiFi.status() != WL_CONNECTED) { // Wait until its rerady
     delay(500);
     Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP()); // Show the IP adress
```

You can already try this out your NODEMCU should connect to your wifi. In your Serial monitor you will see the IP-adress.

### Connect it to your telegram bot

Ok now that we have a wifi connected plant its time too send some messages. So lets include some libraries to make this possible.

We will use the folowing libraries:

* [ArduinoJSON V6.17.3](https://arduinojson.org/)
* [AsyncTelegram V1.1.2](https://github.com/svenvs/socialPlant/blob/main/codeExamples/ReadMoisture/plantMood.ino)
Arduino Json is used by the AsyncTelegram library

You can install them by going to: Tools > Manage libraries. You should see a screen like this:

![alt text](https://raw.githubusercontent.com/svenvs/socialPlant/main/pictures/asyncTelegram.PNG "search screen arduino")

here you can search for the libraries.

When they are installed we can start enhancing our code with some cool new functionalities.

First we must include our new library like this:

```C++
#include "AsyncTelegram.h"
```

Now instantiate the telegram ```AsyncTelegram``` object

```C++
AsyncTelegram myBot;
```

And create a constance with our token, and make sure that we use SSL

```C++
const char* BotToken = "TOKEN INCLUDING NUMBERS";
WiFiClientSecure net_ssl;
```

Now we can update our setup method to make the connection with Telegram. this is the code you need and you need to have wifi so place it after that is done :D.

```C++
myBot.setClock("CET-1CEST,M3.5.0,M10.5.0/3");

// Set the Telegram bot properies
myBot.setUpdateTime(2000);
myBot.setTelegramToken(BotToken);

Serial.print("\nTest Telegram connection... ");
myBot.begin() ? Serial.println("OK") : Serial.println("NOK");
```

And in the loop you can start getting and sending messages like so:

```C++
TBMessage msg;
if (myBot.getNewMessage(msg)) {
    if (msg.text.equalsIgnoreCase("HOWRU")) {
        myBot.sendMessage(msg, "Superb!");
    }
}
```

Well now you know it all to make your social plant good luck and have fun!
