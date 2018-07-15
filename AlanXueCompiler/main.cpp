#include "scanner.h"
#include "dictionary.h"
#include "config.h"

#include <cstdlib>

void init() {
	Config::init();
}

int main() {

	init();

    Scanner scanner("input.cpp", new Dictionary());

	scanner.NextToken();

	system("pause");
    return 0;
}