#include <iostream>

#include "ZHOR_ENGINE/zhor.hpp"

int main(int argc, char *argv[])
{
	GameController controller;
	if(controller.createWindow()){
		controller.run();
	}

	return 0;
}