#include "worker.h"

Worker::Worker(QObject *parent) : QObject(parent)
{
}

Worker::~Worker()
{
    m_akt->Shutdown();
    std::cerr << "~Worker()" << std::endl;
}

void Worker::signalHandler(std::shared_ptr<event::BaseEvent> event)
{  
    if ("UpdateAvailable" == event->variant)
    {
        emit updateAvailable();
    }
}

void Worker::doWork()
{
    Config m_config("/home/intel/OTA-HMI/HMI_test/aktualizr/config/sota_local.toml");
    m_akt = std::unique_ptr<Aktualizr>(new Aktualizr(m_config));
    std::function<void(std::shared_ptr<event::BaseEvent>)> m_handler =
            std::bind(&Worker::signalHandler, this, std::placeholders::_1);
    m_akt->SetSignalHandler(m_handler);
//    m_akt->Run();
    m_akt->FetchMetadata();
    m_akt->CheckUpdates();
}
