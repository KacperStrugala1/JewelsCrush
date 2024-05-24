#include "mainwindow.h"
#include <cstdlib>
#include <ctime>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    centralWidget(new QWidget(this)),
    gridLayout(new QGridLayout(centralWidget)),
    selectedButton(-1)
{
    srand(time(nullptr));
    for (int i = 0; i < 100; ++i) {
        QPushButton *button = new QPushButton(this);
        button->setFixedSize(40, 40);
        int value = rand() % 5;  // 5 rodzajów "cukierków"
        buttonValues.append(value);
        buttons.append(button);
        gridLayout->addWidget(button, i / 10, i % 10);
    }

    for (int i = 0; i < 100; ++i) {
        connect(buttons[i], &QPushButton::clicked, [this, i]() { handleButtonClick(i); });
    }

    updateButtonColors();
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
}

void MainWindow::handleButtonClick(int id)
{
    if (selectedButton == -1) {
        selectedButton = id;
        buttons[id]->setStyleSheet("border: 2px solid yellow;");
    } else {
        swapButtons(selectedButton, id);
        selectedButton = -1;
        updateButtonColors();
        checkMatches();
    }
}

void MainWindow::swapButtons(int id1, int id2)
{
    if (abs(id1 / 10 - id2 / 10) + abs(id1 % 10 - id2 % 10) == 1) {
        std::swap(buttonValues[id1], buttonValues[id2]);
    }
}

void MainWindow::checkMatches()
{
    QVector<int> toRemove;
    for (int i = 0; i < 100; ++i) {
        int value = buttonValues[i];
        if (i % 10 < 8 && buttonValues[i+1] == value && buttonValues[i+2] == value) {
            toRemove << i << i+1 << i+2;
        }
        if (i / 10 < 8 && buttonValues[i+10] == value && buttonValues[i+20] == value) {
            toRemove << i << i+10 << i+20;
        }
    }
    if (!toRemove.isEmpty()) {
        for (int index : toRemove) {
            buttonValues[index] = -1;
        }
        removeMatches();
    }
}

void MainWindow::removeMatches()
{
    for (int col = 0; col < 10; ++col) {
        for (int row = 9; row >= 0; --row) {
            if (buttonValues[row * 10 + col] == -1) {
                for (int k = row; k > 0; --k) {
                    buttonValues[k * 10 + col] = buttonValues[(k - 1) * 10 + col];
                }
                buttonValues[col] = rand() % 5;
            }
        }
    }
    updateButtonColors();
}

void MainWindow::updateButtonColors()
{
    for (int i = 0; i < 100; ++i) {
        QColor color = getColorForValue(buttonValues[i]);
        buttons[i]->setStyleSheet(QString("background-color: %1;").arg(color.name()));
        if (selectedButton != i) {
            buttons[i]->setStyleSheet(QString("background-color: %1;").arg(color.name()));
        }
    }
}

QColor MainWindow::getColorForValue(int value)
{
    switch (value) {
    case 0: return QColor(Qt::red);
    case 1: return QColor(Qt::green);
    case 2: return QColor(Qt::blue);
    case 3: return QColor(Qt::yellow);
    case 4: return QColor(Qt::magenta);
    default: return QColor(Qt::white);
    }
}
