/*
 * File:   Serial.cpp
 * Author: msobral
 *
 * Created on 9 de Março de 2016, 13:15
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/select.h>

#include "Serial.h"

#define MAX_SERIAL_BYTES 64

Serial::Serial() {
}

Serial::Serial(const Serial& orig) {
}

Serial::~Serial() {
}

Serial::Serial(const char* path, int rate) {
  struct termios tio;

  tty_fd=open(path, O_RDWR|O_NOCTTY);
  if (tty_fd < 0) throw -10;

  tcgetattr(tty_fd, &tio);

  tio.c_iflag = 0;
  tio.c_oflag = 0;
  //tio.c_cflag=CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
  tio.c_cflag = 0x8bd;
  tio.c_lflag = 0;

  tio.c_cc[0] = 3;
  tio.c_cc[1] = 0x1c;
  tio.c_cc[2] = 0x7f;
  tio.c_cc[3] = 0x15;
  tio.c_cc[4] = 4;
  tio.c_cc[5] = 0;
  tio.c_cc[6] = 0;
  tio.c_cc[7] = 0;
  tio.c_cc[8] = 0x11;
  tio.c_cc[9] = 0x13;
  tio.c_cc[10] = 0x1a;
  tio.c_cc[11] = 0;
  tio.c_cc[12] = 0x12;
  tio.c_cc[13] = 0xf;
  tio.c_cc[14] = 0x17;
  tio.c_cc[15] = 016;
  for (int i=16; i < 32; i++) tio.c_cc[i] = 0;

  //cfmakeraw(&tio);
  cfsetospeed(&tio,rate);            // 115200 baud
  cfsetispeed(&tio,rate);            // 115200 baud

  tcsetattr(tty_fd,TCSANOW,&tio);

  long flag;
  ioctl(tty_fd, F_GETFL, &flag);
  flag |= O_NONBLOCK;
  ioctl(tty_fd, F_SETFL, &flag);
}

bool Serial::cca() {
    // se a serial estiver com bytes no buffer, então está
    // recebendo algo ...
    fd_set r;
    struct timeval tv = {0,0};

    FD_ZERO(&r);
    FD_SET(tty_fd, &r);

    // faz um poll na serial
    int n = select (tty_fd+1, &r, NULL, NULL, &tv);
    return (n < 1); // sem bytes para ler
}

int Serial::write(char* buffer, int len) {
    //if (not cca()) return 0;

    int pos = 0;
    while (pos < len) {
        int bytes = len - pos;
        if (bytes > MAX_SERIAL_BYTES) bytes = MAX_SERIAL_BYTES;
        int sent = ::write(tty_fd, buffer+pos, bytes);
        pos += sent;
        ::tcdrain(tty_fd);
    }
    return pos;
}

int Serial::read(char* buffer, int len, bool block) {
    if (block) {
        fd_set r;

        FD_ZERO(&r);
        FD_SET(tty_fd, &r);
        select (tty_fd+1, &r, NULL, NULL, NULL);
    }
    int n = ::read(tty_fd, buffer, len);

    return n;
}

int Serial::read(char* buffer, int len) {
    return read(buffer, len, false);
}

char Serial::read_byte() {
    char c;

    read(&c, 1, false);
    return c;
}
