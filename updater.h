#ifndef UPDATER_H
#define UPDATER_H

#include <QLocale>
#include <QThread>

#include <aktualizr/src/libaktualizr/primary/aktualizr.h>

class Updater : public QThread
{
    Q_OBJECT
public:
    explicit Updater(QObject *parent = nullptr);
    ~Updater() Q_DECL_OVERRIDE;

private:
    void run() Q_DECL_OVERRIDE;
    void signalHandler(const std::shared_ptr<event::BaseEvent> &event);

    std::unique_ptr<Aktualizr> m_akt;
    std::vector<Uptane::Target> m_updates;

    boost::program_options::variables_map m_Map;

    QLocale m_locale;

signals:
    void updatesAvailable(const QString &updates, const QString &size);
    void downloadProgress(double value);
    void downloadComplete();
    void installComplete();

public slots:
    void checkUpdates();
    void downloadUpdates();
    void installUpdates();
};

#endif // UPDATER_H
