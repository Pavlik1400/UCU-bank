#include "service_tools/utils.hpp"
#include "auth/client.hpp"
#include "auth/constants.hpp"
#include <boost/program_options/parsers.hpp>
#include <stdexcept>
#include <vector>
#include <boost/program_options.hpp>
#include <ostream>

namespace po = boost::program_options;

enum rpc_funcs {
    tfa_pwd,
    tfa_otp,
    sess_info
};
inline std::string rpc_funcs_to_str(rpc_funcs f) noexcept(false)
{
    switch (f) {
        case tfa_pwd: return "tfa_pwd";
        case tfa_otp: return "tfa_otp";
        case sess_info: return "sess_info";
        default: throw std::runtime_error("wrong_type");
    }
}
std::istream& operator>> (std::istream &is, rpc_funcs &func) noexcept(false)
{
    std::string tk;
    is >> tk;

    if      (tk == rpc_funcs_to_str(tfa_pwd))   func = tfa_pwd;
    else if ( tk == rpc_funcs_to_str(tfa_otp))  func = tfa_otp;
    else if (tk == rpc_funcs_to_str(sess_info)) func = sess_info;
    else    throw po::validation_error(po::validation_error::invalid_option_value);
    return is;
};

int main(int argc, char * argv[]) {
    rpc_funcs func;
    auth::AuthDU adu;
    po::options_description des("Allowed options");
    po::positional_options_description pos;
    pos.add("func", 1)
        .add("cred", 1)
        .add("data", 1);    

    des.add_options()
        ("func", po::value(&func)->required())
        ("cred", po::value(&adu.cred)->required())
        ("data", po::value(&adu.data)->required())
    ;
    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(des).positional(pos).run(), vm);
    po::notify(vm);
    std::cout << "===REQUEST===\n" 
        "function: " << rpc_funcs_to_str(func) << "\n"
        "cred:     " << adu.cred << "\n"
        "data:     " << adu.data << std::endl;
    
    auto cnf = load_json_config("./configs/main.json");
    std::pair<auth::status, auth::AuthDU> rsp;
    auth::Client client{cnf};
    switch (func) {
    case tfa_pwd:
        rsp = client.tfa_pwd(adu);
        break;

    case tfa_otp:
        rsp = client.tfa_otp(adu);
        break;

    case sess_info:
        rsp = client.sess_info(adu);
        break;
    }

    auto & [status, payload] = rsp;

    std::cout << "===RESPONSE===\n" 
        "status: " << status << std::endl;
    if (status != auth::status::OK) return 0;

    std::cout << 
        "cred:   " << payload.cred << "\n"
        "data:   " << payload.data << std::endl;
    return 0;
}