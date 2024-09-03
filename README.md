# Gödel Numbering-Based Encryption/Decryption Algorithm

## Overview

This repository contains an implementation of a cryptographic model based on Gödel Numbering. The algorithm leverages the Sieve of Eratosthenes for precomputing prime numbers and utilizes the Mersenne Twister (mt19937-64) for random number generation. The model is capable of performing encryption and decryption of strings with lengths up to 1 million characters within 1 second.

## Table of Contents

- [Features](#features)
- [Encryption and Decryption Process](#encryption-and-decryption-process)
- [Examples](#examples)


## Features

- **Fast Encryption/Decryption**: Can handle strings up to 1 million characters in less than a second.
- **Prime Number Based Encoding**: Utilizes prime numbers and Gödel Numbering for unique character encoding.
- **Diffie-Hellman Key Exchange**: Secure key exchange using Diffie-Hellman for generating encryption keys.
- **Buffer String for Security**: Adds buffer strings to encrypted text for additional security and randomness.


## Encryption and Decryption Process


### Overview

This section describes how to encrypt and decrypt a message using the Gödel Numbering-Based Encryption/Decryption Algorithm.

### Step 1: Generate the Encryption Key

Use the `diffie_hellman` function to generate an encryption key. This function utilizes the Diffie-Hellman key exchange method to create a secure key.

### Step 2: Encrypt the Message

Encrypt your message using the `encrypt` function. This function takes the message and the generated key as inputs and produces an encrypted string. The encryption process involves converting each character of the message into a numerical representation, encoding it using prime numbers, and appending a buffer string for added security.

### Step 3: Decrypt the Message

Decrypt the encrypted text using the `decrypt` function. This function takes the encrypted string and the same key used for encryption, and it reconstructs the original message. The decryption process reverses the encryption steps to recover the plaintext message.

### Process Details

- **Key Generation**: Create a secure key using Diffie-Hellman.
- **Encryption**: Convert the message to a numerical format, encode with prime numbers, and add a buffer string.
- **Decryption**: Reverse the encoding and buffer addition to recover the original message.

This process ensures that your message is securely transformed and then accurately restored.




## Examples
  ### Example: Encrypting and Decrypting a Message

Suppose we want to encrypt the message "Hello, World!" using the provided encryption algorithm.

**Step 1: Generate the Encryption Key**  
First, we use the `diffie_hellman` function to generate a key based on the Diffie-Hellman key exchange method.


unsigned long long key = diffie_hellman(7911, 1567689892, 292787734);

**Step 2: Encrypt the Message**

string message = "Hello, World!";
string encrypted_text = encrypt(message, key);
cout << "Encrypted Text: " << encrypted_text << endl;

Encrypted Text: 74231725653{N2Z}23255378519{y4A}29849789639{8Mc}31937563685{7Op}77448733268{K1@}169536148549{L3t}43875142287{U$W}31937563685{7Op}29849789639{8Mc}23255378519{y4A}213461782319{`X&}74231725653{N2Z}

**Step 3: Decrypt the Message**

string decrypted_text = decrypt(encrypted_text, key);
cout << "Decrypted Text: " << decrypted_text << endl;

Decrypted Text: Hello, World!




