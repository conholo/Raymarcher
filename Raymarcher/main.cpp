#include "rmpch.h"

#include "Core/Application.h"
#include "Layers/TestLayer.h"

int main()
{
	auto* app = new RM::Application(RM::CreateRef<TestLayer>("Test Layer"));
	app->Run();
	delete app;
}