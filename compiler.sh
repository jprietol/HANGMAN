echo "Start the compiler process"
gcc -g ./lib/gui/interface.c ./lib/errors/debug.c ./lib/logic/words.c ./lib/logic/control.c -c
#gcc interface.o debug.o -D DEBUG main.c -o hangman && mv ./hangman ./definitive_file/app/
gcc  -g interface.o debug.o  words.o control.o -D DEBUG main.c  -o hangman -lpthread && mv ./hangman ./build/app/

mv ./*.o ./lib_compilers

chmod 755 ./build/app/hangman
