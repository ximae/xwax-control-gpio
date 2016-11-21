/*
 * 
 *
 *
 *	How to test:
 *	  Use the SoC's pull-up and pull down resistors that are avalable
 *	on input pins. So compile & run this program (via sudo), then
 *	in another terminal:
 *		gpio mode 0 up
 *		gpio mode 0 down
 *	at which point it should trigger an interrupt. Toggle the pin
 *	up/down to generate more interrupts to test.
 *
 * compile:
 *
 * gcc -Wall -o keycontrol keycontrol.c rotaryencoder.c keysend.c -lwiringPi -lpthread
 *
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <fcntl.h>
#include "rotaryencoder.h"
#include "config.h"
#include "keysend.h"


#define	DEBOUNCE_TIME	200

// globalComparator:

  int uinp_fd;


/*********** Functions ************/


/* rotary loop thread */


PI_THREAD (rotary_loop) {

struct encoder *encoder = setupencoder(rot1_pin_a,rot1_pin_b);
long value;

 while (1) {

   long l = encoder -> value;
   if (l != value) {
	
	       if ( l > value) { send_Up();  }
     	
	       if ( l < value) { send_Down(); }	
            
            value = l;
	    }

	delay(50);    
  }
}

/* experimental set recorder thread */

PI_THREAD (record) {

   time_t rawtime;
   struct tm *info;

   char filename[80];
   char command[100];

   time( &rawtime );

   info = localtime( &rawtime );
   strftime(filename, 80, "%d_%m_%Y__%H_%M_%S", info);

  strcpy( command, "arecord -f dat -D T6_pair1  --vumeter=stereo " );
  
  strcat(command , filename);
  
  strcat(command , ".wav");

  system(command);
  
  return 0;

} 

/* pendrive mount and rescan function */


void penmount(void) {
  system("umount /dev/sda1");	    
   sleep(1);
  system("mount /dev/sda1 /media/odroid/usbdrive");
   sleep(1);
  send_CST();
   sleep(1);
}


/* myInterrupts functions */


void myInterrupt0 (void) { 
   int debounceTime = DEBOUNCE_TIME ;
   if (millis () < debounceTime)
      {
	debounceTime = millis () + DEBOUNCE_TIME ;
      }
   else { 
         send_F1() ;
         delay(200);
        }
   while (digitalRead (f1) == HIGH) {
      delay (1) ;
      debounceTime = millis () + DEBOUNCE_TIME ;
     }
 }

void myInterrupt1 (void) { 
   int debounceTime = DEBOUNCE_TIME ;
   if (millis () < debounceTime)
      {
	debounceTime = millis () + DEBOUNCE_TIME ;
      }
   else {
         send_F2();
         delay(200);
        }
   while (digitalRead (f2) == HIGH) {
      delay (1) ;
      debounceTime = millis () + DEBOUNCE_TIME ;
     }
 }

void myInterrupt2 (void) { 
   int debounceTime = DEBOUNCE_TIME ;
   if (millis () < debounceTime)
      {
	debounceTime = millis () + DEBOUNCE_TIME ;
      }
   else { 
         send_F3() ;
         delay(200);
        }
   while (digitalRead (f3) == HIGH) {
      delay (1) ;
      debounceTime = millis () + DEBOUNCE_TIME ;
     }
 }

void myInterrupt3 (void) { 
   int debounceTime = DEBOUNCE_TIME ;
   if (millis () < debounceTime)
      {
	debounceTime = millis () + DEBOUNCE_TIME ;
      }
   else { send_F5() ;
          delay(200); 
        }
   while (digitalRead (f5) == HIGH) {
      delay (1) ;
      debounceTime = millis () + DEBOUNCE_TIME ;
     }
 }

