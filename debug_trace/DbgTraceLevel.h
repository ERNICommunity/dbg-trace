/*
 * DbgTraceLevels.h
 *
 *  Created on: 14.04.2015
 *      Author: aschoepfer
 */

#ifndef PLAT_DEBUG_TRACE_DBGTRACELEVEL_H_
#define PLAT_DEBUG_TRACE_DBGTRACELEVEL_H_

class DbgTrace_Level
{
public:

  typedef enum
  {
    none      = -1,
    emergency =  0,
    alert     =  1,
    critical  =  2,
    error     =  3,
    warning   =  4,
    notice    =  5,
    info      =  6,
    debug     =  7
  } Level;

  virtual ~DbgTrace_Level() { }

private:
  DbgTrace_Level() { }

  DbgTrace_Level& operator = (const DbgTrace_Level& src); // assignment operator
  DbgTrace_Level(const DbgTrace_Level& src);              // copy constructor
};


#endif /* PLAT_DEBUG_TRACE_DBGTRACELEVEL_H_ */
