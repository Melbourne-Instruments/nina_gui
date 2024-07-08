/**
 *-----------------------------------------------------------------------------
 * Copyright (c) 2022-2023 Melbourne Instruments, Australia
 *-----------------------------------------------------------------------------
 * @file  spi_monitor_thread.cpp
 * @brief SPI Monitor Thread class implementation.
 *-----------------------------------------------------------------------------
 */
#include <cstring>
#include <fstream>
#include <thread>
#include "spi_monitor_thread.h"
#include "common.h"

// Constants
constexpr auto POLL_TIMEOUT = 100;


//----------------------------------------------------------------------------
// SpiMonitorThread
//----------------------------------------------------------------------------
SpiMonitorThread::SpiMonitorThread(QObject *parent) : QThread(parent)
{
    // Initialise class variables
    _exit_thread = false;
}

SpiMonitorThread::~SpiMonitorThread()
{
    // Stop the thread
    _exit_thread = true;
    wait();
}

void SpiMonitorThread::run()
{
    int file_size = -1;
    uint count = 0;
    while (!_exit_thread)
    {
        std::ifstream f("/udata/spi.log", std::ifstream::ate);
        int size = f.tellg();
        if (file_size == -1)
        {
            if (size != -1)
            {
                file_size = size;
            }
        }
        else
        {
            if (size != file_size)
            {
                count++;
                emit spi_status_msg(count);
                file_size = size;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(POLL_TIMEOUT));
    }

    // Thread exited
    DEBUG_MSG("SpiMonitorThread: thread: EXIT");
}
