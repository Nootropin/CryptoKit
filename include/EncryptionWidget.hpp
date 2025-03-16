#ifndef ENCRYPTION_WIDGET_HPP
#define ENCRYPTION_WIDGET_HPP

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QMenu>
#include <iostream>
#include <QFileDialog>
#include <QDir>
#include <fstream>
#include "EncryptionWidgetDataModel.hpp"
#include "RainbowButton.hpp"
class MyMainWindow;
class EncryptionWidget : public QWidget {
    Q_OBJECT
public:
    EncryptionWidget(MyMainWindow* parent, EncryptionWidgetDataModel model);
    ~EncryptionWidget(){};
private:
    EncryptionWidgetDataModel model;
    MyMainWindow* parentWindow;
    QTextEdit* textBlock;
    QTextEdit* resultBlock;
    QTextEdit* passwordInput;
    RainbowButton* encryptButt;
    RainbowButton* decryptButt;
    RainbowButton* openFileButt;
    QAction* rainbowTick;
    QAction* themeSwap;
    QMenu* encryptionMenu;
public slots:
    void changeEncryption(int i);
private slots:
    void encrypt();
    void decrypt();
    void openFileButton();
};

#endif // ENCRYPTION_WIDGET_HPP
