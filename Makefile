pi : main.c
	cc -o pi main.c -pthread -lm


clean :
	rm -f pi
