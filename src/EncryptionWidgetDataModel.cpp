#include "EncryptionWidgetDataModel.hpp"
#include <sstream>
#include <iomanip>

EncryptionWidgetDataModel::EncryptionWidgetDataModel(std::vector<EncryptionBase*> cryptors)
    : currentEncryptionId(0), cryptors(cryptors) {}

QString EncryptionWidgetDataModel::encryptCurrent(const QString& input, const QString& password) const {
    // Convert input and password from QString to std::vector<unsigned char>
    std::string inputStd = input.toStdString();
    std::string passwordStd = password.toStdString();
    std::vector<unsigned char> inputVec(inputStd.begin(), inputStd.end());
    std::vector<unsigned char> passwordVec(passwordStd.begin(), passwordStd.end());

    // Get the current cryptor and encrypt the data
    EncryptionBase* cryptor = cryptors[currentEncryptionId];
    std::vector<unsigned char> encryptedData = cryptor->encrypt(inputVec, passwordVec);

    // Convert the encrypted data to a hexadecimal string
    std::ostringstream oss;
    for (unsigned char byte : encryptedData) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    return QString::fromStdString(oss.str());
}

QString EncryptionWidgetDataModel::decryptCurrent(const QString& input, const QString& password) const {
    // Convert the input hex string into a vector of bytes
    std::string hexStr = input.toStdString();
    std::vector<unsigned char> encryptedData;
    if (hexStr.size() % 2 != 0) {
        // Invalid hex string length; return empty string
        return QString();
    }
    for (size_t i = 0; i < hexStr.size(); i += 2) {
        std::string byteString = hexStr.substr(i, 2);
        unsigned char byte = static_cast<unsigned char>(std::stoi(byteString, nullptr, 16));
        encryptedData.push_back(byte);
    }

    // Convert password from QString to std::vector<unsigned char>
    std::string passwordStd = password.toStdString();
    std::vector<unsigned char> passwordVec(passwordStd.begin(), passwordStd.end());

    // Get the current cryptor and decrypt the data
    EncryptionBase* cryptor = cryptors[currentEncryptionId];
    std::vector<unsigned char> decryptedData = cryptor->decrypt(encryptedData, passwordVec);

    // Convert the decrypted bytes back to a string
    std::string decryptedStr(decryptedData.begin(), decryptedData.end());
    return QString::fromStdString(decryptedStr);
}

std::vector<EncryptionBase*> EncryptionWidgetDataModel::getCryptors() const {
    return this->cryptors;
}

void EncryptionWidgetDataModel::setEncryption(int id) {
    this->currentEncryptionId = id;
}