#include <gtest/gtest.h>
#include "Signaling.h"

class Button {
public:
    Signal<> clicked;

    void click() {
        clicked.emit();
    }
};

class Application {
public:
    void onButtonClicked() {
        ++clickCount;
    }

    int clickCount = 0;
};

void standaloneFunction(std::ostringstream& oss) {
    oss << "Standalone function called!" << std::endl;
}


TEST(SignalSlotTest, MemberFunctionSlot) {
    Button button;
    Application *app = new Application();

    button.clicked.connect(Slot::create(app, &Application::onButtonClicked));

    button.click();
    button.click();

    EXPECT_EQ(app->clickCount, 2);
}

TEST(SignalSlotTest, StandaloneFunctionSlot) {
    Button button;
    std::ostringstream oss;

    auto slot = [&oss]() {
        oss << "Button clicked!" << std::endl;
    };

    button.clicked.connect(slot);

    button.click();

    EXPECT_EQ(oss.str(), "Button clicked!\n");
}

TEST(SignalSlotTest, StandaloneFunctionWithParameters) {
    Button button;
    std::ostringstream oss;

    button.clicked.connect([&oss]() { standaloneFunction(oss); });

    button.click();

    EXPECT_EQ(oss.str(), "Standalone function called!\n");
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
