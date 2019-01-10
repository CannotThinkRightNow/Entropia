#ifndef LOGGING_H_
#define LOGGING_H_

#pragma once

#include <spdlog/logger.h>

#define SECTION_HEADER "=================================================="
#define SECTION_HEADER_NAMED "=========================%s========================="
#define SECTION_SPLITTER "--------------------------------------------------"
#define SECTION_FOOTER "=================================================="

namespace logging
{
    void init();
    void terminate();

    const std::shared_ptr<spdlog::logger>& getLogger();
    const std::shared_ptr<spdlog::logger>& getUnformattedLogger();
    const std::shared_ptr<spdlog::logger>& getLogger(std::string name);

    void println();
    void printArgs(std::string name, int argc, char** argv);
}

#endif /* LOGGING_H_ */
