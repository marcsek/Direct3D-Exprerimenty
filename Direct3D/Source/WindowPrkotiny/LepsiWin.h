#pragma once
/**
*     /\
*    /??\
*	 Header ktorý sa používa na importovanie "Windows.h" 
*	 \??/
*	  \/
*/

/* Windows 7+ */
#define WIN32_WINNT 0x0601
#include <sdkddkver.h>

/* Vypnutie niektorých funkcií Windowsu */
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define STRICT

#include "Windows.h"
