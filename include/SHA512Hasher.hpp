#ifndef SHA512_HASH_HPP
#define SHA512_HASH_HPP

#include "HashBase.hpp"
#include <vector>
#include <string>

class SHA_512_Hasher : public HashBase {
public:
    SHA_512_Hasher();
    std::vector<unsigned char> getHash(std::vector<unsigned char>& input) const;
    std::string getHashName() const { return "SHA-512"; }
    int getHashLength() const { return 64; }
};

#endif