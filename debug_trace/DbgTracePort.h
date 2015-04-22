/*
 * DbgTracePort.h
 *
 *  Created on: 16.03.2015
 *      Author: niklausd
 */

#ifndef PLAT_DEBUG_TRACE_DBGTRACEPORT_H_
#define PLAT_DEBUG_TRACE_DBGTRACEPORT_H_

#include "DbgTraceLevel.h"
#include <Print.h>

#define TR_PRINT(PORT, LEVEL, MSG)  do { if (((PORT)->getLevel()>=(LEVEL))) (PORT)->print((MSG)); } while (0);

class DbgTrace_Out;

class DbgTrace_Port : public Print
{
public:

  DbgTrace_Port(const char* tag);
  DbgTrace_Port(const __FlashStringHelper* tag);
  virtual ~DbgTrace_Port() { }

  DbgTrace_Port* getNextPort() { return m_nextPort; }
  void setNextPort(DbgTrace_Port* nextPort) { if(0 != nextPort) m_nextPort = nextPort; }

  void setOut(DbgTrace_Out* out) { m_out = out; }
  DbgTrace_Out* getOut() { return m_out; }

  void setLevel(DbgTrace_Level::Level level) { m_level = level; }
  DbgTrace_Level::Level getLevel() { return m_level; }

  const char* getTag() { return m_tag; }

  virtual size_t write(const uint8_t *buffer, size_t size);
  virtual size_t write(uint8_t num);

  static const uint8_t s_cMaxPortTagLength = 16;

private:
  DbgTrace_Out* m_out;
  DbgTrace_Level::Level m_level;
  DbgTrace_Port* m_nextPort;
  const char* m_tag;

private: // forbidden default functions
  DbgTrace_Port& operator = (const DbgTrace_Port& src); // assignment operator
  DbgTrace_Port(const DbgTrace_Port& src);              // copy constructor
  DbgTrace_Port();
};

#endif /* PLAT_DEBUG_TRACE_DBGTRACEPORT_H_ */
