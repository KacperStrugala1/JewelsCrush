#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QVector>
#include <QColor>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleButtonClick(int id);

private:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVector<QPushButton*> buttons;
    QVector<int> buttonValues;
    int selectedButton;
    void swapButtons(int id1, int id2);
    void checkMatches();
    void removeMatches();
    void updateButtonColors();
    QColor getColorForValue(int value);
};

#endif // MAINWINDOW_H
