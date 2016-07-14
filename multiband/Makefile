#==============================================================================
#	Makefile for building Visual Studio projects on cygwin	
#							Mar. 4th 2012
#							Shoichi Ikeda
#==============================================================================

BUILD='/cygdrive/c/Windows/Microsoft.NET/Framework/v4.0.30319/MSBuild.exe' 

BUILD_CONFIG=Release
# BUILD_CONFIG=Debug
BUILD_FLAGS=/consoleloggerparameters:Verbosity=minimal /property:Configuration=$(BUILD_CONFIG)


# CAT=cat
CAT=nkf -w


DOXYGEN=doxygen
DOXYGEN_FLAG=
DOXYGEN_FILE=Doxyfile
DOXYGEN_DIR=./html

SVN=svn

# VSTHOST='C:\Program Files\vsthostx64\vsthost'
VSTHOST=vsthost

#------------------------------------------------------------------------------
build:	
	$(BUILD) $(BUILD_FLAGS) *.sln | $(CAT)

rebuild:
	$(BUILD) $(BUILD_FLAGS) /t:$@ *.sln | $(CAT)

clean:
	$(BUILD) $(BUILD_FLAGS) /t:$@ *.sln | $(CAT)

debug:	build vsthost

doc:
	rm -rf $(DOXYGEN_DIR)
	$(DOXYGEN) $(DOXYGEN_FLAG) $(DOXYGEN_FILE)

update:
	$(SVN) $@

commit:
	$(SVN) $@

vsthost:
	$(VSTHOST)

