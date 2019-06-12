#ifndef CLIENT_MAIN_HPP_
#define CLIENT_MAIN_HPP_

#pragma once

#include "config.h"

#include <boost/filesystem.hpp>

namespace CONFIG_NAMESPACE
{
    boost::filesystem::path executable_path() noexcept;
}

#endif /* CLIENT_MAIN_HPP_ */
