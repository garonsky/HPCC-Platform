#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QThread>
#include "Worker.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    void addComponentToList(char *pComponent);
    void addServiceToList(char *pService);

private:
    Ui::MainWindow *ui;

//    QThread *m_pThread;
//    CWorker *m_pWorker;

private slots:
//    void on_componentListUpdated();
    void on_actionOpen_triggered();
};

#endif // MAINWINDOW_HPP
