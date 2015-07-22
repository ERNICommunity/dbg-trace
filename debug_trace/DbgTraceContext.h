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

/**
 * @brief The debug trace ports and outputs are assigned to a global trace context.
 * Normally there's no need for more than one context within a project. All ports and outputs of the context are accessible by single linked lists.
 * The ownership of the single linked lists is handled by the ports and outputs itself. The context has a pointer to the first port and output to be
 * able to iterate through the elements of the list.
 *
 * A debug trace context is has a debug CLI topic. All instantiated ports, attach they're own debug CLI commands to this topic. With the commands the user
 * is been able to edit the port settings at the runtime of the application.
 */
class DbgTrace_Context
{
public:

  /**
   * @brief Constructor of a debug trace context.
   * A pointer of the new instance is automatically assigned to the static trace context variable.
   * @param cliParentNode Pointer to a debug CLI topic for the context. To be able to add debug CLI commands for the ports of this trace context.
   */
  DbgTrace_Context(DbgCli_Topic* cliParentNode);

  /**
   * @brief Destructor of the debug trace context.
   */
  virtual ~DbgTrace_Context() { }
  
  /**
   * @brief Search the port with the given tag.
   * @param tag The tag to look for.
   * @return tracePort with the given tag, or 0 (nullptr) otherwise.
   */
  DbgTrace_Port* getTracePort(const char* tag);

  /**
   * @brief Add's a given port to the single linked list of ports. It's checked that there are not multiple ports
   * with the same tag in the list.
   * @param port The new port to add.
   */
  void addTracePort(DbgTrace_Port* port);

  /**
   * @brief Delete the port with the given tag.
   * @param tag The tag to delete.
   */
  void deleteTracePort(const char* tag);

  /**
   * @brief Search the port with the given name.
   * @param name The name to look for.
   * @return tracePort with the given tag, or 0 (nullptr) otherwise.
   */
  DbgTrace_Out* getTraceOut(const char* name);

  /**
   * @brief Return the first trace out, with this, its possible to iterate over all out's
   * with its getNext() methods.
   * @return first trace out, or 0 (nullptr) if no out exists.
   */
  DbgTrace_Out* getFirstTraceOut() { return m_firstOut; }

  /**
   * @brief Add's a given out to the single linked list of out's. It's checked that there are not multiple out's
   * with the same name in the list.
   * @param out The new out to add.
   */
  void addTraceOut(DbgTrace_Out* out);

  /**
   * @brief Delete the out with the given name.
   * @param name The name to delete.
   */
  void deleteTraceOut(const char* name);

  /**
   * @brief Get the global debug trace context.
   * @return Pointer to the global debug trace context instance.
   */
  static DbgTrace_Context* getContext() { return s_context; }

private:
  static DbgTrace_Context* s_context; /*!< Pointer to the global debug trace context. */
  DbgCli_Topic* m_contextDbgTopic;    /*!< Pointer to the debug CLI Topic of the trace context. */
  DbgTrace_Port* m_firstPort;         /*!< Pointer to first added trace port, enables to iterate with the context over all ports (stored in a single linked list). */
  DbgTrace_Out* m_firstOut;           /*!< Pointer to first added trace outputs, enables to iterate with the context over all outputs (stored in a single linked list). */

private: // forbidden default functions
  DbgTrace_Context& operator = (const DbgTrace_Context& src); // assignment operator
  DbgTrace_Context(const DbgTrace_Context& src);              // copy constructor
  DbgTrace_Context();                                         // default constructor
};

#endif /* PLAT_DEBUG_TRACE_DBGTRACECONTEXT_H_ */
