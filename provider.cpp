#include "provider.h"


Provider::Provider(QObject *parent) : QObject(parent),
    m_downloadProgress(0)
{
    connect(&m_worker, &Worker::updatesAvailable, this, &Provider::updatesAvailableSlot);
    connect(&m_worker, &Worker::downloadProgress, this, &Provider::downloadProgressSlot);
    connect(&m_worker, &Worker::downloadComplete, this, &Provider::downloadCompleteSlot);
    connect(&m_worker, &Worker::installComplete, this, &Provider::installCompleteSlot);

    connect(this, &Provider::download, &m_worker, &Worker::downloadUpdates);
    connect(this, &Provider::install, &m_worker, &Worker::installUpdates);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, &m_worker, &Worker::checkUpdates);
    connect(m_timer, &QTimer::timeout, [=](){
        m_timer->start(10000);
    });

    m_worker.start();
    m_timer->start(50);
}

int Provider::downloadProgress() const
{
    return m_downloadProgress;
}

QString Provider::updates() const
{
    return m_updates;
}

QString Provider::updateSize() const
{
    return m_updateSize;
}

void Provider::downloadUpdates()
{
    m_timer->stop();
    emit download();
}

void Provider::installUpdates()
{
    emit install();
}

void Provider::updatesAvailableSlot(const QString &updates, const QString &size)
{
    m_updates = updates;
    m_updateSize = size;
    emit updatesChanged();
    emit updateSizeChanged();

    emit updateAvailable();
}

void Provider::downloadProgressSlot(int value)
{
    if (m_downloadProgress != value)
    {
        m_downloadProgress = value;
        emit downloadProgressChanged();
    }
}

void Provider::downloadCompleteSlot()
{
    m_downloadProgress = 0;
    emit downloadProgressChanged();
    emit downloadComplete();
}

void Provider::installCompleteSlot()
{
    emit installationComplete();
}
