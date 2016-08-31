#include "Framing.h"
int main(){
	//char * frame;
	const char * path = "/dev/ttyUSB0";
	char flag = 0x7e;
    char* data = (char*)malloc(10);
    data[0] = flag;
    data[1] = 'O';
    data[2] = 'l';
    data[3] = 'a';
    data[4] = ' ';
    data[5] = 'M';
    data[6] = 'U';
    data[7] = 'N';
    data[8] = 'D';
    data[9] = 'O';


    Serial serial(path,9600);
	Framing testa(serial,8,1024);
    testa.send(data,10);
    testa.receive(data);
return 0;
}
