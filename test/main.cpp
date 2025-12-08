#include <cstring>
#include <iostream>
extern "C" void rc_4(const unsigned char *key, size_t keylen,
                     unsigned char *data, size_t datalen);

extern "C" char my_rand();
extern "C" void my_rand_set_seed();

int main() {
    my_rand_set_seed();
    // unsigned char key[] = { 'k','e','y' };
    // unsigned char data[] = "Hellokldjsfdlsf;, RC4!";
    // size_t n = strlen((char*)data);

    // std::cout << "Before: " << data << "\n";
    // rc_4(key, sizeof(key), data, n);
    // std::cout << "Encrypted (raw bytes): ";
    // for(size_t i=0;i<n;i++) printf("%02X ", data[i]);
    // std::cout << "\n";

    // rc_4(key, sizeof(key), data, n); // decrypt
    // std::cout << "After: " << data << "\n";
    const char *chars = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM_!?.,@#$%^&*-+=";
    for (int i = 0; i < 10;i++){
        char ch = chars[(unsigned int)my_rand() % 68];
        std::cout << ch << '\n';
    }
    return 0;
}
