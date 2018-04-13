/*
 * entry.cpp
 *
 *  Created for: GlobalLogic Bootcamp
 *       Author: vitalii.lysenko
 *
 * Entry class source.
 * You have to write an implementation of all member functions
 * except of encode(). It is already defined in encode.cpp and
 * provided to you as GCC static library.
 *
 * This source will be used when Jenkins builds the unit tests.
 *
 */

#include "entry.h"

/*
 * The main task is to puzzle out the encode() algorithm and to
 * write the decode() one.
 *
 * Good luck!
 *
 */
void Entry::encode()
{
	::encode( m_buf, m_size );
}

