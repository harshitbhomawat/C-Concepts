#include <stdio.h>

// Define a structure without pragma pack
struct NormalStruct {
	char a;    // Size: 1 byte
	int b;     // Size: 4 bytes (on most systems)
	char c;	// Size: 1 byte
	double d;	// Size: 8 byte
};

struct SecondNormalStruct {
	char a;    // Size: 1 byte
	char c;	// Size: 1 byte
	int b;     // Size: 4 bytes (on most systems)
	double d;	// Size: 8 byte
};

struct ThirdNormalStruct {
	double d;	// Size: 8 byte
	int b;     // Size: 4 bytes (on most systems)
	char a;    // Size: 1 byte
	char c;	// Size: 1 byte
};

// Define a structure with pragma pack
#pragma pack(push, 1)
struct PackedStruct {
	char a;    // Size: 1 byte
	int b;     // Size: 4 bytes (on most systems)
	char c;    // Size: 1 byte
	double d;	// Size: 8 byte
};
#pragma pack(pop)

int main() {
    printf("Size of NormalStruct: %zu bytes\n", sizeof(struct NormalStruct));
	printf("Size of SecondNormalStruct: %zu bytes\n", sizeof(struct SecondNormalStruct));
	printf("Size of ThirdNormalStruct: %zu bytes\n", sizeof(struct ThirdNormalStruct));
    printf("Size of PackedStruct: %zu bytes\n", sizeof(struct PackedStruct));
    return 0;
}
