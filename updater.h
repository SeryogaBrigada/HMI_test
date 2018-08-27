#ifndef UPDATER_H
#define UPDATER_H

#include <QMutex>
#include <QThread>
#include <QQueue>

#include <aktualizr/src/libaktualizr/primary/aktualizr.h>

namespace bpo = boost::program_options;

class Updater : public QThread
{
    Q_OBJECT
public:
    explicit Updater(QObject *parent = nullptr);
    ~Updater() Q_DECL_OVERRIDE;

private:
    void run() Q_DECL_OVERRIDE;
    void signalHandler(const std::shared_ptr<event::BaseEvent> &event);

    bpo::variables_map parse_options(const std::vector<std::string> &vector);

    std::unique_ptr<Aktualizr> m_akt;
    std::vector<Uptane::Target> m_updates;

    QMutex m_mutex;
    bool m_quit = false;

    enum class Commands
    {
        CheckUpdates,
        DownloadUpdates,
        InstallUpdates
    };

    QQueue<Commands> m_Commands;

signals:
    void updatesAvailable(const QString &updates, const QString &size);
    void downloadProgress(qreal value);
    void downloadComplete();
    void installComplete();

public slots:
    void downloadUpdates();
    void installUpdates();
};

#endif // UPDATER_H
