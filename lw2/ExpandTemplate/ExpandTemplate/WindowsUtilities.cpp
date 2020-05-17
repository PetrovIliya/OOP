#include <Windows.h>
#include <iostream>
#include "WindowsUtilities.h"

void SetRuLanguage()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}