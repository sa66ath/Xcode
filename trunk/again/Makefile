#==============================================================================
#	Makefile for building Visual Studio projects on cygwin	
#							Mar. 4th 2012
#							Shoichi Ikeda
#==============================================================================

BUILD='/cygdrive/c/Windows/Microsoft.NET/Framework/v4.0.30319/MSBuild.exe' 

BUILD_FLAGS=/consoleloggerparameters:Verbosity=minimal

# CAT=cat
CAT=nkf -w

#------------------------------------------------------------------------------
all:	build

build:	
	$(BUILD) $(BUILD_FLAGS) | $(CAT)

rebuild:
	$(BUILD) $(BUILD_FLAGS) /t:$@ | $(CAT)

clean:
	$(BUILD) $(BUILD_FLAGS) /t:$@ | $(CAT)

