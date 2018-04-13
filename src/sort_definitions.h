/*
 * \file sort_definitions.h
 *
 * \brief The header file is included into the main test source file and write protected from editing by testee.
 *
 * \author Ihor Dutchak (ihor.dutchak@globallogic.com) and Vitalii Lysenko (vitalii.lysenko@globallogic.com)
 *
 * Do not change the content of this file, it will be restored by Jenkins CI.
 *
 *
 * Copyright © 2017 by GlobaLogic. All rights reserved.
 *
 */
#ifndef SORT_DEFINITIONS_H
#define SORT_DEFINITIONS_H

#include <string>

struct BoxDimensions
{
    double width;
    double height;
    double length;

    bool operator ==(const BoxDimensions &r) const
    {
        return width == r.width && height == r.height && length == r.length;
    }
};

struct Package
{
    std::string name;
    BoxDimensions dimensions;

    /*
    * \fn double volume() const
    *
    * \brief The member function to calculate the volume from the dimensions.
    *
    */
    double volume() const;

    double weight;
};

inline bool operator ==(const Package &l, const Package &r)
{
    return l.name == r.name && l.dimensions == r.dimensions && l.weight == r.weight;
}

/*
 * \fn template<typename T> inline void mySortContainer(T &container)
 *
 * \brief The function to sort descending an arbitrary container.
 *
 */
template<typename T>
inline void mySortContainer(T &container);


#endif // SORT_DEFINITIONS_H