void myInterrupt4 (void) {
   int debounceTime = DEBOUNCE_TIME ;
   if (millis () < debounceTime)
      {
	debounceTime = millis () + DEBOUNCE_TIME ;
      }
   else {
         send_F6() ;
         delay(200); 
        }
   while (digitalRead (f6) == HIGH) {
      delay (1) ;
      debounceTime = millis () + DEBOUNCE_TIME ;
     }
 }

void myInterrupt5 (void) {
  int debounceTime = DEBOUNCE_TIME ;
   if (millis () < debounceTime)
      {
	debounceTime = millis () + DEBOUNCE_TIME ;
      }
   else {
         send_F7();
         delay(200);
        }
   while (digitalRead (f7) == HIGH) {
      delay (1) ;
      debounceTime = millis () + DEBOUNCE_TIME ;
     }
 }

void myInterrupt6 (void) { 
  int debounceTime = DEBOUNCE_TIME ;
   if (millis () < debounceTime)
      {
	debounceTime = millis () + DEBOUNCE_TIME ;
      }
   else {
         send_Left(); 
         delay(300);
        }
}

void myInterrupt7 (void) { 
   int debounceTime = DEBOUNCE_TIME ;
   if (millis () < debounceTime)
      {
	debounceTime = millis () + DEBOUNCE_TIME ;
      }
   else {
         send_Right() ; 
         delay(300);
        }
}

void myInterrupt8 (void) {
   int debounceTime = DEBOUNCE_TIME ;
   if (millis () < debounceTime)
      {
	debounceTime = millis () + DEBOUNCE_TIME ;
      }
   else { 
	   send_SF2() ;
	   delay (200);
        }  
   while (digitalRead (sf2) == HIGH) {
      delay (1) ;
      debounceTime = millis () + DEBOUNCE_TIME ;
     }
}

void myInterrupt9 (void) {
   int debounceTime = DEBOUNCE_TIME ;
   if (millis () < debounceTime)
      {
	debounceTime = millis () + DEBOUNCE_TIME ;
      }
   else {
	   send_SF5() ;
	   delay(200);
        }  
   while (digitalRead (sf5) == HIGH) {
      delay (1) ;
      debounceTime = millis () + DEBOUNCE_TIME ;
     }
}

void myInterrupt10 (void) {
   int debounceTime = DEBOUNCE_TIME ;
   if (millis () < debounceTime)
      {
	debounceTime = millis () + DEBOUNCE_TIME ;
      }

   while (digitalRead (cst) == HIGH) {
      delay (1) ;
      debounceTime = millis () + DEBOUNCE_TIME ;
     }
}

void myInterrupt11 (void) {
   int debounceTime = DEBOUNCE_TIME ;
   if (millis () < debounceTime)
      {
	debounceTime = millis () + DEBOUNCE_TIME ;
      }
   else send_CF3() ; 
   while (digitalRead (cf3) == HIGH) {
      delay (1) ;
      debounceTime = millis () + DEBOUNCE_TIME ;
     }
}

void myInterrupt12 (void) {
   int debounceTime = DEBOUNCE_TIME ;
   if (millis () < debounceTime)
      {
	debounceTime = millis () + DEBOUNCE_TIME ;
      }
   else send_CF7() ; 
   while (digitalRead (cf7) == HIGH) {
      delay (1) ;
      debounceTime = millis () + DEBOUNCE_TIME ;
     }
}


 /*
 *********************************************************************************
 * main
 *********************************************************************************
 */

