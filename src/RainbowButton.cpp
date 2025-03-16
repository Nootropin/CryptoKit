#include "RainbowButton.hpp"

// Initialize static member
bool RainbowButton::rainbowOn = false;

RainbowButton::RainbowButton(QString text, QWidget* parent)
    : QPushButton(text, parent), hueShift(0) {
    setStyleSheet("QPushButton { color: white; font-size: 16px; padding: 8px 16px; border-radius: 10px; }");

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &RainbowButton::updateGradient);
    timer->start(10); // Update every 10ms
}

void RainbowButton::swapRainbow() {
    rainbowOn = !rainbowOn;
    setStyleSheet(R"(
        QPushButton {
            background-color: #3A3A3A; /* Dark Gray */
            border: 1px solid #555;
            border-radius: 10px;
            padding: 10px;
            font-size: 16px;
            color: white;
        }
        QPushButton:hover {
            background-color: #4A4A4A;
        }
        QPushButton:pressed {
            background-color: #555555;
        }
    )");
}

void RainbowButton::swapMode() {
    rainbowOn = !rainbowOn;
}

void RainbowButton::updateGradient() {
    // Create a dynamic linear gradient with shifting colors
    if (rainbowOn) {
        QString gradient = QString(
            "QPushButton {"
            "    border-radius: 10px;"
            "    padding: 8px 16px;"
            "    font-size: 16px;"
            "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0, "
            "        stop:0 %1, stop:0.25 %2, stop:0.5 %3, stop:0.75 %4, stop:1 %5);"
            "    color: white;"
            "}"
        ).arg(QColor::fromHsv((hueShift + 0) % 360, 255, 255).name())
         .arg(QColor::fromHsv((hueShift + 72) % 360, 255, 255).name())
         .arg(QColor::fromHsv((hueShift + 144) % 360, 255, 255).name())
         .arg(QColor::fromHsv((hueShift + 216) % 360, 255, 255).name())
         .arg(QColor::fromHsv((hueShift + 288) % 360, 255, 255).name());

        setStyleSheet(gradient);

        hueShift = (hueShift + 5) % 360; // Shift hue to animate the gradient
    } else {
        setStyleSheet(R"(
            QPushButton {
                background-color: #3A3A3A; /* Dark Gray */
                border: 1px solid #555;
                border-radius: 10px;
                padding: 10px;
                font-size: 16px;
                color: white;
            }
            QPushButton:hover {
                background-color: #4A4A4A;
            }
            QPushButton:pressed {
                background-color: #555555;
            }
        )");
    }
}