#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class MainWindow: public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget* parent=nullptr);
        ~MainWindow();
    
    private:
        QWidget* m_central_widget;
        QVBoxLayout* m_layout;
        QPushButton* button_calcul;
        QLabel* start_label;
    
    private slots:
        void update_start_label();
    
    signals:
        void label_updated();
    
};

#endif