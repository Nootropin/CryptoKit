#ifndef SHA_256_HPP
#define SHA_256_HPP
#include "HashBase.hpp"
#include <openssl/sha.h>
class SHA_256_Hasher : public HashBase{
    public:
        SHA_256_Hasher(){

        }
        std::string getHashName() const { return "SHA-256"; }
        int getHashLength() const { return 32; }
    private:
        const int hashLength = 32;
        const std::string hashName = "SHA-256";
};
#endif