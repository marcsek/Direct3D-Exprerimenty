#pragma once
/**
*     /\
*    /??\
*	Header ktor� sa pou��va na importovanie "Windows.h" 
*	 \??/
*	  \/
*/

/* Windows 7+ */
#define WIN32_WINNT 0x0601
#include <sdkddkver.h>

/* Vypnutie niektor�ch funkci� Windowsu */
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define STRICT

#include "Windows.h"