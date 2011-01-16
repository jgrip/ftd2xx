/*
Copyright (c) 2010, Johan Grip
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "ftd2xx.h"
#include <stdio.h>
#include <windows.h>

static HINSTANCE gs_hDLL = 0;
static FILE *debug;

static void debugtime(void)
{
	SYSTEMTIME localtime;

	GetLocalTime(&localtime);

	fprintf(debug, "[%02d:%02d:%02d.%04d] ", localtime.wHour, localtime.wMinute, localtime.wSecond, localtime.wMilliseconds);
}

#define DEBUG(x) debugtime(); fprintf x; fflush(debug);

int (__stdcall * _O_FT_Close)();
int (__stdcall * _O_FT_ClrDtr)();
int (__stdcall * _O_FT_ClrRts)();
//int (__stdcall * _O_FT_CreateDeviceInfoList)();
typedef FT_STATUS (__stdcall FT_CreateDeviceInfoList)(LPDWORD);
FT_CreateDeviceInfoList* _O_FT_CreateDeviceInfoList;
int (__stdcall * _O_FT_CyclePort)();
int (__stdcall * _O_FT_EE_Program)();
int (__stdcall * _O_FT_EE_ProgramEx)();
int (__stdcall * _O_FT_EE_Read)();
int (__stdcall * _O_FT_EE_ReadEx)();
int (__stdcall * _O_FT_EE_UARead)();
int (__stdcall * _O_FT_EE_UASize)();
int (__stdcall * _O_FT_EE_UAWrite)();
int (__stdcall * _O_FT_EraseEE)();
int (__stdcall * _O_FT_GetBitMode)();
int (__stdcall * _O_FT_GetComPortNumber)();
int (__stdcall * _O_FT_GetDeviceInfo)();
int (__stdcall * _O_FT_GetDeviceInfoDetail)();
//int (__stdcall * _O_FT_GetDeviceInfoList)();
typedef FT_STATUS (__stdcall FT_GetDeviceInfoList)(FT_DEVICE_LIST_INFO_NODE *,LPDWORD);
FT_GetDeviceInfoList* _O_FT_GetDeviceInfoList;
int (__stdcall * _O_FT_GetDriverVersion)();
int (__stdcall * _O_FT_GetEventStatus)();
int (__stdcall * _O_FT_GetLatencyTimer)();
int (__stdcall * _O_FT_GetLibraryVersion)();
int (__stdcall * _O_FT_GetModemStatus)();
int (__stdcall * _O_FT_GetQueueStatus)();
int (__stdcall * _O_FT_GetStatus)();
int (__stdcall * _O_FT_IoCtl)();
typedef FT_STATUS (__stdcall FT_ListDevices)(PVOID,PVOID,DWORD);
FT_ListDevices* _O_FT_ListDevices;
int (__stdcall * _O_FT_Open)();
int (__stdcall * _O_FT_OpenEx)();
int (__stdcall * _O_FT_Purge)();
//int (__stdcall * _O_FT_Read)();
typedef FT_STATUS (__stdcall FT_Read)(FT_HANDLE,LPVOID,DWORD,LPDWORD);
FT_Read* _O_FT_Read;
int (__stdcall * _O_FT_ReadEE)();
int (__stdcall * _O_FT_Reload)();
int (__stdcall * _O_FT_Rescan)();
int (__stdcall * _O_FT_ResetDevice)();
int (__stdcall * _O_FT_ResetPort)();
int (__stdcall * _O_FT_RestartInTask)();
//int (__stdcall * _O_FT_SetBaudRate)();
typedef FT_STATUS (__stdcall FT_SetBaudRate)(FT_HANDLE,ULONG);
FT_SetBaudRate* _O_FT_SetBaudRate;
int (__stdcall * _O_FT_SetBitMode)();
int (__stdcall * _O_FT_SetBreakOff)();
int (__stdcall * _O_FT_SetBreakOn)();
int (__stdcall * _O_FT_SetChars)();
//int (__stdcall * _O_FT_SetDataCharacteristics)();
typedef FT_STATUS (__stdcall FT_SetDataCharacteristics)(FT_HANDLE,UCHAR,UCHAR,UCHAR);
FT_SetDataCharacteristics* _O_FT_SetDataCharacteristics;
int (__stdcall * _O_FT_SetDeadmanTimeout)();
int (__stdcall * _O_FT_SetDivisor)();
int (__stdcall * _O_FT_SetDtr)();
int (__stdcall * _O_FT_SetEventNotification)();
int (__stdcall * _O_FT_SetFlowControl)();
int (__stdcall * _O_FT_SetLatencyTimer)();
int (__stdcall * _O_FT_SetResetPipeRetryCount)();
int (__stdcall * _O_FT_SetRts)();
int (__stdcall * _O_FT_SetTimeouts)();
int (__stdcall * _O_FT_SetUSBParameters)();
int (__stdcall * _O_FT_SetWaitMask)();
int (__stdcall * _O_FT_StopInTask)();
int (__stdcall * _O_FT_W32_CancelIo)();
int (__stdcall * _O_FT_W32_ClearCommBreak)();
int (__stdcall * _O_FT_W32_ClearCommError)();
int (__stdcall * _O_FT_W32_CloseHandle)();
int (__stdcall * _O_FT_W32_CreateFile)();
int (__stdcall * _O_FT_W32_EscapeCommFunction)();
int (__stdcall * _O_FT_W32_GetCommMask)();
int (__stdcall * _O_FT_W32_GetCommModemStatus)();
int (__stdcall * _O_FT_W32_GetCommState)();
int (__stdcall * _O_FT_W32_GetCommTimeouts)();
int (__stdcall * _O_FT_W32_GetLastError)();
int (__stdcall * _O_FT_W32_GetOverlappedResult)();
int (__stdcall * _O_FT_W32_PurgeComm)();
int (__stdcall * _O_FT_W32_ReadFile)();
int (__stdcall * _O_FT_W32_SetCommBreak)();
int (__stdcall * _O_FT_W32_SetCommMask)();
int (__stdcall * _O_FT_W32_SetCommState)();
int (__stdcall * _O_FT_W32_SetCommTimeouts)();
int (__stdcall * _O_FT_W32_SetupComm)();
int (__stdcall * _O_FT_W32_WaitCommEvent)();
int (__stdcall * _O_FT_W32_WriteFile)();
int (__stdcall * _O_FT_WaitOnMask)();
//int (__stdcall * _O_FT_Write)();
typedef FT_STATUS (__stdcall FT_Write)(FT_HANDLE,LPVOID,DWORD,LPDWORD);
FT_Write* _O_FT_Write;
int (__stdcall * _O_FT_WriteEE)();

char* DumpResult(FT_STATUS res)
{
	char *table[] = {
	"FT_OK",
	"FT_INVALID_HANDLE",
    "FT_DEVICE_NOT_FOUND",
    "FT_DEVICE_NOT_OPENED",
    "FT_IO_ERROR",
    "FT_INSUFFICIENT_RESOURCES",
    "FT_INVALID_PARAMETER",
    "FT_INVALID_BAUD_RATE",
    "FT_DEVICE_NOT_OPENED_FOR_ERASE",
    "FT_DEVICE_NOT_OPENED_FOR_WRITE",
    "FT_FAILED_TO_WRITE_DEVICE",
    "FT_EEPROM_READ_FAILED",
    "FT_EEPROM_WRITE_FAILED",
    "FT_EEPROM_ERASE_FAILED",
	"FT_EEPROM_NOT_PRESENT",
	"FT_EEPROM_NOT_PROGRAMMED",
	"FT_INVALID_ARGS",
	"FT_NOT_SUPPORTED",
	"FT_OTHER_ERROR",
	"FT_DEVICE_LIST_NOT_READY"
	};
	return table[res];
}

static void hexdump(const char *pre, void *data, int size)
{
    /* dumps size bytes of *data to stdout. Looks like:
     * [0000] 75 6E 6B 6E 6F 77 6E 20
     *                  30 FF 00 00 00 00 39 00 unknown 0.....9.
     * (in a single line of course)
     */

    unsigned char *p = (unsigned char *)data;
    unsigned char c;
    int n;
    char bytestr[4] = {0};
    char addrstr[10] = {0};
    char hexstr[ 16*3 + 5] = {0};
    char charstr[16*1 + 5] = {0};

    for(n=1;n<=size;n++) {
        if (n%16 == 1) {
            /* store address for this line */
            _snprintf(addrstr, sizeof(addrstr), "%.4x",
               ((unsigned int)p-(unsigned int)data) );
        }
            
        c = *p;
        if (isalnum(c) == 0) {
            c = '.';
        }

        /* store hex str (for left side) */
        _snprintf(bytestr, sizeof(bytestr), "%02X ", *p);
        strncat(hexstr, bytestr, sizeof(hexstr)-strlen(hexstr)-1);

        /* store char str (for right side) */
        _snprintf(bytestr, sizeof(bytestr), "%c", c);
        strncat(charstr, bytestr, sizeof(charstr)-strlen(charstr)-1);

        if(n%16 == 0) { 
            /* line completed */
			DEBUG((debug,"%s [%4.4s]   %-50.50s  %s\n", pre, addrstr, hexstr, charstr));
            hexstr[0] = 0;
            charstr[0] = 0;
        } else if(n%8 == 0) {
            /* half line: add whitespaces */
            strncat(hexstr, "  ", sizeof(hexstr)-strlen(hexstr)-1);
            strncat(charstr, " ", sizeof(charstr)-strlen(charstr)-1);
        }
        p++; /* next byte */
    }

    if (strlen(hexstr) > 0) {
        /* print rest of buffer if not empty */
		DEBUG((debug,"%s [%4.4s]   %-50.50s  %s\n", pre, addrstr, hexstr, charstr));
    }
}

