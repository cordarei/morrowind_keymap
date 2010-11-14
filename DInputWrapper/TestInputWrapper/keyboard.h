#pragma once

typedef unsigned char byte_t;
size_t const KeyboardSize = 256;
byte_t const EscapeKey = 0x01;

class keyboard {
public:
	keyboard() {
		reset();
	}

	bool pressed(byte_t const key) const {
		return 0 != (_bytes[key] & 0x80);
	}

	byte_t value(byte_t const key) const {
		return _bytes[key];
	}

	byte_t* data() { return _bytes; }

	void reset() {
		for(int i=0; i<KeyboardSize; ++i)
			_bytes[i] = 0;
	}

private:
	byte_t _bytes[KeyboardSize];
};