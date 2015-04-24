/*
 * DbgPrintFile.cpp
 *
 *  Created on: 21.04.2015
 *      Author: aschoepfer
 */

#include "DbgPrintFile.h"
#ifdef ARDUINO
#include <Arduino.h>
#else
#include <stdio.h>
#endif

DbgPrint_File::DbgPrint_File()
{ }

// TODO write to file
void DbgPrint_File::print(const char str[])
{

}

#ifdef ARDUINO
// TODO write to file
void DbgPrint_File::print(const __FlashStringHelper* fshvar)
{

}
#endif
