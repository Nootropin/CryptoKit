#include "AES.hpp"
#include <openssl/evp.h>
#include <openssl/err.h>
#include <vector>
#include <string>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <iostream>

std::vector<unsigned char> AESEncryption::encrypt(std::vector<unsigned char>& input,
                                                  std::vector<unsigned char>& password) const {
    std::vector<unsigned char> output;
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
        return output; // Error handling

    const EVP_CIPHER* cipher = EVP_aes_256_cbc();
    int key_len = EVP_CIPHER_key_length(cipher);   // 32 bytes for AES-256
    int iv_len  = EVP_CIPHER_iv_length(cipher);     // 16 bytes IV

    unsigned char key[32];
    unsigned char iv[16];
    for(auto& i:iv){
        i = 0;
    }
    // Derive key and IV from password (using a null salt for demonstration)
    int derived = EVP_BytesToKey(cipher, EVP_sha256(), nullptr,
                                 password.data(), password.size(), 1, key, iv);
    if (derived != key_len) {
        EVP_CIPHER_CTX_free(ctx);
        return output;
    }

    if (1 != EVP_EncryptInit_ex(ctx, cipher, nullptr, key, iv)) {
        EVP_CIPHER_CTX_free(ctx);
        return output;
    }

    std::ostringstream oss;
    for (unsigned char byte : key) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    std::cout << "\"" << oss.str() << "\"" << std::endl;
    std::ostringstream ass;
    for (unsigned char byte : iv) {
        ass << std::setfill('0') << static_cast<int>(byte);
    }
    std::cout << "\"" << ass.str() << "\"" << std::endl;
    // Allocate sufficient output buffer (input size + block size)
    int outlen1 = input.size() + EVP_CIPHER_block_size(cipher);
    output.resize(outlen1);
    int outlen_actual = 0;

    if (1 != EVP_EncryptUpdate(ctx, output.data(), &outlen_actual, input.data(), input.size())) {
        EVP_CIPHER_CTX_free(ctx);
        return std::vector<unsigned char>();
    }

    int outlen2 = 0;
    if (1 != EVP_EncryptFinal_ex(ctx, output.data() + outlen_actual, &outlen2)) {
        EVP_CIPHER_CTX_free(ctx);
        return std::vector<unsigned char>();
    }

    output.resize(outlen_actual + outlen2);
    EVP_CIPHER_CTX_free(ctx);
    return output;
}

std::vector<unsigned char> AESEncryption::decrypt(std::vector<unsigned char>& input,
                                                  std::vector<unsigned char>& password) const {
    std::vector<unsigned char> output;
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
        return output;

    const EVP_CIPHER* cipher = EVP_aes_256_cbc();
    int key_len = EVP_CIPHER_key_length(cipher);
    int iv_len  = EVP_CIPHER_iv_length(cipher);

    unsigned char key[32];
    unsigned char iv[16];
    for(auto& i:iv){
        i = 0;
    }
    int derived = EVP_BytesToKey(cipher, EVP_sha256(), nullptr,
                                 password.data(), password.size(), 1, key, iv);

    std::ostringstream oss;
    for (unsigned char byte : key) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    std::cout << "\"" << oss.str() << "\"" << std::endl;
    if (derived != key_len) {
        EVP_CIPHER_CTX_free(ctx);
        return output;
    }

    if (1 != EVP_DecryptInit_ex(ctx, cipher, nullptr, key, iv)) {
        EVP_CIPHER_CTX_free(ctx);
        return output;
    }

    // Allocate output buffer (at least input size)
    int outlen1 = input.size();
    output.resize(outlen1);
    int outlen_actual = 0;

    if (1 != EVP_DecryptUpdate(ctx, output.data(), &outlen_actual, input.data(), input.size())) {
        EVP_CIPHER_CTX_free(ctx);
        return std::vector<unsigned char>();
    }

    int outlen2 = 0;
    if (1 != EVP_DecryptFinal_ex(ctx, output.data() + outlen_actual, &outlen2)) {
        EVP_CIPHER_CTX_free(ctx);
        return std::vector<unsigned char>();
    }

    output.resize(outlen_actual + outlen2);
    EVP_CIPHER_CTX_free(ctx);
    return output;
}