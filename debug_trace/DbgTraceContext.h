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
   * Search the port with the given tag.
   * @param tag The tag to look for.
   * @return tracePort with the given tag, or 0 (nullptr) otherwise.
   */
  DbgTrace_Port* getTracePort(const char* tag);

  /**
   * Add's a given port to the single linked list of ports. It's checked that there are not multiple ports
   * with the same tag in the list.
   * @param The new port to add.
   */
  void addTracePort(DbgTrace_Port* port);

  /**
   * Delete the port with the given tag.
   * @param tag The tag to delete.
   */
  void deleteTracePort(const char* tag);

  /**
   * Search the port with the given name.
   * @param name The name to look for.
   * @return tracePort with the given tag, or 0 (nullptr) otherwise.
   */
  DbgTrace_Out* getTraceOut(const char* name);

  /**
     * Return the first trace out, with this, its possible to iterate over all out's
     * with its getnext() methods.
     * @return first trace out, or 0 (nullptr) if no out exists.
     */
  DbgTrace_Out* getFirstTraceOut() { return m_firstOut; }

  /**
   * Add's a given out to the single linked list of out's. It's checked that there are not multiple out's
   * with the same name in the list.
   * @param The new out to add.
   */
  void addTraceOut(DbgTrace_Out* out);

  /**
   * Delete the out with the given name.
   * @param name The name to delete.
   */
  void deleteTraceOut(const char* name);

  static void assignContext(DbgTrace_Context* context) { s_context = context; }
  static DbgTrace_Context* getContext() { return s_context; }

private:
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
