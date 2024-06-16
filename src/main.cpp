#include "Arduino.h"
#include "MIDIUSB.h"

midiEventPacket_t rx;
bool _blink = false;

void blink(void){
    digitalWrite(LED_BUILTIN, _blink);
    _blink = !_blink;
}

void usb_device_loop(void)
{
    rx = MidiUSB.read();
	if (rx.header != 0){
        Serial1.write((uint8_t *)&rx, 4);
        blink();
	} 
}

uint8_t uart_buf[4] = {0};
size_t buf_p = 0;

void midi_uart_loop(void){
    int data = Serial1.read();
    if(data != -1){
        uart_buf[buf_p] = (uint8_t)data;
        buf_p++;
        if(buf_p == 4){
            MidiUSB.write(uart_buf, 4);
            buf_p = 0;
        }
        MidiUSB.flush();
        blink();
    }
}


void setup(){
    Serial1.begin(31250);
    blink();
}

void loop(){
    usb_device_loop();
    midi_uart_loop();
}