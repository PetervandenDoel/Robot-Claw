Pictures have been included and below the pictures there is an explanation of design choices


<img src="https://github.com/PetervandenDoel/Robot-Claw/assets/73015873/af0889a6-7423-4307-9a6c-34c6a29ee2d0" width="400" height="300" />

<img src="https://github.com/PetervandenDoel/Robot-Claw/assets/73015873/51e9a5e7-8e7a-490d-8dcb-96f2d673c20e" width="400" height="300" />
<img src="https://github.com/PetervandenDoel/Robot-Claw/assets/73015873/6382f749-248e-4361-b53c-ef7e72ca8670" width="400" height="300" />

<img src="https://github.com/PetervandenDoel/Robot-Claw/assets/73015873/15f82367-69b0-4884-9342-ba6e84c2b8d0" width="400" height="300" />

<img src="https://github.com/PetervandenDoel/Robot-Claw/assets/73015873/8a9e8ee0-6425-4c25-b33c-d96be40cbf88" width="400" height="300" />


**Design choices:**

**Power planes:** a ground and 12 Volt plane were used in order to minimize the impedance between the power supply and components

**power supply** 12V barrel jack will normally supply power, but there is also a 12V GND header which allows for other power supplies to be used besides just the barrel Jack. The 5V GND header proved useful for providing only digital power when trying to debug our design without actually driving the motor and causing our claw to move; it allowed to test our state machine, decoder, and control system while moving the claw by hand.

**Motor Traces:** the PCB traces supplying the motor with power were made very thick in order to minimize resistance

**Headers:** There are two sets of headers, one to connect the analog PCB to the digital PCB and the other one to connect the analog PCB to the motor. for both of them an additional debug header was provided. The motor debug header proved useful for debugging because it allowed us to probe the motor's encoder pulses and power signals. A pure 5V GND and 12V GND header were also included to allow us to supply power to other devices, serve as an additional power source besides the barrel Jack, and hotswap power supply regulation capacitors to see what worked for us.

**PCB shape:** the PCB's edges were clipped in order to avoid having 90 degree edges on our power planes. The PCB was also designed to be compact and small to fit within an internal compartment of the claw


**Motor driver:** A premade H bridge IC with sufficent rated current simplifies the process of driving the motor and allows us to not have to worry about any of the complex timing that goes into designing an H bridge driver to avoid shorts 

**Motor** a JGA25 brshed DC motor was chosen with a built in decoder and 42 to one gearbox to allow for sufficient torque and for the motor shaft to be directly coupled to our claw mechanism without needing to construct a gearbox ourselves

**room for improvement** 

**too much room for caps** the Altium footprints chosen for our power supply regulation capacitors are way too big for what we actually used, some smaller ones would have helped us save space

**analog to digital PCB header** the plastic clip to connect the analog PCB to the digital PCB never ended up being used. It would have been better to have two identical thru-hole headers to allow for debugging the signals that would go from the analog to digital board.

