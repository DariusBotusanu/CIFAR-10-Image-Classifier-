#pragma once
#pragma pack(push)
#pragma pack(1)
typedef struct Image {
	unsigned char label;
	unsigned char redChannel[1024];
	unsigned char greenChannel[1024];
	unsigned char blueChannel[1024];
}Image;
#pragma pack(pop)

