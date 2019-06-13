// Modified from https://stackoverflow.com/a/1008289/9341868.

#ifndef CORE_SINGLETONS_H_
#define CORE_SINGLETONS_H_

#pragma once

#include "config.h"

namespace CONFIG_NAMESPACE
{
    template<class T>
    class singleton
    {
    protected:
        // Constructor.
        singleton<T>() {}

    public:
        static T& instance()
        {
            // Guaranteed to be destroyed.
            // Instantiated on first use.
            static T instance;
            return instance;
        }

        // C++ 11
        // =======
        // We can use the better technique of deleting the methods
        // we don't want.
        //
        // Note: Scott Meyers mentions in his Effective Modern
        //       C++ book, that deleted functions should generally
        //       be public as it results in better error messages
        //       due to the compilers behavior to check accessibility
        //       before deleted status.

        singleton<T>(const singleton<T>&) = delete;
        virtual void operator=(const singleton<T>&) = delete;
    };

    template<class T>
    class thread_local_singleton
    {
    protected:
        // Constructor.
        thread_local_singleton<T>() {}

    public:
        static T& instance()
        {
            // Guaranteed to be destroyed.
            // Instantiated on first use.
            thread_local T instance;
            return instance;
        }

        // C++ 11
        // =======
        // We can use the better technique of deleting the methods
        // we don't want.
        //
        // Note: Scott Meyers mentions in his Effective Modern
        //       C++ book, that deleted functions should generally
        //       be public as it results in better error messages
        //       due to the compilers behavior to check accessibility
        //       before deleted status.

        thread_local_singleton<T>(const thread_local_singleton<T>&) = delete;
        virtual void operator=(const thread_local_singleton<T>&) = delete;
    };
}

#endif /* CORE_SINGLETONS_H_ */
