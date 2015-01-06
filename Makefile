all: dict.txt
	mingw-gcc -O0 -DDEBUG=1 -g *.c -o cwg

clean:
	rm -R cwg *.dat Traditional_Dawg_Text_For_Word-List.txt *.dat.txt *.dot *.dSYM Numbered-Word-List.txt
