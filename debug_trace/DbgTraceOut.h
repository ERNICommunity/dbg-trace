/*
 * DbgTraceOut.h
 *
 *  Created on: 20.04.2015
 *      Author: aschoepfer
 */

#ifndef PLAT_DEBUG_TRACE_DBGTRACEOUT_H_
#define PLAT_DEBUG_TRACE_DBGTRACEOUT_H_

class DbgTrace_Context;
class IDbgPrint;

/**
 * @brief Instance of a trace output, print trace messages by calling a DbgPrint writer instance (e.g. console or file print).
 *
 * The trace output is assigned to a global trace context automatically.
 */
class DbgTrace_Out
{
public:

  /**
   * @brief Constructor to create a new output instance. The output will be automatically assigned to the mentioned debug trace context.
   * @param context Pointer to the global debug trace context.
   * @param name The name of the output, which should be unique and and not longer than the specified max size. The output can afterwards be globally
   * accessed by its content and name.
   * @param dbgPrint Pointer to a print writer instance.
   */
  DbgTrace_Out(DbgTrace_Context* context, const char* name, IDbgPrint* dbgPrint);

  /**
   * @brief Destructor of a trace output instance.
   */
  virtual ~DbgTrace_Out();

  /**
   * @brief Get the next output instance. All outputs in a context are stored with a single linked list.
   * @return Next output or 0 (nullptr) if there is no further output.
   */
  DbgTrace_Out* getNextOut() { return m_nextOut; }

  /**
   * * @brief Set the next output. All outputs of a context are stored with a single linked list.
   * The outputs are added automatically by its creation from the context.
   * @param nextOut Pointer to the next output.
   */
  void setNextOut(DbgTrace_Out* nextOut) { if(0 != nextOut) m_nextOut = nextOut; }

  /**
    * @brief Get the name of the output instance.
    * @return Name string of this output.
    */
  const char* getName() { return m_name; }

  /**
   * @brief Prints a trace message, by calling its dbgPrint instance.
   * @param str Const char message to be printed out.
   */
  void print(const char* str);

  static const unsigned int s_cMaxOutNameLength = 16; /*!< Max. number of characters for a output name. */

private:
  const char* m_name; /*!< Name of this output. Must be unique within the trace context. Name length should not exceed s_cMaxOutNameLength. */
  DbgTrace_Out* m_nextOut; /*!< Pointer to next output. The context can iterate through this single linked list. */
  IDbgPrint* m_dbgPrint; /*!< The print instance, this abstraction improves the testability of the trace output. */

private: // forbidden default functions
  DbgTrace_Out& operator = (const DbgTrace_Out& src); // assignment operator
  DbgTrace_Out(const DbgTrace_Out& src);              // copy constructor
  DbgTrace_Out();
};

#endif /* PLAT_DEBUG_TRACE_DBGTRACEOUT_H_ */
