#include "provider.h"

Provider::Provider(QObject *parent) : QObject(parent),
    m_downloadProgress(0)
{
    connect(&m_updater, &Updater::updatesAvailable, this, &Provider::updatesAvailableSlot);
    connect(&m_updater, &Updater::downloadProgress, this, &Provider::downloadProgressSlot);
    connect(&m_updater, &Updater::downloadComplete, this, &Provider::downloadCompleteSlot);
    connect(&m_updater, &Updater::installComplete, this, &Provider::installCompleteSlot);

    connect(this, &Provider::download, &m_updater, &Updater::downloadUpdates);
    connect(this, &Provider::install, &m_updater, &Updater::installUpdates);

    QTimer *m_timer = new QTimer(this);
    m_timer->setSingleShot(true);

    connect(m_timer, &QTimer::timeout, &m_updater, &Updater::checkUpdates);

    m_updater.start();
    m_timer->start(50);

    m_checkUpdateTimer = new QTimer(this);
    m_checkUpdateTimer->setSingleShot(true);

    connect(m_checkUpdateTimer, &QTimer::timeout, [this](){
        emit noUpdates();
    });

    m_checkUpdateTimer->start(5000);
}


double Provider::downloadProgress() const
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
    emit download();
}

void Provider::installUpdates()
{
    emit install();
}

void Provider::updatesAvailableSlot(const QString &updates, const QString &size)
{
    m_checkUpdateTimer->stop();

    m_updates    = updates;
    m_updateSize = size;
    emit updatesChanged();
    emit updateSizeChanged();

    emit updateAvailable();
}

void Provider::downloadProgressSlot(double value)
{
    if (!qFuzzyCompare(m_downloadProgress, value))
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
