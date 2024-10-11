#include <stdio.h>

// Main Win32 API header.
#include < windows.h >

#define BUFFER_SIZE 256

      
int main()
{
    HANDLE hDevID = INVALID_HANDLE_VALUE; // Identifier of the serial port.
                                        // by default fix at -1 (INVALID_HANDLE_VALUE)
    hDevID = CreateFile( // open the serial port
        "\\\\.\\COM5",
        GENERIC_READ | GENERIC_WRITE,
        0,    // Must be opened with exclusive-access.
        NULL, // No security attributes.
        OPEN_EXISTING, // Must use OPEN_EXISTING.
        0,    // Not overlapped I/O.
        NULL  // hTemplate must be NULL for comm devices.
        );
        
    if (hDevID == INVALID_HANDLE_VALUE)
    {    printf("CreateFile() failed\n");
        return -1;

    }else
    {
        printf("CreateFile() succeeded\n");
    }

// we can show the port paramters
    DCB dcb; // Structure defining port options.
    memset(&dcb, 0, sizeof(DCB)); // this function puts zero to all the memoris pointed by dcb
                                // so dcb initialized by all zero
    if (!GetCommState(hDevID, &dcb)) // now dcb is filled by all the port option
    {
        printf("GetCommState() failed\n");
        return -1;
    }
    printf("baud rate = %d\n",dcb.BaudRate);
    printf("Parity = %d\n",dcb.Parity);
    printf("Byte Size = %d\n",dcb.ByteSize);
    printf("Stop Bit = %d\n",dcb.StopBits);
    // ONESTOPBIT    0
    // ONE5STOPBITS    1
    // TWOSTOPBITS    2
    
    // we can change some options for example
    dcb.BaudRate = 9600 ;
    // so we must apply these new parameters
        if (!SetCommState(hDevID, &dcb))
    {
        printf("SetCommState() failed\n");
        return -1;
    }
// now, we write a series of caracters to the port using command WriteFile
    // #define BUFFER_SIZE 256
    // char writebuf[BUFFER_SIZE]; // Buffer used to write data.
    // strcpy(writebuf, "HELLO\n");
    // now write  with command WriteFile
    // int writtenbytes = 0; // Number of bytes successfully written by WriteFile().

    // if (WriteFile(hDevID, writebuf, BUFFER_SIZE, (LPDWORD)&writtenbytes, NULL))
    // {
    //     if (writtenbytes == 0)
    //     {
    //         printf("WriteFile() timed out\n");
    //         return -1;
    //     }
    // }
    // else
    // {
    //     printf("WriteFile() failed\n");
    //     return -1;
    // }
    // printf("%d bytes were written\n",writtenbytes );
    
// Now let's read some bytes from the port
    char readbuf[BUFFER_SIZE]; // Buffer used to read data.
    int readbuflen = 0; // Number of bytes to read.
    int readbytes = 0; // Final number of bytes successfully read by all the calls of ReadFile().
    int nbbytes = 0; // Number of bytes successfully read by each call of ReadFile().
    int i = 0;
//    if we want to read an entire buffer :
//    memset(readbuf, 0, BUFFER_SIZE); // Fill the buffer of 0 (to erase any previous read data).
    readbuflen = 10; // We expect for examle 10 bytes
    readbytes = 0;
    nbbytes = 0;
    char buffer[BUFFER_SIZE] = { 0 };

    // The number of bytes that are sent and we will receive might not be
    // received entirely with a single call of ReadFile() so
    // we need to check the number of bytes received and retry if necessary.
    // This depends on several things, including the serial port timeout options,
    // the internal program of the device,...
    // We might also get a blocking loop depending on these things (note that ReadFile() and WriteFile() block
    // during the time of communication).
    // Here we read byte by byte and we end the loop when we receive a 0 caracter
    while (1) {
        if (ReadFile(hDevID, &readbuf, BUFFER_SIZE, (LPDWORD)&nbbytes, NULL)) {
            if (nbbytes == 0) {
                printf("ReadFile() timed out\n");
                return -1;
            }
        }
        else {
            printf("ReadFile() failed\n");
            return -1;
        }
        memset(buffer, 0, sizeof(buffer));
        // readbytes += nbbytes; // here nbbytes is alwayes equal to 1
        printf("%x, %d\n",*readbuf, nbbytes); // print the read caracters on the screen
        // buffer[i++]=readbuf; // save the string in a buffer
        // printf("%s\n",buffer);
    }
    // buffer[i]=0;
    // buffer[0] += 0x100000;

    //------------------------------------------------------------------------------------------------------
    // Step 6 : Closing the serial port
    //------------------------------------------------------------------------------------------------------

    // Close the COM4 serial port.
    if (!CloseHandle(hDevID))
    {
        printf("CloseHandle() failed\n");
        return -1;
    }

    return 0;

}