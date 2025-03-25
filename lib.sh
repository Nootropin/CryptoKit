if command -v apt >/dev/null; then
    sudo apt update && sudo apt install -y openssl libssl-dev qt6-base-dev qt6-tools-dev qt6-tools-dev-tools
elif command -v pacman >/dev/null; then
    sudo pacman -Syu --noconfirm openssl qt6-base qt6-tools
elif command -v dnf >/dev/null; then
    sudo dnf install -y openssl openssl-devel qt6-qtbase-devel qt6-linguist qt6-qttools-devel
elif command -v brew >/dev/null; then
    brew install openssl qt6
elif command -v pacman >/dev/null && [[ "$(uname -o)" == "Msys" ]]; then
    pacman -Syu --noconfirm mingw-w64-x86_64-openssl mingw-w64-x86_64-qt6
else
    echo "Unsupported OS. Install OpenSSL and Qt6 manually."
fi