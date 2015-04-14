/*
 * DbgTraceContext.h
 *
 *  Created on: 14.04.2015
 *      Author: aschoepfer
 */

#ifndef PLAT_DEBUG_TRACE_DBGTRACECONTEXT_H_
#define PLAT_DEBUG_TRACE_DBGTRACECONTEXT_H_

class DbgTraceContext
{
private:
  DbgTraceContext() { }

public:
  static DbgTraceContext* instance();

  virtual ~DbgTraceContext() { }
  

private:
  static DbgTraceContext* s_instance;


private:


private: // forbidden default functions
  DbgTraceContext& operator = (const DbgTraceContext& src); // assignment operator
  DbgTraceContext(const DbgTraceContext& src);              // copy constructor
};

#endif /* PLAT_DEBUG_TRACE_DBGTRACECONTEXT_H_ */
