#include <gtest/gtest.h>
#include "SHA256Hasher.hpp"
#include <iomanip>
class SHA256_TEST : public ::testing::Test{
    public:
        SHA256_TEST(){
            hasher = new SHA_256_Hasher;
        }
        SHA_256_Hasher* hasher;
};
TEST_F(SHA256_TEST,AB_TEST){
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
        "a320480f534776bddb5cdb54b1e93d210a3c7d199e80a23c1b2178497b184c76", // 1
        "23ef5bc444b253a86e0c7d7867319721db8098c76a13bba8847a63cd5032cc08", // 2
        "97fcbff534246572ed56d54308db820532055bf8a39f319486f40b5ae51aa980", // 3
        "1c5f019d83d50f58126a1816ec2acd3ccfce3f22ae9e3a69585bc580964aaf02", // 4
        "58ff4f334732bbaaeaa24f9b8cd640ac899bca575ac9f5e50bac89cb15b3de8d", // 5
        "ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb", // 6
        "f9b2c9ca5d58ec71e63623240c420de81a992cc44551b036a9a88b42c6ef2076", // 7
        "1e5f68c50ec56a3f5980bbcee513bce0e2a4d4406fefb6d6907c2def2f863d4c", // 8
        "0fc0ed0d299ac64ec10ce85da63fb15cbba1ace70c5010a37e5cbbf737adee18", // 9
        "caefda7f338b6a9ec19a840416089acad546fa278da6cb3fb6b6dc6bdc2bcf60", // 10
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

TEST_F(SHA256_TEST,AA_TEST){
    for(unsigned char i = 0;i<255;i++){
        std::vector<unsigned char> vctr(32,i);
        EXPECT_EQ(hasher->getHash(vctr),hasher->getHash(vctr));
    }
}
