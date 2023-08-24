The PCB for all the digital hardware. Below the images is an explanation of design choices.

<img src="https://github.com/PetervandenDoel/Robot-Claw/assets/73015873/27716c2b-3801-4ce6-bc72-dd474d37a0b1" width="700" height="400" />



<img src="https://github.com/PetervandenDoel/Robot-Claw/assets/73015873/295caf69-c65b-4892-b7d5-8aabb33e5432" width="700" height="400" />


<img src="https://github.com/PetervandenDoel/Robot-Claw/assets/73015873/d133d0b1-39c8-410c-9bc2-9dcd4601d2da" width="700" height="400" />


<img src="https://github.com/PetervandenDoel/Robot-Claw/assets/73015873/50656222-de1f-4df2-a5ca-3444cfa94f17" width="700" height="400" />


<img src="https://github.com/PetervandenDoel/Robot-Claw/assets/73015873/e829cc34-ff70-43ec-9e00-15822eba24f5" width="700" height="400" />


**Decoder and MUX:** The motor decoder chip that was chosen counts encoder pulses and returns them as a 32 bit value. The data is accessed across 8 pins with a 2 bit internal multiplexer to iterate through each set of eight bits to retrieve the 32 bit value. In order to save on GPI opens a three bit multiplexer was used which complicated the firmware's get_position() routine,  



**Headers:** This is really the key theme of this PCB so the header types will be discussed individually. All of the all the headers used in this PCB were arduino female headers with clips inside of them similar to this screenshot.

<img src="https://github.com/PetervandenDoel/Robot-Claw/assets/73015873/020b1d6c-8450-42b5-88df-2fa568d9b31e" width="400" height="200" />

**Level shifter headers:** the headers labelled MUXLS, MISCLS, DECLS, and ANLS are for adafruit level shifters to shift the signals between the 3.3V ESP32 and the 5V multiplexer, ultrasound sensor, decoder, and analog PCB interface respectively. While the ESP 32 can tolerate 5 volts as an input, it cannot output 3.3 volts and it is simply best practice to level shift either way. It proved useful to keep the level shifters and headers because they could be removed to perform tests with breadboard prototypes or use the headers as debug pins and placed back in whenever we wanted. At one point when we did not have an ESP32 available, we simply shorted all of the level shifter headers together with jumpers and ran the board using a 5V Arduino mega.

**ESP32 Headers:** The ESP 32 dev board could be removed and plug back into headers as opposed to having it soldered into the PCB. The ESP 32 would actually refuse to have code flashed on to it when it was plugged into the PCB or our breadboard prototype(probably something to do with where TX and RX pins are connected) so the arduino style headers proved essential. The second set of debug headers directly adjacent also proved to be extremely useful when trying to identify issues with noise and multiplexer signals
