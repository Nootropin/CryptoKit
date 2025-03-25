#include "SHA1Hasher.hpp"
std::vector<unsigned char> SHA_1_Hasher::getHash(std::vector<unsigned char>& input) const{
    std::vector<unsigned char> hash(20);
    SHA_CTX sha1;
    SHA1_Init(&sha1);
    std::vector<unsigned char> vInput(input.begin(), input.end());
    SHA1_Update(&sha1, vInput.data(), vInput.size());
    SHA1_Final(hash.data(), &sha1);
    return hash;
}