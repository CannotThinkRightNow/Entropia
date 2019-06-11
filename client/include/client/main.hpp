#ifndef CLIENT_MAIN_HPP_
#define CLIENT_MAIN_HPP_

#pragma once

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>

boost::filesystem::path executable_path() noexcept;

#endif /* CLIENT_MAIN_HPP_ */
