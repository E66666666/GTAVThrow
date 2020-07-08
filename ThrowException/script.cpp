#include "script.h"

#include <inc/natives.h>
#include <inc/enums.h>
#include <inc/main.h>

#include <stdexcept>
#include <string>

void showNotification(const std::string& message) {
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");

	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((char*)message.c_str());

	int id = UI::_DRAW_NOTIFICATION(false, false);
}

void update() {
	try {
		if (GAMEPLAY::_HAS_CHEAT_STRING_JUST_BEEN_ENTERED(GAMEPLAY::GET_HASH_KEY((char*)"throw"))) {
			throw std::logic_error("catch me!");
		}
	}
	catch(std::logic_error& ex) {
		showNotification(std::string("Caught A: ") + ex.what());
	}
	catch (std::exception& ex) {
		showNotification(std::string("Caught B: ") + ex.what());
	}
	catch(...) {
		showNotification("Caught C");
	}
}

void main() {
	while (true) {
		update();
		WAIT(0);
	}
}

void ScriptMain() {
	srand(GetTickCount());
	main();
}
