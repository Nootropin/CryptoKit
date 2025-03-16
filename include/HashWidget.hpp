#ifndef HASH_WIDGET_HPP
#define HASH_WIDGET_HPP

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QMenu>
#include <iostream>
#include <QFileDialog>
#include <QDir>
#include <fstream>
#include "HashWindowDataModel.hpp"
#include "Gui.hpp"
#include "RainbowButton.hpp"
class MyMainWindow;
class HashWidget : public QWidget {
    Q_OBJECT

public:
    HashWidget(MyMainWindow* parent, HashWindowDataModel model);
    ~HashWidget(){};
private:
    HashWindowDataModel model;
    MyMainWindow* parentWindow;
    QTextEdit* textBlock;
    QTextEdit* resultBlock;
    RainbowButton* convertButt;
    RainbowButton* openFileButt;
    QAction* rainbowTick;
    QAction* themeSwap;
    QMenu* hashMenu;
public slots:
    void changeHash(int i);
private slots:
    void convertButton();
    void openFileButton();
    void rainbowSwaping();
    void themeSwaping();
};

#endif // HASH_WIDGET_HPP
