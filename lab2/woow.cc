#include "woow.hh"

void addPadding(std::vector<uint8_t>& message) {
	size_t paddLength = 16 - (message.size() % 16);
	paddLength = paddLength ? paddLength : 16;
	for (size_t i = 1; i < paddLength; i++) {
		message.push_back(0);
	}
	message.push_back(paddLength);
}

void removePadding(std::vector<uint8_t>& message) {
	size_t paddLength = message.back();
	message.pop_back();
	while (--paddLength){
		if (message.back()) {
			throw "Wrong padding";
		}
		message.pop_back();
	}
}

std::vector<uint8_t> encr(const uint8_t *key, uint8_t* IV, std::vector<uint8_t>& message) {
	std::vector<uint8_t> encryptedMessage;
	encryptedMessage.reserve((message.size()));
	uint8_t ciphertext[AES_BLOCK_SIZE];
	uint8_t roundkeys[AES_ROUND_KEY_SIZE];
	aes_key_schedule_128(key, roundkeys);
	uint64_t n = message.size() / 16;
	auto it = message.begin();
	aes_encrypt_128(roundkeys, IV, ciphertext);
	for (int i = 0; i < 16; i++) IV[i] = ciphertext[i];
	for (uint64_t counter = 0; counter < n; counter++) {
		for (size_t i = 15; i >= 0; --i) {
			IV[i]++;
			if (IV[i]) break;
		}
		aes_encrypt_128(roundkeys, IV, ciphertext);
		for (size_t i = 0; i < 16; i++) {
			encryptedMessage.push_back(*(it++) ^ ciphertext[i]);
		}
	}
	return encryptedMessage;
}

std::vector<uint8_t> encrypt(const uint8_t *key, uint8_t *IV, std::vector<uint8_t> message) {
	addPadding(message);
	message = encr(key, IV, message);
	return message;
}

std::vector<uint8_t> decrypt(const uint8_t *key, uint8_t *IV, std::vector<uint8_t> encryptedMessage) {
	encryptedMessage = encr(key, IV, encryptedMessage);
	removePadding(encryptedMessage);
	return encryptedMessage;
}