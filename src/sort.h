/*
 * \file sort.h
 *
 * \brief The header file is included into the main test source file and available for editing by testee.
 *
 * \author Ihor Dutchak (ihor.dutchak@globallogic.com) and Vitalii Lysenko (vitalii.lysenko@globallogic.com)
 *
 * Add necessary declarations and definitions to this header file to solve the test problems.
 *
 *
 * Copyright © 2017 by GlobaLogic. All rights reserved.
 *
 */
#ifndef SORT_H
#define SORT_H

#include "sort_definitions.h"

/*
 * \fn <document the signature of lessByTask() here>
 *
 * \brief The function to compare two Package objects by special criteria.
 *
 * The objects should be compared by volumes if both weights are greater than 3. In other cases
 * the objects should be compared by weights.
 *
 */
bool lessByTask(const Package &i, const Package &j) 
{
	if ((i.weight > 3) && (j.weight > 3)) {
		return i.volume() < j.volume();
	}
	return i.weight < j.weight;
}
#endif // SORT_H
