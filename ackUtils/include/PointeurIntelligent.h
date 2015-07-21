/*
 * PointeurIntelligent.h
 *
 *  Created on: 4 sept. 2010
 *      Author: romain
 */

#ifndef POINTEURINTELLIGENT_H_
#define POINTEURINTELLIGENT_H_

#include <boost/intrusive_ptr.hpp>
template<class T>
class PointeurIntelligent: public boost::intrusive_ptr<T>
{
public:
    PointeurIntelligent()
    {
    }
    PointeurIntelligent(T* t)
    {
        reset(t);
    }
    virtual ~PointeurIntelligent()
    {
    }
    void operator=(T* p)
    {
        reset(p);
    }
    operator T*()
    {
        return this->get();
    }
};

#endif /* POINTEURINTELLIGENT_H_ */
