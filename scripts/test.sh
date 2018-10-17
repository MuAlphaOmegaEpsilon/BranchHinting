### COLORING SCHEME ###
ORANGE='\033[0;33m'
RC='\033[0m' # Remove color

### SCRIPT PART ###
cd ..
cd build

echo -e ${ORANGE}STARTING CMAKE${RC}
cmake .. -DTEST=ON

printf "\n${ORANGE}STARTING MAKE${RC}\n"
make

printf "\n${ORANGE}STARTING TESTING PHASE${RC}\n"
make test

printf "\n${ORANGE}CLEANING BUILD FOLDER${RC}\n"
rm -r *
printf "Removed all files.\n\n"
