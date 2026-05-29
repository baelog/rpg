#ifndef TYPES_HPP
#define TYPES_HPP

#include <unordered_map>
#include <stdint.h>

#define MAX_ENTITIES 20 //TODO later

#define ComponantValue uint32_t
#define Entity uint32_t
#define ComponentSignature uint32_t


typedef std::unordered_map<ComponentSignature, bool> Signature;

#endif