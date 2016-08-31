
/*
 * File:   Serial.h
 * Author: msobral
 *
 * Created on 9 de Março de 2016, 13:15
 */

#ifndef SERIAL_H
#define	SERIAL_H

#include <termios.h>

class Serial {
public:
    Serial();
    Serial(const char * path, int rate);
    Serial(const Serial& orig);
    virtual ~Serial();
    int get() { return tty_fd;}
    bool cca();
    int write(char * buffer, int len);
    int read(char * buffer, int len);
    int read(char * buffer, int len, bool block);
    char read_byte();
private:
    int tty_fd;
};

#endif	/* SERIAL_H */


