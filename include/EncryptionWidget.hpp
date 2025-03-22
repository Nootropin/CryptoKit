#ifndef ENCRYPTION_WIDGET_HPP
#define ENCRYPTION_WIDGET_HPP

#include <QWidget>
#include <QSlider>
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
#include "MyWidget.hpp"
class MyMainWindow;
class EncryptionWidget : public MyWidget {
    Q_OBJECT
public:
    EncryptionWidget(MyMainWindow* parent, EncryptionWidgetDataModel model);
    ~EncryptionWidget(){};
    virtual void setInputText(const QString& input) override;
    virtual void setOutputText(const QString& input) override {};
    virtual QString getInputText() const override {};
    virtual QString getOutputText() const override ;
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
