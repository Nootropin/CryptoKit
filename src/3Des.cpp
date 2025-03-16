#include "3Des.hpp"

TripleDESEncryption::TripleDESEncryption() {
    encryptionName = "3DES";
}

std::vector<unsigned char> TripleDESEncryption::encrypt(std::vector<unsigned char>& input, std::vector<unsigned char>& password) const {
    if (password.size() != 24) {
        throw std::invalid_argument("Password must be 24 bytes long for 3DES encryption.");
    }

    DES_cblock key1, key2, key3;
    std::copy(password.begin(), password.begin() + 8, key1);
    std::copy(password.begin() + 8, password.begin() + 16, key2);
    std::copy(password.begin() + 16, password.end(), key3);

    DES_key_schedule ks1, ks2, ks3;
    DES_set_key_unchecked(&key1, &ks1);
    DES_set_key_unchecked(&key2, &ks2);
    DES_set_key_unchecked(&key3, &ks3);

    std::vector<unsigned char> output(input.size());
    DES_ede3_cbc_encrypt(input.data(), output.data(), input.size(), &ks1, &ks2, &ks3, &key1, DES_ENCRYPT);

    return output;
}

std::vector<unsigned char> TripleDESEncryption::decrypt(std::vector<unsigned char>& input, std::vector<unsigned char>& password) const {
    if (password.size() != 24) {
        throw std::invalid_argument("Password must be 24 bytes long for 3DES decryption.");
    }

    DES_cblock key1, key2, key3;
    std::copy(password.begin(), password.begin() + 8, key1);
    std::copy(password.begin() + 8, password.begin() + 16, key2);
    std::copy(password.begin() + 16, password.end(), key3);

    DES_key_schedule ks1, ks2, ks3;
    DES_set_key_unchecked(&key1, &ks1);
    DES_set_key_unchecked(&key2, &ks2);
    DES_set_key_unchecked(&key3, &ks3);

    std::vector<unsigned char> output(input.size());
    DES_ede3_cbc_encrypt(input.data(), output.data(), input.size(), &ks1, &ks2, &ks3, &key1, DES_DECRYPT);

    return output;
}

std::string TripleDESEncryption::getEncryptionName() const {
    return encryptionName;
}