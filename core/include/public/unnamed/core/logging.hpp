#ifndef CORE_LOGGING_HPP_
#define CORE_LOGGING_HPP_

#pragma once

#include "config.h"

#include <spdlog/logger.h>

// Format String Syntax: https://fmt.dev/latest/syntax.html
#define SECTION_HEADER "=================================================="
#define SECTION_HEADER_NAMED "{:=^50}"
#define SECTION_SPLITTER "--------------------------------------------------"
#define SECTION_FOOTER "=================================================="

namespace CONFIG_NAMESPACE
{
    namespace logging
    {
        void init();
        void terminate();

        const std::shared_ptr<spdlog::logger>& logger() noexcept;
        const std::shared_ptr<spdlog::logger>& unformatted_logger() noexcept;
        const std::shared_ptr<spdlog::logger>& logger(const std::string name);

        void println();
        void print_args(const std::string name, const int argc, const char *argv[]);
    }
}

#endif /* CORE_LOGGING_HPP_ */
