#!/usr/bin/python3
"""UTF-8 Validation"""


def validUTF8(data):
    """
    Validate if a given data represents a valid UTF-8 encoding.

    Args:
        data (list[int]): A list of integers representing the UTF-8 encoding.

    Returns:
        bool: True if data is a valid UTF-8 encoding, False otherwise.
    """
    # Constants for bit masks
    MASK_1BYTE = 0x80  # 10000000
    MASK_2BYTE = 0xE0  # 11100000
    MASK_3BYTE = 0xF0  # 11110000
    MASK_4BYTE = 0xF8  # 11111000
    MASK_CONTINUATION = 0xC0  # 11000000

    # Expected values for each type
    EXPECTED_1BYTE = 0x00  # 00000000
    EXPECTED_2BYTE = 0xC0  # 11000000
    EXPECTED_3BYTE = 0xE0  # 11100000
    EXPECTED_4BYTE = 0xF0  # 11110000
    EXPECTED_CONTINUATION = 0x80  # 10000000

    i = 0
    while i < len(data):
        # Get the current byte and ensure we only look
        # at 8 least significant bits
        byte = data[i] & 0xFF

        # Determine the number of bytes in this character
        if byte & MASK_1BYTE == EXPECTED_1BYTE:
            # 1-byte character
            i += 1
        elif byte & MASK_2BYTE == EXPECTED_2BYTE:
            # 2-byte character
            if i + 1 >= len(data):
                return False
            if (data[i + 1] & MASK_CONTINUATION) != EXPECTED_CONTINUATION:
                return False
            i += 2
        elif byte & MASK_3BYTE == EXPECTED_3BYTE:
            # 3-byte character
            if i + 2 >= len(data):
                return False
            # Check continuation bytes
            cont1 = (data[i + 1] & MASK_CONTINUATION) == EXPECTED_CONTINUATION
            cont2 = (data[i + 2] & MASK_CONTINUATION) == EXPECTED_CONTINUATION
            if not (cont1 and cont2):
                return False
            i += 3
        elif byte & MASK_4BYTE == EXPECTED_4BYTE:
            # 4-byte character
            if i + 3 >= len(data):
                return False
            # Check continuation bytes
            cont1 = (data[i + 1] & MASK_CONTINUATION) == EXPECTED_CONTINUATION
            cont2 = (data[i + 2] & MASK_CONTINUATION) == EXPECTED_CONTINUATION
            cont3 = (data[i + 3] & MASK_CONTINUATION) == EXPECTED_CONTINUATION
            if not (cont1 and cont2 and cont3):
                return False
            i += 4
        else:
            # Invalid byte pattern
            return False

    return True
