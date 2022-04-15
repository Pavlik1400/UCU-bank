#include "service_tools/utils.hpp"
#include "client.hpp"
#include <iostream>

    
int main(void)
{
    auto cnf = load_json_config("./configs/main.json");
    auth::Client client{cnf};
    client.log1("M", "X", "L");
    client.log1("Makkusu Shiroi", "+380(xx)xxxxx", "0000");
    return 0; 
}