#include <gtest/gtest.h>
#include "SHA1Hasher.hpp"
#include <iomanip>
class SHA1_TEST : public ::testing::Test{
    public:
        SHA1_TEST(){
            hasher = new SHA_1_Hasher;
        }
        SHA_1_Hasher* hasher;
};
TEST_F(SHA1_TEST,AB_TEST){
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
        "4d9012b4a77a9524d675dad27c3276ab5705e5e8", // 1
        "94eb8cc5cebb9598da57e04fdb45a45d84e08d28", // 2
        "68915e96c323c8d080ccdc7dfa9df4288d28c0d3", // 3
        "9b3b161cfc6b904973b8f96f4ec48085e5a629f3", // 4
        "128e68c7e6ed1fa6be110a1a9d1a1a969ea1bae7", // 5
        "86f7e437faa5a7fce15d1ddcb9eaeaea377667b8", // 6
        "e1bc846440ec2fb557a5a271e785cd4c648883fa", // 7
        "0853777e7c9a807b3aeb2df03be6e9a70a5e1ff5", // 8
        "b681d97d0752b56a75cc5ac34b75161e348173a3", // 9
        "cde955288814accdce65678253d83bf28fcf9b66", // 10
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

TEST_F(SHA1_TEST,AA_TEST){
    for(unsigned char i = 0;i<255;i++){
        std::vector<unsigned char> vctr(32,i);
        EXPECT_EQ(hasher->getHash(vctr),hasher->getHash(vctr));
    }
}
