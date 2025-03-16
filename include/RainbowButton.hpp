#ifndef RAINBOW_BUTTON_HPP
#define RAINBOW_BUTTON_HPP

#include <QPushButton>
#include <QTimer>

class RainbowButton : public QPushButton {
    Q_OBJECT

public:
    RainbowButton(QString text, QWidget* parent = nullptr);
    ~RainbowButton(){}
    void swapRainbow();
    static void swapMode();

private slots:
    void updateGradient();

private:
    static bool rainbowOn;
    int hueShift;
};

#endif // RAINBOW_BUTTON_HPP