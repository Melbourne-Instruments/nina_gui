/**
 *-----------------------------------------------------------------------------
 * Copyright (c) 2022-2023 Melbourne Instruments, Australia
 *-----------------------------------------------------------------------------
 * @file  gui_msg_thread.cpp
 * @brief GUI Message Thread class implementation.
 *-----------------------------------------------------------------------------
 */
#include <mqueue.h>
#include <poll.h>
#include "gui_msg_thread.h"

// Constants
constexpr char GUI_MSG_QUEUE_NAME[] = "/nina_msg_queue";
constexpr uint GUI_MSG_QUEUE_SIZE   = 50;
constexpr auto GUI_POLL_TIMEOUT     = 1;

//----------------------------------------------------------------------------
// GuiMsgThread
//----------------------------------------------------------------------------
GuiMsgThread::GuiMsgThread(QObject *parent) : QThread(parent)
{
    // Initialise class variables
    _exit_gui_msgs_thread = false;
}

//----------------------------------------------------------------------------
// ~GuiMsgThread
//----------------------------------------------------------------------------
GuiMsgThread::~GuiMsgThread()
{
    // Stop the thread
    _exit_gui_msgs_thread = true;
    wait();
}

//----------------------------------------------------------------------------
// run
//----------------------------------------------------------------------------
void GuiMsgThread::run()
{
    mq_attr attr;

    // Open the GUI Message Queue (create if it doesn't exist)
    std::memset(&attr, 0, sizeof(attr));
    attr.mq_maxmsg = GUI_MSG_QUEUE_SIZE;
    attr.mq_msgsize = sizeof(GuiMsg);
    mqd_t desc = ::mq_open(GUI_MSG_QUEUE_NAME, (O_CREAT|O_RDONLY),
                           (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH),
                           &attr);
    if (desc == (mqd_t)-1)
    {
        // Error opening the GUI Message Queue
        MSG("GuiMsgThread: ERROR: Could not open the GUI message queue: " << errno);
        return;
    }

    // Run until the thread is stopped
    while(!_exit_gui_msgs_thread)
    {
        timespec poll_time;
        auto msg = GuiMsg();

        // Wait for GUI events, timeout, or an error
        clock_gettime(CLOCK_REALTIME, &poll_time);
        poll_time.tv_sec += GUI_POLL_TIMEOUT;        
        int res = ::mq_timedreceive(desc, (char *)&msg, sizeof(msg), NULL, &poll_time);
        if (res == sizeof(msg))
        {
            // Switch on the message type
            switch (msg.type) 
            {
                case GuiMsgType::SET_LEFT_STATUS:
                    emit left_status_msg(msg.left_status);
                    break;

                case GuiMsgType::SET_LAYER_STATUS:
                    emit layer_status_msg(msg.layer_status);
                    break;

                case GuiMsgType::SET_MIDI_STATUS:
                    emit midi_status_msg(msg.midi_status);
                    break;

                case GuiMsgType::SET_TEMPO_STATUS:
                    emit tempo_status_msg(msg.tempo_status);
                    break;

                case GuiMsgType::SHOW_HOME_SCREEN:
                    emit home_screen_msg(msg.home_screen);
                    break;

                case GuiMsgType::SHOW_LIST_ITEMS:
                    emit list_items_msg(msg.list_items);
                    break;

                case GuiMsgType::LIST_SELECT_ITEM:
                    emit list_select_item_msg(msg.list_select_item);
                    break;

                case GuiMsgType::SET_SOFT_BUTTONS:
                    emit soft_buttons_msg(msg.soft_buttons);
                    break;                

                case GuiMsgType::SOFT_BUTTONS_STATE:
                    emit soft_buttons_state_msg(msg.soft_buttons_state);
                    break;
                
                case GuiMsgType::PARAM_UPDATE:
                    emit param_update_msg(msg.param_update);
                    break;

                case GuiMsgType::PARAM_VALUE_UPDATE:
                    emit param_value_update_msg(msg.param_value_update);
                    break;

                case GuiMsgType::ENUM_PARAM_UPDATE:
                    emit enum_param_update_msg(msg.enum_param_update);
                    break;                  

                case GuiMsgType::ENUM_PARAM_UPDATE_VALUE:
                    emit enum_param_value_update_msg(msg.list_select_item);
                    break;

                case GuiMsgType::EDIT_NAME:
                    emit edit_name_msg(msg.edit_name);
                    break;

                case GuiMsgType::EDIT_NAME_SELECT_CHAR:
                    emit edit_name_select_char_msg(msg.edit_name_select_char);
                    break;

                case GuiMsgType::EDIT_NAME_CHANGE_CHAR:
                    emit edit_name_change_char_msg(msg.edit_name_change_char);
                    break;

                case GuiMsgType::SHOW_CONFIRMATION_SCREEN:
                    emit confirmation_screen_msg(msg.confirmation_screen);
                    break;

                case GuiMsgType::SHOW_WARNING_SCREEN:
                    emit warning_screen_msg(msg.warning_screen);
                    break;

                case GuiMsgType::CLEAR_BOOT_WARNING_SCREEN:
                    emit clear_boot_warning_msg();
                    break;

                case GuiMsgType::SET_SYSTEM_COLOUR:
                    emit set_system_colour_msg(msg.set_system_colour);
                    break;

                default:
                    // Ignore any unknown messages
                    break;
            }
        }
        else if (res == -1)
        {
            // If not a timeout
            if (errno != ETIMEDOUT)
            {
                // An error occurred, stop processing the queue
                DEBUG_MSG("GuiMsgThread: Message Queue error: " << errno);
                break;
            }
        }

    }

    // Thread exited
    DEBUG_MSG("GuiMsgThread: thread: EXIT");

    // Close the GUI message queue
    ::mq_close(desc);
    //::mq_unlink(GUI_MSG_QUEUE_NAME);
}
