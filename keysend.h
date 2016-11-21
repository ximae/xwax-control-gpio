#ifndef KEYSEND_H
#define KEYSEND_H

int setup_uinput_device();

void send_key_event(int fd, unsigned int keycode, int keyvalue);

void send_Left(void);

void send_Right(void);

void send_Up(void);

void send_Down(void);

void send_F1(void);

void send_F2(void);

void send_F3(void);

void send_F5(void);

void send_F6(void);

void send_F7(void);

void send_F9(void);

void send_F10(void);

void send_F11(void);

void send_CF3(void);

void send_CF7(void);

void send_CF11(void);

void send_SF2(void);

void send_SF3(void);

void send_SF5(void);

void send_SF7(void);

void send_SF9(void);

void send_SF10(void);

void send_CTab(void);

void send_CST(void);

#endif