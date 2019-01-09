#ifndef FILES_H_
#define FILES_H_

#pragma once

#include "config.h"
#include "utilities/singletons.h"

#include <string>

namespace io
{
#if WIDE_STRING
    using string = std::wstring;
#else /* WIDE_STRING */
    using string = std::string;
#endif

    class File
    {
    private:
        const string path;

    public:
        File(string path);
        virtual const string getPath();
    };

    template<class T>
    class SingletonFile : public File, public Singleton<T>
    {
    protected:
        SingletonFile<T>(string path);
    };
    
    // Files
    namespace files
    {
        class Pointer final : public SingletonFile<Pointer>
        {
            friend class Singleton<Pointer>;

        private:
            string dataPath;
            Pointer();

        public:
            const string getPath() override;
            const string getDataPath();
        };
    }
}

#endif /* FILES_H_ */
