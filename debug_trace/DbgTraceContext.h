/*
 * DbgTraceContext.h
 *
 *  Created on: 14.04.2015
 *      Author: aschoepfer
 */

#ifndef PLAT_DEBUG_TRACE_DBGTRACECONTEXT_H_
#define PLAT_DEBUG_TRACE_DBGTRACECONTEXT_H_

#include "DbgCliTopic.h"

class DbgTrace_Out;
class DbgTrace_Port;

class DbgTrace_Context
{
public:
  DbgTrace_Context(DbgCli_Topic* cliParentNode);

  virtual ~DbgTrace_Context() { }
  
  /**
   * Search the port with the given tag. If no such port exists, a new port with the searched tag will be created.
   * @param tag The tag to look for.
   * @return tracePort with the given tag, or a new created port with this tag.
   */
  DbgTrace_Port* getTracePort(char* tag);

  /**
   * Search the port with the given name.
   * @param name The name to look for.
   * @return tracePort with the given tag, or 0 (nullptr) otherwise.
   */
  DbgTrace_Out* getTraceOut(char* name);

  /**
   * Add's a given out to the single linked list of out's. It's checked that there are not multiple out's
   * with the same name in the list.
   * @param The new out to add.
   * @return true if out could be added to the list. False otherwise, e.g. there is already an out with same name.
   */
  bool addTraceOut(DbgTrace_Out* out);

  static void assignContext(DbgTrace_Context* context) { s_context = context; }
  static DbgTrace_Context* getContext() { return s_context; }

private:
  DbgTrace_Port* createTracePort(char* tag);

  static DbgTrace_Context* s_context;
  DbgCli_Topic* m_contextDbgTopic;
  DbgTrace_Port* m_firstPort;
  DbgTrace_Out* m_firstOut;

private: // forbidden default functions
  DbgTrace_Context& operator = (const DbgTrace_Context& src); // assignment operator
  DbgTrace_Context(const DbgTrace_Context& src);              // copy constructor
  DbgTrace_Context();                                         // default constructor
};

#endif /* PLAT_DEBUG_TRACE_DBGTRACECONTEXT_H_ */
