/*
 * DbgPrintConsole.cpp
 *
 *  Created on: 21.04.2015
 *      Author: aschoepfer
 */

#include "DbgPrintConsole.h"

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <stdio.h>
#endif

DbgPrint_Console::DbgPrint_Console()
{ }

void DbgPrint_Console::print(const char* str)
{
#ifdef ARDUINO
  Serial.println(str);
#else
  printf("%s\n", str);
#endif
}

#ifdef ARDUINO
void DbgPrint_Console::print(const __FlashStringHelper* fshvar)
{
  Serial.println(fshvar);
}
#endif
