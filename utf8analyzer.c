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

int size_of_codepoint(char c) {
    if((c & 0b10000000) == 0b00000000) { return 1; }
    if((c & 0b11100000) == 0b11000000) { return 2; }
    if((c & 0b11110000) == 0b11100000) { return 3; }
    if((c & 0b11111000) == 0b11110000) { return 4; }
    return -1;
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
	

    // 1. Whether the String is valid ASCII  

    if(is_ascii(argv[1])) { printf("All characters are valid ASCII.\n");}
    else{printf("String contains non-ASCII characters.\n");}

    // 3.) Length of the whole string in bytes.
    length_of_string(argv[1]);

    // implement the UTF-8 analyzer here 
   // 4. The number of UTF-8 codepoints represented by the string
   int numOfCodepoints = 0;
   for (int i = 0; i < strlen(argv[1]); ) {
        numOfCodepoints++;
        i += size_of_codepoint(argv[1][i]);
   }
   printf("Number of code points: %d\n", numOfCodepoints);

   // 6. How many bytes are used to represent each codepoint
   char numOfBytes[numOfCodepoints + 1];
   numOfBytes[numOfCodepoints] = '\0';
   int idx = 0;
   for (int i = 0; i < strlen(argv[1];)) {
        int size = size_of_codepoint(argv[1][i]);
        numOfBytes[idx] = (char) size;
        i += size;
   }
   printf("Bytes per code point: %s\n", numOfBytes);

   // 7. Substring of the input string containing only the first 6 codepoints
   char substring[24];
   int idx = 0;
   int i = 0;
   numOfCodepoints = 0;
   int len = strlen(argv[1]);
   while (numOfCodepoints < 6 && i < len) {
        int cp = size_of_codepoint(argv[1][i]);
        for (int j = 0; j < cp; j++) {
            substring[idx++] = argv[1][i + j];
        }
        i += cp;
        numOfCodepoints++;
   }
   substring[idx] = '\0';
   printf("Substring of the first 6 code points: \"%s\"\n", substring);
   
   // 8. All animal emojis in the input string
   printf("Animal emojis: ");
   i = 0;
   char emoji[5];

   while (i < len) {
        int cp = 0;
        uint32_t code_point = utf8_decode(&argv[1][i], &cp);
        if (is_animal_emoji(code_point)) {
                memcpy(emoji, &argv[1][i], cp);
                emoji[cp] = '\0';
                printf("%s ", emoji);
        }

        i += cp;
   }
}
