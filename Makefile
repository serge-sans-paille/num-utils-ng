
#	File : Makefile
#	Compile all files in each directory

PROJECT	= num-utils-nv
DIST	= $(PROJECT)


TARFILE	= $(DIST).tar.gz

all:
	$(MAKE) -C src all

clean :
	$(MAKE)	-C src clean

check :
	$(MAKE) -C tests check

dist: $(TARFILE)


$(TARFILE):
	$(RM) -fr $(DIST)
	$(RM) -f $(TARFILE)
	mkdir $(DIST)
	cp ./README $(DIST)
	cp ./Makefile $(DIST)
	cd $(DIST)
	mkdir $(DIST)/src
	cd ..
	cp ./src/*.c $(DIST)/src
	cp ./src/Makefile $(DIST)/src
	cp -R ./docs $(DIST) 
	tar zchf $(DIST).tar.gz $(DIST) --exclude CVS
	$(RM) -r $(DIST)


