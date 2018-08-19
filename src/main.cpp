#include <Arduino.h>

#include <SH1106Wire.h>

#include "espix-core.h"
#include "espix-deisgn.h"

unsigned long lastUpdate = 0;
unsigned long lastViewChange = 0;

SH1106Wire display(0x3c, D1, D2);
Application app(&display);
DrawingContext *context;

int viewCount = 2;
int viewIndex = 0;
View *views[] = {new TextView("Hello."), new TextView("Think Different.", FONT_SIZE_H2)};

void setView(int index, TransitionOptions options = TRANSITION_OPTIONS_NONE) {
  viewIndex = index;
  app.setRootView(views[viewIndex], options);
  lastViewChange = millis();
}

void nextView() {
  viewIndex++;
  if (viewIndex >= viewCount) {
    viewIndex = 0;
  }
  setView(viewIndex, TransitionOptions(TRANSITION_TO_LEFT));
}

void previousView() {
  viewIndex--;
  if (viewIndex < 0) {
    viewIndex = viewCount - 1;
  }
  setView(viewIndex, TransitionOptions(TRANSITION_TO_RIGHT));
}

void setup() {
  Serial.begin(115200);
  Serial.println();

  app.begin();
  // Settings
  app.getScreen()->setBrightness(100);
  app.getScreen()->setOrientation(true);

  setView(0);
}

void loop() {
  if (millis() - lastViewChange > 3000) {
    nextView();
  }
  int timeBudget = app.update();
  if (timeBudget > 0) {
    delay(timeBudget);
  }
}
