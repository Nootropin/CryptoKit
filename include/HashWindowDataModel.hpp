#ifndef HASH_WINDOW_DATA_MODEL_HPP
#define HASH_WINDOW_DATA_MODEL_HPP

#include <vector>
#include <QString>
#include "HashBase.hpp"

class HashWindowDataModel {
public:
    HashWindowDataModel(std::vector<HashBase*> hashers);

    QString getCurrentHash(const QString& input) const;
    std::vector<HashBase*> getHashes() const;
    void setHash(int id);

private:
    std::vector<HashBase*> hashers;
    int currentHashId;
};

#endif // HASH_WINDOW_DATA_MODEL_HPP