extern "C" void __declspec(naked) __stdcall _I_FT_Close()
{
        DEBUG((debug,"FT_Close\n"));
        __asm{ jmp _O_FT_Close }
}

extern "C" void __declspec(naked) __stdcall _I_FT_ClrDtr()
{
        DEBUG((debug,"FT_ClrDtr\n"));
        __asm{ jmp _O_FT_ClrDtr }
}

extern "C" void __declspec(naked) __stdcall _I_FT_ClrRts()
{
        DEBUG((debug,"FT_ClrRts\n"));
        __asm{ jmp _O_FT_ClrRts }
}

extern "C" FT_STATUS __stdcall _I_FT_CreateDeviceInfoList(LPDWORD lpdwNumDevs)
{
		FT_STATUS res;
        //DEBUG((debug,"FT_CreateDeviceInfoList\n"));
		//DEBUG((debug,":: lpdwNumDevs = %p\n",lpdwNumDevs));
		res = _O_FT_CreateDeviceInfoList(lpdwNumDevs);
		//DEBUG((debug,":: result %s\n", DumpResult(res)));
        return res;
}

extern "C" void __declspec(naked) __stdcall _I_FT_CyclePort()
{
        DEBUG((debug,"FT_CyclePort\n"));
        __asm{ jmp _O_FT_CyclePort }
}

