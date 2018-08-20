#include "provider.h"
#include "worker.h"

Provider::Provider(QObject *parent) : QObject(parent)
{
    Worker *m_worker = new Worker;
    m_worker->moveToThread(&m_workerThread);
    connect(&m_workerThread, &QThread::finished, m_worker, &Worker::deleteLater);
    connect(m_worker, &Worker::updateAvailable, this, &Provider::updateAvailableSlot);
    connect(&m_workerThread, &QThread::started, m_worker, &Worker::doWork);
    m_workerThread.start();
}

Provider::~Provider()
{
    m_workerThread.quit();
    m_workerThread.wait();
    std::cerr << "~Provider()" << std::endl;
}

void Provider::updateAvailableSlot()
{
    emit updateAvailable();
}
