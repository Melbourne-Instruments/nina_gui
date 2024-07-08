/**
 *-----------------------------------------------------------------------------
 * Copyright (c) 2022-2023 Melbourne Instruments, Australia
 *-----------------------------------------------------------------------------
 * @file  gui_msg_thread.h
 * @brief GUI Message Thread class definitions.
 *-----------------------------------------------------------------------------
 */
#ifndef GUI_MSG_THREAD_H
#define GUI_MSG_THREAD_H

#include <atomic>
#include <QThread>
#include "common.h"

// GUI Message Thread class
class GuiMsgThread : public QThread
{
	Q_OBJECT
public:
    GuiMsgThread(QObject *parent);
    ~GuiMsgThread();
    void run();

signals:
    void left_status_msg(const LeftStatus& msg);
    void layer_status_msg(const LayerStatus& msg);
    void midi_status_msg(const MidiStatus& msg);
    void tempo_status_msg(const TempoStatus& msg);
    void home_screen_msg(const HomeScreen& msg);
    void list_items_msg(const ListItems& msg);
    void list_select_item_msg(const ListSelectItem& msg);
    void soft_buttons_msg(const SoftButtons& msg);
    void soft_buttons_state_msg(const SoftButtonsState& msg);
    void param_update_msg(const ParamUpdate& msg);
    void param_value_update_msg(const ParamValueUpdate& msg);
    void enum_param_update_msg(const EnumParamUpdate& msg);
    void enum_param_value_update_msg(const ListSelectItem& msg);
    void edit_name_msg(const EditName& msg);
    void edit_name_select_char_msg(const EditNameSelectChar& msg);
    void edit_name_change_char_msg(const EditNameChangeChar& msg);
    void confirmation_screen_msg(const ConfirmationScreen& msg);
    void warning_screen_msg(const WarningScreen& msg);
    void clear_boot_warning_msg();
    void set_system_colour_msg(const SetSystemColour &msg);

private:
    std::atomic<bool> _exit_gui_msgs_thread;
};

#endif