extern "C" void __declspec(naked) __stdcall _I_FT_EE_Program()
{
        DEBUG((debug,"FT_EE_Program\n"));
        __asm{ jmp _O_FT_EE_Program }
}

extern "C" void __declspec(naked) __stdcall _I_FT_EE_ProgramEx()
{
        DEBUG((debug,"FT_EE_ProgramEx\n"));
        __asm{ jmp _O_FT_EE_ProgramEx }
}

extern "C" void __declspec(naked) __stdcall _I_FT_EE_Read()
{
        DEBUG((debug,"FT_EE_Read\n"));
        __asm{ jmp _O_FT_EE_Read }
}

extern "C" void __declspec(naked) __stdcall _I_FT_EE_ReadEx()
{
        DEBUG((debug,"FT_EE_ReadEx\n"));
        __asm{ jmp _O_FT_EE_ReadEx }
}

extern "C" void __declspec(naked) __stdcall _I_FT_EE_UARead()
{
        DEBUG((debug,"FT_EE_UARead\n"));
        __asm{ jmp _O_FT_EE_UARead }
}

extern "C" void __declspec(naked) __stdcall _I_FT_EE_UASize()
{
        DEBUG((debug,"FT_EE_UASize\n"));
        __asm{ jmp _O_FT_EE_UASize }
}

extern "C" void __declspec(naked) __stdcall _I_FT_EE_UAWrite()
{
        DEBUG((debug,"FT_EE_UAWrite\n"));
        __asm{ jmp _O_FT_EE_UAWrite }
}

extern "C" void __declspec(naked) __stdcall _I_FT_EraseEE()
{
        DEBUG((debug,"FT_EraseEE\n"));
        __asm{ jmp _O_FT_EraseEE }
}

extern "C" void __declspec(naked) __stdcall _I_FT_GetBitMode()
{
        DEBUG((debug,"FT_GetBitMode\n"));
        __asm{ jmp _O_FT_GetBitMode }
}

extern "C" void __declspec(naked) __stdcall _I_FT_GetComPortNumber()
{
        DEBUG((debug,"FT_GetComPortNumber\n"));
        __asm{ jmp _O_FT_GetComPortNumber }
}

extern "C" void __declspec(naked) __stdcall _I_FT_GetDeviceInfo()
{
        //DEBUG((debug,"FT_GetDeviceInfo\n"));
        __asm{ jmp _O_FT_GetDeviceInfo }
}

extern "C" FT_STATUS __stdcall _I_FT_GetDeviceInfoDetail()
{
        //DEBUG((debug,"FT_GetDeviceInfoDetail\n"));
        __asm{ jmp _O_FT_GetDeviceInfoDetail }
}

extern "C" FT_STATUS __stdcall _I_FT_GetDeviceInfoList(FT_DEVICE_LIST_INFO_NODE *pDest,LPDWORD lpdwNumDevs)
{
		FT_STATUS res;

        //DEBUG((debug,"FT_GetDeviceInfoList\n"));
		//DEBUG((debug,":: lpdwNumDevs %d\n",lpdwNumDevs));
		res = _O_FT_GetDeviceInfoList(pDest, lpdwNumDevs);
		return res;
}

extern "C" void __declspec(naked) __stdcall _I_FT_GetDriverVersion()
{
        DEBUG((debug,"FT_GetDriverVersion\n"));
        __asm{ jmp _O_FT_GetDriverVersion }
}

extern "C" void __declspec(naked) __stdcall _I_FT_GetEventStatus()
{
        DEBUG((debug,"FT_GetEventStatus\n"));
        __asm{ jmp _O_FT_GetEventStatus }
}

