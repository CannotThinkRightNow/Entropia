#ifndef IO_HPP_
#define IO_HPP_

#pragma once

#include <string>
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>

namespace io
{
    using boost::filesystem::path;

    void init();

    bool read(const path file, std::string &out, const bool failfast, const std::iostream::openmode mode);
    bool write(const path file, const std::string content, const bool failfast, const std::iostream::openmode mode);

    namespace files
    {
        const path getPointerPath();
        const path getDataPath();
        const path getDefaultDataPath();

        namespace details
        {
            const path getPointerPath();
            const path getDefaultDataPath();
        }
    }
}

#endif /* IO_HPP_ */
