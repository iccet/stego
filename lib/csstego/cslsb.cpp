#include "cslsb.hpp"

bool Encode(const char *data, char *container, int64_t size)
{
    BOOST_LOG_TRIVIAL(debug) << data << container << size;
    return true;
}

const char *Decode(char *container, int64_t size)
{
    BOOST_LOG_TRIVIAL(debug) << size << container;
    return "test";
}
