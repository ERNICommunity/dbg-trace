/*
 * DbgTracePort.cpp
 *
 *  Created on: 16.03.2015
 *      Author: niklausd
 */

#include "DbgTraceContext.h"
#include "DbgTraceOut.h"
#include "DbgTracePort.h"

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <time.h>
#endif
#include <stdio.h>

DbgTrace_Port::DbgTrace_Port(DbgTrace_Context* context, const char* tag, DbgTrace_Out* out, DbgTrace_Level::Level level)
: m_out(out)
, m_level(level)
, m_nextPort(0)
, m_tag(tag)
{
  if(0 != context)
  {
    context->addTracePort(this);
  }
}

#ifdef ARDUINO
DbgTrace_Port::DbgTrace_Port(DbgTrace_Context* context, const __FlashStringHelper* tag, DbgTrace_Out* out, DbgTrace_Level::Level level)
: m_out(out)
, m_level(level)
, m_nextPort(0)
, m_tag(reinterpret_cast<const char*>(tag))
{
  if(0 != context)
  {
    context->addTracePort(this);
  }
}
#endif

DbgTrace_Port::~DbgTrace_Port()
{
  //Delete tracePort in single linked list
  DbgTrace_Context* context = DbgTrace_Context::getContext();
  if(0 != context)
  {
    context->deleteTracePort(m_tag);
  }
}

void DbgTrace_Port::printStr(const char* str)
{
  if(0 != m_out)
  {
#ifdef ARDUINO
    char timeStr[s_cArduinoTimeStamp];
#else
    char timeStr[s_cTestTimeStamp];
#endif
    char stream[s_cTraceBufSize];
    getTime(timeStr);
    snprintf(stream, sizeof(stream), "%s - %s: %s\n", timeStr, getTag(), str);

    m_out->print(stream);
  }
}

void DbgTrace_Port::printLong(long num)
{
  if(0 != m_out)
  {
#ifdef ARDUINO
    char timeStr[s_cArduinoTimeStamp];
#else
    char timeStr[s_cTestTimeStamp];
#endif
    char stream[s_cTraceBufSize];
    getTime(timeStr);
    snprintf(stream, sizeof(stream), "%s - %s: %ld\n", timeStr, getTag(), num);

    m_out->print(stream);
  }
}

void DbgTrace_Port::printDbl(double val)
{
  if(0 != m_out)
  {
#ifdef ARDUINO
    char timeStr[s_cArduinoTimeStamp];
#else
    char timeStr[s_cTestTimeStamp];
#endif
    getTime(timeStr);
    char stream[s_cTraceBufSize];
    snprintf(stream, sizeof(stream), "%s - %s: %f\n", timeStr, getTag(), val);

    m_out->print(stream);
  }
}

void DbgTrace_Port::getTime(char* timeStr)
{
#ifdef ARDUINO
  sprintf(timeStr,"%ld", millis());
#else
  _strtime(timeStr);
#endif
}


