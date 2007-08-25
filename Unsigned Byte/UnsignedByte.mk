##
## Auto Generated makefile, please do not edit
##
WorkspaceName=MUD Development
WorkspacePath=/home/sverre/code/ub
ProjectName=UnsignedByte

## DebugUnicode
ifeq ($(type),DebugUnicode)
ConfigurationName=DebugUnicode
IntermediateDirectory=Intermediate
OutDir=$(IntermediateDirectory)
LinkerName=g++
ArchiveTool=ar rcu
SharedObjectLinkerName=g++ -shared 
ObjectSuffix=.o
DebugSwitch=-g
IncludeSwitch=-I
LibrarySwitch=-l
OutputSwitch=-o
LibraryPathSwitch=-L
PreprocessorSwitch=-D
SourceSwitch=-c
CompilerName=g++
RcCompilerName=
OutputFile=../UnsignedByte
Preprocessors=
CmpOptions=-g -Wall $(Preprocessors)
RcCmpOptions=
LinkOptions=
IncludePath=$(IncludeSwitch). $(IncludeSwitch)../include 
RcIncludePath=
Libs=$(LibrarySwitch)mysqlite3 $(LibrarySwitch)myresource $(LibrarySwitch)pthread $(LibrarySwitch)dl $(LibrarySwitch)mysqlite3 
LibPath=$(LibraryPathSwitch). $(LibraryPathSwitch).. 
endif

Objects=$(IntermediateDirectory)/Account$(ObjectSuffix) $(IntermediateDirectory)/Area$(ObjectSuffix) $(IntermediateDirectory)/Cache$(ObjectSuffix) $(IntermediateDirectory)/Character$(ObjectSuffix) $(IntermediateDirectory)/Colour$(ObjectSuffix) $(IntermediateDirectory)/DatabaseMgr$(ObjectSuffix) $(IntermediateDirectory)/EditorAccount$(ObjectSuffix) $(IntermediateDirectory)/EditorArea$(ObjectSuffix) $(IntermediateDirectory)/EditorColour$(ObjectSuffix) $(IntermediateDirectory)/EditorLoginAccount$(ObjectSuffix) \
	$(IntermediateDirectory)/EditorMobile$(ObjectSuffix) $(IntermediateDirectory)/EditorNewAccount$(ObjectSuffix) $(IntermediateDirectory)/EditorNewCharacter$(ObjectSuffix) $(IntermediateDirectory)/EditorOLC$(ObjectSuffix) $(IntermediateDirectory)/EditorPlaying$(ObjectSuffix) $(IntermediateDirectory)/EditorRoom$(ObjectSuffix) $(IntermediateDirectory)/EditorScript$(ObjectSuffix) $(IntermediateDirectory)/EditorSector$(ObjectSuffix) $(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/MCharacter$(ObjectSuffix) \
	$(IntermediateDirectory)/PCharacter$(ObjectSuffix) $(IntermediateDirectory)/Race$(ObjectSuffix) $(IntermediateDirectory)/Room$(ObjectSuffix) $(IntermediateDirectory)/Sector$(ObjectSuffix) $(IntermediateDirectory)/UBHandler$(ObjectSuffix) $(IntermediateDirectory)/UBSocket$(ObjectSuffix) $(IntermediateDirectory)/SQLSocket$(ObjectSuffix) $(IntermediateDirectory)/Command$(ObjectSuffix) $(IntermediateDirectory)/ub$(ObjectSuffix) $(IntermediateDirectory)/EditorCommand$(ObjectSuffix) \
	$(IntermediateDirectory)/GrantGroup$(ObjectSuffix) $(IntermediateDirectory)/Permission$(ObjectSuffix) $(IntermediateDirectory)/EditorGrantGroup$(ObjectSuffix) $(IntermediateDirectory)/EditorPermission$(ObjectSuffix) $(IntermediateDirectory)/OLCEditor$(ObjectSuffix) $(IntermediateDirectory)/Editor$(ObjectSuffix) $(IntermediateDirectory)/EditorString$(ObjectSuffix) 

##
## Main Build Tragets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	$(LinkerName) $(OutputSwitch) $(OutputFile) $(LinkOptions) $(Objects) $(LibPath) $(Libs)

makeDirStep:
	@test -d Intermediate || mkdir Intermediate

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Account$(ObjectSuffix): Account.cpp $(IntermediateDirectory)/Account$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Account.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Account$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Account$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Account$(ObjectSuffix) -MF$(IntermediateDirectory)/Account$(ObjectSuffix).d -MM Account.cpp

$(IntermediateDirectory)/Area$(ObjectSuffix): Area.cpp $(IntermediateDirectory)/Area$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Area.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Area$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Area$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Area$(ObjectSuffix) -MF$(IntermediateDirectory)/Area$(ObjectSuffix).d -MM Area.cpp

$(IntermediateDirectory)/Cache$(ObjectSuffix): Cache.cpp $(IntermediateDirectory)/Cache$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Cache.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Cache$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Cache$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Cache$(ObjectSuffix) -MF$(IntermediateDirectory)/Cache$(ObjectSuffix).d -MM Cache.cpp

$(IntermediateDirectory)/Character$(ObjectSuffix): Character.cpp $(IntermediateDirectory)/Character$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Character.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Character$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Character$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Character$(ObjectSuffix) -MF$(IntermediateDirectory)/Character$(ObjectSuffix).d -MM Character.cpp

$(IntermediateDirectory)/Colour$(ObjectSuffix): Colour.cpp $(IntermediateDirectory)/Colour$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Colour.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Colour$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Colour$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Colour$(ObjectSuffix) -MF$(IntermediateDirectory)/Colour$(ObjectSuffix).d -MM Colour.cpp

$(IntermediateDirectory)/DatabaseMgr$(ObjectSuffix): DatabaseMgr.cpp $(IntermediateDirectory)/DatabaseMgr$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) DatabaseMgr.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/DatabaseMgr$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/DatabaseMgr$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/DatabaseMgr$(ObjectSuffix) -MF$(IntermediateDirectory)/DatabaseMgr$(ObjectSuffix).d -MM DatabaseMgr.cpp