int main (void) {

//setup devices struct annd array

if ((uinp_fd = setup_uinput_device()) < 0) {
   printf("Unable to find uinput device\n");
   return -1;
  }

  wiringPiSetup() ;
  
  sleep(3);

   wiringPiISR (f1, INT_EDGE_FALLING, myInterrupt0);
   wiringPiISR (f2, INT_EDGE_FALLING, myInterrupt1);
   wiringPiISR (f5, INT_EDGE_FALLING, myInterrupt3);
   wiringPiISR (f6, INT_EDGE_FALLING, myInterrupt4);

   pinMode (left, INPUT) ;
   pinMode (right, INPUT) ;
   pinMode (f3, INPUT) ;
   pinMode (f7, INPUT) ; 
   pinMode (cf3, INPUT) ;
   pinMode (cf7, INPUT) ;
   pinMode (sf2, INPUT) ;
   pinMode (sf5, INPUT) ;
   pinMode (cst, INPUT) ;
   

pullUpDnControl(left,PUD_DOWN);
pullUpDnControl(right,PUD_DOWN);
pullUpDnControl(f3,PUD_DOWN);
pullUpDnControl(f7,PUD_DOWN);
pullUpDnControl(cf3,PUD_DOWN);
pullUpDnControl(cf7,PUD_DOWN);
pullUpDnControl(sf2,PUD_DOWN);
pullUpDnControl(sf5,PUD_DOWN);
pullUpDnControl(cst,PUD_DOWN);


int a[24];
int i = 0;
for ( i = 0; i < 24; i = i+1) { a[i] = 0; }

  printf(" waiting...\n");
 

/********* main loops **********/

piThreadCreate (rotary_loop) ;

while  ( a >= 0 ) {
   
     a[0] = digitalRead(left);
     a[1] = digitalRead(right);
     a[2] = digitalRead(f3); 
     a[3] = digitalRead(f7);
     a[4] = digitalRead(cf3);
     a[5] = digitalRead(cf7);
     a[6] = digitalRead(sf2);
     a[7] = digitalRead(sf5);
     a[8] = digitalRead(cst); 
     
   if ( a[0] > 0 ) {
     myInterrupt6();
     if ( a[8] > 0) { a[0] = a[0]; }
     else { a[0]= 0; }
    }

    if ( a[1] > 0 ) {
     myInterrupt7();
     if ( a[8] > 0) { a[1] = a[1]; }
     else { a[1]= 0; }
    }

   if ( a[2] > 0) {
      myInterrupt2();
      if ( a[8] > 0) { a[2] = a[2]; }
      else { a[2]= 0; }
    }

   if ( a[3]> 0 ) {
     myInterrupt5();
     if ( a[8] > 0) { a[3] = a[3]; }
     else { a[3]= 0; }
    } 

   if ( a[4]> 0) {
     myInterrupt11();
     a[4] = 0;
    }
    
   if ( a[5] > 0) {
     myInterrupt12();
     a[5] = 0;
    }
   
   if ( a[6] > 0 ) {
    myInterrupt8();
     if ( a[8] > 0) { a[6] = a[6]; }
     else { a[6]= 0; }
    }

    if ( a[7] > 0 ) {
     myInterrupt9();
     if ( a[8] > 0) { a[7] = a[7]; }
     else { a[7]= 0; }
    }

    if ( a[8] > 0 ) {
     myInterrupt10();
     
    } 
     
    /* Experimental switch combinations for extra functions ****** 
     *                                                           *
     *         rescan + f3 + f7 = system shutdown                *
     *         rescan + right = screen keyboard (install onboard)*
     *         rescan + left = rescan                            *        
     *         rescan + clone 1  = record on pair 3              *
     *         rescan + clone 2 = relaunch xwax                  *
     *         rescan + f3 = toggle deck 1 control type          *
     *         rescan + f7 = toggle deck 2 control type          *
     *                                                           *
     *************************************************************/


    if ( a[8] > 0 && a[2] > 0 &&  a[3] > 0 ) {
      system("shutdown -P now");
      delay(200);
      a[8] = a[2] = a[3] = 0;
     } 

    if ( a[8] > 0 && a[1] > 0 ) {
       system("onboard");
       delay(200);
       a[8] = a[1] = 0;
     }

    if ( a[8] > 0 && a[0] > 0 ) {
       penmount():
       delay(200);
       a[8] = a[0] = 0;
     }

    if ( a[8] > 0 && a[6] > 0 ) {
      system("pkill xwax");  
      piThreadCreate (record) ;
      delay(200);
      a[8] = a[6] = 0;
     }

    if ( a[8] > 0 && a[7] > 0 ) {
      system ("pkill arecord");
      system ("./home/odroid/Scripts/startxwax");
      delay(200);
      a[8] = a[7] = 0;
     }

    if ( a[8] > 0 && a[2] > 0 ) {
      send_CF3();
      delay(200);
      a[8] = a[2] = 0;
     }

    if ( a[8] > 0 && a[3] > 0 ) {
      send_CF7();
      delay(200);
      a[8] = a[3] = 0;
     }

     /* end of experimental swicth combinations */

   usleep(10000);
  }

return 0;  

}


