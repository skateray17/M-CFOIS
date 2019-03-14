#include "woow.h"
#include <ctime>
#include <cstdlib>
#include <cstring>

void example() {
	uint8_t i, r;

	/* 128 bit key */
	uint8_t key[] = {
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
			0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,

	};

	uint8_t plaintext[] = {
			0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
			0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
	};

	uint8_t ciphertext[AES_BLOCK_SIZE];
	const uint8_t const_cipher[AES_BLOCK_SIZE] = {
			0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30,
			0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a,
	};

	uint8_t roundkeys[AES_ROUND_KEY_SIZE];

	printf("Plain text:\n");
	for (i = 0; i < AES_BLOCK_SIZE; i++) {
		printf("%2x ", plaintext[i]);
	}
	printf("\n\n");

	// key schedule
	aes_key_schedule_128(key, roundkeys);
	printf("Round Keys:\n");
	for (r = 0; r <= AES_ROUNDS; r++) {
		for (i = 0; i < AES_BLOCK_SIZE; i++) {
			printf("%2x ", roundkeys[r*AES_BLOCK_SIZE + i]);
		}
		printf("\n");
	}
	printf("\n");

	// encryption
	aes_encrypt_128(roundkeys, plaintext, ciphertext);
	printf("Cipher text:\n");
	for (i = 0; i < AES_BLOCK_SIZE; i++) {
		printf("%2x ", ciphertext[i]);
	}
	for (i = 0; i < AES_BLOCK_SIZE; i++) {
		if (ciphertext[i] != const_cipher[i]) { break; }
	}
	if (AES_BLOCK_SIZE != i) { printf("\nENCRYPT WRONG\n\n"); }
	else { printf("\nENCRYPT CORRECT\n\n"); }


	// decryption
	aes_decrypt_128(roundkeys, ciphertext, ciphertext);
	printf("Plain text:\n");
	for (i = 0; i < AES_BLOCK_SIZE; i++) {
		printf("%2x ", ciphertext[i]);
	}
	for (i = 0; i < AES_BLOCK_SIZE; i++) {
		if (ciphertext[i] != plaintext[i]) { break; }
	}
	if (AES_BLOCK_SIZE != i) { printf("\nDECRYPT WRONG\n\n"); }
	else { printf("\nDECRYPT CORRECT\n\n"); }

}

void woow(const uint8_t *key, const char* message, char* encryptedMessage) {
	const char * m1 = message;
	char* e1 = encryptedMessage;
	printf("%s", message);
	uint8_t IVAndCounter[16];
	srand(time(NULL));
	for (size_t i = 0; i < 8; i++) {
		*(IVAndCounter + i) = rand(); // random IV
	}
	uint64_t counter = 1;
	uint8_t ciphertext[AES_BLOCK_SIZE];
	uint8_t roundkeys[AES_ROUND_KEY_SIZE];
	aes_key_schedule_128(key, roundkeys);
	int n = strlen(message) / 8;
	while (n--) {
		for (size_t i = 0; i < 8; i++) {
			*(IVAndCounter + 15 - i) = counter & (0xFF << (8 * i));
		}
		aes_encrypt_128(roundkeys, IVAndCounter, ciphertext);
		for (size_t i = 0; i < 8; i++) {
			*(encryptedMessage++) = *(message++) ^ ciphertext[i];
		}
		counter++;
	}
	for (size_t i = 0; i < 8; i++) {
		*(IVAndCounter + 15 - i) = counter & (0xFF << (8 * i));
	}
	aes_encrypt_128(roundkeys, IVAndCounter, ciphertext);
	const size_t additional = strlen(message) - 8 * (strlen(message) / 8);
	for (size_t i = 0; i < additional; i++) {
		*(encryptedMessage++) = *(message++) ^ ciphertext[i];
	}

	printf("\nCipher text:\n");
	for (size_t i = 0; i < strlen(e1); i++) {
		printf("%2x ", (uint8_t)e1[i]);
	}
	printf("\n\n%s", e1);
	// ??? dec ???
	encryptedMessage = e1;
	n = strlen(m1) / 8;
	counter = 1;
	while (n--) {
		for (size_t i = 0; i < 8; i++) {
			*(IVAndCounter + 15 - i) = counter & (0xFF << (8 * i));
		}
		aes_encrypt_128(roundkeys, IVAndCounter, ciphertext);
		for (size_t i = 0; i < 8; i++) {
			*(encryptedMessage++) = *(encryptedMessage) ^ ciphertext[i];
		}
		counter++;
	}
	for (size_t i = 0; i < 8; i++) {
		*(IVAndCounter + 15 - i) = counter & (0xFF << (8 * i));
	}
	aes_encrypt_128(roundkeys, IVAndCounter, ciphertext);
	for (size_t i = 0; i < additional; i++) {
		*(encryptedMessage++) = *(encryptedMessage) ^ ciphertext[i];
	}
	*encryptedMessage = 0;
	printf("\nDecripted text:\n");
	for (size_t i = 0; i < strlen(e1); i++) {
		printf("%2x ", (uint8_t)e1[i]);
	}

	printf("\n\n%s", e1);
}