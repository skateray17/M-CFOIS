#include "woow.hh"
#include <iostream>
#include <ctime>
#include <fstream>

int main() {
	srand(time(NULL));
	std::cout << "Hi, what type of operation do you want to perform?\n(E)ncryption\n(D)ecription\n";
	char operation;
	std::cin >> operation;
	uint8_t key[16];
	uint64_t IV[2];
	std::string filePath;
	if (operation == 'E' || operation == 'e') {
		std::cout << "Enter path to file with key\n";
		std::cin >> filePath;
		std::ifstream kin(filePath, std::ios::binary);
		for (size_t i = 0; i < 16; i++) {
			kin >> key[i];
		}
		//std::cout << "Enter path to file with IV\n";
		//std::cin >> filePath;
		//std::ifstream ivin(filePath, std::ios::binary);
		for (size_t i = 0; i < 2; i++) {
			kin>> IV[i];
		}
		std::cout << "Enter path to file for encryption\n";
		std::cin >> filePath;
		std::ifstream in(filePath, std::ios::binary);
		std::vector<uint8_t> buf(std::istreambuf_iterator<char>(in), {});
		std::vector<uint8_t> enc = encrypt(key, IV, buf);
		std::cout << "Enter path to file for result\n";
		std::cin >> filePath;
		std::ofstream cipher(filePath, std::ios::binary);
		std::copy(enc.begin(), enc.end(), std::ostreambuf_iterator<char>(cipher));
		std::cout << "Encryption completed!";
		return 0;
	}
	if (operation == 'D' || operation == 'd') {
		std::cout << "Enter path to file with key\n";
		std::cin >> filePath;
		std::ifstream kin(filePath, std::ios::binary);
		for (size_t i = 0; i < 16; i++) {
			kin >> key[i];
		}		
		//std::cout << "Enter path to file with IV\n";
		//std::cin >> filePath;
		//std::ifstream ivin(filePath, std::ios::binary);
		for (size_t i = 0; i < 2; i++) {
			kin >> IV[i];
		}
		std::cout << "Enter path to file for decryption\n";
		std::cin >> filePath;
		std::ifstream in(filePath, std::ios::binary);
		std::vector<uint8_t> enc(std::istreambuf_iterator<char>(in), {});
		std::vector<uint8_t> v = decrypt(key, IV, enc);
		std::cout << "Enter path to file for result\n";
		std::cin >> filePath;
		std::ofstream output(filePath, std::ios::binary);
		std::copy(v.begin(), v.end(), std::ostreambuf_iterator<char>(output));
		std::cout << "Decryption completed!";
		return 0;
	}
	std::cout << "Wrong operation type, terminating program :c";
}
