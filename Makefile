round: round.c
	gcc -o round round.c -lm
my_seq: my_seq.c
	gcc -o my_seq my_seq.c
my_grep: my_grep.c
	gcc -o my_grep my_grep.c
my_hexdump: my_hexdump.c
	gcc -o my_hexdump my_hexdump.c
all: round my_seq my_grep my_hexdump

round-test: round.c
	./round -k 1024
my_seq-test: my_seq.c
	./my_seq -f 1 -l 10
my_grep-test: my_grep.c
	./my_grep -c Hi text.txt
my_hexdump-test: my_hexdump.c
	./my_hexdump /etc/issue
test: round-test my_seq-test my_grep-test my_hexdump-test

clean:
	rm round my_seq my_grep my_hexdump
