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

    m_updater.start();

    m_checkUpdateTimer = new QTimer(this);
    m_checkUpdateTimer->setSingleShot(true);

    connect(m_checkUpdateTimer, &QTimer::timeout, [this](){
        emit noUpdates();
    });

    m_checkUpdateTimer->start(8000);
}

QString Provider::remainingDownloadTime() const {
  if (qFuzzyCompare(m_downloadProgress, 0.0)) return "0:00";

  QTime t(0, 0, 0, 0);
  t = t.addMSecs(static_cast<int>(downloadTime_.elapsed() * 100 / m_downloadProgress));
  return t.toString("m:ss");
}

qreal Provider::downloadProgress() const
{
    return std::round(m_downloadProgress * 10.0) / 10.0;
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
    downloadTime_.start();
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

void Provider::downloadProgressSlot(qreal value)
{
    if (!qFuzzyCompare(m_downloadProgress, value))
    {
        m_downloadProgress = value;
        emit downloadProgressChanged();
        emit remainingDownloadTimeChanged();
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
