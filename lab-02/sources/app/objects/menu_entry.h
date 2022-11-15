#ifndef _MENU_ENTRY_H_
#define _MENU_ENTRY_H_

#include <functional>
#include <string>

struct MenuEntry
{
    int m_id;
    
    std::string m_entry_name;
    
    std::function<auto(void)->void> m_action;
    
    MenuEntry(const int& id, const std::string& entry_name
    , const std::function<auto()->void> action = [] () {});

    MenuEntry(const MenuEntry&);
};

#endif 