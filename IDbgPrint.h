/*
 * IDbgPrint.h
 *
 *  Created on: 21.04.2015
 *      Author: aschoepfer
 */
#ifndef PLAT_DEBUG_TRACE_IDBGPRINT_H_
#define PLAT_DEBUG_TRACE_IDBGPRINT_H_

#ifdef ARDUINO
#include <Arduino.h>
#endif

/**
 * @brief Interface to a print instance (e.g. console, file writer)
 */

class IDbgPrint
{
protected: /// interface - constructor must not be accessible
  IDbgPrint() { }

public:
  virtual ~IDbgPrint() { }

  /**
   * Print method to write a given string to a file, console or other device
   * @param str Pointer to const char, which will be printed by the function.
   */
  virtual void print(const char* str) = 0;
#ifdef ARDUINO
  /**
   * Like the other print function but optimized for embedded controllers, using flash memory for the string.
   * @param fshvar String to be printed (to be created with the F("") macro.
   */
  virtual void print(const __FlashStringHelper* fshvar) = 0;
#endif

private: // forbidden default functions
  IDbgPrint& operator = (const IDbgPrint& src); // assignment operator
  IDbgPrint(const IDbgPrint& src);              // copy constructor
};

#endif /* PLAT_DEBUG_TRACE_IDBGPRINT_H_ */
