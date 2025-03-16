#ifndef HASH_BASE_HPP
#define HASH_BASE_HPP
#include<vector>
#include<string>
class HashBase{
    public:
        virtual std::vector<unsigned char> getHash(std::vector<unsigned char>& input) const;
        virtual std::string getHashName() const {return hashName;};
        virtual int getHashLength() const {return hashLength;};
        HashBase(){};
    private:
        const int hashLength = 0;
        const std::string hashName = "123"; 
};
#endif