$(IntermediateDirectory)/EditorAccount$(ObjectSuffix): EditorAccount.cpp $(IntermediateDirectory)/EditorAccount$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) EditorAccount.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/EditorAccount$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorAccount$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorAccount$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorAccount$(ObjectSuffix).d -MM EditorAccount.cpp

$(IntermediateDirectory)/EditorArea$(ObjectSuffix): EditorArea.cpp $(IntermediateDirectory)/EditorArea$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) EditorArea.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/EditorArea$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorArea$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorArea$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorArea$(ObjectSuffix).d -MM EditorArea.cpp

$(IntermediateDirectory)/EditorColour$(ObjectSuffix): EditorColour.cpp $(IntermediateDirectory)/EditorColour$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) EditorColour.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/EditorColour$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorColour$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorColour$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorColour$(ObjectSuffix).d -MM EditorColour.cpp

$(IntermediateDirectory)/EditorLoginAccount$(ObjectSuffix): EditorLoginAccount.cpp $(IntermediateDirectory)/EditorLoginAccount$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) EditorLoginAccount.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/EditorLoginAccount$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorLoginAccount$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorLoginAccount$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorLoginAccount$(ObjectSuffix).d -MM EditorLoginAccount.cpp

$(IntermediateDirectory)/EditorMobile$(ObjectSuffix): EditorMobile.cpp $(IntermediateDirectory)/EditorMobile$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) EditorMobile.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/EditorMobile$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorMobile$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorMobile$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorMobile$(ObjectSuffix).d -MM EditorMobile.cpp

$(IntermediateDirectory)/EditorNewAccount$(ObjectSuffix): EditorNewAccount.cpp $(IntermediateDirectory)/EditorNewAccount$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) EditorNewAccount.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/EditorNewAccount$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorNewAccount$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorNewAccount$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorNewAccount$(ObjectSuffix).d -MM EditorNewAccount.cpp

$(IntermediateDirectory)/EditorNewCharacter$(ObjectSuffix): EditorNewCharacter.cpp $(IntermediateDirectory)/EditorNewCharacter$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) EditorNewCharacter.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/EditorNewCharacter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorNewCharacter$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorNewCharacter$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorNewCharacter$(ObjectSuffix).d -MM EditorNewCharacter.cpp

$(IntermediateDirectory)/EditorOLC$(ObjectSuffix): EditorOLC.cpp $(IntermediateDirectory)/EditorOLC$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) EditorOLC.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/EditorOLC$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorOLC$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorOLC$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorOLC$(ObjectSuffix).d -MM EditorOLC.cpp

