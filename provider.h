#ifndef PROVIDER_H
#define PROVIDER_H

#include <QObject>
#include <QThread>
#include <QTimer>

#include "worker.h"

class Provider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int downloadProgress READ downloadProgress NOTIFY downloadProgressChanged)
    Q_PROPERTY(QString updates READ updates NOTIFY updatesChanged)
    Q_PROPERTY(QString updateSize READ updateSize NOTIFY updateSizeChanged)

public:
    explicit Provider(QObject *parent = nullptr);

    int downloadProgress() const;
    QString updates() const;
    QString updateSize() const;

private:
    Worker m_worker;
    int m_downloadProgress;
    QString m_updates;
    QString m_updateSize;
    QTimer *m_timer = nullptr;

signals:
    void download();
    void install();
    void updateAvailable();
    void downloadComplete();

    void downloadProgressChanged();
    void updatesChanged();
    void updateSizeChanged();
    void installationComplete();

public slots:
    void downloadUpdates();
    void installUpdates();

    void updatesAvailableSlot(const QString &updates, const QString &size);
    void downloadProgressSlot(int value);
    void downloadCompleteSlot();
    void installCompleteSlot();
};

#endif // PROVIDER_H
