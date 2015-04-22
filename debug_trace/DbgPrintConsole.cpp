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

void DbgPrint_Console::print(const char* buf)
{
#ifdef ARDUINO
  Serial.println(buf);
#else
  printf("%s\n", buf);
#endif
}

