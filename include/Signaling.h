#ifndef SIGNAL_SLOT_H
#define SIGNAL_SLOT_H

#include <functional>
#include <vector>
#include <algorithm>

template<typename... Args>
class Signal {
public:
    using SlotType = std::function<void(Args...)>;

    void connect(SlotType slot) {
        slots.push_back(slot);
    }

    void disconnect(SlotType slot) {
        auto it = std::remove_if(slots.begin(), slots.end(),
            [&slot](const SlotType& s) { return s.target_type() == slot.target_type(); });
        slots.erase(it, slots.end());
    }

    void emit(Args... args) {
        for (auto& slot : slots) {
            slot(args...);
        }
    }

private:
    std::vector<SlotType> slots;
};

class Slot {
public:
    template<typename T, typename... Args>
    static std::function<void(Args...)> create(T* instance, void (T::*func)(Args...)) {
        return [instance, func](Args... args) {
            (instance->*func)(args...);
        };
    }

    static std::function<void()> create(void(*func)()) {
        return [func]() {
            func();
        };
    }
};

#endif // SIGNAL_SLOT_H