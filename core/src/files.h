#ifndef FILES_H_
#define FILES_H_

#pragma once

#include "utilities/singletons.h"

#include <string>

namespace io
{
    class File
    {
    private:
        const std::string path;

    public:
        File(std::string path);
        virtual const std::string getPath();
    };

    template<class T>
    class SingletonFile : public File, public Singleton<T>
    {
    protected:
        SingletonFile<T>(std::string path);
    };
    
    // Files
    namespace files
    {
        class Pointer final : public SingletonFile<Pointer>
        {
            friend class Singleton<Pointer>;

        private:
            std::string dataPath;
            Pointer();

        public:
            const std::string getPath() override;
            const std::string getDataPath();
        };
    }
}

#endif /* FILES_H_ */
