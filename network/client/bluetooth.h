/* 
 * RFCOMM socket for Linux by using BlueZ
 * Copyright (C) 2015 by Tony Cho
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef RFCOMM_SOCKET_H
#define RFCOMM_SOCKET_H

/* server channel */
#define RFCOMM_SERVER_PORT_NUM			5				
 
/* destination address */
#define RFCOMM_SERVER_BLUETOOTH_ADDR	"98:D3:21:F8:31:76"	/* it should be modified in your environment */

#define BUTTON_NUMBER  16

#define BUFFER_LEN 2

enum architechture {
    NONE,
    PIC8
};

typedef struct DataHeader {
    __int16 arc;
    __int16 size;
}DataHeader;

typedef struct Data{
    DataHeader header; 
    float joystickX;
    float joystickY;
    char button[BUFFER_LEN];
    __int16 gx;
    __int16 gy;
    __int16 gz;
    char arc; // specify the architecture of the sender
    char crc;
}Data;

#endif