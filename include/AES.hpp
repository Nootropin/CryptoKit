#ifndef AES_HPP
#define AES_HPP

#include "EncryptionBase.hpp"
#include <openssl/evp.h>
#include <openssl/err.h>
#include <vector>
#include <string>
#include <cstring>

class AESEncryption : public EncryptionBase {
public:
    virtual std::vector<unsigned char> encrypt(std::vector<unsigned char>& input,
                                               std::vector<unsigned char>& password) const override;
    virtual std::vector<unsigned char> decrypt(std::vector<unsigned char>& input,
                                               std::vector<unsigned char>& password) const override;
    virtual std::string getEncryptionName() const override { return "AES"; }
};

#endif // AES_HPP