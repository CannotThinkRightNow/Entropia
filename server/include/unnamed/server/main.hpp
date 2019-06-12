#ifndef SERVER_MAIN_HPP_
#define SERVER_MAIN_HPP_

#pragma once

#include "config.h"

#include <boost/filesystem.hpp>

namespace CONFIG_NAMESPACE
{
    boost::filesystem::path executable_path() noexcept;
}

#endif /* SERVER_MAIN_HPP_ */
