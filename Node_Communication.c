#include <SPI.h> //Call SPI library so you can communicate with the nRF24L01+
#include <nRF24L01.h>
#include <RF24.h>

#define node_id 1;
int act_sens = 3;
int temp_sens = A0;
int ldr = A1;



const int pinCE = 9; //This pin is used to set the nRF24 to standby (0) or active mode (1)
const int pinCSN = 10;
RF24 radio(pinCE, pinCSN); // Declare object from nRF24 library (Create your wireless SPI)
const uint64_t wAddress = 0xE8E8F0F0E1LL;

typedef struct{
int node ;
int activity;
float temp;
int light;
}data;

data tr;



void setup()
{
pinMode(act_sens,INPUT);
tr.node = node_id;
Serial.begin(9600);  //start serial to communication
Serial.print("Initialised Node ");
Serial.println(tr.node);
radio.begin();  //Start the nRF24 module
radio.openWritingPipe(wAddress);	// setup pipe to transmit over
radio.stopListening();
}

void loop()
{
tr.activity = digitalRead(act_sens);
tr.temp = (analogRead(temp_sens))*500/1024;
tr.light = analogRead(ldr);
Serial.print("Transmitter: ");
Serial.print(tr.node); //print which pipe or transmitter this is from
Serial.print("\t Activity: ");
Serial.print(tr.activity); //print payload or the number the transmitter guessed
Serial.print("\t Temp: ");
Serial.print(tr.temp); //print payload or the number the transmitter guessed
Serial.print("\t Light: ");
Serial.print(tr.light); //print payload or the number the transmitter guessed

Serial.println();
if (!radio.write( &tr, sizeof(tr) ))
{Serial.println("Data sending failed");}
else
{Serial.println("Data sent to server ");}
radio.powerDown();
delay(1000);
radio.powerUp();
}
