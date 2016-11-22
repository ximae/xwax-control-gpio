
interface control program for xwax. It uses the gpios available in the odroic c1 or c2 to connect switch buttons and a rotary to inject keypresses for the program interface control. This version uses a one pin per switch configuration and due to the odroids interrupt limitations in the gpio, a mix of gpio pin polling and gpio interrupt driven functions.

needs the wiringpi library.

set up ur desired wiring pi pins in config.h

I have left commented code in the main program for more available actions in xwax if you desire to add them.

If it is going to be used in a rpi 2/3, you can modify the program for a pure interrupt based version:

  - expand on the wiringPiISR functions so it is reading all the pins/functions you need.
  - remove the pinMode and pullUpDnControl control functions for those pins.
  - remove the array and its initialization before the main loop
  - remove all the if conditionals from main while loop, you can also even further slow it down if you want through the usleep() in it. 
  
   This way the main loop will just lock the program in an infinite and slow loop, while it waits for the interrupts on the wiringPiISR   functions, which have their own threads.



How to test:
 	  Use the SoC's pull-up and pull down resistors that are avalable	on input pins. 
    
    So compile & run this program (via sudo):
    
    gcc -Wall -o xwaxcontrol xwaxcontrol.c rotaryencoder.c keysend.c -lwiringPi -lpthread
    
    sudo ./xwaxcontrol
    
    then in another terminal:
     
 	 	gpio mode 0 up
 	 	gpio mode 0 down
 	
  at which point it should trigger an interrupt. Toggle the pin
 	up/down to generate more interrupts to test.


compile:
 
  gcc -Wall -o xwaxcontrol xwaxcontrol.c rotaryencoder.c keysend.c -lwiringPi -lpthread
 
 
