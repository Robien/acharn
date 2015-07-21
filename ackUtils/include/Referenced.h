/*
 * Referenced.h
 *
 *  Created on: 4 sept. 2010
 *      Author: romain
 */

#ifndef REFERENCED_H_
#define REFERENCED_H_

#include <boost/intrusive_ptr.hpp>

class Referenced
{
public:
    Referenced();
    virtual ~Referenced();
    friend void intrusive_ptr_add_ref(Referenced* p)
    {
        ++p->references;
    }
    friend void intrusive_ptr_release(Referenced* p)
    {
        if (--p->references == 0)
            delete p;
    }
    inline unsigned int getNombreReference()
    {
        return references;
    }
    inline bool exist()
    {
        return references > 0;
    }
    inline bool isUndefined()
    {
        return references == 0;
    }

protected:
    Referenced& operator=(const Referenced&)
    {
        return *this;
    }
private:
    Referenced(const Referenced& other);

private:
    unsigned int references;
};

#endif /* REFERENCED_H_ */
