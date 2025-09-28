#ifndef MAINWINDOW_HH
#define MAINWINDOW_H
#include "QMainWindow"
#include "QWidget"
#include "QPushButton"
#include "QVBoxLayout"
#include "QLabel"

class MainWindow: public QMainWindow
{

    public:
        MainWindow(QWidget* parent=nullptr);
        ~MainWindow();
    
    private:
        QWidget* m_central_widget;
        QVBoxLayout* m_layout;
        QPushButton* button_calcul;
        QLabel* start_label;
};

#endif