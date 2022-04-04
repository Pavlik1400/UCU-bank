#ifndef UCU_BANK_LOGGING_H
#define UCU_BANK_LOGGING_H

#include <iostream>
#include <fstream>

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
#include <boost/log/expressions/keyword_fwd.hpp>
#include <boost/log/expressions/keyword.hpp>

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace expr = boost::log::expressions;
namespace src = boost::log::sources;
namespace keywords = boost::log::keywords;
namespace sinks = boost::log::sinks;

#define CUSTOM_LOG(logger, sev) \
   BOOST_LOG_STREAM_WITH_PARAMS( \
      (logger), \
         (set_get_attrib("File", path_to_filename(__FILE__))) \
         (set_get_attrib("Line", __LINE__)) \
         (::boost::log::keywords::severity = (boost::log::trivial::sev)) \
   )

template<typename ValueType>
ValueType set_get_attrib(const char* name, ValueType value) {
    auto attr = logging::attribute_cast<attrs::mutable_constant<ValueType>>(logging::core::get()->get_thread_attributes()[name]);
    attr.set(value);
    return attr.get();
}

inline std::string path_to_filename(std::string path) {return path.substr(path.find_last_of("/\\")+1);}

namespace logger {

    void my_color_formatter(logging::record_view const& record, logging::formatting_ostream& stream);

    void my_file_formatter(logging::record_view const& record, logging::formatting_ostream& stream);

    void init();

}

#endif //UCU_BANK_LOGGING_H
