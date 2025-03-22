#ifndef GUI_HPP
#define GUI_HPP

#include "HashBase.hpp"
#include "HashWindowDataModel.hpp"
#include "EncryptionWidgetDataModel.hpp"
#include "EncryptionBase.hpp"
#include "RainbowButton.hpp"
#include <QtWidgets>
#include <QObject>
#include <QVBoxLayout>
#include <iostream>
#include <QHBoxLayout>
#include <QTextBlock>
#include <sstream>
#include <iomanip>
#include <QMainWindow>
#include "EncodingWidget.hpp"
#include <QStackedWidget>
#include <QMenuBar>
#include <fstream>
class HashWidget;
class EncryptionWidget;
class MyMainWindow : public QMainWindow {
    Q_OBJECT
public:
    MyMainWindow(QWidget* parent, HashWindowDataModel model, EncryptionWidgetDataModel encryptModel, EncodingWidgetDataModel encodModel);
    ~MyMainWindow(){};
private:
    void initMenus();
    void initStackedWidget();
    void makeFilesButtonsInactive();
    void makeFilesButtonsActive();
private slots:
    void rainbowSwaping();
    void openHash(int counter);
    void openEncryption(int counter);
    void openEncoding();
    void swapSpaces();
    void openFile();
    void saveFile();
private:
    QMenu* fileMenu;
    QStackedWidget* stackedWidget;
    HashWindowDataModel hashingModel;
    EncryptionWidgetDataModel encryptionModel;
    EncodingWidgetDataModel encodingModel;
    HashWidget* hashWidget;
    EncryptionWidget* encryptionWidget;
    EncodingWidget* encoding;
};

#endif // GUI_HPP
