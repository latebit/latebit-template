#include <latebit/Colors.h>
#include <latebit/DisplayManager.h>
#include <latebit/Object.h>

#include "../characters/Fish.cpp"
#include "latebit/ResourceManager.h"

using namespace lb;

class WelcomeText : public lb::Object {
public:
  WelcomeText() { this->setType("WelcomeText"); }

  int draw() override {
    int result = 0;

    // This comes from the CMakeLists.txt file
    std::string version = LATEBIT_VERSION;

    result += DM.drawString(this->getPosition(), "Welcome to LateBit",
                            lb::ALIGN_CENTER, lb::BLACK);
    result += DM.drawString(this->getPosition() + Vector(1, 1),
                            "Welcome to LateBit", lb::ALIGN_CENTER, lb::WHITE);

    result += DM.drawString(this->getPosition() + Vector(0, 20), version,
                            lb::ALIGN_CENTER, lb::WHITE);
    return result;
  }
};

class GameScene : public lb::Object {
private:
  WelcomeText *welcomeText = new WelcomeText();
  Fish *fish = new Fish();

public:
  GameScene() {
    setType("GameScene");

    DM.setBackground(Color::BLUE);
    auto music = RM.getMusic("music");

    if (music != nullptr) {
      music->play();
    }

    auto center =
        Vector(DM.getHorizontalCells() / 2.0, DM.getVerticalCells() / 2.0);
    this->welcomeText->setPosition(center);

    auto fishBox = this->fish->getBox();
    this->fish->setPosition(
        center - Vector(fishBox.getWidth() / 2, 32 - fishBox.getHeight() / 2));
  }
};