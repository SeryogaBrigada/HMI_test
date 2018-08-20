#ifndef PROVIDER_H
#define PROVIDER_H

#include <QObject>
#include <QThread>

class Provider : public QObject
{
    Q_OBJECT
public:
    explicit Provider(QObject *parent = nullptr);
    ~Provider() Q_DECL_OVERRIDE;

private:
    QThread m_workerThread;

signals:
    void updateAvailable();

public slots:
    void updateAvailableSlot();
};

#endif // PROVIDER_H
