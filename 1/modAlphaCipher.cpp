#include "modAlphaCipher.h"
#include <locale>
modAlphaCipher::modAlphaCipher(
    const std::wstring& wskey)
{
    //std::locale loc("ru_RU.UTF-8");
    //std::locale::global(loc);
    for (unsigned i=0; i<numAlpha.size(); i++) {
        alphaNum[numAlpha[i]]=i;
    }
    key = convert(getValidKey(wskey));
}
std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    //std::locale loc("ru_RU.UTF-8");
    //std::locale::global(loc);
    std::vector<int> work = convert(getValidOpenText(open_text));
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}
std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
    //std::locale loc("ru_RU.UTF-8");
    //std::locale::global(loc);
    std::vector<int> work = convert(getValidCipherText(cipher_text));
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}
inline std::vector<int> modAlphaCipher::convert(const std::wstring& ws)
{
    //std::locale loc("ru_RU.UTF-8");
    //std::locale::global(loc);
    std::vector<int> result;
    for(auto c:ws) {
        result.push_back(alphaNum[c]);
    }
    return result;
}
inline std::wstring modAlphaCipher::convert(const std::vector<int>& v)
{
    //std::locale loc("ru_RU.UTF-8");
    //std::locale::global(loc);
    std::wstring result;
    for(auto i:v) {
        result.push_back(numAlpha[i]);
    }
    return result;
}
inline std::wstring modAlphaCipher::getValidKey(const std::wstring & ws)
{
    //std::locale loc("ru_RU.UTF-8");
    //std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> codec;
    if (ws.empty())
        throw cipher_error("Пустой ключ");
    std::wstring tmp(ws);
    std::string s = codec.to_bytes(ws);
    for (auto & c:tmp) {
        if (!iswalpha(c)) {
            throw cipher_error(std::string("Неправильный формат ключа") + s);
        }
        if (iswlower(c))
            c = towupper(c);
    }
    return tmp;
}
inline std::wstring modAlphaCipher::getValidOpenText(const std::wstring & ws)
{
    //std::locale loc("ru_RU.UTF-8");
    //std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> codec;
    std::wstring tmp;
    for (auto c:ws) {
        if (iswalpha(c)) {
            if (iswlower(c))
                tmp.push_back(towupper(c));
            else
                tmp.push_back(c);
        }
    }
    if (tmp.empty())
        throw cipher_error("Пустой текст");
    return tmp;
}
inline std::wstring modAlphaCipher::getValidCipherText(const std::wstring & ws)
{
    //std::locale loc("ru_RU.UTF-8");
    //std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> codec;
    if (ws.empty())
        throw cipher_error("Пустой текст");
    for (auto c:ws) {
        std::string s = codec.to_bytes(ws);
        if (!iswupper(c))
            throw cipher_error(std::string("Неверный формат текста")+s);
    }
    return ws;
}
