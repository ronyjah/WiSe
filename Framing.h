#ifndef FRAMING_H_
#define FRAMING_H_

#include "Serial.h"
#include <string>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
class Framing : public Serial
{

public:
    //Framing(Serial &s):serial(s){}// passagem parametro por referencia
	Framing(Serial & dev, int bytes_min, int bytes_max):Serial(dev){
		porta = &dev;
	};
	//min_bytes = bytes_min;
	//max_bytes = bytes_max;
	//Framing(){}

	void send(char * buffer, int bytes);
    int receive(char * buffer);
    ~Framing(){}

private:
    int min_bytes, max_bytes;
    Serial *porta;

};
#endif /* FRAMING_H_ */
