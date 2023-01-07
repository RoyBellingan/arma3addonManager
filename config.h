#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include "decodehtml.h"


void decodeJson(const std::string& raw);

void updateJson(unsigned int id, const std::string& name);

AddonMap extractAddonFromJson();

#endif // CONFIG_H
