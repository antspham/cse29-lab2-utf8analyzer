#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

uint32_t utf8_decode(const char input[], int *length) {
    unsigned char b0 = input[0];

    if ((b0 & 0b10000000) == 0) {
        *length = 1;
        return b0 & 0x7F;
    } else if ((b0 & 0b11100000) == 0b11000000) {
        unsigned char b1 = input[1];
        *length = 2;
        return (((uint32_t)(b0 & 0b00011111)) << 6) |
               (b1 & 0b00111111);
    } else if ((b0 & 0b11110000) == 0b11100000) {
        unsigned char b1 = input[1];
        unsigned char b2 = input[2];
        *length = 3;
        return (((uint32_t)(b0 & 0b00001111)) << 12) |
               (((uint32_t)(b1 & 0b00111111)) << 6) |
               (b2 & 0b00111111);
    } else if ((b0 & 0b11111000) == 0b11110000) {
        unsigned char b1 = input[1];
        unsigned char b2 = input[2];
        unsigned char b3 = input[3];
        *length = 4;
        return (((uint32_t)(b0 & 0b00000111)) << 18) |
               (((uint32_t)(b1 & 0b00111111)) << 12) |
               (((uint32_t)(b2 & 0b00111111)) << 6) |
               (b3 & 0b00111111);
    }

    *length = 1;
    return 0xFFFD;
}

void length_of_string(const char str[]) {
	int length = strlen(str);
	printf("Length in bytes: %d\n", length);

}

void to_uppercase(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 32;
        }
    }
}

bool is_ascii(const char str[]) {
	for(int i = 0; str[i] != '\0'; i++) {
		if((unsigned char)str[i] > 127) {
			return false;
		}
	
	}
	return true;
}

void print_decimal_codepoints(const char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        int len;
        uint32_t cp = utf8_decode(&str[i], &len);
        printf("%u\n", cp);
        i += len;
    }
}



int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: utf8analyzer \"<UTF-8 encoded string>\"\n");
        return 1;
    }

    // implement the UTF-8 analyzer here
	

    // Uppercase 

    if(is_ascii(argv[1])) { printf("All characters are valid ASCII.\n");}
    else{printf("String contains non-ASCII characters.\n");}

    //Length in bytes
    length_of_string(argv[1]);

    // implement the UTF-8 analyzer here 

}