extern "C" void __declspec(naked) __stdcall _I_FT_GetLatencyTimer()
{
        DEBUG((debug,"FT_GetLatencyTimer\n"));
        __asm{ jmp _O_FT_GetLatencyTimer }
}

extern "C" void __declspec(naked) __stdcall _I_FT_GetLibraryVersion()
{
        DEBUG((debug,"FT_GetLibraryVersion\n"));
        __asm{ jmp _O_FT_GetLibraryVersion }
}

extern "C" void __declspec(naked) __stdcall _I_FT_GetModemStatus()
{
        DEBUG((debug,"FT_GetModemStatus\n"));
        __asm{ jmp _O_FT_GetModemStatus }
}

extern "C" void __declspec(naked) __stdcall _I_FT_GetQueueStatus()
{
        //DEBUG((debug,"FT_GetQueueStatus\n"));
        __asm{ jmp _O_FT_GetQueueStatus }
}

extern "C" void __declspec(naked) __stdcall _I_FT_GetStatus()
{
        //DEBUG((debug,"FT_GetStatus\n"));
        __asm{ jmp _O_FT_GetStatus }
}

extern "C" void __declspec(naked) __stdcall _I_FT_IoCtl()
{
        DEBUG((debug,"FT_IoCtl\n"));
        __asm{ jmp _O_FT_IoCtl }
}

extern "C" FT_STATUS __stdcall _I_FT_ListDevices(PVOID pArg1,PVOID pArg2,DWORD Flags)
{
		FT_STATUS res;
        //DEBUG((debug,"FT_ListDevices 0x%08x,0x%08x\n",pArg1,pArg2));
		//DEBUG((debug,":: Flags "));
		//if (Flags & FT_LIST_BY_INDEX)
			//DEBUG((debug,"LIST_BY_INDEX "));
		//if (Flags & FT_LIST_NUMBER_ONLY)
			//DEBUG((debug,"LIST_NUMBER_ONLY "));
		//if (Flags & FT_LIST_ALL)
			//DEBUG((debug,"LIST_ALL"));
		//DEBUG((debug,"\n"));
        res = _O_FT_ListDevices(pArg1,pArg2,Flags);
		//DEBUG((debug,":: result %s\n", DumpResult(res)));
		return res;
}

extern "C" void __declspec(naked) __stdcall _I_FT_Open()
{
        DEBUG((debug,"FT_Open\n"));
        __asm{ jmp _O_FT_Open }
}

extern "C" void __declspec(naked) __stdcall _I_FT_OpenEx()
{
        DEBUG((debug,"FT_OpenEx\n"));
        __asm{ jmp _O_FT_OpenEx }
}

extern "C" void __declspec(naked) __stdcall _I_FT_Purge()
{
        DEBUG((debug,"FT_Purge\n"));
        __asm{ jmp _O_FT_Purge }
}

extern "C" FT_STATUS __stdcall _I_FT_Read(FT_HANDLE ftHandle,LPVOID lpBuffer,DWORD dwBytesToRead,LPDWORD lpBytesReturned)
{
		FT_STATUS res;
        //DEBUG((debug,"FT_Read\n"));
		res = _O_FT_Read(ftHandle,lpBuffer,dwBytesToRead,lpBytesReturned);
		hexdump("<", lpBuffer, *lpBytesReturned);
		return res;
}

extern "C" void __declspec(naked) __stdcall _I_FT_ReadEE()
{
        DEBUG((debug,"FT_ReadEE\n"));
        __asm{ jmp _O_FT_ReadEE }
}

extern "C" void __declspec(naked) __stdcall _I_FT_Reload()
{
        DEBUG((debug,"FT_Reload\n"));
        __asm{ jmp _O_FT_Reload }
}

extern "C" void __declspec(naked) __stdcall _I_FT_Rescan()
{
        DEBUG((debug,"FT_Rescan\n"));
        __asm{ jmp _O_FT_Rescan }
}

extern "C" void __declspec(naked) __stdcall _I_FT_ResetDevice()
{
        DEBUG((debug,"FT_ResetDevice\n"));
        __asm{ jmp _O_FT_ResetDevice }
}

extern "C" void __declspec(naked) __stdcall _I_FT_ResetPort()
{
        DEBUG((debug,"FT_ResetPort\n"));
        __asm{ jmp _O_FT_ResetPort }
}

extern "C" void __declspec(naked) __stdcall _I_FT_RestartInTask()
{
        DEBUG((debug,"FT_RestartInTask\n"));
        __asm{ jmp _O_FT_RestartInTask }
}

extern "C" FT_STATUS __stdcall _I_FT_SetBaudRate(FT_HANDLE ftHandle, ULONG BaudRate)
{
		FT_STATUS res;

        DEBUG((debug,"FT_SetBaudRate %d\n",BaudRate));
		res = _O_FT_SetBaudRate(ftHandle, BaudRate);
		return res;
}

