#include <iostream>
#include "BaseRunner/BaseRunner.h"

int main() {
	std::srand(std::time(nullptr));
	BaseRunner runner;
	runner.run();
}
