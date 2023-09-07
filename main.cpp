#include "ucp_sms_msg.hpp"

#include <iostream>

int main(int argc, char * argv[])
{
    if( argc != 4 ) {
        std::cout << "usage: " << argv[0] << "<sender number> <recipient number> <message>\n";
        return 0;
    }

    std::cout << ucp_sms_msg(argv[1],argv[2],argv[3]) << '\n';

    return 0;
}
