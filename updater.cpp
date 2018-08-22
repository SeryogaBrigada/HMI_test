#include <QCoreApplication>

#include "aktualizr/src/libaktualizr/uptane/secondaryfactory.h"
#include "updater.h"

Updater::Updater(QObject *parent) : QThread(parent)
{
    auto m_args = QCoreApplication::arguments();

    if (!m_args.isEmpty()) {
        std::vector<std::string> m_list;

        for (auto it = m_args.cbegin() + 1; it != m_args.cend(); it++)
            m_list.push_back(it->toStdString());

        m_Map = parse_options(m_list);
    }
}

Updater::~Updater()
{
    m_akt->Shutdown();
    wait();
}

void Updater::run()
{
    Config m_config(m_Map);
    m_config.uptane.running_mode = RunningMode::kManual;

    m_akt = std::unique_ptr<Aktualizr>(new Aktualizr(m_config));

    if (m_Map.count("secondary")) {
        auto sconfigs = m_Map["secondary"].as<std::vector<boost::filesystem::path>>();

        for (const auto &sconf : sconfigs)
            m_akt->AddSecondary(Uptane::SecondaryFactory::makeSecondary(sconf));
    }

    std::function<void(std::shared_ptr<event::BaseEvent>)> m_handler =
            std::bind(&Updater::signalHandler, this, std::placeholders::_1);

    m_akt->SetSignalHandler(m_handler);
    m_akt->Run();
}

void Updater::signalHandler(const std::shared_ptr<event::BaseEvent> &event)
{
    static unsigned long m_totalUpdatesCount{};
    static unsigned long m_downloadComplete{};

    if ("UpdateAvailable" == event->variant)
    {
        m_updates = static_cast<event::UpdateAvailable *>(event.get())->updates;
        m_totalUpdatesCount = m_updates.size();

        auto caclSize = [=](int64_t size) {
            QString prefix;
            double d_size{};

            if (size < 1000) {
                prefix = QStringLiteral(" B");
                d_size = size;
            }
            else if (size < 1000000) {
                prefix = QStringLiteral(" KB");
                d_size = size / 1000.0;
            }
            else if (size < 1000000000) {
                prefix = QStringLiteral(" MB");
                d_size = size / 1000000.0;
            }
            else {
                prefix = QStringLiteral(" GB");
                d_size = size / 1000000000.0;
            }

            return m_locale.toString(d_size, 'f', 2) + prefix;
        };

        QString updateInfo;
        int64_t totalSize{};

        for (const auto &u : m_updates) {
            updateInfo.append(QString("%1 \t\t %2\n")
                              .arg(QString::fromStdString(u.filename()))
                              .arg(caclSize(u.length())));
            totalSize += u.length();
        }

        emit updatesAvailable(updateInfo, caclSize(totalSize));
    }
    else if ("DownloadProgressReport" == event->variant)
    {
        unsigned int m_progress = static_cast<event::DownloadProgressReport *>(event.get())->progress;

        Q_ASSERT(m_totalUpdatesCount != 0);
        emit downloadProgress(static_cast<double>(m_progress) / (m_totalUpdatesCount - m_downloadComplete));
    }
    else if ("DownloadComplete" == event->variant)
    {
        m_downloadComplete++;

        if (m_downloadComplete == m_totalUpdatesCount) {
            m_downloadComplete = 0;

            emit downloadComplete();
        }
    }
    else if ("InstallComplete" == event->variant)
    {
        m_totalUpdatesCount = 0;
        m_updates.clear();
        m_akt->FetchMetadata();

        emit installComplete();
    }
}

void Updater::checkUpdates()
{
    m_akt->FetchMetadata();
}

void Updater::downloadUpdates()
{
    m_akt->Download(m_updates);
}

void Updater::installUpdates()
{
    m_akt->Install(m_updates);
}


bpo::variables_map Updater::parse_options(const std::vector<std::string> &vector) {
    bpo::options_description description("QML GUI for libaktualizr");
    // clang-format off
    // Try to keep these options in the same order as Config::updateFromCommandLine().
    // The first three are commandline only.
    description.add_options()
            ("help,h", "print usage")
            ("version,v", "Current version")
            ("config,c", bpo::value<std::vector<boost::filesystem::path> >()->composing(), "configuration file or directory")
            ("secondary", bpo::value<std::vector<boost::filesystem::path> >()->composing(), "secondary ECU json configuration file")
            ("loglevel", bpo::value<int>(), "set log level 0-5 (trace, debug, info, warning, error, fatal)");
    // clang-format on

    bpo::variables_map vm;
    std::vector<std::string> unregistered_options;
    try {
        bpo::basic_parsed_options<char> parsed_options =
                bpo::command_line_parser(vector).options(description).run();
        bpo::store(parsed_options, vm);
        bpo::notify(vm);
        unregistered_options = bpo::collect_unrecognized(parsed_options.options, bpo::include_positional);
        if (vm.count("help") == 0 && !unregistered_options.empty()) {
            std::cout << description << "\n";
            exit(EXIT_FAILURE);
        }
    } catch (const bpo::required_option &ex) {
        // print the error and append the default commandline option description
        std::cout << ex.what() << std::endl << description;
        exit(EXIT_FAILURE);
    } catch (const bpo::error &ex) {

        // log boost error
        LOG_ERROR << "boost command line option error: " << ex.what();

        // print the error message to the standard output too, as the user provided
        // a non-supported commandline option
        std::cout << ex.what() << '\n';

        // set the returnValue, thereby ctest will recognize
        // that something went wrong
        exit(EXIT_FAILURE);
    }

    return vm;
}
