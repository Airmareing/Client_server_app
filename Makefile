CC:=gcc
CFLAGS := -Wall -Werror -Wextra -pthread

all : clean build

build :
	${CC} ${CFLAGS} app.c errprocess.c -o app
	./app

clean :
	rm -f app
