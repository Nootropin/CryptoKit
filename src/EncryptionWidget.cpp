#include "EncryptionWidget.hpp"
#include "Gui.hpp"
EncryptionWidget::EncryptionWidget(MyMainWindow* parent, EncryptionWidgetDataModel model)
    : MyWidget(parent), parentWindow(parent), model(model), encryptionMenu(encryptionMenu) {
    
    int counter = 0;

    QHBoxLayout* horLayout = new QHBoxLayout();
    QVBoxLayout* textBlockLayout = new QVBoxLayout();
    textBlock = new QTextEdit();
    passwordInput = new QTextEdit();
    
    textBlockLayout->addStretch();
    textBlockLayout->addWidget(textBlock, 8);
    textBlockLayout->addWidget(passwordInput, 2);
    textBlockLayout->addStretch();

    QVBoxLayout* buttonBlock = new QVBoxLayout();
    resultBlock = new QTextEdit();
    encryptButt = new RainbowButton("Encrypt");
    decryptButt = new RainbowButton("Decrypt");
    openFileButt = new RainbowButton("Open file");

    buttonBlock->addStretch();
    buttonBlock->addWidget(encryptButt);
    buttonBlock->addWidget(decryptButt);
    buttonBlock->addWidget(openFileButt);
    buttonBlock->addStretch();

    horLayout->addLayout(textBlockLayout, 4);
    horLayout->addLayout(buttonBlock, 2);
    horLayout->addWidget(resultBlock, 4);

    connect(encryptButt, &QPushButton::clicked, this, &EncryptionWidget::encrypt);
    connect(decryptButt, &QPushButton::clicked, this, &EncryptionWidget::decrypt);
    connect(openFileButt, &QPushButton::clicked, this, &EncryptionWidget::openFileButton);

    this->setLayout(horLayout);
}

void EncryptionWidget::encrypt() {
    resultBlock->setText(model.encryptCurrent(textBlock->toPlainText(), passwordInput->toPlainText()));
}

void EncryptionWidget::decrypt() {
    resultBlock->setText(model.decryptCurrent(textBlock->toPlainText(), passwordInput->toPlainText()));
}

void EncryptionWidget::changeEncryption(int i) {
    model.setEncryption(i);
}

void EncryptionWidget::setInputText(const QString& input){
    textBlock->setText(input);
}

QString EncryptionWidget::getOutputText() const{
    return resultBlock->toPlainText();
}

void EncryptionWidget::openFileButton() {
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
    textBlock->setText(blockInput);
}
