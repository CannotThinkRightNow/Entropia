#ifndef CORE_IO_HPP_
#define CORE_IO_HPP_

#pragma once

#include "core/utilities/id.h"

#include <string>

#include <boost/filesystem.hpp>

namespace io
{
    using boost::filesystem::path;

    void init();

    bool read(const path file, std::string &out, const bool failfast, const std::iostream::openmode mode);
    bool write(const path file, const std::string content, const bool failfast, const std::iostream::openmode mode);

    namespace files
    {
        path executable_path() noexcept;
        path pointer_path();
        path data_path();
        path default_data_path();

        namespace details
        {
            typedef path (*executable_path_func_t)();

            void set_executable_path_func(executable_path_func_t func);

            path pointer_path();
            path default_data_path();
        }
    }
}

#endif /* CORE_IO_HPP_ */
