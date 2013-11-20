#include "MainWindow.hpp"
#include "Worker.hpp"
#include "ui_MainWindow.h"
#include "Worker.hpp"
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*m_pThread = new QThread();
    m_pWorker = new CWorker();

    m_pWorker->moveToThread(m_pThread);

    //connect(m_pWorker, SIGNAL(valueChanged(QString)), ui->label, SLOT(setText(QString)));
    connect(m_pWorker, SIGNAL(workRequested()), m_pThread, SLOT(start()));
    connect(m_pThread, SIGNAL(started()), m_pWorker, SLOT(doWork()));
    connect(m_pWorker, SIGNAL(finished()), m_pThread, SLOT(quit()), Qt::DirectConnection);
*/
}

MainWindow::~MainWindow()
{
  /*  m_pWorker->abort();
    m_pThread->quit();

    delete m_pThread;
    delete m_pWorker;*/

    delete ui;
}

/*
void MainWindow::setComponentList(int nCount, char *pComponentList[])
{
    for (int idx = 0; idx < nCount; idx++)
    {
        this->ui->menuAdd_Component->addMenu(pComponentList[idx]);
    }
}*/

void MainWindow::addComponentToList(char *pComponent)
{
    QString qstrComp(pComponent);

    this->ui->menuAdd_Component->addMenu(qstrComp);
}

