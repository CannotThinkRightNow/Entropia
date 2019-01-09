#include "files.h"

#define FILES_ID "Files"

namespace io
{
    File::File(c_str path) : path(path) {}

    template<class T>
    SingletonFile<T>::SingletonFile(c_str path) : io::File(path) {}

    namespace files
    {
        Pointer::Pointer() : SingletonFile<Pointer>("") {}
        c_str Pointer::getDataPath()
        {
            return dataPath;
        }
    }
}
