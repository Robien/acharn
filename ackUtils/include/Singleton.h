/*
 * Singleton.h
 *
 *  Created on: 19 juil. 2010
 *      Author: romain
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

template<typename T>
class Singleton
{
public:

    static inline bool isDefine()
    {
        return (s == 0);
    }

    static T* get()
    {
        if (isDefine())
        {
            s = new T;
        }
        return (static_cast<T*> (s));
    }
    static T* s;
protected:
    Singleton()
    {
    }
    virtual ~Singleton()
    {
    }

};

template<typename T>
T* Singleton<T>::s = 0;

#endif /* SINGLETON_H_ */
