#include "Gui.hpp"
#include "EncryptionWidget.hpp"
#include "EncodingWidget.hpp"
#include "HashWidget.hpp"
MyMainWindow::MyMainWindow(QWidget* parent, HashWindowDataModel model, EncryptionWidgetDataModel encryptModel, EncodingWidgetDataModel encodModel)
    : QMainWindow(parent), hashingModel(model), encryptionModel(encryptModel){
    initMenus();
    initStackedWidget();
}
void MyMainWindow::initStackedWidget(){
    stackedWidget = new QStackedWidget(this);
    hashWidget = new HashWidget(nullptr, hashingModel);
    encryptionWidget = new EncryptionWidget(nullptr, encryptionModel);
    encoding = new EncodingWidget(encodingModel);
    stackedWidget->addWidget(hashWidget);
    stackedWidget->addWidget(encryptionWidget);
    stackedWidget->addWidget(encoding);
    this->setCentralWidget(stackedWidget);
}
void MyMainWindow::initMenus(){
    // init menu's buttons
    fileMenu = menuBar()->addMenu("File");
    QMenu* hashMenu = menuBar()->addMenu("Hashes");
    QMenu* encryptionMenu = menuBar()->addMenu("Encryption");
    QMenu* encodingMenu = menuBar()->addMenu("Encoding");
    QMenu* styleMenu = menuBar()->addMenu("Style");
    // init "Hashes" menu's buttons
    std::vector<HashBase*> hashers = hashingModel.getHashes();
    int counter = 0;
    for (auto& i : hashers) {
        QString tempString = QString::fromStdString(i->getHashName());
        std::cout << i->getHashName() << std::endl;
        QAction* tempAction = new QAction(tempString, this);
        hashMenu->addAction(tempAction);
        connect(tempAction, &QAction::triggered, this, [counter, this]() { this->openHash(counter); });
        counter++;
    }
    // init "Encryption" menu's buttons
    std::vector<EncryptionBase*> encryptions = encryptionModel.getCryptors();
    counter = 0;
    for (auto& i : encryptions) {
        QString tempString = QString::fromStdString(i->getEncryptionName());
        std::cout << i->getEncryptionName() << std::endl;
        QAction* tempAction = new QAction(tempString, this);
        encryptionMenu->addAction(tempAction);
        connect(tempAction, &QAction::triggered, this, [counter, this]() { this->openEncryption(counter); });
        counter++;
    }
    // init static buttons
    QAction* rainbowTick = new QAction("Rainbow buttons", this);
    QAction* openEncodingWindow = new QAction("Encoding",this);
    QAction* spacesSwap = new QAction("Spaces",this);
    QAction* fileOpenAction = new QAction("Open file",this);
    QAction* fileSaveAction = new QAction("Save file",this);
    // add static buttons
    fileMenu->addAction(fileOpenAction);
    fileMenu->addAction(fileSaveAction);
    encodingMenu->addAction(openEncodingWindow);
    encodingMenu->addAction(spacesSwap);
    styleMenu->addAction(rainbowTick);
    // connect static buttons
    connect(fileOpenAction, &QAction::triggered, this, &MyMainWindow::openFile);
    connect(fileSaveAction, &QAction::triggered, this, &MyMainWindow::saveFile);
    connect(openEncodingWindow,&QAction::triggered, this, &MyMainWindow::openEncoding);
    connect(spacesSwap,&QAction::triggered, this, &MyMainWindow::swapSpaces);
    connect(rainbowTick, &QAction::triggered, this, &MyMainWindow::rainbowSwaping);
}

void MyMainWindow::openFile(){
    QString filePath = QFileDialog::getOpenFileName(this, "", QDir::currentPath(), "");
    std::string fileName = filePath.toStdString();
    std::ifstream fileStream(fileName, std::ios::binary);
    
    fileStream.seekg(0, std::ios::end);
    std::streampos fileSize = fileStream.tellg();
    fileStream.seekg(0, std::ios::beg);
    
    std::vector<unsigned char> buffer(fileSize);
    fileStream.read(reinterpret_cast<char*>(buffer.data()), fileSize);
    
    std::string input(buffer.begin(), buffer.end());
    QString blockInput = QString::fromStdString(input);
    // UNSAFE AS FUCK, FIX AFAP
    dynamic_cast<MyWidget*>(stackedWidget->currentWidget())->setInputText(blockInput);
}

void MyMainWindow::saveFile(){
    QString filePath = QFileDialog::getSaveFileName(this, "", QDir::currentPath(), "");
    std::string fileName = filePath.toStdString();
    std::ofstream fileStream(fileName, std::ios::out);
    // UNSAFE AS FUCK, FIX AFAP
    QString fileText = dynamic_cast<MyWidget*>(stackedWidget->currentWidget())->getOutputText();
    fileStream << fileText.toStdString();
    fileStream.close();
}

void MyMainWindow::openHash(int counter){
    makeFilesButtonsActive();
    stackedWidget->setCurrentIndex(0);
    hashWidget->changeHash(counter);
}

void MyMainWindow::openEncryption(int counter){
    makeFilesButtonsActive();
    stackedWidget->setCurrentIndex(1);
    encryptionWidget->changeEncryption(counter);
}

void MyMainWindow::rainbowSwaping() {
    RainbowButton::swapMode();
}

void MyMainWindow::makeFilesButtonsInactive(){
    for(auto& i:fileMenu->actions()){
        i->setEnabled(false);
    }
}

void MyMainWindow::makeFilesButtonsActive(){
    for(auto& i:fileMenu->actions()){
        i->setEnabled(true);
    }
}

void MyMainWindow::openEncoding(){
    makeFilesButtonsInactive();
    stackedWidget->setCurrentIndex(2);
}

void MyMainWindow::swapSpaces(){
    EncodingWidgetDataModel::spaceOn = !EncodingWidgetDataModel::spaceOn;
}
