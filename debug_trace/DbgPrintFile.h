/*
 * DbgPrintFile.h
 *
 *  Created on: 21.04.2015
 *      Author: aschoepfer
 */

#ifndef PLAT_DEBUG_TRACE_DBGPRINTFILE_H_
#define PLAT_DEBUG_TRACE_DBGPRINTFILE_H_

#include "IDbgPrint.h"
#ifdef ARDUINO
#include <Arduino.h>
#endif

/**
 * @brief Debug trace print for printing to a file.
 */
class DbgPrint_File : public IDbgPrint
{
public:

  /**
   * Constructor of a debug trace file printer.
   */
  DbgPrint_File();

  /**
   * Destructor of a debug trace file printer.
   */
  virtual ~DbgPrint_File() { }

  /**
   * @brief Store a string to a file.
   * @param str Const char message to be stored.
   */
  virtual void print(const char* str);
#ifdef ARDUINO
  /**
   * @brief Store a string from flash memory to a file.  (ram optimization for Arduino).
   * @param fshvar Const char message to be stored.
   */
  virtual void print(const __FlashStringHelper* fshvar);
#endif

private: // forbidden default functions
  DbgPrint_File& operator = (const DbgPrint_File& src); // assignment operator
  DbgPrint_File(const DbgPrint_File& src);              // copy constructor
};

#endif /* PLAT_DEBUG_TRACE_DBGPRINTFILE_H_ */
