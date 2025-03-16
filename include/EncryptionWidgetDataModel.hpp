#ifndef ENCRYPTION_WIDGET_DATA_MODEL_HPP
#define ENCRYPTION_WIDGET_DATA_MODEL_HPP

#include <vector>
#include <QString>
#include "EncryptionBase.hpp"

class EncryptionWidgetDataModel {
public:
    EncryptionWidgetDataModel(std::vector<EncryptionBase*> cryptors);

    QString encryptCurrent(const QString& input, const QString& password) const;
    QString decryptCurrent(const QString& input, const QString& password) const;

    std::vector<EncryptionBase*> getCryptors() const;
    void setEncryption(int id);

private:
    std::vector<EncryptionBase*> cryptors;
    int currentEncryptionId;
};

#endif // ENCRYPTION_WIDGET_DATA_MODEL_HPP