extern "C" void __declspec(naked) __stdcall _I_FT_SetBitMode()
{
        DEBUG((debug,"FT_SetBitMode\n"));
        __asm{ jmp _O_FT_SetBitMode }
}

extern "C" void __declspec(naked) __stdcall _I_FT_SetBreakOff()
{
        DEBUG((debug,"FT_SetBreakOff\n"));
        __asm{ jmp _O_FT_SetBreakOff }
}

extern "C" void __declspec(naked) __stdcall _I_FT_SetBreakOn()
{
        DEBUG((debug,"FT_SetBreakOn\n"));
        __asm{ jmp _O_FT_SetBreakOn }
}

extern "C" void __declspec(naked) __stdcall _I_FT_SetChars()
{
        DEBUG((debug,"FT_SetChars\n"));
        __asm{ jmp _O_FT_SetChars }
}

extern "C" FT_STATUS __stdcall _I_FT_SetDataCharacteristics(FT_HANDLE ftHandle, UCHAR WordLength, UCHAR StopBits, UCHAR Parity)
{
		FT_STATUS res;

        DEBUG((debug,"FT_SetDataCharacteristics\n"));
		DEBUG((debug,":: WordLength %d\n",WordLength));
		DEBUG((debug,":: StopBits %d\n",StopBits));
		DEBUG((debug,":: Parity %d\n",Parity));
		res = _O_FT_SetDataCharacteristics(ftHandle,WordLength,StopBits,Parity);
		return res;
}

extern "C" void __declspec(naked) __stdcall _I_FT_SetDeadmanTimeout()
{
        DEBUG((debug,"FT_SetDeadmanTimeout\n"));
        __asm{ jmp _O_FT_SetDeadmanTimeout }
}

extern "C" void __declspec(naked) __stdcall _I_FT_SetDivisor()
{
        DEBUG((debug,"FT_SetDivisor\n"));
        __asm{ jmp _O_FT_SetDivisor }
}

extern "C" void __declspec(naked) __stdcall _I_FT_SetDtr()
{
        DEBUG((debug,"FT_SetDtr\n"));
        __asm{ jmp _O_FT_SetDtr }
}

extern "C" void __declspec(naked) __stdcall _I_FT_SetEventNotification()
{
        DEBUG((debug,"FT_SetEventNotification\n"));
        __asm{ jmp _O_FT_SetEventNotification }
}

extern "C" void __declspec(naked) __stdcall _I_FT_SetFlowControl()
{
        DEBUG((debug,"FT_SetFlowControl\n"));
        __asm{ jmp _O_FT_SetFlowControl }
}

extern "C" void __declspec(naked) __stdcall _I_FT_SetLatencyTimer()
{
        DEBUG((debug,"FT_SetLatencyTimer\n"));
        __asm{ jmp _O_FT_SetLatencyTimer }
}

extern "C" void __declspec(naked) __stdcall _I_FT_SetResetPipeRetryCount()
{
        DEBUG((debug,"FT_SetResetPipeRetryCount\n"));
        __asm{ jmp _O_FT_SetResetPipeRetryCount }
}

extern "C" void __declspec(naked) __stdcall _I_FT_SetRts()
{
        DEBUG((debug,"FT_SetRts\n"));
        __asm{ jmp _O_FT_SetRts }
}

extern "C" void __declspec(naked) __stdcall _I_FT_SetTimeouts()
{
        DEBUG((debug,"FT_SetTimeouts\n"));
        __asm{ jmp _O_FT_SetTimeouts }
}

extern "C" void __declspec(naked) __stdcall _I_FT_SetUSBParameters()
{
        DEBUG((debug,"FT_SetUSBParameters\n"));
        __asm{ jmp _O_FT_SetUSBParameters }
}

extern "C" void __declspec(naked) __stdcall _I_FT_SetWaitMask()
{
        DEBUG((debug,"FT_SetWaitMask\n"));
        __asm{ jmp _O_FT_SetWaitMask }
}

extern "C" void __declspec(naked) __stdcall _I_FT_StopInTask()
{
        DEBUG((debug,"FT_StopInTask\n"));
        __asm{ jmp _O_FT_StopInTask }
}

extern "C" void __declspec(naked) __stdcall _I_FT_W32_CancelIo()
{
        DEBUG((debug,"FT_W32_CancelIo\n"));
        __asm{ jmp _O_FT_W32_CancelIo }
}

extern "C" void __declspec(naked) __stdcall _I_FT_W32_ClearCommBreak()
{
        DEBUG((debug,"FT_W32_ClearCommBreak\n"));
        __asm{ jmp _O_FT_W32_ClearCommBreak }
}

extern "C" void __declspec(naked) __stdcall _I_FT_W32_ClearCommError()
{
        DEBUG((debug,"FT_W32_ClearCommError\n"));
        __asm{ jmp _O_FT_W32_ClearCommError }
}

