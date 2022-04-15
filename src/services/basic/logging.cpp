#include "basic/logging.hpp"

void logger::my_color_formatter(logging::record_view const& record, logging::formatting_ostream& stream)
{
    auto severity = record[logging::trivial::severity];

    switch (severity.get())
    {
        case logging::trivial::severity_level::trace:
            stream << "\e[97m";
            break;
        case logging::trivial::severity_level::debug:
            stream << "\e[34m";
            break;
        case logging::trivial::severity_level::info:
            stream << "\e[32m";
            break;
        case logging::trivial::severity_level::warning:
            stream << "\e[93m";
            break;
        case logging::trivial::severity_level::error:
            stream << "\e[91m";
            break;
        case logging::trivial::severity_level::fatal:
            stream << "\e[41m";
            break;
    }

    auto filename_ref = boost::log::extract<std::string>("File", record);
    auto line_ref = boost::log::extract<int>("Line", record);

    stream << "\e[1m";

    typedef boost::log::formatter formatter;
    formatter f = expr::stream << expr::format_date_time<boost::posix_time::ptime>(
            "TimeStamp", "%d.%m.%Y %H:%M:%S.%f");
    f(record, stream);

    stream
            << "  [" << std::left << std::setw(7) << std::setfill(' ') << severity << "]"
            << "  [" << std::right << std::setw(10) << std::setfill(' ') << filename_ref << ":"
            << std::left << std::setw(4) << std::setfill(' ') << line_ref << "]\t"
            << record[logging::expressions::smessage]
            << "\e[0m";
}

void logger::my_file_formatter(logging::record_view const& record, logging::formatting_ostream& stream)
{
    auto severity = record[logging::trivial::severity];

    auto filename_ref = boost::log::extract<std::string>("File", record);
    auto line_ref = boost::log::extract<int>("Line", record);

    typedef boost::log::formatter formatter;
    formatter f = expr::stream << expr::format_date_time<boost::posix_time::ptime>(
            "TimeStamp", "%d.%m.%Y %H:%M:%S.%f");
    f(record, stream);

    stream
            << "  [" << std::left << std::setw(7) << std::setfill(' ') << severity << "]"
            << "  [" << std::right << std::setw(10) << std::setfill(' ') << filename_ref << ":"
            << std::left << std::setw(4) << std::setfill(' ') << line_ref << "]\t"
            << record[logging::expressions::smessage];
}


void logger::init() {
    logging::core::get()->add_thread_attribute("File", attrs::mutable_constant<std::string>(""));
    logging::core::get()->add_thread_attribute("Line", attrs::mutable_constant<int>(0));

    typedef sinks::synchronous_sink< sinks::text_ostream_backend > text_sink;

    boost::shared_ptr< text_sink > sink = boost::make_shared< text_sink >();
    boost::shared_ptr<std::ostream> stream(&std::cout, boost::null_deleter{});
    sink->locked_backend()->add_stream(stream);
    sink->set_formatter(&my_color_formatter);
    sink->locked_backend()->auto_flush(true);

    boost::shared_ptr< text_sink > file_sink = boost::make_shared< text_sink >();
    file_sink->locked_backend()->add_stream(boost::make_shared< std::ofstream >("logs.log", std::ios_base::app));
    file_sink->set_formatter(&my_file_formatter);
    file_sink->locked_backend()->auto_flush(true);

    logging::core::get()->add_sink(sink);
    logging::core::get()->add_sink(file_sink);
    logging::add_common_attributes();

}
