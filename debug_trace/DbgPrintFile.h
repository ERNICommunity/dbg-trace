/*
 * DbgPrintFile.h
 *
 *  Created on: 21.04.2015
 *      Author: aschoepfer
 */

#ifndef PLAT_DEBUG_TRACE_DBGPRINTFILE_H_
#define PLAT_DEBUG_TRACE_DBGPRINTFILE_H_

#include "IDbgPrint.h"

class DbgPrint_File : public IDbgPrint
{
public:
  DbgPrint_File();
  virtual ~DbgPrint_File() { }

  virtual void print(const char* buf);

private: // forbidden default functions
  DbgPrint_File& operator = (const DbgPrint_File& src); // assignment operator
  DbgPrint_File(const DbgPrint_File& src);              // copy constructor
};

#endif /* PLAT_DEBUG_TRACE_DBGPRINTFILE_H_ */