extern "C" void __declspec(naked) __stdcall _I_FT_W32_CloseHandle()
{
        DEBUG((debug,"FT_W32_CloseHandle\n"));
        __asm{ jmp _O_FT_W32_CloseHandle }
}

extern "C" void __declspec(naked) __stdcall _I_FT_W32_CreateFile()
{
        DEBUG((debug,"FT_W32_CreateFile\n"));
        __asm{ jmp _O_FT_W32_CreateFile }
}

extern "C" void __declspec(naked) __stdcall _I_FT_W32_EscapeCommFunction()
{
        DEBUG((debug,"FT_W32_EscapeCommFunction\n"));
        __asm{ jmp _O_FT_W32_EscapeCommFunction }
}

extern "C" void __declspec(naked) __stdcall _I_FT_W32_GetCommMask()
{
        DEBUG((debug,"FT_W32_GetCommMask\n"));
        __asm{ jmp _O_FT_W32_GetCommMask }
}

extern "C" void __declspec(naked) __stdcall _I_FT_W32_GetCommModemStatus()
{
        DEBUG((debug,"FT_W32_GetCommModemStatus\n"));
        __asm{ jmp _O_FT_W32_GetCommModemStatus }
}

extern "C" void __declspec(naked) __stdcall _I_FT_W32_GetCommState()
{
        DEBUG((debug,"FT_W32_GetCommState\n"));
        __asm{ jmp _O_FT_W32_GetCommState }
}

extern "C" void __declspec(naked) __stdcall _I_FT_W32_GetCommTimeouts()
{
        DEBUG((debug,"FT_W32_GetCommTimeouts\n"));
        __asm{ jmp _O_FT_W32_GetCommTimeouts }
}

extern "C" void __declspec(naked) __stdcall _I_FT_W32_GetLastError()
{
        DEBUG((debug,"FT_W32_GetLastError\n"));
        __asm{ jmp _O_FT_W32_GetLastError }
}

extern "C" void __declspec(naked) __stdcall _I_FT_W32_GetOverlappedResult()
{
        DEBUG((debug,"FT_W32_GetOverlappedResult\n"));
        __asm{ jmp _O_FT_W32_GetOverlappedResult }
}

extern "C" void __declspec(naked) __stdcall _I_FT_W32_PurgeComm()
{
        DEBUG((debug,"FT_W32_PurgeComm\n"));
        __asm{ jmp _O_FT_W32_PurgeComm }
}

extern "C" void __declspec(naked) __stdcall _I_FT_W32_ReadFile()
{
        DEBUG((debug,"FT_W32_ReadFile\n"));
        __asm{ jmp _O_FT_W32_ReadFile }
}

extern "C" void __declspec(naked) __stdcall _I_FT_W32_SetCommBreak()
{
        DEBUG((debug,"FT_W32_SetCommBreak\n"));
        __asm{ jmp _O_FT_W32_SetCommBreak }
}

extern "C" void __declspec(naked) __stdcall _I_FT_W32_SetCommMask()
{
        DEBUG((debug,"FT_W32_SetCommMask\n"));
        __asm{ jmp _O_FT_W32_SetCommMask }
}

extern "C" void __declspec(naked) __stdcall _I_FT_W32_SetCommState()
{
        DEBUG((debug,"FT_W32_SetCommState\n"));
        __asm{ jmp _O_FT_W32_SetCommState }
}

extern "C" void __declspec(naked) __stdcall _I_FT_W32_SetCommTimeouts()
{
        DEBUG((debug,"FT_W32_SetCommTimeouts\n"));
        __asm{ jmp _O_FT_W32_SetCommTimeouts }
}

extern "C" void __declspec(naked) __stdcall _I_FT_W32_SetupComm()
{
        DEBUG((debug,"FT_W32_SetupComm\n"));
        __asm{ jmp _O_FT_W32_SetupComm }
}

extern "C" void __declspec(naked) __stdcall _I_FT_W32_WaitCommEvent()
{
        DEBUG((debug,"FT_W32_WaitCommEvent\n"));
        __asm{ jmp _O_FT_W32_WaitCommEvent }
}

extern "C" void __declspec(naked) __stdcall _I_FT_W32_WriteFile()
{
        DEBUG((debug,"FT_W32_WriteFile\n"));
        __asm{ jmp _O_FT_W32_WriteFile }
}

extern "C" void __declspec(naked) __stdcall _I_FT_WaitOnMask()
{
        DEBUG((debug,"FT_WaitOnMask\n"));
        __asm{ jmp _O_FT_WaitOnMask }
}

extern "C" FT_STATUS __stdcall _I_FT_Write(FT_HANDLE ftHandle,LPVOID lpBuffer,DWORD dwBytesToWrite,LPDWORD lpBytesWritten)
{
		FT_STATUS res;
        //DEBUG((debug,"FT_Write\n"));
		res = _O_FT_Write(ftHandle,lpBuffer,dwBytesToWrite,lpBytesWritten);
		hexdump(">",lpBuffer,dwBytesToWrite);
		return res;
}

