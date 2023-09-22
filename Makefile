CC:=gcc
CFLAGS := -Wall -Werror -Wextra -pthread

all : clean build

build :
	${CC} ${CFLAGS} app.c errprocess.c -o app
	./app

server : clean
	${CC} ${CFLAGS} server.c errprocess.c -o server
	./server

clean :
	rm -f app server
