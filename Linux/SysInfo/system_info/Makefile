all: system_info

func.o: func.c
	g++ -c func.c


system_info.o: system_info.c
	g++ -c system_info.c

system_info: system_info.o func.o
	g++ system_info.o func.o -o system_info

