The PCB for all the digital hardware. Below the images is an explanation of design choices.

<img src="https://github.com/PetervandenDoel/Robot-Claw/assets/73015873/27716c2b-3801-4ce6-bc72-dd474d37a0b1" width="700" height="400" />



<img src="https://github.com/PetervandenDoel/Robot-Claw/assets/73015873/295caf69-c65b-4892-b7d5-8aabb33e5432" width="700" height="400" />


<img src="https://github.com/PetervandenDoel/Robot-Claw/assets/73015873/d133d0b1-39c8-410c-9bc2-9dcd4601d2da" width="700" height="400" />


<img src="https://github.com/PetervandenDoel/Robot-Claw/assets/73015873/50656222-de1f-4df2-a5ca-3444cfa94f17" width="700" height="400" />


<img src="https://github.com/PetervandenDoel/Robot-Claw/assets/73015873/e829cc34-ff70-43ec-9e00-15822eba24f5" width="700" height="400" />



**Decoder and MUX saving GPIOs:** The motor decoder chip that was chosen counts encoder pulses and returns them as a 32 bit value. The decoder requires a clock which is what the crystal oscillator on the PCB is for. The data is accessed across 8 pins with a 2 bit internal multiplexer to iterate through each set of eight bits to retrieve the 32 bit value. With 8 data pins and four pins for interfacing with it, the decoder requires a total of 12 GPIO pins to function. In order to save on GPIO pins a three bit multiplexer was used which complicated the firmware's get_position() routine, but reduced the number of data pins down from 8 to 3 select pins and 1 data input for a total of only 8 GPIO pins needed to read the motor's position.  


**Headers:** This is really the key theme of this PCB so the header types will be discussed individually. All of the all the headers used in this PCB were arduino female headers with clips inside of them similar to this screenshot.

<img src="https://github.com/PetervandenDoel/Robot-Claw/assets/73015873/020b1d6c-8450-42b5-88df-2fa568d9b31e" width="400" height="200" />

**Level shifter headers:** the headers labelled MUXLS, MISCLS, DECLS, and ANLS are for adafruit level shifters to shift the signals between the 3.3V ESP32 and the 5V multiplexer, ultrasound sensor, decoder, and analog PCB interface respectively. While the ESP 32 can tolerate 5 volts as an input, it cannot output 3.3 volts and it is simply best practice to level shift either way. It proved useful to keep the level shifters and headers because they could be removed to perform tests with breadboard prototypes or use the headers as debug pins and placed back in whenever we wanted. At one point when we did not have an ESP32 available, we simply shorted all of the level shifter headers together with jumpers and ran the board using a 5V Arduino mega.

**ESP32 Headers:** The ESP 32 dev board could be removed and plug back into headers as opposed to having it soldered into the PCB. The ESP 32 would actually refuse to have code flashed on to it when it was plugged into the PCB or our breadboard prototype(probably something to do with where TX and RX pins are connected) so the arduino style headers proved essential. The second set of debug headers directly adjacent also proved to be extremely useful when trying to identify issues with noise and multiplexer signals

There are two other headers one to connect the ultrasonic distance sensor module to the esp, and one that connects to the analog PCB to control the motor and act as a 5V power supply for the digital hardware.

**Power planes:** A 5V(red) and GND(blue) plane were implemented with the aim of reducing noise, this should have been done differently and will be discussed among potential improvements 


**potential improvements**

**Decoder crosstalk(main issue):** 
**How do we know the issue is crosstalk?** The motor's position value that the ESP32 acquired from the decoder+MUX was quite prone to spiking and some digital low pass filtering had to be implemented to tell the PID controller to ignore junk data. If the encoder signals themselves were having problems, the huge spikes would have been stored in the decoder's internal register, but these spikes were transient and the values always settled back to a reasonable one which suggests bits being flipped because of crosstalk on the lines between the decoder and the multiplexer. 

**Why is there crosstalk?** The traces connecting the decoder and multiplexer are so close that some of them don't even have any ground plane separating them to absorb EMI(picture below). In the getByte() function, the select signals of these multiplexers change around once per microsecond so it's unsurprising that these high frequency signals can flip bits on adjacent traces that aren't even shielded from one another, they should have been spaced out more.

<img src="https://github.com/PetervandenDoel/Robot-Claw/assets/73015873/e88be956-3e55-42db-9e52-9a0fb076cbaf" width="300" height="200" />

**Unused routing space:** A lot of traces are routed very close together despite the fact that there is actually a lot of space on the board that routing could be done through.

**Crystal is too large, literally:** A very large thru-hole crystal oscillator was chosen for the motor decoder. Seeing how the crystal just clocks digital hardware inside of the decoder, frequency stability and impedance characteristics aren't very important. It would have been wise to compromise on other characteristics in order to get a smaller crystal. 

**Aesthetics:**
**Non-symmetrical screw holes:** Our professor actually criticized us for this funnily enough. There are two holes for screws on the top of the PCB but not the bottom and the asymmetry is kind of weird.
**Sporadic name placement:** Our names are placed in random spots all over the PCB wherever we could fit them, we don't have one nice little corner that we put all of them in; it could look a lot better.
