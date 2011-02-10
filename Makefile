
#	File : Makefile
#	Compile all files in each directory


#all: makefilesrc

#makefilesrc :
#	./src/Makefile    problem for now with this instruction

clear : clean clearsrc

clearsrc : cleansrc
	$(RM) -f ./src/numaverage

clean : cleansrc

cleansrc :
	$(RM) -f ./src/*.o
