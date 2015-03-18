/*
 * DbgTracePort.h
 *
 *  Created on: 16.03.2015
 *      Author: niklausd
 */

#ifndef PLAT_DEBUG_TRACE_DBGTRACEPORT_H_
#define PLAT_DEBUG_TRACE_DBGTRACEPORT_H_

#include "Print.h"


#define TR_PRINT(PORT, LEVEL, MSG)  do { if (((PORT)->getLevel()>=(LEVEL))) (PORT)->print((MSG)); } while (0);


class DbgTrace_Port : public Print
{
public:
  typedef enum
  {
    none      = -1,
    emergency =  0,
    alert     =  1,
    critical  =  2,
    error     =  3,
    warning   =  4,
    notice    =  5,
    info      =  6,
    debug     =  7
  } DbgTraceLevel;

  DbgTrace_Port(const char* tag);
  DbgTrace_Port(const __FlashStringHelper* tag);
  virtual ~DbgTrace_Port();

  void setLevel(DbgTraceLevel level);

  DbgTraceLevel getLevel();

  const char* getTag();

  virtual size_t write(const uint8_t *buffer, size_t size);
  virtual size_t write(uint8_t num);


private:
  DbgTraceLevel m_level;
  const char* m_tag;

private: // forbidden default functions
  DbgTrace_Port& operator = (const DbgTrace_Port& src); // assignment operator
  DbgTrace_Port(const DbgTrace_Port& src);              // copy constructor
};

#endif /* PLAT_DEBUG_TRACE_DBGTRACEPORT_H_ */
