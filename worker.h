#ifndef WORKER_H
#define WORKER_H

#include <QLocale>
#include <QThread>

#include <aktualizr/src/libaktualizr/primary/aktualizr.h>

class Worker : public QThread
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);
    ~Worker() Q_DECL_OVERRIDE;

private:
    void run() Q_DECL_OVERRIDE;
    void signalHandler(const std::shared_ptr<event::BaseEvent> &event);

    std::unique_ptr<Aktualizr> m_akt;
    std::vector<Uptane::Target> m_updates;

    QLocale m_locale;
    QString m_confPath;

signals:
    void updatesAvailable(const QString &updates, const QString &size);
    void downloadProgress(int value);
    void downloadComplete();
    void installComplete();

public slots:
    void checkUpdates();
    void downloadUpdates();
    void installUpdates();
};

#endif // WORKER_H
