#ifndef ENCRYPTION_BASE_HPP
#define ENCRYPTION_BASE_HPP
/**
 * @file EncryptionBase.hpp
 * @brief Implements EncryptionBase class
 * @see EncryptionWidget
 */
#include<vector>
#include<string>
/**
 * @brief Base class for work with EncryptionWidget
 */
class EncryptionBase{
    public:
        /**
         * @brief Function for encryption
         * @param input Input vector, that will be encrypted
         * @param password Vector, that will be used as password
         */
        virtual std::vector<unsigned char> encrypt(std::vector<unsigned char>& input,std::vector<unsigned char>& password) const = 0;
        virtual std::vector<unsigned char> decrypt(std::vector<unsigned char>& input,std::vector<unsigned char>& password) const = 0;
        virtual std::string getEncryptionName() const {return encryptionName;}
        EncryptionBase(){};
    private:
        const std::string encryptionName = "123"; 
};
#endif