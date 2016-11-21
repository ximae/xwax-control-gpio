
interface control program for xwax. It uses the gpios available in the odroic c1 or c2 to connect switch buttons and a rotary to inject keypresses for the program interface control. This version uses a one pin per switch configuration and due to the odroids interrupt limitations in the gpio, a mix of polling and interrupt driver functions.

needs the wiringpi library.

set up ur desired wiring pi pins in config.h

I have left commented code in the main program for more available actions in xwax if you desire to add them.

IF it is going to be used in a rpi, you can modify the program fora pure interrupt based version.


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
 
 