extern "C" void __declspec(naked) __stdcall _I_FT_WriteEE()
{
        DEBUG((debug,"FT_WriteEE\n"));
        __asm{ jmp _O_FT_WriteEE }
}



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		if (!debug)
			debug = fopen("debug.txt","w");
		DEBUG((debug,"DllMain\n"));
		gs_hDLL = LoadLibrary("ftd2xx1.dll");
        _O_FT_Close = GetProcAddress(gs_hDLL, "FT_Close");
        _O_FT_ClrDtr = GetProcAddress(gs_hDLL, "FT_ClrDtr");
        _O_FT_ClrRts = GetProcAddress(gs_hDLL, "FT_ClrRts");
        _O_FT_CreateDeviceInfoList = (FT_CreateDeviceInfoList *)GetProcAddress(gs_hDLL, "FT_CreateDeviceInfoList");
        _O_FT_CyclePort = GetProcAddress(gs_hDLL, "FT_CyclePort");
        _O_FT_EE_Program = GetProcAddress(gs_hDLL, "FT_EE_Program");
        _O_FT_EE_ProgramEx = GetProcAddress(gs_hDLL, "FT_EE_ProgramEx");
        _O_FT_EE_Read = GetProcAddress(gs_hDLL, "FT_EE_Read");
        _O_FT_EE_ReadEx = GetProcAddress(gs_hDLL, "FT_EE_ReadEx");
        _O_FT_EE_UARead = GetProcAddress(gs_hDLL, "FT_EE_UARead");
        _O_FT_EE_UASize = GetProcAddress(gs_hDLL, "FT_EE_UASize");
        _O_FT_EE_UAWrite = GetProcAddress(gs_hDLL, "FT_EE_UAWrite");
        _O_FT_EraseEE = GetProcAddress(gs_hDLL, "FT_EraseEE");
        _O_FT_GetBitMode = GetProcAddress(gs_hDLL, "FT_GetBitMode");
        _O_FT_GetComPortNumber = GetProcAddress(gs_hDLL, "FT_GetComPortNumber");
        _O_FT_GetDeviceInfo = GetProcAddress(gs_hDLL, "FT_GetDeviceInfo");
        _O_FT_GetDeviceInfoDetail = GetProcAddress(gs_hDLL, "FT_GetDeviceInfoDetail");
        _O_FT_GetDeviceInfoList = (FT_GetDeviceInfoList *)GetProcAddress(gs_hDLL, "FT_GetDeviceInfoList");
        _O_FT_GetDriverVersion = GetProcAddress(gs_hDLL, "FT_GetDriverVersion");
        _O_FT_GetEventStatus = GetProcAddress(gs_hDLL, "FT_GetEventStatus");
        _O_FT_GetLatencyTimer = GetProcAddress(gs_hDLL, "FT_GetLatencyTimer");
        _O_FT_GetLibraryVersion = GetProcAddress(gs_hDLL, "FT_GetLibraryVersion");
        _O_FT_GetModemStatus = GetProcAddress(gs_hDLL, "FT_GetModemStatus");
        _O_FT_GetQueueStatus = GetProcAddress(gs_hDLL, "FT_GetQueueStatus");
        _O_FT_GetStatus = GetProcAddress(gs_hDLL, "FT_GetStatus");
        _O_FT_IoCtl = GetProcAddress(gs_hDLL, "FT_IoCtl");
        _O_FT_ListDevices = (FT_ListDevices *)GetProcAddress(gs_hDLL, "FT_ListDevices");
        _O_FT_Open = GetProcAddress(gs_hDLL, "FT_Open");
        _O_FT_OpenEx = GetProcAddress(gs_hDLL, "FT_OpenEx");
        _O_FT_Purge = GetProcAddress(gs_hDLL, "FT_Purge");
        _O_FT_Read = (FT_Read *)GetProcAddress(gs_hDLL, "FT_Read");
        _O_FT_ReadEE = GetProcAddress(gs_hDLL, "FT_ReadEE");
        _O_FT_Reload = GetProcAddress(gs_hDLL, "FT_Reload");
        _O_FT_Rescan = GetProcAddress(gs_hDLL, "FT_Rescan");
        _O_FT_ResetDevice = GetProcAddress(gs_hDLL, "FT_ResetDevice");
        _O_FT_ResetPort = GetProcAddress(gs_hDLL, "FT_ResetPort");
        _O_FT_RestartInTask = GetProcAddress(gs_hDLL, "FT_RestartInTask");
        _O_FT_SetBaudRate = (FT_SetBaudRate *)GetProcAddress(gs_hDLL, "FT_SetBaudRate");
        _O_FT_SetBitMode = GetProcAddress(gs_hDLL, "FT_SetBitMode");
        _O_FT_SetBreakOff = GetProcAddress(gs_hDLL, "FT_SetBreakOff");
        _O_FT_SetBreakOn = GetProcAddress(gs_hDLL, "FT_SetBreakOn");
        _O_FT_SetChars = GetProcAddress(gs_hDLL, "FT_SetChars");
        _O_FT_SetDataCharacteristics = (FT_SetDataCharacteristics *)GetProcAddress(gs_hDLL, "FT_SetDataCharacteristics");
        _O_FT_SetDeadmanTimeout = GetProcAddress(gs_hDLL, "FT_SetDeadmanTimeout");
        _O_FT_SetDivisor = GetProcAddress(gs_hDLL, "FT_SetDivisor");
        _O_FT_SetDtr = GetProcAddress(gs_hDLL, "FT_SetDtr");
        _O_FT_SetEventNotification = GetProcAddress(gs_hDLL, "FT_SetEventNotification");
        _O_FT_SetFlowControl = GetProcAddress(gs_hDLL, "FT_SetFlowControl");
        _O_FT_SetLatencyTimer = GetProcAddress(gs_hDLL, "FT_SetLatencyTimer");
        _O_FT_SetResetPipeRetryCount = GetProcAddress(gs_hDLL, "FT_SetResetPipeRetryCount");
        _O_FT_SetRts = GetProcAddress(gs_hDLL, "FT_SetRts");
        _O_FT_SetTimeouts = GetProcAddress(gs_hDLL, "FT_SetTimeouts");
        _O_FT_SetUSBParameters = GetProcAddress(gs_hDLL, "FT_SetUSBParameters");
        _O_FT_SetWaitMask = GetProcAddress(gs_hDLL, "FT_SetWaitMask");
        _O_FT_StopInTask = GetProcAddress(gs_hDLL, "FT_StopInTask");
        _O_FT_W32_CancelIo = GetProcAddress(gs_hDLL, "FT_W32_CancelIo");
        _O_FT_W32_ClearCommBreak = GetProcAddress(gs_hDLL, "FT_W32_ClearCommBreak");
        _O_FT_W32_ClearCommError = GetProcAddress(gs_hDLL, "FT_W32_ClearCommError");
        _O_FT_W32_CloseHandle = GetProcAddress(gs_hDLL, "FT_W32_CloseHandle");
        _O_FT_W32_CreateFile = GetProcAddress(gs_hDLL, "FT_W32_CreateFile");
        _O_FT_W32_EscapeCommFunction = GetProcAddress(gs_hDLL, "FT_W32_EscapeCommFunction");
        _O_FT_W32_GetCommMask = GetProcAddress(gs_hDLL, "FT_W32_GetCommMask");
        _O_FT_W32_GetCommModemStatus = GetProcAddress(gs_hDLL, "FT_W32_GetCommModemStatus");
        _O_FT_W32_GetCommState = GetProcAddress(gs_hDLL, "FT_W32_GetCommState");
        _O_FT_W32_GetCommTimeouts = GetProcAddress(gs_hDLL, "FT_W32_GetCommTimeouts");
        _O_FT_W32_GetLastError = GetProcAddress(gs_hDLL, "FT_W32_GetLastError");
        _O_FT_W32_GetOverlappedResult = GetProcAddress(gs_hDLL, "FT_W32_GetOverlappedResult");
        _O_FT_W32_PurgeComm = GetProcAddress(gs_hDLL, "FT_W32_PurgeComm");
        _O_FT_W32_ReadFile = GetProcAddress(gs_hDLL, "FT_W32_ReadFile");
        _O_FT_W32_SetCommBreak = GetProcAddress(gs_hDLL, "FT_W32_SetCommBreak");
        _O_FT_W32_SetCommMask = GetProcAddress(gs_hDLL, "FT_W32_SetCommMask");
        _O_FT_W32_SetCommState = GetProcAddress(gs_hDLL, "FT_W32_SetCommState");
        _O_FT_W32_SetCommTimeouts = GetProcAddress(gs_hDLL, "FT_W32_SetCommTimeouts");
        _O_FT_W32_SetupComm = GetProcAddress(gs_hDLL, "FT_W32_SetupComm");
        _O_FT_W32_WaitCommEvent = GetProcAddress(gs_hDLL, "FT_W32_WaitCommEvent");
        _O_FT_W32_WriteFile = GetProcAddress(gs_hDLL, "FT_W32_WriteFile");
        _O_FT_WaitOnMask = GetProcAddress(gs_hDLL, "FT_WaitOnMask");
        _O_FT_Write = (FT_Write *)GetProcAddress(gs_hDLL, "FT_Write");
        _O_FT_WriteEE = GetProcAddress(gs_hDLL, "FT_WriteEE");
		DEBUG((debug,"DllMain: Loaded imports\n"));
		return TRUE;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		if (debug)
			fclose(debug);
		FreeLibrary(gs_hDLL);
		return TRUE;
	}
	return TRUE;
}
