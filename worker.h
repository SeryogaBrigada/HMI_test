#ifndef WORKER_H
#define WORKER_H

#include <QObject>

#include <aktualizr/src/libaktualizr/primary/aktualizr.h>
#include <memory>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);
    ~Worker() Q_DECL_OVERRIDE;

private:
    std::unique_ptr<Aktualizr> m_akt;
    void signalHandler(std::shared_ptr<event::BaseEvent> event);

signals:
    void updateAvailable();

public slots:
    void doWork();
};

#endif // WORKER_H
