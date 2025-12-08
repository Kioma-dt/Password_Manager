#include <iostream>
#include <cstdlib>
#include <string>

extern "C" void rc_4(const unsigned char *key, size_t keylen,
                     unsigned char *data, size_t datalen);

extern "C" char my_rand();
extern "C" void my_rand_set_seed();


bool is_ui_loop_cont = true;

void exit_program();
std::string trim_string(std::string str);
bool check_option_main(std::string option);
bool check_char_in_str(char ch, std::string str);

int main(){

    std::string user_option;

    while (is_ui_loop_cont){
        system("clear");
        std::cout << std::string(20, '-');
        std::cout << "\nWelcome to your Password Manager!\n";
        std::cout << std::string(20, '-');
        std::cout << "\nSelect menu option:\n";

        std::cout << "1. Show all password records (ciphered)\n";
        std::cout << "2. Show all password records (deciphered)\n";
        std::cout << "3. Select password record\n";
        std::cout << "4. Create password record\n";
        std::cout << "5. Generate your private key\n";
        std::cout << "6. Exit\n";

        std::cout << "Option: ";
        std::cin >> user_option;
        system("clear");

        if (!check_option_main(user_option)){
            std::cout << "Wrong menu option!\n";
            std::cout << "Press any key ...\n";
            getchar();
            system("clear");
        }

        switch (user_option.front()) {
            case '6':
                exit_program();
        };
    }
}

void exit_program(){
    is_ui_loop_cont = false;
}

std::string trim_string(std::string str){
    int n = str.size();

    int pos_trim = 0;
    int n_trim = n;

    for (int i = 0; i < n; i++){
        if (str[i] != ' '){
            break;
        }
        pos_trim++;
    }

    for (int i = n - 1; i >= 0; i--){
        if (str[i] != ' '){
            break;
        }
        n_trim--;
    }

    return str.substr(pos_trim, n_trim);
}

bool check_option_main(std::string option){
    option = trim_string(option);

    if (option.size() != 1){
        return false;
    }

    return check_char_in_str(option.front(), "123456");
}

bool check_char_in_str(char ch, std::string str){
    for (int i = 0; i < str.size(); i++){
        if (str[i] == ch){
            return true;
        }
    }

    return false;
}
