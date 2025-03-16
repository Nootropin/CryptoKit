#include "HashWindowDataModel.hpp"
#include <sstream>
#include <iomanip>

HashWindowDataModel::HashWindowDataModel(std::vector<HashBase*> hashers)
    : currentHashId(0), hashers(hashers) {}

QString HashWindowDataModel::getCurrentHash(const QString& input) const {
    // Convert input from QString to std::vector<unsigned char>
    std::string in = input.toStdString();
    std::vector<unsigned char> vInput(in.begin(), in.end());

    // Get the hash using the current hasher
    std::vector<unsigned char> hash = hashers[currentHashId]->getHash(vInput);

    // Convert the hash to a hexadecimal string
    std::stringstream ss;
    for (auto& byte : hash) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }

    // Convert the hexadecimal string to a QString
    return QString::fromStdString(ss.str());
}

std::vector<HashBase*> HashWindowDataModel::getHashes() const {
    return this->hashers;
}

void HashWindowDataModel::setHash(int id) {
    this->currentHashId = id;
}