#include "AlarmView.h"

#include "../Alarm.h"

AlarmView::AlarmView() {
}

AlarmView *AlarmView::getInstance() {
  static AlarmView instance;
  return &instance;
}

void AlarmView::willMount() {
  _step = AlarmSetupStep::SETTING_HOURS;
  _hours = Alarm.getSettings().hours;
  _minutes = Alarm.getSettings().minutes;
  _mode = (uint8_t)Alarm.getSettings().mode;
  Application.showStatusBar();
}

void AlarmView::willUnmount() {
  Application.hideStatusBar();
}

void AlarmView::didSelect() {
  _nextStep();
}

void AlarmView::handleScroll(ScrollEventArgs e) {
  if (_step == AlarmSetupStep::SETTING_HOURS) {
    if (e.delta < 0) {
      if (_hours == 0) {
        _hours = 23;
      } else {
        _hours -= 1;
      }
    } else {
      if (_hours == 23) {
        _hours = 0;
      } else {
        _hours += 1;
      }
    }
  } else if (_step == AlarmSetupStep::SETTING_MINUTES) {
    if (e.delta < 0) {
      if (_minutes == 0) {
        _minutes = 55;
      } else {
        _minutes -= 5;
      }
    } else {
      if (_minutes == 55) {
        _minutes = 0;
      } else {
        _minutes += 5;
      }
    }
  } else if (_step == AlarmSetupStep::SETTING_MODE) {
    if (e.delta < 0) {
      if (_mode == 0) {
        _mode = 2;
      } else {
        _mode -= 1;
      }
    } else {
      if (_mode == 2) {
        _mode = 0;
      } else {
        _mode += 1;
      }
    }
  }
  setDirty();
}

void AlarmView::render(CanvasContext *context) {
  context->setFontSize(FontSize::H1);

  context->setTextAlign(TextAlign::CENTER);
  context->drawString(":", getClientWidth() / 2, 6);

  if (_step == AlarmSetupStep::SETTING_HOURS) {
    context->setColor(Color::WHITE);
    context->fillRect(getClientWidth() / 2 - 36, 8, 32, 24);
    context->setColor(Color::BLACK);
  } else {
    context->setColor(Color::WHITE);
  }
  context->setTextAlign(TextAlign::RIGHT);
  context->drawString((_hours < 10 ? "0" : "") + String(_hours), getClientWidth() / 2 - 7, 6);

  if (_step == AlarmSetupStep::SETTING_MINUTES) {
    context->setColor(Color::WHITE);
    context->fillRect(getClientWidth() / 2 + 4, 8, 32, 24);
    context->setColor(Color::BLACK);
  } else {
    context->setColor(Color::WHITE);
  }
  context->setTextAlign(TextAlign::LEFT);
  context->drawString((_minutes < 10 ? "0" : "") + String(_minutes), getClientWidth() / 2 + 7, 6);

  if (_step == AlarmSetupStep::SETTING_MODE) {
    context->setColor(Color::WHITE);
    context->fillRect(getClientWidth() / 2 - 32, 36, 64, 16);
    context->setColor(Color::BLACK);
  } else {
    context->setColor(Color::WHITE);
  }
  context->setTextAlign(TextAlign::CENTER);
  context->setFontSize(FontSize::NORMAL);
  context->drawString(ALARM_MODES[_mode], getClientWidth() / 2, 37);
}

void AlarmView::_nextStep() {
  if (_step == AlarmSetupStep::SETTING_HOURS) {
    _step = AlarmSetupStep::SETTING_MINUTES;
    setDirty();
  } else if (_step == AlarmSetupStep::SETTING_MINUTES) {
    _step = AlarmSetupStep::SETTING_MODE;
    setDirty();
  } else {
    Alarm.saveSettings({.mode = (AlarmMode)_mode, .hours = _hours, .minutes = _minutes});
    Application.popView();
  }
}
