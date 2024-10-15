bool parse_int(int* a_value, const char** a_pos) {
    // Check for null pointers to avoid crashes
	assert(a_value != NULL);
	assert(a_pos != NULL);
	assert(*a_pos != NULL);

    const char* pos = *a_pos;
    bool is_negative = false;

    // Skip any leading whitespace
    while (*pos == ' ' || *pos == '\t' || *pos == '\n' || *pos == '\r') {
        pos++;
    }

    // Check if the number is negative
    if (*pos == '-') {
        is_negative = true;
        pos++;
    }

    // Check if there is at least one digit after the optional sign
    if (!isdigit(*pos)) {
		*a_pos = pos;
        return false;
    }

    int value = 0;
    while (isdigit(*pos)) {
        // Convert the character to an integer and update the value
        value = value * 10 + (*pos - '0');
        pos++;
    }

    // Apply the sign if the number is negative
    if (is_negative) {
        value = -value;
    }

    // Set the output value and update the position pointer
    *a_value = value;
    *a_pos = pos;

    return true;
}



