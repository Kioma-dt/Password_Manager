#include <iostream>
#include <string>
extern "C" void write_to_file(const char *filename,
                              const char *data,
                            size_t len);
extern "C" char my_rand();
extern "C" void my_rand_set_seed();

const char *chars = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM_!?.,@#$%^&*-+=";

int main(){
    my_rand_set_seed();
    const char *filename = "private_key.txt";
    std::string private_key;

    for (int i = 0; i < 16; i++){
        private_key.push_back(chars[(unsigned char)my_rand() % 80]);
    }

    write_to_file(filename, private_key.c_str(), private_key.size()); 
}