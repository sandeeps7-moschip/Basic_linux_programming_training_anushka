#Define Subdirectories
 
SUB_DIRS = ex3-1/build 
 
#Build all sub directories
 
all:
	@for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir; \
	done

 
clean:
	@for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	
