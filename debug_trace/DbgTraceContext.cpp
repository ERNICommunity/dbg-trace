/*
 * DbgTraceContext.cpp
 *
 *  Created on: 14.04.2015
 *      Author: aschoepfer
 */

#include "DbgTraceContext.h"

DbgTraceContext* DbgTraceContext::s_instance = 0;


DbgTraceContext* DbgTraceContext::instance()
{
  if (0 == s_instance)
  {
    s_instance = new DbgTraceContext();
  }
  return s_instance;
}
