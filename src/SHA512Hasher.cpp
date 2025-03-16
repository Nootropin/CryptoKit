#include "SHA512Hasher.hpp"
#include <openssl/sha.h>
#include <vector>

SHA_512_Hasher::SHA_512_Hasher() {}

std::vector<unsigned char> SHA_512_Hasher::getHash(std::vector<unsigned char>& input) const {
    std::vector<unsigned char> hash(SHA512_DIGEST_LENGTH);
    SHA512_CTX context;
    SHA512_Init(&context);
    SHA512_Update(&context, input.data(), input.size());
    SHA512_Final(hash.data(), &context);
    return hash;
}