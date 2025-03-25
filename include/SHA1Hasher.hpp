#ifndef SHA_1_HPP
#define SHA_1_HPP
#include "HashBase.hpp"
#include <openssl/sha.h>
class SHA_1_Hasher : public HashBase{
    public:
        SHA_1_Hasher(){

        }
        std::string getHashName() const { return "SHA-1"; }
        int getHashLength() const { return 20; }
        std::vector<unsigned char> getHash(std::vector<unsigned char> &input) const;
    private:
        const int hashLength = 20;
        const std::string hashName = "SHA-1";
        
};
#endif