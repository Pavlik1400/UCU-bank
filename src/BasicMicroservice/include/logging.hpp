#ifndef UCU_BANK_LOGGING_H
#define UCU_BANK_LOGGING_H

#include <iostream>

#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/sinks/basic_sink_backend.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/core/null_deleter.hpp>

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace expr = boost::log::expressions;
namespace src = boost::log::sources;
namespace keywords = boost::log::keywords;
namespace sinks = boost::log::sinks;

#define LOG_ADD_FILE boost::log::attribute_cast<boost::log::attributes::mutable_constant<std::string>>(::boost::log::trivial::logger::get().get_attributes()["File"]).set(logger::path_to_filename(__FILE__))
#define LOG_ADD_LINE boost::log::attribute_cast<boost::log::attributes::mutable_constant<int>>(::boost::log::trivial::logger::get().get_attributes()["Line"]).set(__LINE__)

#define LOG(sev) \
   LOG_ADD_FILE;\
   LOG_ADD_LINE;\
   BOOST_LOG_STREAM_WITH_PARAMS(::boost::log::trivial::logger::get(), (::boost::log::keywords::severity = ::boost::log::trivial::sev))

#define MLOG_TRACE std::cout << logger::color(97); LOG(trace)
#define MLOG_DEBUG std::cout << logger::color(34); LOG(debug)
#define MLOG_INFO std::cout << logger::color(32); LOG(info)
#define MLOG_WARNING std::cout << logger::color(93); LOG(warning)
#define MLOG_ERROR std::cout << logger::color(91); LOG(error)
#define MLOG_FATAL std::cout << logger::color(41); LOG(fatal)


namespace logger {

    inline std::string color(uint16_t color) { return "\033[" + std::to_string(color) + "m"; }

    inline std::string path_to_filename(const std::string &path) { return path.substr(path.find_last_of("/\\") + 1); }

    inline void init() {

        boost::log::trivial::logger::get().add_attribute("File", attrs::mutable_constant<std::string>(""));
        boost::log::trivial::logger::get().add_attribute("Line", attrs::mutable_constant<int>(0));

        logging::add_console_log(std::cout,
                                 keywords::format = (
                                         expr::stream
                                                 << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "[%Y-%m-%d %H:%M:%S]")
                                                 << "  [" << std::left << std::setw(7) << std::setfill(' ') << boost::log::trivial::severity << "]"
                                                 << "  [" << std::right << std::setw(10) << std::setfill(' ') << expr::attr<std::string>("File")
                                                 << ":" << std::left << std::setw(4) << std::setfill(' ') << expr::attr<int>("Line") << "]\t"
                                                 << expr::smessage << logger::color(0)
                                 )
        );

        logging::add_common_attributes();
    }


}

#endif //UCU_BANK_LOGGING_H
