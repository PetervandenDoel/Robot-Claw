
<img width="468" alt="ELEC 391 state" src="https://github.com/PetervandenDoel/Robot-Claw/assets/73015873/a092b8a4-749c-4c27-b9c2-955e0ebb2656">

The claw operates as a state machine that will open until a limit switch is hit in order to zero its position, then using an ultrasonic distance sensor it will close when it detects that it is close enough to the ground to pick up an object and once the user carries the claw upwards and then brings it back down above another surface it will drop the object. The claw's position is controlled by driving a motor at a given PWM frequency and direction using a PID control loop triggered at a known control frequency through an interrupt service routine. 

Some firmware design choices

**Filtering: Line 474:** due to bit errors in the signals read from the multiplexers, there are sometimes large spikes in the determined position value. A simple low pass filter is implemented where if the current error differs from the previous error by too large of a number, the previous error is returned. 

**Missed Echos: Line 344:** ultrasound sensor values that are too high are also filtered out because they are assumed to be due to missed echoes

**State machine hysteresis: in every state transition:** I have heard this technique referred to as hysteresis before in some contexts but I'm not sure if that's a proper term. The ultrasonic sensor distance boundaries for transitions between the claw's different states are placed sufficiently far apart enough that rapid transitions when the user has the claw around the border between two states will never happen. 

**get_position modularity: line 113 to 293:** the motor decoder chip outputs a 32 bit value in 8 bit increments determined by select signals fed into the internal multiplexer. Another external multiplexer is used in order to reduce the number of GPIO pins that need to be used to read from the decoder from 8 down to 5. A helper function called getByte was created as a routine to extract one byte of data from the 8 decoder pins by iterating through all the select signals on the external multiplexer. get_position calls getByte 4 times, once for every select signal fed to the decoders internal multiplexer so the total 32 bit value can be acquired

**PID nonlinearities:** due to problems with the static friction of the joints, some nonlinearities were introduced into the PID controller in order to help it behave better. The three PID nonlinearities are listed below and are justified.

**Duty cycle boundries: line 499:** a hard upper and lower limit are placed on the allowable motor driver duty cycles so if the control signal exceeds a certain amount or falls below a certain amount it will be pulled back to within a certain range. Setting a lower bound allows the claw to continue moving as opposed to getting stuck due to static friction when the control signal reduces as the desired position is approached. An upper bound is set because the heavy claws will gain too much momentum if the control signal is allowed to be too high. 

**"settled" condition: line 481:** once the error drops below a certain point the PID loop is told to stop and consider itself to have settled on the correct position as opposed to allowing slight integral error to continue building causing the claw to sharply bounce back and forth. The reason why it sharply bounces back and forth instead of oscillating is because as the control signal slowly builds, the motor slowly starts outputting enough torque to the point where once static friction is overcome the claw will jerk a little bit and then stop again.

**integral error reset:** on every state transition: the integral term for the PID controller is reset every single time a state transition occurs and the new desired position is set. Because the claw moves quite slowly a lot of integral air is build up in the time it takes for the claw to close or open as it does in response to state transitions. This large build of integral error ended up being quite problematic so it was reset to 0 on every state transition

**controlling LED's duty cycle without interrupts: line 442:** in order to avoid any complexities with prioritizing interrupts a single interrupt is used for the PID control loop and controlling the duty cycle of a blinking LED to represent state. Since the LED blinks every 1s the PID loop runs every 0.1s, and the LED duty cycles for the different states differ by increments of 0.1s, an LED counter variable is incremented and modulo operations are used within each state to determine whether the LED should be on or off and this achieves the controlled duty cycle cycle blinking behavior.


**Room for improvement** 

**removing overley cautious multiplexer settle delays** the highly conservative control frequency of 10 Hertz was chosen based on code that gave multiplexer signals excessive amounts of time to settle when acquiring motor position from the decoder. The get_position function has multiple 25ms delays and shortening these delays by orders of magnitude would probably not cause problems and allow for a much faster control frequency and better PID performance.

**Multiple interrupt management**  Since turning an LED on or off is very quick, controlling the LED's duty cycle using another ISR would probably not interrupt our PID controller very much and would have allowed us to have any control frequency we want and any LED duty cycle we want without having to tie the two quantities together in order to use the same interrupt for two tasks.


**separate position acquisition process to allow for increase in control frequency** all of the firmware runs on a single core of the ESP 32, it would be wise to have some tasks like managing the state machine and acquiring the motors's position from the decoder chip running on a separate core from the PID controller and this would allow for a faster control frequency and better performance







