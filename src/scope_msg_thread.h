/**
 *-----------------------------------------------------------------------------
 * Copyright (c) 2023 Melbourne Instruments, Australia
 *-----------------------------------------------------------------------------
 * @file  scope_msg_thread.h
 * @brief Scope Message Thread class definitions.
 *-----------------------------------------------------------------------------
 */
#ifndef SCOPE_MSG_THREAD_H
#define SCOPE_MSG_THREAD_H

#include <atomic>
#include <QThread>
#include "common.h"
#include "scope_data_source.h"

// Scope Message Thread class
class ScopeMsgThread : public QThread
{
	Q_OBJECT
public:
    ScopeMsgThread(ScopeDataSource &data_source, QObject *parent);
    ~ScopeMsgThread();
    void run();

private:
    ScopeDataSource& _scope_data_source;
    std::atomic<bool> _exit_msgs_thread;
};

#endif
