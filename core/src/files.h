#ifndef FILES_H_
#define FILES_H_

#pragma once

#include "config.h"
#include "utilities/typedefs.h"
#include "utilities/singletons.h"

#define FILES_ID "Files"

namespace io
{
    class File
    {
    public:
        const c_str path;
        File(c_str path);
    };

    template<class T>
    class SingletonFile : public File, public Singleton<T>
    {
    public:
        SingletonFile<T>(c_str path);
    };

    // Files
    namespace files
    {
        class Pointer : public SingletonFile<Pointer>
        {
        private:
            c_str dataPath;
            Pointer();

        public:
            c_str getDataPath();
        };
    }
}

#endif /* FILES_H_ */
