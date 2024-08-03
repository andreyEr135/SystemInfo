all: com_data

func.o: func.c
	g++ -c func.c


com_data.o: com_data.c
	g++ -c com_data.c

com_data: com_data.o func.o
	g++ com_data.o func.o -o com_data

