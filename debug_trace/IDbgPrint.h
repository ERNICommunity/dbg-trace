/*
 * IDbgPrint.h
 *
 *  Created on: 21.04.2015
 *      Author: aschoepfer
 */
#ifndef PLAT_DEBUG_TRACE_IDBGPRINT_H_
#define PLAT_DEBUG_TRACE_IDBGPRINT_H_

class IDbgPrint
{
protected: /// interface - constructor must not be accessible
  IDbgPrint() { }

public:
  virtual ~IDbgPrint() { }

  virtual void print(const char *buffer) = 0;

private: // forbidden default functions
  IDbgPrint& operator = (const IDbgPrint& src); // assignment operator
  IDbgPrint(const IDbgPrint& src);              // copy constructor
};

#endif /* PLAT_DEBUG_TRACE_IDBGPRINT_H_ */
