#include "StockView.h"

#include "../../services/ServiceClient.h"

StockView::StockView() : View() {
}

StockView *StockView::getInstance() {
  static StockView instance;
  return &instance;
}

void StockView::render(CanvasContext *context) {
  auto stock = ServiceClient.getStock(0);

  // BABA
  context->setTextAlign(TextAlign::LEFT);
  context->setFontSize(FontSize::NORMAL);
  context->drawString(String(stock.symbol), getClientWidth() / 2, 6);

  // xx.xx
  context->setTextAlign(TextAlign::RIGHT);
  context->setFontSize(FontSize::H1);
  context->drawString(String((int)stock.price) + ".", getClientWidth() - 18, getClientHeight() / 2 - 5);
  context->setTextAlign(TextAlign::LEFT);
  context->setFontSize(FontSize::H2);
  context->drawString(String((int)((stock.price - (int)stock.price) * 100)), getClientWidth() - 18,
                      getClientHeight() / 2 + 2);

  // xxx.xx%
  context->setTextAlign(TextAlign::RIGHT);
  context->setFontSize(FontSize::H2);
  context->drawString(String(abs(stock.changePercent)), getClientWidth() / 2 - 22,
                      getClientHeight() / 2 + 1);
  context->setTextAlign(TextAlign::LEFT);
  context->setFontSize(FontSize::NORMAL);
  context->drawString("%", getClientWidth() / 2 - 22, getClientHeight() / 2 + 5);

  // Triangle
  if (stock.changePercent != 0) {
    _drawTriangle(context, stock.changePercent > 0 ? 1 : -1, 14, 9, 10, 8);
  }
}

void StockView::_drawTriangle(CanvasContext *context, int8_t direction, int8_t x, int8_t y,
                              uint8_t size, uint8_t height) {
  auto halfSize = size / 2;
  if (direction > 0) {
    context->drawLine(x, y, x + halfSize, y + height);
    context->drawLine(x, y, x - halfSize, y + height);
    context->drawLine(x - halfSize, y + height, x + halfSize, y + height);
  } else {
    context->drawLine(x, y + height, x + halfSize, y);
    context->drawLine(x, y + height, x - halfSize, y);
    context->drawLine(x - halfSize, y, x + halfSize, y);
  }
}
