#ifndef UTILS_H
#define UTILS_H

#include <string>
#include "ArrayGenerator.h"

inline std::string tabtypes(arrayType type) {
    switch (type) {
        case arrayType::FULLRANDOM: return "FULLRANDOM";
        case arrayType::ASCENDING: return "ASCENDING";
        case arrayType::DESCENDING: return "DESCENDING";
        case arrayType::PARTLYSORTEDLOW: return "PARTLYSORTEDLOW";
        case arrayType::PARTLYSORTEDHIGH: return "PARTLYSORTEDHIGH";
        default: return "UNKNOWN";
    }
}

#endif // UTILS_H