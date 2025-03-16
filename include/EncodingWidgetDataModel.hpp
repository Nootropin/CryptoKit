#ifndef ENCDOING_WIDGET_MODEL_HPP
#define ENCDOING_WIDGET_MODEL_HPP
#include <QString>
#include <iomanip>
#include <sstream>
#include <vector>
class EncodingWidgetDataModel{
    public:
    // bytes to format
    std::vector<unsigned char> bytesFromBin(const QString& input) const;
    std::vector<unsigned char> bytesFromOct(const QString& input) const;
    std::vector<unsigned char> bytesFromDec(const QString& input) const;
    std::vector<unsigned char> bytesFromHex(const QString& input) const;
    std::vector<unsigned char> bytesFromBase64(const QString& input) const;
    std::vector<unsigned char> bytesFromASCII(const QString& input) const;
    std::vector<unsigned char> bytesFromUTF8(const QString& input) const;
    std::vector<unsigned char> bytesFromUTF16(const QString& input) const;
    // format to bytes
    QString binFromBytes(const std::vector<unsigned char>& input) const;
    QString octFromBytes(const std::vector<unsigned char>& input) const;
    QString decFromBytes(const std::vector<unsigned char>& input) const;
    QString hexFromBytes(const std::vector<unsigned char>& input) const;
    QString base64FromBytes(const std::vector<unsigned char>& input) const;
    QString asciiFromBytes(const std::vector<unsigned char>& input) const;
    QString Utf8FromBytes(const std::vector<unsigned char>& input) const;
    QString Utf16FromBytes(const std::vector<unsigned char>& input) const;
    static bool spaceOn;
};
#endif