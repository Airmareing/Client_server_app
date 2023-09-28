CFLAGS  += -ffunction-sections -fdata-sections -fvisibility=hidden
LDFLAGS += -Wl,--gc-sections
test1: test1.o
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@
test1.o: test1.c
	$(CC) $(CFLAGS) -c $<
install:
	echo "Ok.."
romfs:
	$(ROMFSINST)  test1 /bin/test1
	ln -sf /etc/test1 $(ROMFSDIR)/etc/init.d/S99test1
clean:
	rm -f *.o test1
