The claw operates as a state machine that will open until a limit switch is hit in order to zero its position, then using an ultrasonic distance sensor it will close when it detects that it is close enough to the ground to pick up an object and once the user carries A claw upwards and then brings it back down above another surface it will drop the object. The claw's position is controlled by driving a motor at a given PWM frequency using a PID control loop triggered at a known control frequency through an interrupt service routine. 

Some firmware design choices

