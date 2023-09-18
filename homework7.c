
void titlecase(char *s) {
	// loop over string characters stopping at '\0' delim
	for (int i = 0; s[i] != '\0'; i++) {
		// check if a character follows a space, make sure character is a lowercase letter
		if (s[i] == ' ' && s[i+1] != '\0' && 0x61 <= s[i+1] && s[i+1] <= 0x7A) {
		// lowercase - 32 = uppercase
			s[i+1] = s[i+1] - 32;
		}
	}
}

void fibarray(unsigned short *dest, unsigned num) {
	// put first two terms of fib sequence
	if (num >= 1) {
		dest[0] = 1;
	}
	if (num >= 2) {
		dest[1] = 1;
	}
	// construct the sequence
	for (short i = 2; i < num; i++) {
		short next_term = (dest[i-1] + dest[i-2]) % 65536;
		dest[i] = next_term;
	}
}

// helper function to preserve value of base (base^exponent)
long recpowHelper(long x, unsigned char e, long base) {
	if (e == 0) {
		return 1;
	}
	if (e == 1) {
		return x;
	}
	x *= base;
	// decrement e by 1, x is multiplied by itself e times
	// i.e. we carry out x * ... * x (e times) recursively
	return recpowHelper(x, e-1, base);
}

long recpow(long x, unsigned char e) {
        return recpowHelper(x, e, x);
}

// returns 1 if num is prime, 0 otherwise
int checkprime(unsigned long num) {
	if (num == 1) {
		return 0;
	}
	int stop = (num / 2) + 1;
	// no need to check numbers after stop
	for (int i = 2; i < stop; i++) {
		if (num % i == 0) { 
			return 0; 
		}
	}
	return 1;
}

unsigned long nextprime(unsigned long x) {
	x++;
	// equivalent to python while True
	for (;;) {
		// check if x is prime
		if (checkprime(x) == 1) {
			return x;
		}
		// if not prime go to next num
		else {
			x++;
		}
	}
}

int nondup(int *arr, unsigned length) {
	// nested loop, compares each element to every other element
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			// identifies duplicate, include i != j so element isn't considered duplicate of itself
			if (arr[i] == arr[j] && i != j) {
				break;
			}
			// if j reaches end of length then arr[i] has no duplicate
			if (j >= length-1) {
				return arr[i];
			}
		}
	}
	// sentinel value
	return -1;
}
