#include "Arduino.h"
#include "Application.h"

Application::Application() {
	General::setProgram(this);
}
void Application::setup() {};
void Application::onStart() {};
bool Application::onSerialError() {};
void Application::loop() {};