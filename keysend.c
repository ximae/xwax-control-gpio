

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>

// globalComparator:

int uinp_fd;



/* Setup the uinput device Function */

int setup_uinput_device() {
 uinp_fd = open("/dev/uinput", O_WRONLY | O_NDELAY);
 if (uinp_fd == 0) {
   printf("Unable to open /dev/uinput\n");
   return -1;
  }
 struct uinput_user_dev uinp;
 memset(&uinp, 0, sizeof(uinp)); // Intialize the uInput device to NULL
 strncpy(uinp.name, "Virtual Keyboard Device", strlen("Virtual Keyboard Device"));
 
   uinp.id.version = 4;
   uinp.id.bustype = BUS_USB;
   uinp.id.product = 1;
   uinp.id.vendor = 1;
  
// Setup the uinput device
 ioctl(uinp_fd, UI_SET_EVBIT, EV_KEY);
 ioctl(uinp_fd, UI_SET_EVBIT, EV_REL);
 int i = 0;
 for (i = 0; i < 256; i++) {
   ioctl(uinp_fd, UI_SET_KEYBIT, i);
  }
  
// Create input device into input sub-system
 write(uinp_fd, &uinp, sizeof(uinp));
 if (ioctl(uinp_fd, UI_DEV_CREATE)) {
   printf("Unable to create UINPUT device.");
   return -1;
  }
 return uinp_fd;
}


/* actual key sending function */

void send_key_event(int fd, unsigned int keycode, int keyvalue) {
 struct input_event event;
 gettimeofday(&event.time, NULL);
 
   event.type = EV_KEY;
   event.code = keycode;
   event.value = keyvalue;
   
 if (write(fd, &event, sizeof(event)) < 0) {
   printf("simulate key error\n");
  }
  
   event.type = EV_SYN;
   event.code = SYN_REPORT;
   event.value = 0;
   
 write(fd, &event, sizeof(event));
 if (write(fd, &event, sizeof(event)) < 0) {
   printf("simulate key error\n");
  }
}

/*specific keyode sends*/

//cursors

void send_Left(void)
{
send_key_event(uinp_fd, 105, 1);
send_key_event(uinp_fd, 105, 0);
}

void send_Right(void)
{
send_key_event(uinp_fd, 106, 1);
send_key_event(uinp_fd, 106, 0);
}

void send_Up(void)
{
send_key_event(uinp_fd, 103, 1);
send_key_event(uinp_fd, 103, 0);
}

void send_Down(void)
{
send_key_event(uinp_fd, 108, 1);
send_key_event(uinp_fd, 108, 0);
}

// F keys

void send_F1(void)
{
send_key_event(uinp_fd, 59, 1);
send_key_event(uinp_fd, 59, 0);
}

void send_F2(void)
{
send_key_event(uinp_fd, 60, 1);
send_key_event(uinp_fd, 60, 0);
}

void send_F3(void)
{
send_key_event(uinp_fd, 61, 1);
send_key_event(uinp_fd, 61, 0);
}

void send_F5(void)
{
send_key_event(uinp_fd, 63, 1);
send_key_event(uinp_fd, 63, 0);
}

void send_F6(void)
{
send_key_event(uinp_fd, 64, 1);
send_key_event(uinp_fd, 64, 0);
}

void send_F7(void)
{
send_key_event(uinp_fd, 65, 1);
send_key_event(uinp_fd, 65, 0);
}

void send_F9(void)
{
send_key_event(uinp_fd, 67, 1);
send_key_event(uinp_fd, 67, 0);
}

void send_F10(void)
{
send_key_event(uinp_fd, 68, 1);
send_key_event(uinp_fd, 68, 0);
}

void send_F011(void)
{
send_key_event(uinp_fd, 69, 1);
send_key_event(uinp_fd, 69, 0);
}

// combined keys

void send_CF3(void) {
 send_key_event(uinp_fd, 29, 1);
 send_key_event(uinp_fd, 61, 1);
 send_key_event(uinp_fd, 29, 0);
 send_key_event(uinp_fd, 61, 0);
}

void send_CF7(void) {
 send_key_event(uinp_fd, 29, 1);
 send_key_event(uinp_fd, 65, 1);
 send_key_event(uinp_fd, 29, 0);
 send_key_event(uinp_fd, 65, 0);
}

void send_CF11(void) {
 send_key_event(uinp_fd, 29, 1);
 send_key_event(uinp_fd, 69, 1);
 send_key_event(uinp_fd, 29, 0);
 send_key_event(uinp_fd, 69, 0);
}

void send_SF2(void) {
 send_key_event(uinp_fd, 42, 1);
 send_key_event(uinp_fd, 60, 1);
 send_key_event(uinp_fd, 42, 0);
 send_key_event(uinp_fd, 60, 0);
}

void send_SF5(void) {
 send_key_event(uinp_fd, 42, 1);
 send_key_event(uinp_fd, 63, 1);
 send_key_event(uinp_fd, 42, 0);
 send_key_event(uinp_fd, 63, 0);
}

void send_SF9(void) {
 send_key_event(uinp_fd, 42, 1);
 send_key_event(uinp_fd, 67, 1);
 send_key_event(uinp_fd, 42, 0);
 send_key_event(uinp_fd, 67, 0);
}

void send_SF10(void) {
 send_key_event(uinp_fd, 42, 1);
 send_key_event(uinp_fd, 68, 1);
 send_key_event(uinp_fd, 42, 0);
 send_key_event(uinp_fd, 68, 0);
}

void send_SF3(void) {
 send_key_event(uinp_fd, 42, 1);
 send_key_event(uinp_fd, 61, 1);
 send_key_event(uinp_fd, 42, 0);
 send_key_event(uinp_fd, 61, 0);
}

void send_SF7(void) {
 send_key_event(uinp_fd, 42, 1);
 send_key_event(uinp_fd, 65, 1);
 send_key_event(uinp_fd, 42, 0);
 send_key_event(uinp_fd, 65, 0);
}

void send_CTab(void) {
 send_key_event(uinp_fd, 29, 1);
 send_key_event(uinp_fd, 15, 1);
 send_key_event(uinp_fd, 29, 0);
 send_key_event(uinp_fd, 15, 0);
}

void send_CST(void) {
 send_key_event(uinp_fd, 29, 1);
 send_key_event(uinp_fd, 42, 1);
 send_key_event(uinp_fd, 15, 1);
 send_key_event(uinp_fd, 29, 0);
 send_key_event(uinp_fd, 42, 0);
 send_key_event(uinp_fd, 15, 0);
}


/* xwax input keycode assign 
 *
 *   key_code[up] = 103;
 *   key_code[down] = 108;
 *   key_code[left] = 105; 
 *   key_code[right] = 106;
 *   key_code[f1] = 59;
 *   key_code[f2] = 60;
 *   key_code[f3] = 61;
 *   key_code[f5] = 63;
 *   key_code[f6] = 64;
 *   key_code[f7] = 65;
 *   key_code[f9] = 67;
 *   key_code[f10] = 68;
 *   key_code[f11] = 69;
 *   key_code[control] = 29;
 *   key_code[shift] = 42;
 *   key_code[tab] = 15;
 *
 ****************************/


