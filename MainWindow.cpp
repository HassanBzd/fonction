#include "MainWindow.h"
#include <iostream>
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
    , m_central_widget(nullptr)
    , m_layout(nullptr)
    , start_label(nullptr)
    , button_calcul(nullptr)
{
    m_central_widget = new QWidget(this);
    setCentralWidget(m_central_widget);
    m_layout = new QVBoxLayout(m_central_widget);
    button_calcul = new QPushButton("Calcul",this);
    start_label = new QLabel("HelloWorld", this);
    m_layout->addWidget(start_label);
    m_layout->addWidget(button_calcul);
    QObject::connect(button_calcul, &QPushButton::clicked,this, &MainWindow::update_start_label);

}


void MainWindow::update_start_label(){
    start_label->setText("Ok");
}

MainWindow::~MainWindow(){

}