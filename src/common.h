/**
 *-----------------------------------------------------------------------------
 * Copyright (c) 2021-2023 Melbourne Instruments, Australia
 *-----------------------------------------------------------------------------
 * @file  common.h
 * @brief Common definitions.
 *-----------------------------------------------------------------------------
 */
#ifndef _COMMON_H
#define _COMMON_H

#include <cstring>
#include <iostream>
#include <QMetaType>

//--------------
// Build options
//--------------

// Define to monitor the SPI for errors
//#define SPI_STATUS_MONITOR  1

// Constants
constexpr uint LCD_HEIGHT                   = 480;
constexpr uint LCD_WIDTH                    = 854;
constexpr char MELB_INST_SPLASH_PNG_RES[]   = ":res/Melb_Inst_Splash.png";
constexpr char NINA_SPLASH_PNG_RES[]        = ":res/Nina_Splash.png";
constexpr char BOOT_WARNING_PNG_RES[]       = ":res/Boot_Warning.png";
constexpr char MIDI_STATUS_PNG_RES[]        = ":res/midi-key-trans.png";
constexpr char HOURGLASS_GIF_RES[]          = ":res/hourglass-animated.gif";
constexpr char OCR_A_FONT_RES[]             = ":res/OCR-A.ttf";
constexpr char OCR_B_FONT_RES[]             = ":res/OCR-B.ttf";
constexpr char DSEG7_CLASSIC_FONT_RES[]     = ":res/DSEG7Classic-BoldItalic.ttf";
constexpr uint STD_STR_LEN                  = 40;
constexpr uint EDIT_NAME_STR_LEN            = 20;
constexpr uint LIST_MAX_ITEMS               = 128;
constexpr char DEFAULT_SYSTEM_COLOUR[]      = "FF0000";
constexpr uint SCOPE_NUM_SAMPLES            = 128;
constexpr uint SCOPE_SAMPLES_MSG_SIZE       = (SCOPE_NUM_SAMPLES * 2);
constexpr uint WT_CHART_REFRESH_RATE        = std::chrono::milliseconds(34).count();

// MACRO to show a string on the console
#define MSG(str) do { std::cout << str << std::endl; } while( false )

// MACRO to show a debug string on the console
#ifndef NDEBUG
#define DEBUG_MSG(str) MSG(str)
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

// GUI Message Type
enum GuiMsgType : int
{
    SET_LEFT_STATUS = 0,
    SET_LAYER_STATUS,
    SET_MIDI_STATUS,
    SET_TEMPO_STATUS,
    SHOW_HOME_SCREEN,
    SHOW_LIST_ITEMS,
    LIST_SELECT_ITEM,
    SET_SOFT_BUTTONS,
    SOFT_BUTTONS_STATE,
    PARAM_UPDATE,
    PARAM_VALUE_UPDATE,
    ENUM_PARAM_UPDATE,
    ENUM_PARAM_UPDATE_VALUE,
    EDIT_NAME,
    EDIT_NAME_SELECT_CHAR,
    EDIT_NAME_CHANGE_CHAR,
    SHOW_CONFIRMATION_SCREEN,
    SHOW_WARNING_SCREEN,
    CLEAR_BOOT_WARNING_SCREEN,
    SET_SYSTEM_COLOUR
};

// GUI scope mode
enum GuiScopeMode : int
{
    SCOPE_MODE_OFF,
    SCOPE_MODE_OSC,
    SCOPE_MODE_XY
};

struct LeftStatus
{
    char status[STD_STR_LEN];
};
Q_DECLARE_METATYPE(LeftStatus);

struct LayerStatus
{
    char status[STD_STR_LEN];
};
Q_DECLARE_METATYPE(LayerStatus);

struct MidiStatus
{
    bool midi_active;
};
Q_DECLARE_METATYPE(MidiStatus);

struct TempoStatus
{
    char tempo_string[STD_STR_LEN];
};
Q_DECLARE_METATYPE(TempoStatus);

