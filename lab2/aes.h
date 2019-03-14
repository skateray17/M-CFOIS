#pragma once

#include <cstdio>
#include <stdint.h>

#define AES_BLOCK_SIZE      16
#define AES_ROUNDS          10  // 12, 14
#define AES_ROUND_KEY_SIZE  176 // AES-128 has 10 rounds, and there is a AddRoundKey before first round. (10+1)x16=176.

/**
 * Key schedule for AES-128
 *
 * @param key           16 bytes of master keys
 * @param roundkeys     176 bytes of round keys
 */
void aes_key_schedule_128(const uint8_t *key, uint8_t *roundkeys);

/**
 * Block encryption. The length of plain and cipher should be one block (16 bytes).
 * The plaintext and ciphertext may point to the same memory
 *
 * @param roundkeys     round keys
 * @param plaintext     plain text
 * @param ciphertext    cipher text
 */
void aes_encrypt_128(const uint8_t *roundkeys, const uint8_t *plaintext, uint8_t *ciphertext);

/**
 * Block decryption. The length of plain and cipher should be one block (16 bytes).
 * The ciphertext and plaintext may point to the same memory
 *
 * @param roundkeys     round keys
 * @param ciphertext    cipher text
 * @param plaintext     plain text
 */
void aes_decrypt_128(const uint8_t *roundkeys, const uint8_t *ciphertext, uint8_t *plaintext);
