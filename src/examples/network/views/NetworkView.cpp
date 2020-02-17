#include "NetworkView.h"

NetworkView *NetworkView::getInstance() {
  static NetworkView instance;
  return &instance;
}

void NetworkView::willMount() {
  Application.showStatusBar();
}

void NetworkView::willUnmount() {
  Application.hideStatusBar();
}

void NetworkView::render(CanvasContext *context) {
  context->setTextAlign(TextAlign::CENTER_BOTH);
  context->setFontSize(FontSize::NORMAL);
  context->drawString("IP Address", getClientWidth() / 2, 14);
  context->setFontSize(FontSize::H2);
  context->drawString(WiFiNetwork.getLocalIP(), getClientWidth() / 2, 32);
}