struct HomeScreen
{
    char patch_name[STD_STR_LEN];
    bool patch_modified;
    GuiScopeMode scope_mode;
};
Q_DECLARE_METATYPE(HomeScreen);

struct ListItems
{
    uint num_items;
    uint selected_item;
    char items[LIST_MAX_ITEMS][STD_STR_LEN];
    bool process_enabled_state;
    bool list_item_enabled[LIST_MAX_ITEMS];
};
Q_DECLARE_METATYPE(ListItems);

struct ListSelectItem
{
    uint selected_item;
    bool wt_list;
};
Q_DECLARE_METATYPE(ListSelectItem);

struct SoftButtons
{
    char button1[STD_STR_LEN];
    char button2[STD_STR_LEN];
    char button3[STD_STR_LEN];
};
Q_DECLARE_METATYPE(SoftButtons);

struct SoftButtonsState
{
    int state_button1;
    int state_button2;
    int state_button3;
};
Q_DECLARE_METATYPE(SoftButtonsState);

struct ParamUpdate
{
    char name[STD_STR_LEN];
    char value_string[STD_STR_LEN];
    char display_string[STD_STR_LEN];
    char value_tag[STD_STR_LEN]; 
    uint num_items;
    uint selected_item;
    char list_items[LIST_MAX_ITEMS][STD_STR_LEN];
    bool list_item_enabled[LIST_MAX_ITEMS];
    bool list_item_separator[LIST_MAX_ITEMS];
    bool show_scope;
};
Q_DECLARE_METATYPE(ParamUpdate);

struct ParamValueUpdate
{
    char value_string[STD_STR_LEN];
    char display_string[STD_STR_LEN];
    char value_tag[STD_STR_LEN]; 
    int selected_item;
};
Q_DECLARE_METATYPE(ParamValueUpdate);

struct EnumParamUpdate
{
    char name[STD_STR_LEN];
    uint num_items;
    uint selected_item;
    char list_items[LIST_MAX_ITEMS][STD_STR_LEN];
    bool wt_list;
};
Q_DECLARE_METATYPE(EnumParamUpdate);

struct EditName
{
    char name[STD_STR_LEN];
};
Q_DECLARE_METATYPE(EditName);

struct EditNameSelectChar
{
    uint selected_char;
};
Q_DECLARE_METATYPE(EditNameSelectChar);

struct EditNameChangeChar
{
    uint change_char;
};
Q_DECLARE_METATYPE(EditNameChangeChar);

struct ConfirmationScreen
{
    char line_1[STD_STR_LEN];
    char line_2[STD_STR_LEN];
};
Q_DECLARE_METATYPE(ConfirmationScreen);

struct WarningScreen
{
    bool show;
    bool show_hourglass;
    char line_1[STD_STR_LEN];
    char line_2[STD_STR_LEN];
};
Q_DECLARE_METATYPE(WarningScreen);

struct SetSystemColour
{
    char colour[STD_STR_LEN];
};
Q_DECLARE_METATYPE(SetSystemColour);

// GUI message
struct GuiMsg
{
    GuiMsgType type;
    union 
    {
        LeftStatus left_status;
        LayerStatus layer_status;
        MidiStatus midi_status;
        TempoStatus tempo_status;
        HomeScreen home_screen;
        ListItems list_items;
        ListSelectItem list_select_item;
        SoftButtons soft_buttons;
        SoftButtonsState soft_buttons_state;
        ParamUpdate param_update;
        ParamValueUpdate param_value_update;
        EnumParamUpdate enum_param_update;
        EditName edit_name;
        EditNameSelectChar edit_name_select_char;
        EditNameChangeChar edit_name_change_char;
        ConfirmationScreen confirmation_screen;
        WarningScreen warning_screen;
        SetSystemColour set_system_colour;
    };

    // Constructor/destructor
    GuiMsg() {}
    ~GuiMsg() {}
};

#endif  // _COMMON_H
