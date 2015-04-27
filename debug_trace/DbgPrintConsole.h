/*
 * DbgPrintConsole.h
 *
 *  Created on: 21.04.2015
 *      Author: aschoepfer
 */

#ifndef PLAT_DEBUG_TRACE_DBGPRINTCONSOLE_H_
#define PLAT_DEBUG_TRACE_DBGPRINTCONSOLE_H_

#include "IDbgPrint.h"
#ifdef ARDUINO
#include <Arduino.h>
#endif

class DbgPrint_Console : public IDbgPrint
{
public:
  DbgPrint_Console();
  virtual ~DbgPrint_Console() { }

  virtual void print(const char* str);
#ifdef ARDUINO
  virtual void print(const __FlashStringHelper* fshvar);
#endif

private: // forbidden default functions
  DbgPrint_Console& operator = (const DbgPrint_Console& src); // assignment operator
  DbgPrint_Console(const DbgPrint_Console& src);              // copy constructor
};

#endif /* PLAT_DEBUG_TRACE_DBGPRINTCONSOLE_H_ */
