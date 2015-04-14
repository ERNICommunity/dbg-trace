/*
 * DbgTracePort.h
 *
 *  Created on: 16.03.2015
 *      Author: niklausd
 */

#ifndef PLAT_DEBUG_TRACE_DBGTRACEPORT_H_
#define PLAT_DEBUG_TRACE_DBGTRACEPORT_H_

#include <DbgTraceLevel.h>
#include <Print.h>



#define TR_PRINT(PORT, LEVEL, MSG)  do { if (((PORT)->getLevel()>=(LEVEL))) (PORT)->print((MSG)); } while (0);


class DbgTrace_Port : public Print
{
public:

  DbgTrace_Port(const char* tag);
  DbgTrace_Port(const __FlashStringHelper* tag);
  virtual ~DbgTrace_Port();

  void setLevel(DbgTraceLevel::Level level);

  DbgTraceLevel::Level getLevel();

  const char* getTag();

  virtual size_t write(const uint8_t *buffer, size_t size);
  virtual size_t write(uint8_t num);


private:
  DbgTraceLevel::Level m_level;
  const char* m_tag;

private: // forbidden default functions
  DbgTrace_Port& operator = (const DbgTrace_Port& src); // assignment operator
  DbgTrace_Port(const DbgTrace_Port& src);              // copy constructor
};

#endif /* PLAT_DEBUG_TRACE_DBGTRACEPORT_H_ */
