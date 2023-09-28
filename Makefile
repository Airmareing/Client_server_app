CFLAGS  += -ffunction-sections -fdata-sections -fvisibility=hidden
LDFLAGS += -Wl,--gc-sections

CSA_EXEC = client-server-app
CSA_OBJS = app.o errprocess.o

all: $(CSA_EXEC)

$(CSA_EXEC): $(CSA_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(CSA_EXEC) $(CSA_OBJS)

app.o:
	$(CC) $(CFLAGS) -c app.c

errprocess.o:
	$(CC) $(CFLAGS) -c errprocess.c

server :
	${CC} ${CFLAGS} server.c errprocess.c -o server

install:
	echo ok

romfs:
	$(ROMFSINST) client-server-app /bin/client-server-app

clean:
	rm -f *.o $(CSA_EXEC)