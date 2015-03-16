/*
 * DbgTracePort.cpp
 *
 *  Created on: 16.03.2015
 *      Author: niklausd
 */

#include <DbgTracePort.h>

DbgTrace_Port::DbgTrace_Port()
: m_level(DbgTrace_Port::notice)
{ }

DbgTrace_Port::~DbgTrace_Port()
{ }

void DbgTrace_Port::setLevel(DbgTraceLevel level)
{
  m_level = level;
}

DbgTrace_Port::DbgTraceLevel DbgTrace_Port::getLevel()
{
  return m_level;
}
