
#	File : Makefile
#	Compile all files in each directory


all:
	$(MAKE) -C src $@

clear : clean clearsrc

clearsrc : cleansrc
	$(RM) -f ./src/numaverage

clean : cleansrc

cleansrc :
	$(RM) -f ./src/*.o
