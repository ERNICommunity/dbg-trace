/*
 * DbgTraceContext.h
 *
 *  Created on: 14.04.2015
 *      Author: aschoepfer
 */

#ifndef PLAT_DEBUG_TRACE_DBGTRACECONTEXT_H_
#define PLAT_DEBUG_TRACE_DBGTRACECONTEXT_H_

#include "DbgTracePort.h"
#include "DbgCliTopic.h"

class DbgTrace_Context
{
public:
  DbgTrace_Context(DbgCli_Topic* cliParentNode);

  virtual ~DbgTrace_Context() { }
  
  DbgTrace_Port* getTracePort(char* tag);
//  DbgTrace_Out* getTraceOut(char* tag);

  static void assignContext(DbgTrace_Context* context) { if(0 != context) s_context = context; }
  static DbgTrace_Context* getContext() { return s_context; }

private:
  static DbgTrace_Context* s_context;

  DbgCli_Topic* m_contextDbgTopic;
  DbgTrace_Port* m_firstPort;
//  DbgTrace_Out* m_firstOut;

private: // forbidden default functions
  DbgTrace_Context& operator = (const DbgTrace_Context& src); // assignment operator
  DbgTrace_Context(const DbgTrace_Context& src);              // copy constructor
  DbgTrace_Context();                                          // default constructor
};

#endif /* PLAT_DEBUG_TRACE_DBGTRACECONTEXT_H_ */
