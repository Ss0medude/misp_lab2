#include <iostream>
#include <cctype>
#include  "modAlphaCipher.h"
#include <locale>
#include <codecvt>
#include <typeinfo>
using namespace std;
void check(const wstring& Text, const wstring& key, const bool destructCipherText=false)
{
    //std::locale loc("ru_RU.UTF-8");
    //std::locale::global(loc);
    try {//Чтобы программа не завершалась на обработке исключений вставим обработку исключений
        wstring cipherText;
        wstring decryptedText;
        modAlphaCipher cipher(key);
        cipherText = cipher.encrypt(Text);
        if (destructCipherText)
            cipherText.front() = towlower(cipherText.front());
        decryptedText = cipher.decrypt(cipherText);
        wcout<<L"key="<<key<<endl;
        wcout<<Text<<endl;
        wcout<<cipherText<<endl;
        wcout<<decryptedText<<endl;
    } catch (const cipher_error & e) {
        wcerr<<"Error:  "<<e.what()<<endl;
    }

}

int main()
{
    locale loc("ru_RU.UTF-8");
    std::locale::global(loc);
    check(L"КУРСОВАЯ",L"КЛЮЧ");
    check(L"ХОЧУКУРСОВУЮСДАТЬ",L"");
    check(L"ОЧЕНЬХОЧУ",L"КЛЮЧ000");
    check(L"ОЧЕНЬ ХОЧУ СДАТЬ КУРСОВУЮ",L"КЛЮЧ");
    check(L"000",L"КЛЮЧИК");
}
