#include "Arduino.h"
#include "MIDIUSB.h"

midiEventPacket_t rx;       // this type comes from the MIDIUSB library.
uint8_t uart_buf[4] = {0};  // store the incomming UART data.
size_t buf_p = 0;           // a pointer for the buffer.
bool _blink = false;

void blink(void){
    digitalWrite(LED_BUILTIN, _blink);
    _blink = !_blink;
}

void usb_device_loop(void)
{
    rx = MidiUSB.read();
    if (rx.header != 0){                    // 0 header is just noise.
        Serial1.write((uint8_t *)&rx, 4);   // midiEventPacket_t is a struct with 4 uint8_t's, so we can cast it to an array.
        blink();
    } 
}

void midi_uart_loop(void){
    int data = Serial1.read();
    if(data != -1){                         // -1 means no data.
        uart_buf[buf_p] = (uint8_t)data;    // cast the int to a uint8_t and add it to the buffer.
        buf_p++;                            // incerement the pointer.
        if(buf_p == 4){                     // USB MIDI packets are always 4 bytes.
            MidiUSB.write(uart_buf, 4);
            MidiUSB.flush();
            buf_p = 0;                      // reset the pointer.
            blink();
        }
    }
}

void setup(){
    Serial1.begin(31250);
    blink();                // turn off the LED to start.
}

void loop(){
    usb_device_loop();
    midi_uart_loop();
}