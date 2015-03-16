/*
 * DbgTracePort.h
 *
 *  Created on: 16.03.2015
 *      Author: niklausd
 */

#ifndef PLAT_DEBUG_TRACE_DBGTRACEPORT_H_
#define PLAT_DEBUG_TRACE_DBGTRACEPORT_H_

typedef enum
{
  none      =  -1,
  emergency =   0,
  alert     =   1,
  critical  =   2,
  error     =   3,
  warning   =   4,
  notice    =   5,
  info      =   6,
  debug     =   7
} DbgTraceLevel;

class DbgTrace_Port
{
public:
  typedef enum
  {
    none      =  -1,
    emergency =   0,
    alert     =   1,
    critical  =   2,
    error     =   3,
    warning   =   4,
    notice    =   5,
    info      =   6,
    debug     =   7
  } DbgTraceLevel;

  DbgTrace_Port();
  virtual ~DbgTrace_Port();

  void setLevel(DbgTraceLevel level);

  DbgTraceLevel getLevel();

private:
  DbgTraceLevel m_level;

private: // forbidden default functions
  DbgTrace_Port& operator = (const DbgTrace_Port& src); // assignment operator
  DbgTrace_Port(const DbgTrace_Port& src);              // copy constructor

};

#endif /* PLAT_DEBUG_TRACE_DBGTRACEPORT_H_ */
