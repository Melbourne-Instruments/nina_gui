/**
 *-----------------------------------------------------------------------------
 * Copyright (c) 2022 Melbourne Instruments, Australia
 *-----------------------------------------------------------------------------
 * @file  spi_monitor_thread.h
 * @brief SPI Monitor Thread class definitions.
 *-----------------------------------------------------------------------------
 */
#ifndef SPI_MONITOR_THREAD_H
#define SPI_MONITOR_THREAD_H

#include <atomic>
#include <QThread>
#include "common.h"

// SPI Monitor Thread class
class SpiMonitorThread : public QThread
{
	Q_OBJECT
public:
    SpiMonitorThread(QObject *parent);
    ~SpiMonitorThread();
    void run();

signals:
    void spi_status_msg(uint count);

private:
    std::atomic<bool> _exit_thread;
};

#endif
