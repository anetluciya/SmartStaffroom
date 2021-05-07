#include <SPI.h> //Call SPI library so you can communicate with the nRF24L01+
#include <nRF24L01.h>
#include <RF24.h>

const int pinCE = 9; //This pin is used to set the nRF24 to standby (0) or active mode (1)
const int pinCSN = 10;
RF24 radio(pinCE, pinCSN); // Declare object from nRF24 library (Create your wireless SPI)
const uint64_t rAddress = 0xE8E8F0F0E1LL;
typedef struct{
int node;
int activity;
float temp;
int light;
}data;

data tr;

void setup()
{
Serial.begin(9600);  //start serial to communication
Serial.println("Server On. Listening for transmissions ");
radio.begin();  //Start the nRF24 module
radio.openReadingPipe(1,rAddress);
radio.startListening();             	// Start listening for messages
}

void loop()
{
byte pipeNum = 0; //variable to hold which reading pipe sent data
byte gotByte = 0; //used to store payload from transmit module

while(radio.available(&pipeNum)){ //Check if recieved data
radio.read( &tr, sizeof(tr) ); //read one byte of data and store it in gotByte variable
Serial.print("Transmitter: ");
Serial.print(tr.node); //print which pipe or transmitter this is from
Serial.print("\t Activity: ");
Serial.print(tr.activity); //print payload or the number the transmitter guessed
Serial.print("\t Temp: ");
Serial.print(tr.temp); //print payload or the number the transmitter guessed
Serial.print("\t Light: ");
Serial.print(tr.light); //print payload or the number the transmitter guessed
Serial.println();
}
delay(100);
}
