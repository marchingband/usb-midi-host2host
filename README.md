# USB MIDI Host 2 Host

This simple firmware allows you to build a USB MIDI Host to Host adapter, using 2 Seeed XIAO SAMD21 boards.  
The same firmware goes on both boards.  
The hardware connections are:
* RX -> TX
* TX -> RX
* GND -> GND

The primary use case is to connect your PC to a MIDI device which only has USB MIDI Host input, weather for testing, or for production or performance.  
Any Baud rate will be fine, I have used 31250 for no particular reason.  
Since both boards are in USB Device mode, power comes from the connected MIDI devices, so no other power is needed.

  
![wiring-pic](https://github.com/marchingband/usb-midi-host2host/assets/34205564/0fbe9b8e-1402-4b51-9e2a-beeaf7168b1b)
