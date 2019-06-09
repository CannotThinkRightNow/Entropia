#include "core/config.h"
#include "core/utilities/logging.hpp"

#include <sstream>
#include <map>
#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#if CONFIG_PLATFORM_ANDROID
#include <spdlog/sinks/android_sink.h>
#else /* CONFIG_PLATFORM_ANDROID */
#include <spdlog/sinks/stdout_color_sinks.h>
#endif
#include <boost/filesystem.hpp>

using boost::filesystem::path;

namespace logging
{
    std::shared_ptr<spdlog::logger> logger;
    std::shared_ptr<spdlog::logger> unformatted;
    std::map<const std::string, std::shared_ptr<spdlog::logger>> map;
    path log_directory;

    void init()
    {
        spdlog::init_thread_pool(8192, 1);
#if CONFIG_PLATFORM_ANDROID
        const auto log_sink = std::make_shared<spdlog::sinks::android_sink>();
#else /* CONFIG_PLATFORM_ANDROID */
        const auto log_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
#endif
        const auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>();
        const std::vector<spdlog::sink_ptr> sinks { log_sink, file_sink };
        logger = std::make_shared<spdlog::async_logger>("logger", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
        spdlog::register_logger(logger);
        unformatted = getLogger("raw");
        unformatted->set_pattern("%v");
    }

    void terminate() { spdlog::shutdown(); }

    const std::shared_ptr<spdlog::logger>& getLogger() { return logger; }

    const std::shared_ptr<spdlog::logger>& getUnformattedLogger() { return unformatted; }

    const std::shared_ptr<spdlog::logger>& getLogger(const std::string name)
    {
        if (map.count(name) == 0) // Logger not found.
            map[name] = logger->clone(name);
        return map[name];
    }

    void println() { unformatted->log(unformatted->default_level(), ""); }

    void printArgs(const std::string name, const int argc, const char *argv[])
    {
        const auto logger = getLogger(name);
        logger->info(SECTION_HEADER_NAMED, "Arguments");
        logger->info("Arguments Count: %i", argc);
        std::ostringstream oss;
        oss << "Arguments:";
        for (int i = 0; i < argc; i++)
            oss << " " << argv[i];
        logger->info(oss.str());
        logger->info(SECTION_FOOTER);
    }
}
