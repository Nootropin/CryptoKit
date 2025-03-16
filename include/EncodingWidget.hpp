/**
 * @file EncodingWidget.hpp
 * @brief Implements widget, that will show different encodings
 */

#ifndef ENCODING_WIDGET_HPP
#define ENCODING_WIDGET_HPP

#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QHBoxLayout>
#include "EncodingWidgetDataModel.hpp"

class TextBlock : public QWidget {
    Q_OBJECT
public:
    TextBlock(QString name, QTextEdit* text);

public:
    QLabel* label;
    QTextEdit* text;
};

class EncodingWidget : public QWidget {
    Q_OBJECT

public:
    EncodingWidget(EncodingWidgetDataModel mod);
    EncodingWidget() {};
    ~EncodingWidget() {};

public:
    EncodingWidgetDataModel mod;

    void binChanged();
    void octChanged();
    void hexChanged();
    void decChanged();
    void asciiChanged();
    void base64Changed();
    void utf8Changed();
    void utf16Changed();
    void updateTexts(std::vector<unsigned char> input, int source);

    QTextEdit* binText;
    TextBlock* binBlock;
    QTextEdit* octText;
    TextBlock* octBlock;
    QTextEdit* decText;
    TextBlock* decBlock;
    QTextEdit* hexText;
    TextBlock* hexBlock;
    QTextEdit* base64Text;
    TextBlock* base64Block;
    QTextEdit* asciiText;
    TextBlock* asciiBlock;
    QTextEdit* utf8Text;
    TextBlock* utf8Block;
    QTextEdit* utf16Text;
    TextBlock* utf16Block;
};

#endif // ENCODING_WIDGET_HPP