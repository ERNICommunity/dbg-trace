/*
 * DbgTraceOut.h
 *
 *  Created on: 20.04.2015
 *      Author: aschoepfer
 */

#ifndef PLAT_DEBUG_TRACE_DBGTRACEOUT_H_
#define PLAT_DEBUG_TRACE_DBGTRACEOUT_H_

#include <Print.h>

class IDbgPrint;

class DbgTrace_Out
{
public:
  DbgTrace_Out(char* name, IDbgPrint* dbgPrint);
  virtual ~DbgTrace_Out() { }

  DbgTrace_Out* getNextOut() { return m_nextOut; }
  void setNextOut(DbgTrace_Out* nextOut) { if(0 != nextOut) m_nextOut = nextOut; }

  char* getName() { return m_name; }

  static const uint8_t s_cMaxOutNameLength = 16;

private:
  char* m_name;
  DbgTrace_Out* m_nextOut;
  IDbgPrint* m_dbgPrint;

private: // forbidden default functions
  DbgTrace_Out& operator = (const DbgTrace_Out& src); // assignment operator
  DbgTrace_Out(const DbgTrace_Out& src);              // copy constructor
  DbgTrace_Out();
};

#endif /* PLAT_DEBUG_TRACE_DBGTRACEOUT_H_ */