$(IntermediateDirectory)/EditorPlaying$(ObjectSuffix): EditorPlaying.cpp $(IntermediateDirectory)/EditorPlaying$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) EditorPlaying.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/EditorPlaying$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorPlaying$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorPlaying$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorPlaying$(ObjectSuffix).d -MM EditorPlaying.cpp

$(IntermediateDirectory)/EditorRoom$(ObjectSuffix): EditorRoom.cpp $(IntermediateDirectory)/EditorRoom$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) EditorRoom.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/EditorRoom$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorRoom$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorRoom$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorRoom$(ObjectSuffix).d -MM EditorRoom.cpp

$(IntermediateDirectory)/EditorScript$(ObjectSuffix): EditorScript.cpp $(IntermediateDirectory)/EditorScript$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) EditorScript.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/EditorScript$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorScript$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorScript$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorScript$(ObjectSuffix).d -MM EditorScript.cpp

$(IntermediateDirectory)/EditorSector$(ObjectSuffix): EditorSector.cpp $(IntermediateDirectory)/EditorSector$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) EditorSector.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/EditorSector$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorSector$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorSector$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorSector$(ObjectSuffix).d -MM EditorSector.cpp

$(IntermediateDirectory)/main$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) main.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(ObjectSuffix).d -MM main.cpp

$(IntermediateDirectory)/MCharacter$(ObjectSuffix): MCharacter.cpp $(IntermediateDirectory)/MCharacter$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) MCharacter.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/MCharacter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MCharacter$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/MCharacter$(ObjectSuffix) -MF$(IntermediateDirectory)/MCharacter$(ObjectSuffix).d -MM MCharacter.cpp

$(IntermediateDirectory)/PCharacter$(ObjectSuffix): PCharacter.cpp $(IntermediateDirectory)/PCharacter$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) PCharacter.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/PCharacter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PCharacter$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/PCharacter$(ObjectSuffix) -MF$(IntermediateDirectory)/PCharacter$(ObjectSuffix).d -MM PCharacter.cpp

$(IntermediateDirectory)/Race$(ObjectSuffix): Race.cpp $(IntermediateDirectory)/Race$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Race.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Race$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Race$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Race$(ObjectSuffix) -MF$(IntermediateDirectory)/Race$(ObjectSuffix).d -MM Race.cpp

$(IntermediateDirectory)/Room$(ObjectSuffix): Room.cpp $(IntermediateDirectory)/Room$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Room.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Room$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Room$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Room$(ObjectSuffix) -MF$(IntermediateDirectory)/Room$(ObjectSuffix).d -MM Room.cpp

$(IntermediateDirectory)/Sector$(ObjectSuffix): Sector.cpp $(IntermediateDirectory)/Sector$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Sector.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Sector$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Sector$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Sector$(ObjectSuffix) -MF$(IntermediateDirectory)/Sector$(ObjectSuffix).d -MM Sector.cpp

$(IntermediateDirectory)/UBHandler$(ObjectSuffix): UBHandler.cpp $(IntermediateDirectory)/UBHandler$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) UBHandler.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/UBHandler$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UBHandler$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/UBHandler$(ObjectSuffix) -MF$(IntermediateDirectory)/UBHandler$(ObjectSuffix).d -MM UBHandler.cpp

$(IntermediateDirectory)/UBSocket$(ObjectSuffix): UBSocket.cpp $(IntermediateDirectory)/UBSocket$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) UBSocket.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/UBSocket$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UBSocket$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/UBSocket$(ObjectSuffix) -MF$(IntermediateDirectory)/UBSocket$(ObjectSuffix).d -MM UBSocket.cpp

$(IntermediateDirectory)/SQLSocket$(ObjectSuffix): SQLSocket.cpp $(IntermediateDirectory)/SQLSocket$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) SQLSocket.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/SQLSocket$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SQLSocket$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/SQLSocket$(ObjectSuffix) -MF$(IntermediateDirectory)/SQLSocket$(ObjectSuffix).d -MM SQLSocket.cpp

$(IntermediateDirectory)/Command$(ObjectSuffix): Command.cpp $(IntermediateDirectory)/Command$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Command.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Command$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Command$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Command$(ObjectSuffix) -MF$(IntermediateDirectory)/Command$(ObjectSuffix).d -MM Command.cpp

$(IntermediateDirectory)/ub$(ObjectSuffix): ub.cpp $(IntermediateDirectory)/ub$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) ub.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/ub$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ub$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ub$(ObjectSuffix) -MF$(IntermediateDirectory)/ub$(ObjectSuffix).d -MM ub.cpp

