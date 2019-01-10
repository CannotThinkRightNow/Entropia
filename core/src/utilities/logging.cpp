#include "logging.h"
#include "config.h"

#include <sstream>
#include <map>
#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#if PLATFORM_ANDROID
#include <spdlog/sinks/android_sink.h>
#else /* PLATFORM_ANDROID */
#include <spdlog/sinks/stdout_color_sinks.h>
#endif

namespace logging
{
    std::shared_ptr<spdlog::logger> logger = nullptr;
    std::shared_ptr<spdlog::logger> unformatted = nullptr;
    std::map<std::string, std::shared_ptr<spdlog::logger>> map;

    void init()
    {
        spdlog::init_thread_pool(8192, 1);
#if PLATFORM_ANDROID
        auto log_sink = std::make_shared<spdlog::sinks::android_logger>();
#else /* PLATFORM_ANDROID */
        auto log_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
#endif
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("");
        std::vector<spdlog::sink_ptr> sinks { log_sink, file_sink };
        logger = std::make_shared<spdlog::async_logger>("logger", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
        spdlog::register_logger(logger);
        unformatted = getLogger("raw");
        unformatted->set_pattern("%v");
    }

    void terminate()
    {
        spdlog::shutdown();
    }

    const std::shared_ptr<spdlog::logger>& getLogger()
    {
        return logger;
    }

    const std::shared_ptr<spdlog::logger>& getUnformattedLogger()
    {
        return unformatted;
    }

    const std::shared_ptr<spdlog::logger>& getLogger(std::string name)
    {
        if (map.count(name) == 0) // Create new logger
            map[name] = logger->clone(name);
        return map[name];
    }

    void println()
    {
        unformatted->critical("");
    }

    void printArgs(std::string name, int argc, char** argv)
    {
        auto logger = getLogger(name);
        logger->info(SECTION_HEADER_NAMED, "Arguments");
        logger->info("Arguments Count: %i", argc);
        std::ostringstream oss;
        oss << "Arguments:";
        for (int i = 0; i < argc; i++)
            oss << " " << argv[argc];
        logger->info(oss.str());
        logger->info(SECTION_FOOTER);
    }
}
