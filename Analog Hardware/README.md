Pictures have been included and below the pictures there is an explanation of design choices


<img src="https://github.com/PetervandenDoel/Robot-Claw/assets/73015873/af0889a6-7423-4307-9a6c-34c6a29ee2d0" width="400" height="300" />

<img src="https://github.com/PetervandenDoel/Robot-Claw/assets/73015873/51e9a5e7-8e7a-490d-8dcb-96f2d673c20e" width="400" height="300" />
<img src="https://github.com/PetervandenDoel/Robot-Claw/assets/73015873/6382f749-248e-4361-b53c-ef7e72ca8670" width="400" height="300" />

<img src="https://github.com/PetervandenDoel/Robot-Claw/assets/73015873/15f82367-69b0-4884-9342-ba6e84c2b8d0" width="400" height="300" />

<img src="https://github.com/PetervandenDoel/Robot-Claw/assets/73015873/8a9e8ee0-6425-4c25-b33c-d96be40cbf88" width="400" height="300" />


Design choices:

Power planes: a ground and 12 Volt plane were used in order to minimize the impedance between the power supply and components
Motor Traces: the PCB traces supplying the motor with power were made very thick in order to minimize resistance

Headers: an identical pair of headers was used for the motor connections, one was connected to the motor and one proved useful for debugging because it allowed us to probe the motors encoder pulses and power signals. A pure 5 Volt and 12 Volt header were also included to allow us to get 5 Volt or 12 Volt power easily to anywhere. This also served as an additional header to which we could attach capacitors for filtering the power signals. 

PCB shape: the PCB's edges were clipped in order to avoid having 90 degree edges on our power planes

Motor driver


