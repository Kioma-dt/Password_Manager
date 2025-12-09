#include <iostream>
#include <cstdlib>
#include <limits>
#include <string>
#include <filesystem>
#include <vector>

extern "C" void rc_4(const char *key, size_t keylen,
                     char *data, size_t datalen);

extern "C" char my_rand();
extern "C" void my_rand_set_seed();

extern "C" size_t read_from_file(const char* filename,
                                char* buffer,
                                size_t maxlen);

extern "C" void write_to_file(const char *filename,
                              const char *data,
                            size_t len);


bool is_ui_loop_cont = true;
const char *chars = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM_!?.,@#$%^&*-+=";
std::string private_key;

void exit_program();
std::string trim_string(std::string str);
bool check_option(std::string option, std::string possible_options);
bool check_char_in_str(char ch, std::string str);

std::vector<std::pair<std::string,std::string>> read_records();
void write_records(std::vector<std::pair<std::string,std::string>> records);
std::string generate_password();
std::string create_password();

void show_records_ciphered();
void show_records_deciphered();
void create_record();

int main(){
    my_rand_set_seed();
    const char *private_key_file = "data/private_key.txt";
    char private_key_buffer[16];

    if(read_from_file(private_key_file, private_key_buffer, 16) != 16){
        std::cout << "No Private Key!\n";
        std::cout << "Execute command \" ~/Documents/Asik/Lab_7/PrivateKey/create_private_key\n & mv private_key.txt data/private_key.txt\"!\n";
        system("echo \" ~/Documents/Asik/Lab_7/PrivateKey/create_private_key & mv private_key.txt data/private_key.txt\" | xclip -selection clipboard");
        std::cout << "Press any key ...\n";
        getchar();

        return 0;
    }
    private_key = (const char *)private_key_buffer;

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
        std::cout << "5. Exit\n";

        std::cout << std::string(20, '-') << '\n';
        std::cout << "Option: ";
        std::getline(std::cin, user_option);
        user_option = trim_string(user_option);
        system("clear");

        if (!check_option(user_option,"12345")){
            std::cout << "Wrong menu option!\n";
            std::cout << "Press any key ...\n";
            getchar();
            system("clear");
            continue;
        }

        switch (user_option.front()) {
            case '1':
                show_records_ciphered();
                break;
            case '2':
                show_records_deciphered();
                break;
            case '4':
                create_record();
                break;
            case '5':
                exit_program();
                break;
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

bool check_option(std::string option, std::string possible_options){
    option = trim_string(option);

    if (option.size() != 1){
        return false;
    }

    return check_char_in_str(option.front(), possible_options);
}

bool check_char_in_str(char ch, std::string str){
    for (int i = 0; i < str.size(); i++){
        if (str[i] == ch){
            return true;
        }
    }

    return false;
}

std::vector<std::pair<std::string,std::string>>  read_records(){
    const char *records_file = "data/passwords.txt";
    char buffer[256];

    read_from_file(records_file, buffer, 256);

    std::string str = (const char *)buffer;

    int i = 0, j = 0;
    std::string temp_str;
    std::vector<std::pair<std::string, std::string>> res;

    if (std::filesystem::exists(records_file) 
    && !std::filesystem::is_empty(records_file)){

        for (int i = 0; i < str.size(); i++){
            if (str[i] == ' '){
                temp_str = str.substr(j, i - j);
                j = i + 1;
            }
            if (str[i] == '\n'){
                res.push_back(std::make_pair(temp_str, str.substr(j, i - j)));
                j = i + 1;
            }
        }
    }



    return res;
}

void write_records(std::vector<std::pair<std::string,std::string>> records){
    const char *records_file = "data/passwords.txt";
    std::string res = "";

    if (std::filesystem::exists(records_file)){
        
        for (int i = 0; i < records.size();i++){
            res += records[i].first + ' ' + records[i].second +'\n';
        }


        write_to_file(records_file, res.c_str(), res.size()); 
    }

}

void create_record(){
    system("clear");
    std::cout << std::string(20, '-');
    std::cout << "\nCreating password record...\n";
    std::cout << std::string(20, '-') << '\n';
    std::string description, password;


    while(true){
        std::cout << "Enter description for your password (8 to 32 chars): ";
        std::getline(std::cin, description);
        if (description.size() >= 8 and description.size() <= 32){
            break;
        }
        system("clear");
        std::cout << "Wrong description size!\n";
        std::cout << "Press any key ...\n";
        getchar();
        system("clear");
        std::cout << std::string(20, '-') << '\n';
        std::cout << "Creating password record...\n";
        std::cout << std::string(20, '-') << '\n';
    }

    std::string user_option;
    bool cont_loop = true;


    while (cont_loop){
        system("clear");
        std::cout << std::string(20, '-');
        std::cout << "\nCreating password record...\n";
        std::cout << std::string(20, '-') << '\n';


        std::cout << "\nSelect menu option:\n";

        std::cout << "1. Generate Password\n";
        std::cout << "2. Create Password\n";

        std::cout << std::string(20, '-') << '\n';
        std::cout << "Option: ";
        std::getline(std::cin, user_option);
        user_option = trim_string(user_option);
        system("clear");

        if (!check_option(user_option,"12")){
            std::cout << "Wrong menu option!\n";
            std::cout << "Press any key ...\n";
            getchar();
            system("clear");
            continue;
        }

        switch (user_option.front()) {
            case '1':
                password = generate_password();
                cont_loop = false;
                break;
            case '2':
                password = create_password();
                cont_loop = false;
                break;
        };
    }
    char temp[32];
    password.copy(temp,password.size(), 0);

    rc_4(private_key.c_str(), private_key.size(), temp, password.size());
    std::vector<std::pair<std::string, std::string>> records = read_records();
    records.push_back(std::make_pair(description, temp));
    write_records(records);

    system("clear");
    std::cout << std::string(20, '-') << '\n';
    std::cout << "Creating password record...\n";
    std::cout << std::string(20, '-') << '\n';
    std::cout << "Successfully created record:\n";
    std::cout << description << ' ' << password << '\n';
    std::cout << "Press any key ...\n";
    getchar();
    system("clear");
}

std::string generate_password(){
    std::string password;

    for (int i = 0; i < 32; i++){
        password.push_back(chars[(unsigned char)my_rand() % 79]);
    }

    return password;
}

std::string create_password(){
    system("clear");
    std::string password;
    while (true){
        std::cout << "Enter your password (8 to 32 chars): ";
        std::getline(std::cin, password);
        if (password.size() >= 8 and password.size() <= 32){
            break;
        }
        system("clear");
        std::cout << "Wrong password size!\n";
        std::cout << "Press any key ...\n";
        getchar();
        system("clear");
    }

    return password;
}

void show_records_deciphered(){
    std::cout << std::string(20, '-') << '\n';
    std::cout << "Passwords deciphered:\n";
    std::cout << std::string(20, '-') << '\n';
    std::vector<std::pair<std::string, std::string>> records = read_records();

    for (int i = 0; i < records.size(); i++){
        std::string description = records[i].first;
        std::string password = records[i].second;
        char temp[32];
        password.copy(temp,password.size(), 0);
        rc_4(private_key.c_str(), private_key.size(), temp, password.size());

        temp[password.size()] = '\0';
        password = temp;
        std::cout << i + 1 << ". " << description << ' ' << password << '\n';
    }

    std::cout << "Press any key ...\n";
    getchar();
    system("clear");
}
void show_records_ciphered(){
    std::cout << std::string(20, '-') << '\n';
    std::cout << "Passwords ciphered:\n";
    std::cout << std::string(20, '-') << '\n';
    std::vector<std::pair<std::string, std::string>> records = read_records();

    for (int i = 0; i < records.size(); i++){
        std::string description = records[i].first;
        std::string password = records[i].second;
        std::cout << i + 1 << ". " << description << ' ' << password << '\n';
    }
    std::cout << "Press any key ...\n";
    getchar();
    system("clear");
}