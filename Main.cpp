#include "Application.h"

int main()
{
	Application app;
	while (app.running())
		app.play();

	return 0;
}