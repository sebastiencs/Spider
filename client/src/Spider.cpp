#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include "Hooker.hh"

int main()
{
	Hooker& hooker = Hooker::getInstance();

	hooker.runHookLoop();
}
