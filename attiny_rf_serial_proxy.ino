
#include <SoftwareSerial.h>
#include <VirtualWire.h>

const int vw_receive_pin = 2;
const int vw_transmit_pin = 3;
const int serial_transmit_pin = 1;
const int serial_receive_pin = 0;
const int led_pin = 13;

char inData[50];
int dataIndex = 0;

SoftwareSerial mySerial(serial_receive_pin, serial_transmit_pin);

void setup() {
  delay(1000);
  pinMode(led_pin, OUTPUT);
  
  // virtual wire receive setup.
  vw_set_rx_pin(vw_receive_pin);
  vw_set_tx_pin(vw_transmit_pin);
  vw_setup(2000);
  vw_rx_start(); 
  
  mySerial.begin(9600);
}

void loop() {
  receiving();
}

void receiving() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_have_message()) {
    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
        digitalWrite(led_pin, HIGH);
        int i;    	
        for (i = 0; i < buflen; i++)
        {
          mySerial.print((char) buf[i]);
        }
        digitalWrite(led_pin, LOW);
    }
  }
}


