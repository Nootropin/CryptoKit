/**
 * @file 3Des.hpp
 * @brief TripleDesEncryption definition
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
 * @brief Implement 3DES encryption
 * @details Inherits from EncryptionBase class  
*/
class TripleDESEncryption : public EncryptionBase {
    public:
        TripleDESEncryption();
        std::vector<unsigned char> encrypt(std::vector<unsigned char>& input, std::vector<unsigned char>& password) const override;
        std::vector<unsigned char> decrypt(std::vector<unsigned char>& input, std::vector<unsigned char>& password) const override;
        std::string getEncryptionName() const override;
    private:
        std::string encryptionName;
};

#endif // TRIPLE_DES_ENCRYPTION_HPP