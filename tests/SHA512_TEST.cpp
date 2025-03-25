#include <gtest/gtest.h>
#include "SHA512Hasher.hpp"
#include <iomanip>
class SHA512_TEST : public ::testing::Test{
    public:
        SHA512_TEST(){
            hasher = new SHA_512_Hasher;
        }
        SHA_512_Hasher* hasher;
};
TEST_F(SHA512_TEST,AB_TEST){
    std::vector<std::vector<unsigned char>> inputs;
    std::vector<std::string> stringInputs = { 
        "123321", // 1
        "i love C++ very much", // 2
        "I love writing tests for all this code", // 3
        "Hire me please, I really need this job", //4
        "Here should be a very-very-very-very-very-very long line to check the work with big " 
        "objects to double check, that everything works as expected and nothing breaks half the way", //5
        "a", //6
        "b ", // 7
        "I could write a poem on how interesting it is to test code in C++", // 8
        "I ran out of ideas for strings", // 9
        "This is last string, wish me luck on testing" // 10
    };
    std::vector<std::string> expectedStrings = {
        "ebbcfecbb97654304f3aee0228236ec4d94fa0593ea1ec8236fc3e2b9e6b01546d9ee62550d8ff30d3df9edc65517caa75dcb6dd358e11a9ec5d7cdf8911b0c0", // 1
        "c97146794eb3cc4d9625b63a75b1eb69c60230dab883318ee78227c21f0a58243abb0335959feae1e17a9c6baecfba6df1777fd3ddcef94c527f7c5237b78925", // 2
        "b7a43766a56eebc5015d8fb8b927fc24658ad9d1ea99be201de894f0051da6e3c8e7c833292fc80fb4caf3b8e88fc58d2c4c23b9a4f136ce2aa6697d993c2c49", // 3
        "8899321ce3d3801eced2bc28a613b19ab5f94025a7b32857f0387205b2097468f298473cde1c849a5ede62a0f7fe3240ec928661617849c6d72881a953f8467a", // 4
        "2c2a2711423273b30d4350e303444704a9e89f97e2b051a12bdc7c53d5f010986a532194fa8a7f6df1e1aebdd50773ad9067d409378119088e7a06294c06663e", // 5
        "1f40fc92da241694750979ee6cf582f2d5d7d28e18335de05abc54d0560e0f5302860c652bf08d560252aa5e74210546f369fbbbce8c12cfc7957b2652fe9a75", // 6
        "4d1cce38101a4718799e0c4148875d16d40ea4d89bd50d81ef72e22ae66ef35b91ff4d278e4fdb6d62f5e9ebd3337c579466c5d3096b85e0ba492f90d1f0eb80", // 7
        "3ef9c1b2d76db041af99a15c1a9656ff5a0a7bc1a18ba4f88f1fe042547aef6b604f08f44a3ae127dbe9955af8852a30d341100b46b74476022fdd74ba3f52ab", // 8
        "99343de579db42a9031a267faa493556e8baf6b8d5fadb446d5db03d044f537ddcf825771995956b467789f4d685f685fa6ba6d7a0b2728b312c08cd9a244909", // 9
        "2e1cd99dc14d201e6edb63d22578cbf6fa85e37dcdf07cf43a854241d7c862ffb44fa25afeba9932e2bcdbd73c0cf2d3a1899b7adb870e73a7285436d4d83ca9", // 10
    };
    std::vector<std::vector<unsigned char>> expectedVector;
    for(std::string &str: expectedStrings){
        std::vector<unsigned char> hash;
        for (size_t i = 0; i < str.size(); i += 2) {
            std::string byteString = str.substr(i, 2);
            unsigned char byte = static_cast<unsigned char>(std::stoi(byteString, nullptr, 16));
            hash.push_back(byte);
        }
        expectedVector.push_back(hash);
    }
    for(auto &i:stringInputs){
        std::vector<unsigned char> input(i.begin(),i.end());
        inputs.push_back(input);
    }
    for(int i = 0;i<stringInputs.size();i++){
        EXPECT_EQ(hasher->getHash(inputs[i]),expectedVector[i]);
    }
}

TEST_F(SHA512_TEST,AA_TEST){
    for(unsigned char i = 0;i<255;i++){
        std::vector<unsigned char> vctr(32,i);
        EXPECT_EQ(hasher->getHash(vctr),hasher->getHash(vctr));
    }
}
