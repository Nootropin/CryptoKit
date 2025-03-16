#include "SHA256Hasher.hpp"
std::vector<unsigned char> HashBase::getHash(std::vector<unsigned char> &input) const
{
    std::vector<unsigned char> hash(SHA256_DIGEST_LENGTH);
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    std::vector<unsigned char> vInput(input.begin(), input.end());
    SHA256_Update(&sha256, vInput.data(), vInput.size());
    SHA256_Final(hash.data(), &sha256);
    return hash;
}