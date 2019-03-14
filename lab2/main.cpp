#include "woow.h"
#include <cstdlib>
#include <cstring>

int main() {
	example();
	const char* message = "Wow, that is so secure message. I think it's unbreakable. Woof woof";
	char enc[68];
	uint8_t key[] = {
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
			0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
	};
	woow(key, message, enc);
}