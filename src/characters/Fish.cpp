#include <cstdio>
#include <latebit/EventOut.h>
#include <latebit/EventStep.h>
#include <latebit/Object.h>
#include <latebit/WorldManager.h>

using namespace lb;

class Bubbles : public Object {
public:
  Bubbles(Vector position) {
    setType("Bubbles");
    setSprite("bubbles");
    setSolidness(SPECTRAL);
    setVelocity(Vector(0, -1));
    setPosition(position);
    setAltitude(2);
    subscribe(OUT_EVENT);
  }

  int eventHandler(const Event *p_e) override {
    if (p_e->getType() == OUT_EVENT) {
      WM.markForDelete(this);
      return 1;
    }

    return 0;
  }
};

class Fish : public Object {
public:
  Fish() {
    setType("Fish");
    setSprite("fish");
    subscribe(STEP_EVENT);
  }

  int eventHandler(const Event *p_e) override {
    if (p_e->getType() == STEP_EVENT) {
      if (rand() % 100 == 0) {
        new Bubbles(getPosition() + Vector(16, 0));
      }
      return 1;
    }

    return 0;
  }
};