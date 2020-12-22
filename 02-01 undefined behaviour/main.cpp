#include <iostream>

int main() {
	signed char c = 127;
	c = c + 1;
	if (c > 0) {
		std::cout << "lager\n";
	} else {
		std::cout << "not lager\n";
	}
   return 0;
}