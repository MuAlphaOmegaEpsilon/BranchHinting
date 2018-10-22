### COLORING SCHEME ###
ORANGE='\033[0;33m'
RC='\033[0m' # Remove color

### SCRIPT PART ###
mkdir build
cd build

printf "${ORANGE}STARTING CMAKE ${RC}\n"
cmake .. -DTEST=ON

printf "\n${ORANGE}STARTING MAKE ${RC}\n"
make

printf "\n${ORANGE}STARTING TESTING PHASE ${RC}\n"
make test

cd ..
rm -r build
