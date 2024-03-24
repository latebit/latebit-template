#include "src/scenes/GameScene.cpp"

#include <latebit/Configuration.h>
#include <latebit/GameManager.h>
#include <latebit/Logger.h>
#include <latebit/ResourceManager.h>

using namespace lb;

int main() {
  Configuration::fromFile("latebit.cfg");
  GM.startUp();

  // Load resources
  RM.loadSprite("assets/sprites/fish", "fish");
  RM.loadSprite("assets/sprites/bubbles", "bubbles");
  RM.loadSprite("assets/sprites/logo", "logo");
  RM.loadMusic("assets/audio/music.mp3", "music");

  auto scene = new GameScene();
  GM.run();
  delete scene;

  return 0;
}
