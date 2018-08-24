#ifndef PROVIDER_H
#define PROVIDER_H

#include <QObject>
#include <QThread>
#include <QTimer>

#include "updater.h"

class Provider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal   downloadProgress READ downloadProgress NOTIFY downloadProgressChanged)
    Q_PROPERTY(QString updates READ updates NOTIFY updatesChanged)
    Q_PROPERTY(QString updateSize READ updateSize NOTIFY updateSizeChanged)

public:
    explicit Provider(QObject *parent = nullptr);

    qreal   downloadProgress() const;
    QString updates() const;
    QString updateSize() const;

private:
    Updater m_updater;
    QString m_updates;
    QString m_updateSize;
    qreal   m_downloadProgress;
    QTimer  *m_checkUpdateTimer = nullptr;

signals:
    void download();
    void install();
    void updateAvailable();
    void noUpdates();
    void downloadComplete();
    void installationComplete();

    void downloadProgressChanged();
    void updatesChanged();
    void updateSizeChanged();

public slots:
    void downloadUpdates();
    void installUpdates();

    void updatesAvailableSlot(const QString &updates, const QString &size);
    void downloadProgressSlot(qreal value);
    void downloadCompleteSlot();
    void installCompleteSlot();
};

#endif // PROVIDER_H