$(IntermediateDirectory)/EditorCommand$(ObjectSuffix): EditorCommand.cpp $(IntermediateDirectory)/EditorCommand$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) EditorCommand.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/EditorCommand$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorCommand$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorCommand$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorCommand$(ObjectSuffix).d -MM EditorCommand.cpp

$(IntermediateDirectory)/GrantGroup$(ObjectSuffix): GrantGroup.cpp $(IntermediateDirectory)/GrantGroup$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) GrantGroup.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/GrantGroup$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GrantGroup$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/GrantGroup$(ObjectSuffix) -MF$(IntermediateDirectory)/GrantGroup$(ObjectSuffix).d -MM GrantGroup.cpp

$(IntermediateDirectory)/Permission$(ObjectSuffix): Permission.cpp $(IntermediateDirectory)/Permission$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Permission.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Permission$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Permission$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Permission$(ObjectSuffix) -MF$(IntermediateDirectory)/Permission$(ObjectSuffix).d -MM Permission.cpp

$(IntermediateDirectory)/EditorGrantGroup$(ObjectSuffix): EditorGrantGroup.cpp $(IntermediateDirectory)/EditorGrantGroup$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) EditorGrantGroup.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/EditorGrantGroup$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorGrantGroup$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorGrantGroup$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorGrantGroup$(ObjectSuffix).d -MM EditorGrantGroup.cpp

$(IntermediateDirectory)/EditorPermission$(ObjectSuffix): EditorPermission.cpp $(IntermediateDirectory)/EditorPermission$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) EditorPermission.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/EditorPermission$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorPermission$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorPermission$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorPermission$(ObjectSuffix).d -MM EditorPermission.cpp

$(IntermediateDirectory)/OLCEditor$(ObjectSuffix): OLCEditor.cpp $(IntermediateDirectory)/OLCEditor$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) OLCEditor.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/OLCEditor$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/OLCEditor$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/OLCEditor$(ObjectSuffix) -MF$(IntermediateDirectory)/OLCEditor$(ObjectSuffix).d -MM OLCEditor.cpp

$(IntermediateDirectory)/Editor$(ObjectSuffix): Editor.cpp $(IntermediateDirectory)/Editor$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) Editor.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/Editor$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Editor$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Editor$(ObjectSuffix) -MF$(IntermediateDirectory)/Editor$(ObjectSuffix).d -MM Editor.cpp

$(IntermediateDirectory)/EditorString$(ObjectSuffix): EditorString.cpp $(IntermediateDirectory)/EditorString$(ObjectSuffix).d
	$(CompilerName) $(SourceSwitch) EditorString.cpp $(CmpOptions)   $(OutputSwitch) $(IntermediateDirectory)/EditorString$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EditorString$(ObjectSuffix).d:
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EditorString$(ObjectSuffix) -MF$(IntermediateDirectory)/EditorString$(ObjectSuffix).d -MM EditorString.cpp

##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/Account$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Account$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Area$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Area$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Cache$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Cache$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Character$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Character$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Colour$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Colour$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/DatabaseMgr$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/DatabaseMgr$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorAccount$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorAccount$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorArea$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorArea$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorColour$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorColour$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorLoginAccount$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorLoginAccount$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorMobile$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorMobile$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorNewAccount$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorNewAccount$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorNewCharacter$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorNewCharacter$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorOLC$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorOLC$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorPlaying$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorPlaying$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorRoom$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorRoom$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorScript$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorScript$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorSector$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorSector$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/MCharacter$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/MCharacter$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/PCharacter$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/PCharacter$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Race$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Race$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Room$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Room$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Sector$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Sector$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/UBHandler$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/UBHandler$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/UBSocket$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/UBSocket$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/SQLSocket$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/SQLSocket$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Command$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Command$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/ub$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ub$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorCommand$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorCommand$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/GrantGroup$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/GrantGroup$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Permission$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Permission$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorGrantGroup$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorGrantGroup$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorPermission$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorPermission$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/OLCEditor$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/OLCEditor$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/Editor$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Editor$(ObjectSuffix).d
	$(RM) $(IntermediateDirectory)/EditorString$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EditorString$(ObjectSuffix).d
	$(RM) $(OutputFile)

-include $(IntermediateDirectory)/*.d
