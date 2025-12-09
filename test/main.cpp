#include <cstring>
#include <iostream>
#include <string>
extern "C" void rc_4(const unsigned char *key, size_t keylen,
                     unsigned char *data, size_t datalen);

extern "C" char my_rand();
extern "C" void my_rand_set_seed();

extern "C" size_t read_from_file(const char* filename,
                                unsigned char* buffer,
                                size_t maxlen);


int main() {
    // my_rand_set_seed();
    // unsigned char key[] = { 'k','e','y' };
    // unsigned char data[] = "Hello World";
    // size_t n = strlen((char*)data);

    // std::cout << "Before: " << data << "\n";
    // rc_4(key, sizeof(key), data, n);
    // std::cout << "Encrypted (raw bytes): ";
    // for(size_t i=0;i<n;i++) printf("%02X ", data[i]);
    // std::cout << "\n";

    // rc_4(key, sizeof(key), data, n); // decrypt
    // std::cout << "After: " << data << "\n";
    // const char *chars = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM_!?.,@#$%^&*-+=";
    // unsigned char *buff = new unsigned char[40];
    // generate(buff, 32);
    // std::string str;
    // for (int i = 0; i < 32; i++){
    //     char ch = chars[buff[i]%68];
    //     str.push_back(ch);
    // }
    // std::cout << str << std::endl;

    // const char *filename = "file.txt";
    // unsigned char *buffer = new unsigned char[256];

    // int a = read_from_file(filename, buffer, 256);

    // std::string str = (const char*)buffer;

    // std::cout << str << '\n';
    char *buffer = "abc\0\0";
    std::string str = std::string(buffer, 4).c_str();

    std::cout << str.size() << '\n';

    return 0;
}
