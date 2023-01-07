#ifndef INSTALLADDON_H
#define INSTALLADDON_H

#include "decodehtml.h"
#include <string>

void installAddon(uint id, std::string name);
void installAddon(const AddonMap& addonToInstall);

#endif // INSTALLADDON_H
