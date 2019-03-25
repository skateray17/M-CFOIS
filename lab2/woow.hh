#pragma once

#include "aes.hh"
#include <string>
#include <vector>

std::vector<uint8_t> encrypt(const uint8_t *key, const uint8_t *IV, std::vector<uint8_t> message);
std::vector<uint8_t> decrypt(const uint8_t *key, const uint8_t *IV, std::vector<uint8_t> encryptedMessage);
