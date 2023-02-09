# Part 4: Occupancy Detection and Alert System
You are being asked to design a rudimentary occupancy alert system with the following behavior:
- The system when turned on needs to blink the Green LED once every 3 seconds to show it is armed.
- When the occupancy sensor detects someone, it will output a Logic 1, and your system needs to move into a "Warning" state, where the Green LED stops blinking, and the Red LED Blinks once per second (500ms on, 500ms off).
- If the occupancy detector still shows someone there after 10 seconds, your system should indicate this with the RED Led constantly staying on, and move into the ALERT state.
- If the occupancy detector **before** the 15 seconds goes back to a 0, indicating the room is now empty, then the system should go back to the armed state.
- When in the ALERT State, the only way for the system to go back to the Armed state is to press the P4.1 Button.

## Occupancy Sensor
You will be **first** *emulating* the Occupancy Sensor with the P4.1 button. This can be used for pretty much all of your testing and design.

When you have a design that is working, you can then test your code with a [Passive Infrared Occupancy Detector](https://www.amazon.com/DIYmall-HC-SR501-Motion-Infrared-Arduino/dp/B012ZZ4LPM)

## Getting Started
I highly recommend on paper or a whiteboard drawing up a state machine or something to help understand the flow of the system.

From there, you should work on each stage/state and see if the transitions work. For example, can you get the system to go from the armed state to the warning state.

Remember that your code is going to be running in a loop, so you need to make sure you consider how this is going to work when trying to blink the LEDs.

## Do I need to use Interrupts?
Well, it would be cool, but at the end of the day, we are asking you for a design. Start with polling or what you feel comfortable with, but we would like you to try out using the interrupts, maybe at least for the system Disarm Button.

## Navigating multiple states
One way to approach a system with multiple states is to actually use a case statement in your main loop. For example:
```c
#define ARMED_STATE 0
#define WARNING_STATE 1
#define ALERT_STATE 2

// Put some initialization here

char state = ARMED_STATE;

while(1)
{
  switch (state) {
    case ARMED_STATE:
    {
      // Do something in the ARMED state
      // If something happens, you can move into the WARNING_STATE
      // state = WARNING_STATE
    }
    case WARNING_STATE:
    {
      // Do something in the WARNING_STATE
    }
  }
}
```

## Submission
There is a sample file in this folder you will need to import into your Code Composer and work on. You will need to submit that file, documented well, and a README.md file (you can replace this one) with the documentation that tells someone about what the code is, what it does, how it works etc. For an audience for your README, imagine you at the beginning of the lab, looking for code which does, well, this. 

**LAB REPORT

The goal of this lab was to develop an occupancy sensor that has three states. ARMED, WARNING, and ALERT. For my code, I decided to use polling instend of interrupts. It starts with the watchdog timer being stopped, followed by intiallization of P1.0 and P6.6. This intiallization will configure the LED registers to be clear and set them as outputs. Additionally, P4.1 and P2.3 are configured here as well, both enabled as pull up resistors. P4.1 acts as our "sensor" and P2.3 is the reset button. Finally, I have a global variable totatltime, set as 0. This will ensure that my timer always starts at 0 at boot up.

This brings us to the while(1) loop. Here, the goal is to have the system constantly check for changes in P4.1 and it will make a decision based on P4.1's status:

-The first check is an if statement that checks if P4.1 is NOT pressed and if the totaltime variable is less than 10 seconds. If this condition is met, P6.6, the green LED, will blink every 3 seconds and P1.0, the red LED, will stay turned off. This indictates the ARMED state.

-The second check is another if statement. This one checks if P4.1 IS pressed and if totatltime is less than 10 seconds. If this condition is met, the red LED will blink every 5ms, and the green LED will stay turned off. This is only true if the P4.1 button is constantly held down. if it is released within 10 seconds, it will revert back to the ARMED state. Within this if statement as well, there is a counter, totaltime=totaltime+1 this will update the totaltime variable to however long the button was held. This indicates the WARNING state, and will change to ALERT when 10 seconds is reached.

-The third check is also an if statement. This one simply checks the value of totaltime. If totaltime equals 10 seconds, (or 0x14 in my case) the red LED will stop blinking and stay solid red, even if the P4.1 button is released after the 10 seconds. This indicates the ALERT state.

-The final check is another if statement. This one checks to see if P2.3, the reset button, is pressed. If this condition is met, totaltime is reset to 0. This will clear the timer and as a result, the system will return back to the armed state. This is the only way to clear the ALERT state.
