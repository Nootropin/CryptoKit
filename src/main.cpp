#include "Gui.hpp"
#include "SHA256Hasher.hpp"
#include "SHA512Hasher.hpp"
#include "HashWindowDataModel.hpp"
#include "AES.hpp"
#include "BlowFish.hpp"
#include "3Des.hpp"
#include "EncodingWidget.hpp"
#include <QApplication>
int main(int argc, char *argv[]){
    QApplication q(argc, argv);
    q.setStyle(QStyleFactory::create("Fusion"));
    SHA_256_Hasher hw = SHA_256_Hasher();
    SHA_512_Hasher ha = SHA_512_Hasher();
    AESEncryption a = AESEncryption();
    //BlowfishEncryption b = BlowfishEncryption();
    HashWindowDataModel model = HashWindowDataModel({&hw,&ha});
    EncodingWidgetDataModel mod = EncodingWidgetDataModel();
    TripleDESEncryption tripleDes = TripleDESEncryption();
    EncryptionWidgetDataModel encryptionModel = EncryptionWidgetDataModel({&a,&tripleDes});
    MyMainWindow h = MyMainWindow((QWidget*)nullptr,model,encryptionModel,mod);
    h.show();
    return q.exec();
}