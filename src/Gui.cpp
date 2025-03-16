#include "Gui.hpp"
#include "EncryptionWidget.hpp"
#include "EncodingWidget.hpp"
#include "HashWidget.hpp"
MyMainWindow::MyMainWindow(QWidget* parent, HashWindowDataModel model, EncryptionWidgetDataModel encryptModel, EncodingWidgetDataModel encodModel)
    : QMainWindow(parent), hashingModel(model), encryptionModel(encryptModel){
    
    QMenu* hashMenu = menuBar()->addMenu("Hashes");
    QMenu* encryptionMenu = menuBar()->addMenu("Encryption");
    QMenu* encodingMenu = menuBar()->addMenu("Encoding");
    QMenu* styleMenu = menuBar()->addMenu("Style");
    stackedWidget = new QStackedWidget(this);
    rainbowTick = new QAction("Rainbow buttons", this);
    styleMenu->addAction(rainbowTick);

    hashWidget = new HashWidget(nullptr, model);
    encryptionWidget = new EncryptionWidget(nullptr, encryptModel);
    stackedWidget->addWidget(hashWidget);
    stackedWidget->addWidget(encryptionWidget);
    int counter = 0;
    std::vector<EncryptionBase*> encryptions = encryptionModel.getCryptors();
    for (auto& i : encryptions) {
        QString tempString = QString::fromStdString(i->getEncryptionName());
        std::cout << i->getEncryptionName() << std::endl;
        QAction* tempAction = new QAction(tempString, this);
        encryptionMenu->addAction(tempAction);
        connect(tempAction, &QAction::triggered, this, [counter, this]() { this->openEncryption(counter); });
        counter++;
    }

    counter = 0;
    std::vector<HashBase*> hashers = model.getHashes();
    for (auto& i : hashers) {
        QString tempString = QString::fromStdString(i->getHashName());
        std::cout << i->getHashName() << std::endl;
        QAction* tempAction = new QAction(tempString, this);
        hashMenu->addAction(tempAction);
        connect(tempAction, &QAction::triggered, this, [counter, this]() { this->openHash(counter); });
        counter++;
    }

    EncodingWidget* encoding = new EncodingWidget(encodModel);
    stackedWidget->addWidget(encoding);
    QAction* openEncodingWindow = new QAction("Encoding",this);
    QAction* spacesSwap = new QAction("Spaces",this);
    encodingMenu->addAction(openEncodingWindow);
    encodingMenu->addAction(spacesSwap);
    connect(openEncodingWindow,&QAction::triggered, this, &MyMainWindow::openEncoding);
    connect(spacesSwap,&QAction::triggered, this, &MyMainWindow::swapSpaces);
    connect(rainbowTick, &QAction::triggered, this, &MyMainWindow::rainbowSwaping);

    

    this->setCentralWidget(stackedWidget);
}


void MyMainWindow::openHash(int counter){
    stackedWidget->setCurrentIndex(0);
    hashWidget->changeHash(counter);
}

void MyMainWindow::openEncryption(int counter){
    stackedWidget->setCurrentIndex(1);
    encryptionWidget->changeEncryption(counter);
}

void MyMainWindow::rainbowSwaping() {
    RainbowButton::swapMode();
}

void MyMainWindow::openEncoding(){
    stackedWidget->setCurrentIndex(2);
}

void MyMainWindow::swapSpaces(){
    EncodingWidgetDataModel::spaceOn = !EncodingWidgetDataModel::spaceOn;
}
