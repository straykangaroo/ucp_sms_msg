#ifndef UCP_SMS_MSG
#define UCP_SMS_MSG

#include <string>


/**
    Build a UCP/EMI message string for sending a SMS from \p from to \p to
    @param  from    sender's phone number
    @param  to      recipient's phone number
    @param  message text message
    @return UCP/EMI message string
    @note   The Operation Type used is "01" ("Call input operation") and the hard-coded Transaction Reference Number is 1
    @see    https://www.vodafone.de/downloadarea/EmiSpec_44a.pdf
*/
std::string ucp_sms_msg(const std::string & from, const std::string & to, const std::string & msg);

#endif  // UCP_SMS_MSG
