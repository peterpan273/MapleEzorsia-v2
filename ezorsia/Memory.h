#pragma once
#include "logger.h"
#include <windows.h>


#define INITMAPLEHOOK(pOrigFunc, Func_t, pNewFunc, dwAddress, firstval) \
    while (1) {                                                                \
        if (ReadValue<BYTE>(dwAddress) != firstval) {                             \
            Sleep(1);                                                             \
        } else {                                                                  \
            break;                                                                \
        }                                                                         \
    }                                                                             \
    pOrigFunc = reinterpret_cast<Func_t>(dwAddress);                              \
    if (!Memory::SetHook(true, reinterpret_cast<void**>(&pOrigFunc), pNewFunc)) { \
        Log("Failed to hook maple func at address %d", dwAddress);                \
    }

class Memory
{
public:
	static bool SetHook(bool attach, void** ptrTarget, void* ptrDetour);
	static void FillBytes(DWORD dwOriginAddress, unsigned char ucValue, int nCount);
	static void WriteString(DWORD dwOriginAddress, const char* sContent);
	static void WriteByte(DWORD dwOriginAddress, unsigned char ucValue);
	static void WriteShort(DWORD dwOriginAddress, unsigned short usValue);
	static void WriteInt(DWORD dwOriginAddress, unsigned int dwValue);
	static void WriteDouble(DWORD dwOriginAddress, double dwValue);
	static void CodeCave(void* ptrCodeCave, DWORD dwOriginAddress, int nNOPCount);
	static void WriteByteArray(DWORD dwOriginAddress, unsigned char* ucValue, const int ucValueSize);
	static bool UseVirtuProtect;
};

