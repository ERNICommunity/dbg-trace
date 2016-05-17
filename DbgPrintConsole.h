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

/**
 * @brief Debug trace print for printing to a console output.
 */
class DbgPrint_Console : public IDbgPrint
{
public:

  /**
   * Constructor of a debug trace console printer.
   */
  DbgPrint_Console();

  /**
   * Destructor of a debug trace console printer.
   */
  virtual ~DbgPrint_Console() { }

  /**
   * @brief Prints a string to the console output.
   * @param str Const char message to be printed.
   */
  virtual void print(const char* str);
#ifdef ARDUINO
  /**
   * @brief Prints a string from flash memory to the console output. (ram optimization for Arduino).
   * @param fshvar Const char message to be printed.
   */
  virtual void print(const __FlashStringHelper* fshvar);
#endif

private: // forbidden default functions
  DbgPrint_Console& operator = (const DbgPrint_Console& src); // assignment operator
  DbgPrint_Console(const DbgPrint_Console& src);              // copy constructor
};

#endif /* PLAT_DEBUG_TRACE_DBGPRINTCONSOLE_H_ */
