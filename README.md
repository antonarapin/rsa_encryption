This project contains four programs, including keygen, encrypt, decrypt, and factorial. Each program needs to be compiled individually using the directions listed below.

-- keygen --
To compile: make keygen
To run: `./keygen <numberone> <numbertwo> <publicfile> <privatefile>`
Description:
The keygen program takes in two prime numbers and two text files as command line arguments. Public and private keys will be generated from the two prime numbers <numberone> and <numbertwo>. Public key will be written to the <publicfile> and private key will be written to the <privatefile>. Program will prompt the user if one or both passed in numbers are not prime or are too small. If passed in numbers are greater than 100000, they will not be checked for primality.

-- encrypt -- 
To compile: make encrypt
To run: `./encrypt <publickeyfile> <textfile> <encryptedfile>`
Description:
The encrypt program takes in three file names as command line arguments. It uses the public key that is contained in <publickeyfile> and encrypts the phrase from the <textfile>. The resulting encrypted message is written to the <encryptedfile>. In order for the program to encrypt the message, it should be written to the <textfile> and <publickeyfile> should contain a pair of numbers which are the public key. Proper encryption is achieved when the message that is being encrypted is written in English letters. This encryption method is not secure enough and should not be used for practical purpouses or protection.

-- decrypt -- 
To compile: make decrypt
To run: `./decrypt <privatefile> <encryptedfile> <decryptedfile>`
Description:
The decrypt program takes three file names as command line arguments. It uses private key from <privatefile> to decrypt the encrypted message contained in <encryptedfile>. The decrypted message is then written to the <decryptedfile>. For the proper decryption, private key should match the public key with which the message was encrypted. 

-- factorial --
To compile: make factorial
To run: `./factorial <number>`
Description:
The factorial program computes a fatorial of a given number. It takes in a single command liine argument <number> integer, computes and prints out the factorial of the passed in <number>. 
