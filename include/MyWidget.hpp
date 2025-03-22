#ifndef MY_WIDGET_HPP
#define MY_WIDGET_HPP
#include <QWidget>
class MyWidget : public QWidget{
    public:
        MyWidget(QWidget* parent) : QWidget(parent) {}
        virtual void setInputText(const QString& input) = 0;
        virtual QString getInputText() const = 0;
        virtual void setOutputText(const QString& input)  = 0;
        virtual QString getOutputText() const = 0;
};
#endif