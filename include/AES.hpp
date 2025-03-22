#ifndef AES_HPP
#define AES_HPP
/**
 * @file AES.hpp
 * @brief AES encryption implementation
 * @see EncryptionBase
 */
#include "EncryptionBase.hpp"
#include <openssl/evp.h>
#include <openssl/err.h>
#include <vector>
#include <string>
#include <cstring>

/**
 * @brief 3DES encryption algorithm.
 * @details Inherits from @ref EncryptionBase and implements the AES
 * Uses OpenSSL's AES functions under the hood.
 * @note The password is internally converted SHA-1 hash
 */
class AESEncryption : public EncryptionBase {
public:
    virtual std::vector<unsigned char> encrypt(std::vector<unsigned char>& input,
                                               std::vector<unsigned char>& password) const override;
    virtual std::vector<unsigned char> decrypt(std::vector<unsigned char>& input,
                                               std::vector<unsigned char>& password) const override;
    virtual std::string getEncryptionName() const override { return "AES"; }
};

#endif // AES_HPP