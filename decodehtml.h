#ifndef DECODEHTML_H
#define DECODEHTML_H

#include <string>
#include <map>

using AddonMap = std::map<uint, std::string>;
class DecodeHTML {
      public:
	AddonMap fromHtml(const std::string& html);
};

#endif // DECODEHTML_H
