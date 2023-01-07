#ifndef BOOSTJSON_H
#define BOOSTJSON_H

#include <boost/json.hpp>

void        pretty_print(std::string& res, boost::json::value const& jv, std::string* indent = nullptr);
std::string pretty_print(boost::json::value const& jv);

#endif // BOOSTJSON_H
