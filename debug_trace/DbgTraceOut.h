/*
 * DbgTraceOut.h
 *
 *  Created on: 20.04.2015
 *      Author: aschoepfer
 */

#ifndef PLAT_DEBUG_TRACE_DBGTRACEOUT_H_
#define PLAT_DEBUG_TRACE_DBGTRACEOUT_H_

class DbgTrace_Context;
class IDbgPrint;

class DbgTrace_Out
{
public:
  DbgTrace_Out(DbgTrace_Context* context, const char* name, IDbgPrint* dbgPrint);
  virtual ~DbgTrace_Out();

  DbgTrace_Out* getNextOut() { return m_nextOut; }
  void setNextOut(DbgTrace_Out* nextOut) { if(0 != nextOut) m_nextOut = nextOut; }

  const char* getName() { return m_name; }

  void print(const char* str);

  static const unsigned int s_cMaxOutNameLength = 16;

private:
  const char* m_name;
  DbgTrace_Out* m_nextOut;
  IDbgPrint* m_dbgPrint;

private: // forbidden default functions
  DbgTrace_Out& operator = (const DbgTrace_Out& src); // assignment operator
  DbgTrace_Out(const DbgTrace_Out& src);              // copy constructor
  DbgTrace_Out();
};

#endif /* PLAT_DEBUG_TRACE_DBGTRACEOUT_H_ */
