echo "Start the hangman game"

cd app/
ln -s ../logs logs_ln
ln -s ../words words_bank.ln
./hangman
