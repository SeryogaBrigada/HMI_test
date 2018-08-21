#include <QCoreApplication>
#include <QCommandLineParser>

#include "worker.h"


Worker::Worker(QObject *parent) : QThread(parent)
{
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::translate("worker", "Aktualizr HMI GUI"));
    parser.addPositionalArgument("path", QCoreApplication::translate("worker", "Configuration file path"));
    parser.addVersionOption();
    parser.addHelpOption();

    QCommandLineOption configPath(QStringList() << "c" << "config",
                                  QCoreApplication::translate("worker", "Configuration file path"));
    parser.addOption(configPath);
    parser.process(QCoreApplication::arguments());

    if (parser.isSet(configPath))
        m_confPath = parser.positionalArguments().first();
}

Worker::~Worker()
{
    m_akt->Shutdown();
    wait();
}

void Worker::run()
{
    Config m_config(m_confPath.toStdString());
    m_config.uptane.running_mode = RunningMode::kManual;

    m_akt = std::unique_ptr<Aktualizr>(new Aktualizr(m_config));

    std::function<void(std::shared_ptr<event::BaseEvent>)> m_handler =
            std::bind(&Worker::signalHandler, this, std::placeholders::_1);

    m_akt->SetSignalHandler(m_handler);
    m_akt->Run();
}

void Worker::signalHandler(const std::shared_ptr<event::BaseEvent> &event)
{
    if ("UpdateAvailable" == event->variant)
    {
        m_updates = dynamic_cast<event::UpdateAvailable *>(event.get())->updates;

        auto caclSize = [=](int64_t size) {
            QString prefix;
            double d_size{};

            if (size < 1000) {
                prefix = " B";
                d_size = size;
            }
            else if (size < 1000000) {
                prefix = " KB";
                d_size = size / 1000.0;
            }
            else if (size < 1000000000) {
                prefix = " MB";
                d_size = size / 1000000.0;
            }
            else {
                prefix = " GB";
                d_size = size / 1000000000.0;
            }

            return m_locale.toString(d_size, 'f', 2) + prefix;
        };

        QString updateInfo;
        int64_t totalSize{};

        for (const auto &u : m_updates) {
            updateInfo.append(QString("%1 \t\t %2\n").arg(QString::fromStdString(u.filename()))
                              .arg(caclSize(u.length())));
            totalSize += u.length();
        }

        emit updatesAvailable(updateInfo, caclSize(totalSize));
    }
    else if ("DownloadProgressReport" == event->variant)
    {
        unsigned int m_progress = dynamic_cast<event::DownloadProgressReport *>(event.get())->progress;
        emit downloadProgress(static_cast<int>(m_progress));
    }
    else if ("DownloadComplete" == event->variant)
    {
        emit downloadComplete();
    }
    else if ("InstallComplete" == event->variant)
    {
        m_updates.clear();
        m_akt->FetchMetadata();

        emit installComplete();
    }
}

void Worker::checkUpdates()
{
    m_akt->FetchMetadata();
}

void Worker::downloadUpdates()
{
    m_akt->Download(m_updates);
}

void Worker::installUpdates()
{
    m_akt->Install(m_updates);
}
