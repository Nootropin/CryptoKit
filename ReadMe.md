# What is the project
The project's purpose is to make easy to use GUI tool for encrypting, cyphering, hashing and other cryptographic functions in simple GUI interface
# Requirements
This project for work requires
- OpenSSL
- QT6 
## Requirements installation
You can use bash script name lib.sh located in root folder or install libraries manually
### Script installation
```bash
bash lib.sh
```
### Manual installation
#### Debian/Ubuntu (APT)
```bash
sudo apt update
sudo apt install -y openssl libssl-dev qt6-base-dev qt6-tools-dev qt6-tools-dev-tools
```
#### Arch Linux (Pacman)
```bash
sudo pacman -Syu 
sudo pacman -S --noconfirm openssl qt6-base qt6-tools
```
#### Fedora (DNF)
```bash
sudo dnf install -y openssl openssl-devel qt6-qtbase-devel qt6-linguist qt6-qttools-devel
```
#### macOS (Homebrew)
```bash
brew install openssl qt6
```
# Building 
🔴 <span style="font-size: 20px;color: red;">__!Remember to install requied libraries!__</span>
## Build executable on Linux
```bash
git clone https://github.com/Nootropin/CryptoKit
cd CryptoKit
mkdir build
cd build
cmake ..
make -j4
./main
```
## Build tests
```bash
git clone https://github.com/Nootropin/CryptoKit
cd CryptoKit
mkdir build
cd build
cmake -DBUILD_TESTS=ON ..
make -j4 tests
./runTests
```
# ToDo
- Implement new algorithms
- Make key derive function choose for encryption
- Implement digital signature and assymetric encryption
- Make choose of hash and encrypted output (Base64, binary, hex and etc...)
- Improve design
- Improve file IO 
- Improve error handling and GUI feedback
- Document all code
- Write tests