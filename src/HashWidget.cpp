#include "HashWidget.hpp"
#include "Gui.hpp"
HashWidget::HashWidget(MyMainWindow* parent, HashWindowDataModel model) 
    : MyWidget(parent), parentWindow(parent), model(model){
    
    int counter = 0;
    std::vector<HashBase*> hasher = model.getHashes();

    QHBoxLayout* horLayout = new QHBoxLayout();
    textBlock = new QTextEdit();
    QVBoxLayout* buttonBlock = new QVBoxLayout();
    resultBlock = new QTextEdit();
    convertButt = new RainbowButton("Convert");
    openFileButt = new RainbowButton("Open file");

    buttonBlock->addStretch();
    buttonBlock->addWidget(convertButt);
    buttonBlock->addWidget(openFileButt);
    buttonBlock->addStretch();

    horLayout->addWidget(textBlock, 4);
    horLayout->addLayout(buttonBlock, 2);
    horLayout->addWidget(resultBlock, 4);

    connect(convertButt, &QPushButton::clicked, this, &HashWidget::convertButton);
    connect(textBlock, &QTextEdit::textChanged, this, &HashWidget::convertButton);
    connect(openFileButt, &QPushButton::clicked, this, &HashWidget::openFileButton);

    this->setLayout(horLayout);
}

void HashWidget::convertButton() {
    resultBlock->setText(model.getCurrentHash(textBlock->toPlainText()));
}

void HashWidget::changeHash(int i) {
    model.setHash(i);
    convertButton();
}

void HashWidget::openFileButton() {
    QString filePath = QFileDialog::getOpenFileName(nullptr, "", QDir::currentPath(), "");
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
    convertButton();
}

void HashWidget::rainbowSwaping() {
    convertButt->swapRainbow();
    openFileButt->swapRainbow();
    std::cout << "Rainbow swapped" << std::endl;
}

void HashWidget::themeSwaping() {
    std::cout << "Swaped" << std::endl;
}

void HashWidget::setInputText(const QString& input){
    textBlock->setText(input);
}

QString HashWidget::getOutputText() const{
    return resultBlock->toPlainText();
}