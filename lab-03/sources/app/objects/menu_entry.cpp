#include "menu_entry.h"

MenuEntry::MenuEntry(const int& id, const std::string& entry_name
    , const std::function<auto()->void> action) {
    m_id = id;
    m_entry_name = entry_name;
    m_action = action;
}

MenuEntry::MenuEntry(const MenuEntry& another) {
    m_id = another.m_id;
    m_entry_name = another.m_entry_name;
    m_action = another.m_action;
}