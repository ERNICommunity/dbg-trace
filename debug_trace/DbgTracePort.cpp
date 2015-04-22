/*
 * DbgTracePort.cpp
 *
 *  Created on: 16.03.2015
 *      Author: niklausd
 */

#include "DbgTraceLevel.h"
#include "DbgTracePort.h"
#include <string.h>
#include <Arduino.h>

DbgTrace_Port::DbgTrace_Port(const char* tag)
: m_out(0)
, m_level(DbgTrace_Level::notice)
, m_nextPort(0)
, m_tag(tag)
{ }

DbgTrace_Port::DbgTrace_Port(const __FlashStringHelper* tag)
: m_out(0)
, m_level(DbgTrace_Level::notice)
, m_nextPort(0)
, m_tag(reinterpret_cast<const char*>(tag))
{ }

inline size_t DbgTrace_Port::write(const uint8_t *buffer, size_t size)
{
  size_t n = 0;
  n += Serial.print(millis());
  n += Serial.print(F(" - "));
  n += Serial.print(getTag());
  n += Serial.print(F(": "));
  while (size--)
  {
    n += Serial.write(*buffer++);
  }
  n += Serial.println();
  return n;
}

inline size_t DbgTrace_Port::write(uint8_t num)
{
  size_t n = 0;
  n += Serial.write(num);
  return n;
}
