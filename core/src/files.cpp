#include "config.h"
#include "utilities/types.h"
#include "utilities/logging.h"
#include "utilities/singletons.h"

#define FILES_ID "Files"

namespace io
{
    class File
    {
    public:
        const c_str path;
        File(c_str path) : path(path){}
    };

    template<class T>
    class SingletonFile : public Singleton<T>, public File
    {
    public:
        SingletonFile(c_str path) : File(path){}
    };

    // Files
    namespace files
    {
        class Pointer : public SingletonFile<Pointer>
        {
        };
    }
}
