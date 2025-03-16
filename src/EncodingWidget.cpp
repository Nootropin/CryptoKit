#include "EncodingWidget.hpp"

TextBlock::TextBlock(QString name, QTextEdit* text) : QWidget(nullptr) {
    label = new QLabel(name);
    QVBoxLayout* newLayout = new QVBoxLayout();
    newLayout->addWidget(label, 2);
    this->text = text;
    newLayout->addWidget(text, 20);
    this->setLayout(newLayout);
}

EncodingWidget::EncodingWidget(EncodingWidgetDataModel mod) : QWidget(nullptr),mod(mod) {
    binText = new QTextEdit();
    octText = new QTextEdit();
    decText = new QTextEdit();
    hexText = new QTextEdit();
    base64Text = new QTextEdit();
    asciiText = new QTextEdit();
    utf8Text = new QTextEdit();
    utf16Text = new QTextEdit();

    binBlock = new TextBlock("Bin", binText);
    octBlock = new TextBlock("Oct", octText);
    decBlock = new TextBlock("Dec", decText);
    hexBlock = new TextBlock("Hex", hexText);
    base64Block = new TextBlock("Base64", base64Text);
    asciiBlock = new TextBlock("ASCII", asciiText);
    utf8Block = new TextBlock("UTF-8", utf8Text);
    utf16Block = new TextBlock("UTF-16", utf16Text);

    connect(binText, &QTextEdit::textChanged, this, &EncodingWidget::binChanged);
    connect(decText, &QTextEdit::textChanged, this, &EncodingWidget::decChanged);
    connect(octText, &QTextEdit::textChanged, this, &EncodingWidget::octChanged);
    connect(hexText, &QTextEdit::textChanged, this, &EncodingWidget::hexChanged);
    connect(base64Text, &QTextEdit::textChanged, this, &EncodingWidget::base64Changed);
    connect(utf8Text, &QTextEdit::textChanged, this, &EncodingWidget::utf8Changed);
    connect(utf16Text, &QTextEdit::textChanged, this, &EncodingWidget::utf16Changed);
    connect(asciiText, &QTextEdit::textChanged, this, &EncodingWidget::asciiChanged);

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(binBlock, 1);
    layout->addWidget(octBlock, 1);
    layout->addWidget(decBlock, 1);
    layout->addWidget(hexBlock, 1);
    layout->addWidget(base64Block, 1);
    layout->addWidget(asciiBlock, 1);
    layout->addWidget(utf8Block, 1);
    layout->addWidget(utf16Block, 1);
    this->setLayout(layout);
}

void EncodingWidget::binChanged() {
    updateTexts(mod.bytesFromBin(binText->toPlainText()), 2);
}

void EncodingWidget::octChanged() {
    updateTexts(mod.bytesFromOct(octText->toPlainText()), 8);
}

void EncodingWidget::hexChanged() {
    updateTexts(mod.bytesFromHex(hexText->toPlainText()), 16);
}

void EncodingWidget::decChanged() {
    updateTexts(mod.bytesFromDec(decText->toPlainText()), 10);
}

void EncodingWidget::asciiChanged() {
    updateTexts(mod.bytesFromASCII(asciiText->toPlainText()), 11);
}

void EncodingWidget::base64Changed() {
    updateTexts(mod.bytesFromBase64(base64Text->toPlainText()), 64);
}

void EncodingWidget::utf8Changed() {
    updateTexts(mod.bytesFromUTF8(utf8Text->toPlainText()), 18);
}

void EncodingWidget::utf16Changed() {
    updateTexts(mod.bytesFromUTF16(utf16Text->toPlainText()), 116);
}

void EncodingWidget::updateTexts(std::vector<unsigned char> input, int source) {
    QList<QTextEdit*> editors = {
        binText, octText, decText, hexText,
        base64Text, asciiText, utf8Text, utf16Text
    };

    // Block all signals
    for (auto editor : editors) editor->blockSignals(true);

    if (source != 2) binText->setText(mod.binFromBytes(input));
    if (source != 16) hexText->setText(mod.hexFromBytes(input));
    if (source != 10) decText->setText(mod.decFromBytes(input));
    if (source != 8) octText->setText(mod.octFromBytes(input));
    if (source != 11) asciiText->setText(mod.asciiFromBytes(input));
    if (source != 64) base64Text->setText(mod.base64FromBytes(input));
    if (source != 18) utf8Text->setText(mod.Utf8FromBytes(input));
    if (source != 116) utf16Text->setText(mod.Utf16FromBytes(input));

    // Unblock all signals
    for (auto editor : editors) editor->blockSignals(false);
}