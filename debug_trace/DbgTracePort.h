/*
 * DbgTracePort.h
 *
 *  Created on: 16.03.2015
 *      Author: niklausd
 */

#ifndef PLAT_DEBUG_TRACE_DBGTRACEPORT_H_
#define PLAT_DEBUG_TRACE_DBGTRACEPORT_H_

#include "DbgTraceLevel.h"
#ifdef ARDUINO
#include <Arduino.h>
#endif

class DbgTrace_Context;
class DbgTrace_Out;

#define TR_PRINT_STR(PORT, LEVEL, MSG)  do { if (((PORT)->getLevel()>=(LEVEL))) (PORT)->printStr((MSG)); } while (0);
#define TR_PRINT_LONG(PORT, LEVEL, MSG)  do { if (((PORT)->getLevel()>=(LEVEL))) (PORT)->printLong((MSG)); } while (0);
#define TR_PRINT_DBL(PORT, LEVEL, MSG)  do { if (((PORT)->getLevel()>=(LEVEL))) (PORT)->printDbl((MSG)); } while (0);
#ifdef ARDUINO
#define TR_PRINT_FSTR(PORT, LEVEL, MSG)  do { if (((PORT)->getLevel()>=(LEVEL))) (PORT)->printFStr((MSG)); } while (0);
#endif

class DbgTrace_Port
{
public:

  DbgTrace_Port(DbgTrace_Context* context, const char* tag, DbgTrace_Out* out, DbgTrace_Level::Level level);
#ifdef ARDUINO
  DbgTrace_Port(DbgTrace_Context* context, const __FlashStringHelper* tag, DbgTrace_Out* out, DbgTrace_Level::Level level);
#endif
  virtual ~DbgTrace_Port();

  DbgTrace_Port* getNextPort() { return m_nextPort; }
  void setNextPort(DbgTrace_Port* nextPort) { if(0 != nextPort) m_nextPort = nextPort; }

  void setOut(DbgTrace_Out* out) { m_out = out; }
  DbgTrace_Out* getOut() { return m_out; }

  void setLevel(DbgTrace_Level::Level level) { m_level = level; }
  DbgTrace_Level::Level getLevel() { return m_level; }

//  template <typename Tmsg> void print(Tmsg msg);
  void printStr(const char* str);
#ifdef ARDUINO
  void printFStr(const __FlashStringHelper* str) { printStr(reinterpret_cast<const char*>(str)); }
#endif
  void printLong(long num);
  void printDbl(double val);

  const char* getTag() { return m_tag; }
  void createCliNodes(DbgCli_Topic* contextTopic);

  static const unsigned int s_cMaxPortTagLength = 16;
  static const unsigned int s_cTestTimeStamp = 10;
  static const unsigned int s_cArduinoTimeStamp = 12;
  static const unsigned int s_cTraceBufSize = s_cMaxPortTagLength + s_cMaxPortTagLength + 40;

private:
  void getTime(char* timeStr);

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
