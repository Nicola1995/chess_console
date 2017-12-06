#include "Desk.h"
#include "Validator.h"
#include <stdio.h>
#include <iostream>

int main()
{
	Desk desk;
	Validator validator(desk);
	desk.init();
	return 0;
}
