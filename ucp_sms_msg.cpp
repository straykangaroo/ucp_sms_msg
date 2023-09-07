#include "ucp_sms_msg.hpp"

#include <cassert>
#include <iomanip>
#include <ios>
#include <numeric>
#include <sstream>


namespace {

/**
    Convert a std::size_t to a string, \p width wide, right-justified, padded with \p padding
    @param  value   value to stringify
    @param  width   resulting string length
    @param  padding char used for padding
    @return the string
*/
std::string to_string_padded(std::size_t value, std::size_t width, char padding)
{
    std::ostringstream buf;
    buf << std::setfill(padding) << std::right << std::setw(width) << value;
    return buf.str();
}

/**
    Calculate checksum (sum of all bytes, take the LSB) of a string
    @param  s   a string
    @return checksum of \p s
*/
unsigned char checksum(const std::string & s)
{
    return std::accumulate(s.begin(),s.end(),0) & 0xFF;         // sum all chars, take the LSB
}


/**
    Textual hex representation of an unsigned char (uppercase, two char long, zero-padded, right-justified)
    @param  c   an unsigned char
    @post   RESULT.length() == 2
    @return textual hex representation of \p c
*/
std::string to_hex(unsigned char c)
{
    std::ostringstream buf;

    buf << std::hex << std::uppercase << std::setfill('0') << std::right << std::setw(2) << static_cast<int>(c);

    assert( buf.str().length() == 2 );
    return buf.str();
}

/**
    Textual hex representation of a string (uppercase, each hex digit zero-padded, right-justified)
    @param  s   a string
    @post   RESULT.length() == s.length() * 2
    @return textual hex representation of \p s
*/
std::string to_hex(const std::string & s)
{
    std::ostringstream buf;

    buf << std::hex << std::uppercase << std::setfill('0') << std::right << std::setw(2);
    for( unsigned char c : s ) {
        buf << static_cast<int>(c);
    }

    assert( buf.str().length() == s.length() * 2 );
    return buf.str();
}

}   // namespace (anoymous)

std::string ucp_sms_msg(const std::string & from, const std::string & to, const std::string & msg)
{
    constexpr char stx = 0x02;
    constexpr char etx = 0x03;
    
    std::string header =    "01/"           /* Transaction Reference Number. Right-justified with a leading zero                */
                            "00000/"        /* Message length. 5 chars long, zero-padded, right-justified. Will be filled later */
                            "O/"            /* Transaction Indicator. 'O' means "operation" (vs 'R' meaning "result")           */
                            "01"            /* Operation Type. "01" is "Call input operation"                                   */
                            ;
                            
    std::string data =      to + '/' + from
                            + "//"          /* N_A (empty field, as per protocol)                                               */
                            "3/"            /* Message Type. '3' means "alphanumeric message"                                   */
                            + to_hex(msg);
                            
    std::string ucp = header + '/' + data + '/';
    
    ucp.replace( 3,     /* message length field starts at position 3 in ucp */
                 5,     /* message length field is 5 chars long             */
                 to_string_padded(  ucp.length(),
                                    5,  /* message length field is 5 chars long             */
                                    '0' /* message length field is zero-padded              */
                                 )
                );

    return stx + ucp + to_hex(checksum(ucp)) + etx;
}


