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

void DbgPrint_File::print(const char* buf)
{

  //TODO implement write to file
#ifdef ARDUINO
  Serial.println(buf);
#else
  printf("%s\n", buf);
#endif
}
