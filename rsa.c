#include <stdio.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp; }
        return a;
}


long long mod_inverse(long long e, long long phi) {
    long long t1 = 0, t2 = 1, r1 = phi, r2 = e;
    while (r2 != 0) {
        long long quotient = r1 / r2;
        long long t = t1 - quotient * t2; t1 = t2; t2 = t;
        long long r = r1 - quotient * r2; r1 = r2; r2 = r;
    }
    if (t1 < 0) t1 = t1 + phi;
    return t1;
}


long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1; base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1; base = (base * base) % mod;
    }
    return result;
}

=================================================================== */

int main() {


    long long p = 61;
    long long q = 53;


    long long n = p * q;


    long long phi = (p - 1) * (q - 1); // For 61 and 53, phi is 3120.


    long long e = 17;


    long long d = mod_inverse(e, phi); // d becomes 2753

    // --- Setup Complete! Let's print our keys ---
    printf("PUBLIC KEY  (Give to everyone) : Padlock (e)=%lld, Modulus (n)=%lld\n", e, n);
    printf("PRIVATE KEY (Keep hidden!)     : Key (d)=%lld, Modulus (n)=%lld\n\n", d, n);



    long long original_message = 65;


    long long ciphertext = mod_exp(original_message, e, n);

    printf("Original Message: %lld\n", original_message);
    printf("Encrypted Cipher: %lld (This is what travels across the internet)\n", ciphertext);


    long long decrypted_message = mod_exp(ciphertext, d, n);

    printf("Decrypted Message: %lld (The math perfectly reverses!)\n", decrypted_message);

    return 0;
}