/***************************************************************************************************************
*                                                                                                              *
*  Alternate options for configuring the program depending on what setup and actions you want xwax to preform  *
*                                                                                                              *
****************************************************************************************************************/

/* Alternate actions pin config 

   pinMode (ctab, INPUT) ;
   pinMode (up, INPUT) ;
   pinMode (down, INPUT) ;
   pinMode (f1, INPUT) ;
   pinMode (f2, INPUT) ;
   pinMode (f5, INPUT) ;
   pinMode (f6, INPUT) ;
   pinMode (f9, INPUT) ;
   pinMode (f10, INPUT) ;
   pinMode (f11, INPUT) ;
   pinMode (cf11, INPUT) ;
   pinMode (sf3, INPUT) ;
   pinMode (sf7, INPUT) ;
   pinMode (sf9, INPUT) ;
   pinMode (sf10, INPUT) ;
 
 pullUpDnControl(ctab,PUD_DOWN);
 pullUpDnControl(up,PUD_DOWN);
 pullUpDnControl(down,PUD_DOWN);
 pullUpDnControl(f1,PUD_DOWN);
 pullUpDnControl(f2,PUD_DOWN);
 pullUpDnControl(f5,PUD_DOWN);
 pullUpDnControl(f6,PUD_DOWN);
 pullUpDnControl(f9,PUD_DOWN);
 pullUpDnControl(f10,PUD_DOWN);
 pullUpDnControl(f11,PUD_DOWN);
 pullUpDnControl(cf11,PUD_DOWN);
 pullUpDnControl(sf3,PUD_DOWN);
 pullUpDnControl(sf7,PUD_DOWN);
 pullUpDnControl(sf9,PUD_DOWN);
 pullUpDnControl(sf10,PUD_DOWN);

*/

/* alternate pin readings
     
     a[9] = digitalRead(up);
     a[10] = digitalRead(down);
     a[11] = digitalRead(f1);
     a[12] = digitalRead(f2);
     a[13] = digitalRead(f5);
     a[14] = digitalRead(f6);
     a[15] = digitalRead(f9);
     a[16] = digitalRead(f10);
     a[17] = digitalRead(f11);
     a[18] = digitalRead(cf11);
     a[19] = digitalRead(sf3);
     a[20] = digitalRead(sf7);
     a[21] = digitalRead(sf9);
     a[22] = digitalRead(sf10);
     a[23] = digitalRead(ctab);
     
*/

/* alternate interrupt functions
   
   wiringPiISR (left, INT_EDGE_FALLING, myInterrupt6);
   wiringPiISR (right, INT_EDGE_FALLING, myInterrupt7);
   wiringPiISR (f3, INT_EDGE_FALLING, myInterrupt2);
   wiringPiISR (f7, INT_EDGE_FALLING, myInterrupt5);
   wiringPiISR (cf3, INT_EDGE_FALLING, myInterrupt11);
   wiringPiISR (cf7, INT_EDGE_FALLING, myInterrupt12);
   wiringPiISR (sf2, INT_EDGE_FALLING, myInterrupt8);
   wiringPiISR (sf5, INT_EDGE_FALLING, myInterrupt9);
   wiringPiISR (cst, INT_EDGE_FALLING, myInterrupt10);
   .....
   
*/   
   
