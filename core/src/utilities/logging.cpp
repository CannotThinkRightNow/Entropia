#include "config.h"
#include STR(CONFIG_NAMESPACE/core/utilities/logging.hpp)

#include <sstream>

#include <initializer_list>
#include <map>

#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#ifdef CONFIG_PLATFORM_ANDROID
#include <spdlog/sinks/android_sink.h>
#else /* CONFIG_PLATFORM_ANDROID */
#include <spdlog/sinks/stdout_color_sinks.h>
#endif

#include <boost/filesystem.hpp>
#include STR(CONFIG_NAMESPACE/core/utilities/io.hpp)

using namespace CONFIG_NAMESPACE;
using boost::filesystem::path;

namespace CONFIG_NAMESPACE
{
    namespace logging
    {
        std::shared_ptr<spdlog::logger> logger_;
        std::shared_ptr<spdlog::logger> unformatted;
        std::map<const std::string, std::shared_ptr<spdlog::logger>> map;
        path log_directory;

        void init()
        {
            log_directory = io::files::data_path();
            spdlog::init_thread_pool(8192, 1);

#ifdef CONFIG_PLATFORM_ANDROID
            const auto log_sink = std::make_shared<spdlog::sinks::android_sink>();
#else /* CONFIG_PLATFORM_ANDROID */
            const auto log_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
#endif
            const auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>((log_directory / "log.log").string());
            logger_ = std::make_shared<spdlog::async_logger>("default", std::initializer_list<spdlog::sink_ptr> { log_sink, file_sink }, spdlog::thread_pool());
            spdlog::register_logger(logger_);
            unformatted = logger("raw");
            unformatted->set_pattern("%v");
        }

        void terminate() { spdlog::shutdown(); }

        const std::shared_ptr<spdlog::logger>& logger() noexcept { return logger_; }

        const std::shared_ptr<spdlog::logger>& unformatted_logger() noexcept { return unformatted; }

        const std::shared_ptr<spdlog::logger>& logger(const std::string name)
        {
            if (map.count(name) == 0) // Logger not found.
                map[name] = logger_->clone(name);
            return map[name];
        }

        void println() { unformatted->log(unformatted->default_level(), ""); }

        void print_args(const std::string name, const int argc, const char *argv[])
        {
            const auto logger_ = logger(name);
            logger_->info(SECTION_HEADER_NAMED, "Arguments");
            logger_->info("Arguments Count: {:d}", argc);
            std::ostringstream oss;
            oss << "Arguments:";
            for (int i = 0; i < argc; i++)
                oss << " " << argv[i];
            logger_->info(oss.str());
            logger_->info(SECTION_FOOTER);
        }
    }
}
