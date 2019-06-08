#ifndef IO_H_
#define IO_H_

#pragma once

#include "core/config.h"

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>

namespace io
{
    namespace files
    {
        typedef boost::filesystem::path path;
        
        const path getPointerPath();
    }
}

#endif /* IO_H_ */
