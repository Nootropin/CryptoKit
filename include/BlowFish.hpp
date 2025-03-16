/**
 * @file BlowFish.hpp
 * @brief DOESN'T WORK AT ALL, DON'T USE
 * @todo MAKE THIS WORK
 */
#ifndef BLOWFISH_ENCRYPTION_HPP
#define BLOWFISH_ENCRYPTION_HPP

#include "EncryptionBase.hpp"
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <vector>
#include <string>
#include <iostream>

class BlowfishEncryption : public EncryptionBase {
public:
    std::vector<unsigned char> encrypt(std::vector<unsigned char>& input, std::vector<unsigned char>& password) const override {
        if (password.size() < 4 || password.size() > 56 || (password.size() % 8 != 0)) {
            std::cerr << "Invalid key length: " << password.size() << std::endl;
            return {};
        }

        std::vector<unsigned char> iv(8);
        if (RAND_bytes(iv.data(), iv.size()) <= 0) {
            return {};
        }

        EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
        
        if (!ctx) {
            std::cerr << "CTX FAIL" << std::endl;
            return {};
        }

        if (1 != EVP_EncryptInit_ex(ctx, EVP_bf_cbc(), NULL, password.data(), iv.data())) {
            EVP_CIPHER_CTX_free(ctx);
            std::cerr << "Encryption FAIL" << std::endl;
            return {};
        }

        std::vector<unsigned char> ciphertext(iv);
        ciphertext.resize(iv.size() + input.size() + EVP_MAX_BLOCK_LENGTH);

        int len = 0;
        int ciphertext_len = iv.size();

        if (1 != EVP_EncryptUpdate(ctx, ciphertext.data() + ciphertext_len, &len, input.data(), input.size())) {
            std::cerr << "Encryption update FAIL" << std::endl;
            EVP_CIPHER_CTX_free(ctx);
            return {};
        }
        ciphertext_len += len;

        if (1 != EVP_EncryptFinal_ex(ctx, ciphertext.data() + ciphertext_len, &len)) {
            std::cerr << "Encryption final FAIL" << std::endl;
            EVP_CIPHER_CTX_free(ctx);
            return {};
        }
        ciphertext_len += len;

        EVP_CIPHER_CTX_free(ctx);
        ciphertext.resize(ciphertext_len);
        return ciphertext;
    }

    std::vector<unsigned char> decrypt(std::vector<unsigned char>& input, std::vector<unsigned char>& password) const override {
        if (password.size() < 4 || password.size() > 56 || input.size() < 8) {
            return {};
        }

        std::vector<unsigned char> iv(input.begin(), input.begin() + 8);
        std::vector<unsigned char> ciphertext(input.begin() + 8, input.end());

        EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
        if (!ctx) {
            return {};
        }

        if (1 != EVP_DecryptInit_ex(ctx, EVP_bf_cbc(), nullptr, password.data(), iv.data())) {
            EVP_CIPHER_CTX_free(ctx);
            return {};
        }

        std::vector<unsigned char> plaintext(ciphertext.size() + EVP_MAX_BLOCK_LENGTH);
        int len = 0;
        int plaintext_len = 0;

        if (1 != EVP_DecryptUpdate(ctx, plaintext.data(), &len, ciphertext.data(), ciphertext.size())) {
            EVP_CIPHER_CTX_free(ctx);
            return {};
        }
        plaintext_len += len;

        if (1 != EVP_DecryptFinal_ex(ctx, plaintext.data() + plaintext_len, &len)) {
            EVP_CIPHER_CTX_free(ctx);
            return {};
        }
        plaintext_len += len;

        EVP_CIPHER_CTX_free(ctx);
        plaintext.resize(plaintext_len);
        return plaintext;
    }

    std::string getEncryptionName() const override {
        return "Blowfish";
    }
};

#endif // BLOWFISH_ENCRYPTION_HPP