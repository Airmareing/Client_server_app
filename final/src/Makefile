CFLAGS  += -ffunction-sections -fdata-sections -fvisibility=hidden
LDFLAGS += -Wl,--gc-sections
test1: test1.o
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@
test1.o: test1.c
	$(CC) $(CFLAGS) -c $<
install:
	echo "Ok.."
romfs:
	$(ROMFSINST) -S test1 /bin/test1
	$(ROMFSINST) -S ../init.d/S99test1 /etc/rc.d/S99test1
	$(ROMFSINST) -s /etc/rc.d/S99test1 /etc/init.d/test1
clean:
	rm -f *.o test1
