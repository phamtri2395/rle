#include "RLE.h"
#include <stdlib.h>

byte *compress_rle(const byte* raw, long raw_size, long& compressed_size) {
	compressed_size = 0;
	long pos = 0;

	// Scan for compressed size first
	byte last_byte = raw[0];
	byte length = 0;
	for (long i = 0; i <= raw_size; i++) {
		if (last_byte == raw[i] && length < 255) { // check if length > char type can hold
			length++;
		}
		else {
			compressed_size += 2;
			last_byte = raw[i];
			length = 1;
		}
	}

	// Compress data
	byte *compressed_data = (byte*)malloc(sizeof(byte) * compressed_size);
	last_byte = raw[0];
	length = 0;
	for (long i = 0; i <= raw_size; i++) {
		if (last_byte == raw[i] && length < 255) { // check if length > char type can hold
			length++;
		}
		else {
			compressed_data[pos++] = last_byte;
			compressed_data[pos++] = length;

			last_byte = raw[i];
			length = 1;
		}
	}

	return compressed_data;
}

byte *decompress_rle(const byte *data, long compressed_size, long & result_size) {
	// Check condition of input's size first
	if ((compressed_size < 2) || ((compressed_size % 2) != 0)) {
		return null;
	}

	result_size = 0;
	long pos = 0;

	// Scan for decompressed size
	for (long i = 1; i < compressed_size; i += 2) {
		int temp = data[i];
		result_size += (long)data[i];
	}

	// Decompress
	byte *result = (byte*)malloc(sizeof(byte) * result_size);
	for (long i = 1; i < compressed_size; i += 2) {
		for (byte j = 0; j < data[i + 1]; j++) {
			result[pos++] = data[i];
		}
	}

	return result;
}
