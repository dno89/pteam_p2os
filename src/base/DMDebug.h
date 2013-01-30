/**
 * \file DMDebug.h
 * \author Daniele Molinari (daniele.molinari2@studenti.unipr.it)
 * \version 1.1
 */

/*
 *  Some useful debug macro
 *  Copyright (C) 2011  <copyright holder> <email>
 * 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef	_DMDEBUG_H
#define	_DMDEBUG_H

#include <fstream>

/*
 * 	CREATE OR IMPORT THE DEBUG FILE
 */

#define CREATE_PRIVATE_DEBUG_LOG(FNAME)\
static std::ofstream dm_log(FNAME, std::ios_base::trunc);

#define CREATE_GLOBAL_DEBUG_LOG(FNAME)\
std::ofstream dm_log(FNAME, std::ios_base::trunc);

#define IMPORT_GLOBAL_DEBUG_LOG()\
extern std::ofstream dm_log;

#define ACCESS_DEBUG_LOG() dm_log

#ifndef NDEBUG

/**
 * \brief Print a message
 */
#define DEBUG_P(X, CONTEXT)\
dm_log << #CONTEXT" -->\t" <<\
X << std::endl;

/**
 * \brief Print a message with no context
 */
#define DEBUG_PNC(X)\
dm_log <<\
X << std::endl;

/**
 * \brief trace a value
 */
#define DEBUG_T(X, CONTEXT)\
dm_log << #CONTEXT" -->\t" <<\
#X << " = " << (X) << std::endl;

/**
 * \brief trace a value with no context
 */
#define DEBUG_TNC(X)\
dm_log <<\
#X << " = " << (X) << std::endl;


/**
 * \brief trace a value in hexadecimal
 */
#define DEBUG_HT(X, CONTEXT)\
dm_log << #CONTEXT" -->\t" <<\
#X << " = " << std::hex << (X) << std::dec << std::endl;

/**
 * \brief trace a value with a newline before the value itself
 */
#define DEBUG_TL(X, CONTEXT)\
dm_log << #CONTEXT" -->\t" <<\
#X << " = \n" << (X) << std::endl;

/**
 * \brief trace a value with the capability to concatenate several expression
 */
#define DEBUG_TCAT(X, CONTEXT)\
dm_log << #CONTEXT" -->\t" <<\
#X << " = \n" << X << std::endl;

/**
 * \brief trace a value and preserve the X action with no debug info
 */
#define DEBUG_TPRESERVE(X, CONTEXT)\
dm_log << #CONTEXT" -->\t" <<\
#X << " = " << (X) << std::endl;

#else
//no debug info, let the user know!
#warning "NO DEBUG INFO!!!!"
#define DEBUG_T(X, CONTEXT)
#define DEBUG_TNC(X)
#define DEBUG_HT(X, CONTEXT)
#define DEBUG_TL(X, CONTEXT)
#define DEBUG_P(X, CONTEXT)
#define DEBUG_PNC(X)
#define DEBUG_TCAT(X, CONTEXT)
#define DEBUG_TPRESERVE(X, CONTEXT) X;
#endif  //NDEBUG

#endif	//_DMDEBUG_H


/*		USE EXAMPLE			*/
/**
 * @note the macro are active ONLY if NDEBUG is not defined! If this flag is defined the macro is replaced with an EMPTY STRING
 * @note if you want to disable the printing but preserve the argument evaluation (for example a function call) use DEBUG_TPRESERVE
 * 
 * somewhere in a .cpp file (creation must be done ONLY ONCE for each different object)
 * @code
 * //create a debug log at /tmp/debug.log
 * CREATE_DEBUG_LOG("/tmp/debug.log",)
 * 
 * //create another debug log, we must specify a different stream object:
 * CREATE_DEBUG_LOG("/tmp/another_debug.log", another_file)
 * @endcode
 * 
 * somewhere else
 * @code
 * //import the first debug file
 * IMPORT_DEBUG_LOG()
 * //import the second debug file
 * IMPORT_DEBUG_LOG(another_file)
 * @endcode
 * 
 * actual usage example
 * @code
 * Var myVar = 10;
 * //trace the value of myVar, in the context "MyClass::MyFunction"
 * DEBUG_T(myVar, MyClass::MyFunction) //MyClass::MyFunction	-->	myVar = 10
 * 
 * //print the message "hello" in context "main"
 * DEBUG_P("hello", main)	//main	-->	hello
 * 
 * //DEBUG_P allow for concatenation
 * int i = 15;
 * DEBUG_P("reached iteration " << i, MyClass::MyFunction)		//MyClass::MyFunction	-->	reached iteration 15
 * //DEBUG_TCAT allow for concatenation in trace... useless?
 * 
 * //if you don't want the context use DEBUG_*NC
 * //there are version to print hexadecimal values and to put a new line before the value
 * @endcode
 */