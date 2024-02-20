#include <stdio.h>
#include <stdarg.h>
#define PRINTBYTES_HEX 1
#define PRINTBYTES_BIN 2
#define PRINTBYTES_ASCII 4

// this is from stackoverflow https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c "
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0') 


#define SPACE_NEWLINE(i,n) \
    if((i+1)%n == 0){ \
        fprintf(stderr,"\n"); \
    } \


// set this to zero to disable logs
int print_logs = 1;


// log helper function, so that you can print things to stderr quickly and easily and then disable them without commenting them out 
void log(const char* fmt, ...){
    if(print_logs){
        va_list args;
        va_start(args,fmt);
        vfprintf(stderr,fmt,args);
        va_end(args);
    }
}





void printbytes(const void* location, const int offset, const int no_bytes, const int flags){
    unsigned char* location_bytes = (unsigned char*)location;
    location_bytes = location_bytes + offset;

    for(int i = 0; i<no_bytes;i++){
        switch(flags){
            case (PRINTBYTES_HEX):
                fprintf(stderr,"%02x",location_bytes[i]);
                if ((i+1)%4 == 0){
                    fprintf(stderr," ");
                }
                SPACE_NEWLINE(i,4);
                SPACE_NEWLINE(i,8);
                break;
            case (PRINTBYTES_BIN):
                fprintf(stderr,BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(location_bytes[i]));
                SPACE_NEWLINE(i,2);
                SPACE_NEWLINE(i,8);
                break;
            case (PRINTBYTES_ASCII):
                fprintf(stderr,"%c ", location_bytes[i]);
                break;
        }
    }
    if ((no_bytes-1)%2 !=0){
        fprintf(stderr,"\n");
    } 
}
