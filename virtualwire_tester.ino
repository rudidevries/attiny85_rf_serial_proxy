#include <VirtualWire.h>

const int vw_receive_pin = 7;
const int vw_transmit_pin = 12;

char inChar = 0;
byte count = 1;

void setup() {
  // put your setup code here, to run once:
  vw_set_rx_pin(vw_receive_pin);
  vw_set_tx_pin(vw_transmit_pin);
  vw_setup(2000);
  
  Serial.begin(9600);
}

void loop() {
  char msg[9] = {'h','e','l','l','o',' ', '#', '\r','\n'};

  msg[6] = count;
  vw_send((uint8_t *)msg, 9);
  vw_wait_tx(); // Wait until the whole message is gone
  delay(1000);
  count = count + 1;
  
  while (Serial.available() > 0) {
          // read the incoming byte:
          inChar = (char) Serial.read();

          // say what you got:
          Serial.print("I received: ");
          Serial.println(inChar);
  }
}
