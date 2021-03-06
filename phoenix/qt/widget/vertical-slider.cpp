namespace phoenix {

Size pVerticalSlider::minimumSize() {
  return {20, 0};
}

void pVerticalSlider::setLength(unsigned length) {
  length += length == 0;
  qtSlider->setRange(0, length - 1);
  qtSlider->setPageStep(length >> 3);
}

void pVerticalSlider::setPosition(unsigned position) {
  qtSlider->setValue(position);
}

void pVerticalSlider::constructor() {
  qtWidget = qtSlider = new QSlider(Qt::Vertical);
  qtSlider->setRange(0, 100);
  qtSlider->setPageStep(101 >> 3);
  connect(qtSlider, SIGNAL(valueChanged(int)), SLOT(onChange()));

  pWidget::synchronizeState();
  setLength(verticalSlider.state.length);
  setPosition(verticalSlider.state.position);
}

void pVerticalSlider::destructor() {
  delete qtSlider;
  qtWidget = qtSlider = nullptr;
}

void pVerticalSlider::orphan() {
  destructor();
  constructor();
}

void pVerticalSlider::onChange() {
  verticalSlider.state.position = qtSlider->value();
  if(verticalSlider.onChange) verticalSlider.onChange();
}

}
