#include "AgendaUI.hpp"
#include "Date.hpp"
#include "User.hpp"
#include "AgendaService.hpp"
#include <iostream>
using namespace std;
int main(void) {
	AgendaUI ui;
	ui.OperationLoop();
	return 0;
}
