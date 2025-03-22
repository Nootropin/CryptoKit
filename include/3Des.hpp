/**
 * @file 3Des.hpp
 * @brief Triple DES (3DES) encryption implementation.
 * @see EncryptionBase
 */
#ifndef TRIPLE_DES_ENCRYPTION_HPP
#define TRIPLE_DES_ENCRYPTION_HPP

#include "EncryptionBase.hpp"
#include <openssl/des.h>
#include <openssl/rand.h>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>

/**
 * @brief 3DES encryption algorithm.
 * @details Inherits from @ref EncryptionBase and implements the Triple Data Encryption Standard (3DES).
 * Uses OpenSSL's DES functions under the hood.
 * 
 * @note The password is internally converted to three 56-bit DES keys.
 */
class TripleDESEncryption : public EncryptionBase {
public:
    TripleDESEncryption();

    /**
     * @copydoc EncryptionBase::encrypt
     * @details For 3DES, the `password` vector must be at least 24 bytes long (3×8-byte DES keys).
     * @throws std::invalid_argument If `password` size is insufficient.
     */
    std::vector<unsigned char> encrypt(std::vector<unsigned char>& input, std::vector<unsigned char>& password) const override;

    /**
     * @copydoc EncryptionBase::decrypt
     * @details Uses the same key derivation logic as @ref encrypt.
     */
    std::vector<unsigned char> decrypt(std::vector<unsigned char>& input, std::vector<unsigned char>& password) const override;

    /**
     * @brief Returns the name of the encryption algorithm.
     * @return "3DES" as a string.
     */
    std::string getEncryptionName() const override;

private:
    std::string encryptionName{"3DES"}; // Explicitly set the algorithm name
};
#endif // TRIPLE_DES_ENCRYPTION_HPP