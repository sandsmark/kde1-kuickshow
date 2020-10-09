VER = `cat src/version.h | grep \" | cut -f3 -d' ' | sed -e 's/\"//g'`

# These will be the subdirectories of this directory
SUBDIRS = src po etc pics doc

release:
	export cdir=`pwd`; \
	export ver=$(VER); \
	export version=$$ver; \
	export packname=kuickshow-$$version; \
	export kdate=`date +%D`; \
	cp -ar $$cdir $$cdir.release && \
	cd $$cdir.release && cat kuickshow.spec.in | \
		sed -e "s#KUICKSHOWVERSION#$$version#" > $$packname.spec && \
	cat kuickshow.lsm.in | \
		sed -e "s#KUICKSHOWVERSION#$$version#" \
		    -e "s#KUICKSHOWDATE#$$kdate#" > $$packname.lsm && \
	$(MAKE) maintainer-clean && \
	find . -type d -name CVS | xargs rm -rf && \
	find . -type f -name "*~" | xargs rm -f && \
	$(MAKE) -f Makefile.cvs dist && \
	cd $$cdir.release/.. && mv kuickshow.release $$packname && \
	tar cfz $$packname.tar.gz $$packname
