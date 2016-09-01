
#include "Framing.h"
using namespace std;

void Framing::send(char * buffer, int bytes){
porta->write(buffer,bytes);
}

int Framing::receive(char *buffer)
{
    int numero_bytes=0;
    //FILE *received_file;
    //rpmaçdp
    //received_file = fopen(argv[3], "w");
/*
    char Flag = 0x7e;
    char Flag2 = 0x7d;

    if (strcmp(buffer, Flag) == 0)
    {
        cout << "ashow 7E"
        //handle(Flag);
    }
    if (strcmp(buffer, Flag2) == 0)
    {
        cout << "ashow 7D"
        //handle(Flag);
    }
    numero_bytes++;
*/
    //fclose(received_file);
    return numero_bytes;

}

/*
bool Framing::handle(char byte)
{
    int Estado;

     switch(Estado)
            {
                case 0:
                    break;

                case 1:
                    break;

                case 2:
                    break;

                case 3:

                    // return true se quadro completo ( novo 7E)
                    break;

                default:
                    break;
            }
}
*/
