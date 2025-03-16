#include "EncodingWidgetDataModel.hpp"
#include <QIODevice>       // Add this
#include <QDataStream> 
#include <QRegularExpression>
#include <QByteArray>
#include <QDataStream>
#include <QChar>

using namespace std;
bool EncodingWidgetDataModel::spaceOn = true;
// Convert formatted strings to byte arrays
//-----------------------------------------------------------------------------
vector<unsigned char> EncodingWidgetDataModel::bytesFromBin(const QString& input) const {
    QString cleaned = input;
    cleaned.remove(QRegularExpression("[^01]"));  // Remove non-binary chars
    
    // Pad to multiple of 8 bits
    if(cleaned.size() % 8 != 0)
        cleaned = QString(8 - cleaned.size() % 8, '0') + cleaned;

    vector<unsigned char> result;
    for(int i=0; i<cleaned.size(); i+=8) {
        QString byteStr = cleaned.mid(i, 8);
        bool ok;
        result.push_back(byteStr.toUInt(&ok, 2));
    }
    return result;
}

vector<unsigned char> EncodingWidgetDataModel::bytesFromOct(const QString& input) const {
    QString cleaned = input;
    cleaned.remove(QRegularExpression("[^0-7]"));
    
    vector<unsigned char> result;
    QStringList tokens = cleaned.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    for(const QString& token : tokens) {
        bool ok;
        unsigned long val = token.toULong(&ok, 8);
        if(ok && val <= 0xFF)
            result.push_back(val);
    }
    return result;
}

vector<unsigned char> EncodingWidgetDataModel::bytesFromDec(const QString& input) const {
    QStringList tokens = input.split(QRegularExpression("[^0-9]"), Qt::SkipEmptyParts);
    vector<unsigned char> result;
    for(const QString& token : tokens) {
        bool ok;
        unsigned long val = token.toULong(&ok);
        if(ok && val <= 0xFF)
            result.push_back(val);
    }
    return result;
}

vector<unsigned char> EncodingWidgetDataModel::bytesFromHex(const QString& input) const {
    QByteArray hexData = input.toLatin1();
    QByteArray byteArray = QByteArray::fromHex(hexData);
    return vector<unsigned char>(byteArray.begin(), byteArray.end());
}

vector<unsigned char> EncodingWidgetDataModel::bytesFromBase64(const QString& input) const {
    QByteArray byteArray = QByteArray::fromBase64(input.toUtf8());
    return vector<unsigned char>(byteArray.begin(), byteArray.end());
}

vector<unsigned char> EncodingWidgetDataModel::bytesFromASCII(const QString& input) const {
    QByteArray ascii = input.toLatin1();
    return vector<unsigned char>(ascii.begin(), ascii.end());
}

vector<unsigned char> EncodingWidgetDataModel::bytesFromUTF8(const QString& input) const {
    QByteArray utf8 = input.toUtf8();
    return vector<unsigned char>(utf8.begin(), utf8.end());
}

vector<unsigned char> EncodingWidgetDataModel::bytesFromUTF16(const QString& input) const {
    QByteArray bytes;
    QDataStream stream(&bytes, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::BigEndian);
    for(QChar ch : input)
        stream << ch.unicode();
    return vector<unsigned char>(bytes.begin(), bytes.end());
}

// Convert byte arrays to formatted strings
//-----------------------------------------------------------------------------
QString EncodingWidgetDataModel::binFromBytes(const vector<unsigned char>& input) const {
    QStringList result;
    for(unsigned char byte : input)
        result.append(QString("%1").arg(byte, 8, 2, QLatin1Char('0')));
    if(spaceOn){
        return result.join(" ");
    }return result.join("");
}

QString EncodingWidgetDataModel::octFromBytes(const vector<unsigned char>& input) const {
    QStringList result;
    for(unsigned char byte : input)
        result.append(QString("%1").arg(byte, 3, 8, QLatin1Char('0')));
     if(spaceOn){
        return result.join(" ");
    }return result.join("");
}

QString EncodingWidgetDataModel::decFromBytes(const vector<unsigned char>& input) const {
    QStringList result;
    for(unsigned char byte : input)
        result.append(QString::number(byte));
     if(spaceOn){
        return result.join(" ");
    }return result.join("");
}

QString EncodingWidgetDataModel::hexFromBytes(const vector<unsigned char>& input) const {
    QByteArray bytes(reinterpret_cast<const char*>(input.data()), input.size());
     if(spaceOn){
        return QString(bytes.toHex(' ').toUpper());
    }return QString(bytes.toHex().toUpper());
}

QString EncodingWidgetDataModel::base64FromBytes(const vector<unsigned char>& input) const {
    QByteArray bytes(reinterpret_cast<const char*>(input.data()), input.size());
    return QString(bytes.toBase64());
}

QString EncodingWidgetDataModel::asciiFromBytes(const vector<unsigned char>& input) const {
    QByteArray bytes(reinterpret_cast<const char*>(input.data()), input.size());
    // Replace non-ASCII characters with '?'
    for(int i=0; i<bytes.size(); ++i)
        if(bytes[i] < 0x20 || bytes[i] > 0x7E)
            bytes[i] = '?';
    return QString::fromLatin1(bytes);
}

QString EncodingWidgetDataModel::Utf8FromBytes(const vector<unsigned char>& input) const {
    QByteArray bytes(reinterpret_cast<const char*>(input.data()), input.size());
    return QString::fromUtf8(bytes);
}

QString EncodingWidgetDataModel::Utf16FromBytes(const vector<unsigned char>& input) const {
    if(input.size() % 2 != 0) return QString();
    
    QByteArray bytes(reinterpret_cast<const char*>(input.data()), input.size());
    QDataStream stream(bytes);
    stream.setByteOrder(QDataStream::BigEndian);
    
    QString result;
    while(!stream.atEnd()) {
        quint16 code;
        stream >> code;
        result.append(QChar(code));
    }
    return result;
}