#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/machikania_jap.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/machikania_jap.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=debug.c document.c editor.c fontx2.c library.c linker.c music.c run.c statement.c string.c value.c compiler.c error.c exception.c file.c float.c function.c globalvars.c keyinput.c memory.c operator.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/debug.o ${OBJECTDIR}/document.o ${OBJECTDIR}/editor.o ${OBJECTDIR}/fontx2.o ${OBJECTDIR}/library.o ${OBJECTDIR}/linker.o ${OBJECTDIR}/music.o ${OBJECTDIR}/run.o ${OBJECTDIR}/statement.o ${OBJECTDIR}/string.o ${OBJECTDIR}/value.o ${OBJECTDIR}/compiler.o ${OBJECTDIR}/error.o ${OBJECTDIR}/exception.o ${OBJECTDIR}/file.o ${OBJECTDIR}/float.o ${OBJECTDIR}/function.o ${OBJECTDIR}/globalvars.o ${OBJECTDIR}/keyinput.o ${OBJECTDIR}/memory.o ${OBJECTDIR}/operator.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/debug.o.d ${OBJECTDIR}/document.o.d ${OBJECTDIR}/editor.o.d ${OBJECTDIR}/fontx2.o.d ${OBJECTDIR}/library.o.d ${OBJECTDIR}/linker.o.d ${OBJECTDIR}/music.o.d ${OBJECTDIR}/run.o.d ${OBJECTDIR}/statement.o.d ${OBJECTDIR}/string.o.d ${OBJECTDIR}/value.o.d ${OBJECTDIR}/compiler.o.d ${OBJECTDIR}/error.o.d ${OBJECTDIR}/exception.o.d ${OBJECTDIR}/file.o.d ${OBJECTDIR}/float.o.d ${OBJECTDIR}/function.o.d ${OBJECTDIR}/globalvars.o.d ${OBJECTDIR}/keyinput.o.d ${OBJECTDIR}/memory.o.d ${OBJECTDIR}/operator.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/debug.o ${OBJECTDIR}/document.o ${OBJECTDIR}/editor.o ${OBJECTDIR}/fontx2.o ${OBJECTDIR}/library.o ${OBJECTDIR}/linker.o ${OBJECTDIR}/music.o ${OBJECTDIR}/run.o ${OBJECTDIR}/statement.o ${OBJECTDIR}/string.o ${OBJECTDIR}/value.o ${OBJECTDIR}/compiler.o ${OBJECTDIR}/error.o ${OBJECTDIR}/exception.o ${OBJECTDIR}/file.o ${OBJECTDIR}/float.o ${OBJECTDIR}/function.o ${OBJECTDIR}/globalvars.o ${OBJECTDIR}/keyinput.o ${OBJECTDIR}/memory.o ${OBJECTDIR}/operator.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=debug.c document.c editor.c fontx2.c library.c linker.c music.c run.c statement.c string.c value.c compiler.c error.c exception.c file.c float.c function.c globalvars.c keyinput.c memory.c operator.c main.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/machikania_jap.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX270F256B
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/debug.o: debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/debug.o.d 
	@${RM} ${OBJECTDIR}/debug.o 
	@${FIXDEPS} "${OBJECTDIR}/debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/debug.o.d" -o ${OBJECTDIR}/debug.o debug.c     
	
${OBJECTDIR}/document.o: document.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/document.o.d 
	@${RM} ${OBJECTDIR}/document.o 
	@${FIXDEPS} "${OBJECTDIR}/document.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/document.o.d" -o ${OBJECTDIR}/document.o document.c     
	
${OBJECTDIR}/editor.o: editor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/editor.o.d 
	@${RM} ${OBJECTDIR}/editor.o 
	@${FIXDEPS} "${OBJECTDIR}/editor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/editor.o.d" -o ${OBJECTDIR}/editor.o editor.c     
	
${OBJECTDIR}/fontx2.o: fontx2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/fontx2.o.d 
	@${RM} ${OBJECTDIR}/fontx2.o 
	@${FIXDEPS} "${OBJECTDIR}/fontx2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/fontx2.o.d" -o ${OBJECTDIR}/fontx2.o fontx2.c     
	
${OBJECTDIR}/library.o: library.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/library.o.d 
	@${RM} ${OBJECTDIR}/library.o 
	@${FIXDEPS} "${OBJECTDIR}/library.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/library.o.d" -o ${OBJECTDIR}/library.o library.c     
	
${OBJECTDIR}/linker.o: linker.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/linker.o.d 
	@${RM} ${OBJECTDIR}/linker.o 
	@${FIXDEPS} "${OBJECTDIR}/linker.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/linker.o.d" -o ${OBJECTDIR}/linker.o linker.c     
	
${OBJECTDIR}/music.o: music.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/music.o.d 
	@${RM} ${OBJECTDIR}/music.o 
	@${FIXDEPS} "${OBJECTDIR}/music.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/music.o.d" -o ${OBJECTDIR}/music.o music.c     
	
${OBJECTDIR}/run.o: run.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/run.o.d 
	@${RM} ${OBJECTDIR}/run.o 
	@${FIXDEPS} "${OBJECTDIR}/run.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/run.o.d" -o ${OBJECTDIR}/run.o run.c     
	
${OBJECTDIR}/statement.o: statement.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/statement.o.d 
	@${RM} ${OBJECTDIR}/statement.o 
	@${FIXDEPS} "${OBJECTDIR}/statement.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/statement.o.d" -o ${OBJECTDIR}/statement.o statement.c     
	
${OBJECTDIR}/string.o: string.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/string.o.d 
	@${RM} ${OBJECTDIR}/string.o 
	@${FIXDEPS} "${OBJECTDIR}/string.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/string.o.d" -o ${OBJECTDIR}/string.o string.c     
	
${OBJECTDIR}/value.o: value.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/value.o.d 
	@${RM} ${OBJECTDIR}/value.o 
	@${FIXDEPS} "${OBJECTDIR}/value.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/value.o.d" -o ${OBJECTDIR}/value.o value.c     
	
${OBJECTDIR}/compiler.o: compiler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/compiler.o.d 
	@${RM} ${OBJECTDIR}/compiler.o 
	@${FIXDEPS} "${OBJECTDIR}/compiler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/compiler.o.d" -o ${OBJECTDIR}/compiler.o compiler.c     
	
${OBJECTDIR}/error.o: error.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/error.o.d 
	@${RM} ${OBJECTDIR}/error.o 
	@${FIXDEPS} "${OBJECTDIR}/error.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/error.o.d" -o ${OBJECTDIR}/error.o error.c     
	
${OBJECTDIR}/exception.o: exception.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/exception.o.d 
	@${RM} ${OBJECTDIR}/exception.o 
	@${FIXDEPS} "${OBJECTDIR}/exception.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/exception.o.d" -o ${OBJECTDIR}/exception.o exception.c     
	
${OBJECTDIR}/file.o: file.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/file.o.d 
	@${RM} ${OBJECTDIR}/file.o 
	@${FIXDEPS} "${OBJECTDIR}/file.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/file.o.d" -o ${OBJECTDIR}/file.o file.c     
	
${OBJECTDIR}/float.o: float.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/float.o.d 
	@${RM} ${OBJECTDIR}/float.o 
	@${FIXDEPS} "${OBJECTDIR}/float.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/float.o.d" -o ${OBJECTDIR}/float.o float.c     
	
${OBJECTDIR}/function.o: function.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/function.o.d 
	@${RM} ${OBJECTDIR}/function.o 
	@${FIXDEPS} "${OBJECTDIR}/function.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/function.o.d" -o ${OBJECTDIR}/function.o function.c     
	
${OBJECTDIR}/globalvars.o: globalvars.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/globalvars.o.d 
	@${RM} ${OBJECTDIR}/globalvars.o 
	@${FIXDEPS} "${OBJECTDIR}/globalvars.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/globalvars.o.d" -o ${OBJECTDIR}/globalvars.o globalvars.c     
	
${OBJECTDIR}/keyinput.o: keyinput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/keyinput.o.d 
	@${RM} ${OBJECTDIR}/keyinput.o 
	@${FIXDEPS} "${OBJECTDIR}/keyinput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/keyinput.o.d" -o ${OBJECTDIR}/keyinput.o keyinput.c     
	
${OBJECTDIR}/memory.o: memory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/memory.o.d 
	@${RM} ${OBJECTDIR}/memory.o 
	@${FIXDEPS} "${OBJECTDIR}/memory.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/memory.o.d" -o ${OBJECTDIR}/memory.o memory.c     
	
${OBJECTDIR}/operator.o: operator.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/operator.o.d 
	@${RM} ${OBJECTDIR}/operator.o 
	@${FIXDEPS} "${OBJECTDIR}/operator.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/operator.o.d" -o ${OBJECTDIR}/operator.o operator.c     
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c     
	
else
${OBJECTDIR}/debug.o: debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/debug.o.d 
	@${RM} ${OBJECTDIR}/debug.o 
	@${FIXDEPS} "${OBJECTDIR}/debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/debug.o.d" -o ${OBJECTDIR}/debug.o debug.c     
	
${OBJECTDIR}/document.o: document.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/document.o.d 
	@${RM} ${OBJECTDIR}/document.o 
	@${FIXDEPS} "${OBJECTDIR}/document.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/document.o.d" -o ${OBJECTDIR}/document.o document.c     
	
${OBJECTDIR}/editor.o: editor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/editor.o.d 
	@${RM} ${OBJECTDIR}/editor.o 
	@${FIXDEPS} "${OBJECTDIR}/editor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/editor.o.d" -o ${OBJECTDIR}/editor.o editor.c     
	
${OBJECTDIR}/fontx2.o: fontx2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/fontx2.o.d 
	@${RM} ${OBJECTDIR}/fontx2.o 
	@${FIXDEPS} "${OBJECTDIR}/fontx2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/fontx2.o.d" -o ${OBJECTDIR}/fontx2.o fontx2.c     
	
${OBJECTDIR}/library.o: library.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/library.o.d 
	@${RM} ${OBJECTDIR}/library.o 
	@${FIXDEPS} "${OBJECTDIR}/library.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/library.o.d" -o ${OBJECTDIR}/library.o library.c     
	
${OBJECTDIR}/linker.o: linker.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/linker.o.d 
	@${RM} ${OBJECTDIR}/linker.o 
	@${FIXDEPS} "${OBJECTDIR}/linker.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/linker.o.d" -o ${OBJECTDIR}/linker.o linker.c     
	
${OBJECTDIR}/music.o: music.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/music.o.d 
	@${RM} ${OBJECTDIR}/music.o 
	@${FIXDEPS} "${OBJECTDIR}/music.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/music.o.d" -o ${OBJECTDIR}/music.o music.c     
	
${OBJECTDIR}/run.o: run.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/run.o.d 
	@${RM} ${OBJECTDIR}/run.o 
	@${FIXDEPS} "${OBJECTDIR}/run.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/run.o.d" -o ${OBJECTDIR}/run.o run.c     
	
${OBJECTDIR}/statement.o: statement.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/statement.o.d 
	@${RM} ${OBJECTDIR}/statement.o 
	@${FIXDEPS} "${OBJECTDIR}/statement.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/statement.o.d" -o ${OBJECTDIR}/statement.o statement.c     
	
${OBJECTDIR}/string.o: string.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/string.o.d 
	@${RM} ${OBJECTDIR}/string.o 
	@${FIXDEPS} "${OBJECTDIR}/string.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/string.o.d" -o ${OBJECTDIR}/string.o string.c     
	
${OBJECTDIR}/value.o: value.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/value.o.d 
	@${RM} ${OBJECTDIR}/value.o 
	@${FIXDEPS} "${OBJECTDIR}/value.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/value.o.d" -o ${OBJECTDIR}/value.o value.c     
	
${OBJECTDIR}/compiler.o: compiler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/compiler.o.d 
	@${RM} ${OBJECTDIR}/compiler.o 
	@${FIXDEPS} "${OBJECTDIR}/compiler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/compiler.o.d" -o ${OBJECTDIR}/compiler.o compiler.c     
	
${OBJECTDIR}/error.o: error.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/error.o.d 
	@${RM} ${OBJECTDIR}/error.o 
	@${FIXDEPS} "${OBJECTDIR}/error.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/error.o.d" -o ${OBJECTDIR}/error.o error.c     
	
${OBJECTDIR}/exception.o: exception.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/exception.o.d 
	@${RM} ${OBJECTDIR}/exception.o 
	@${FIXDEPS} "${OBJECTDIR}/exception.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/exception.o.d" -o ${OBJECTDIR}/exception.o exception.c     
	
${OBJECTDIR}/file.o: file.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/file.o.d 
	@${RM} ${OBJECTDIR}/file.o 
	@${FIXDEPS} "${OBJECTDIR}/file.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/file.o.d" -o ${OBJECTDIR}/file.o file.c     
	
${OBJECTDIR}/float.o: float.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/float.o.d 
	@${RM} ${OBJECTDIR}/float.o 
	@${FIXDEPS} "${OBJECTDIR}/float.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/float.o.d" -o ${OBJECTDIR}/float.o float.c     
	
${OBJECTDIR}/function.o: function.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/function.o.d 
	@${RM} ${OBJECTDIR}/function.o 
	@${FIXDEPS} "${OBJECTDIR}/function.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/function.o.d" -o ${OBJECTDIR}/function.o function.c     
	
${OBJECTDIR}/globalvars.o: globalvars.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/globalvars.o.d 
	@${RM} ${OBJECTDIR}/globalvars.o 
	@${FIXDEPS} "${OBJECTDIR}/globalvars.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/globalvars.o.d" -o ${OBJECTDIR}/globalvars.o globalvars.c     
	
${OBJECTDIR}/keyinput.o: keyinput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/keyinput.o.d 
	@${RM} ${OBJECTDIR}/keyinput.o 
	@${FIXDEPS} "${OBJECTDIR}/keyinput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/keyinput.o.d" -o ${OBJECTDIR}/keyinput.o keyinput.c     
	
${OBJECTDIR}/memory.o: memory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/memory.o.d 
	@${RM} ${OBJECTDIR}/memory.o 
	@${FIXDEPS} "${OBJECTDIR}/memory.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/memory.o.d" -o ${OBJECTDIR}/memory.o memory.c     
	
${OBJECTDIR}/operator.o: operator.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/operator.o.d 
	@${RM} ${OBJECTDIR}/operator.o 
	@${FIXDEPS} "${OBJECTDIR}/operator.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/operator.o.d" -o ${OBJECTDIR}/operator.o operator.c     
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c     
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/machikania_jap.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  lib_videoout_machikania.X.a libsdfsio.a ps2keyboard.X.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/machikania_jap.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    lib_videoout_machikania.X.a libsdfsio.a ps2keyboard.X.a          -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/machikania_jap.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  lib_videoout_machikania.X.a libsdfsio.a ps2keyboard.X.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/machikania_jap.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    lib_videoout_machikania.X.a libsdfsio.a ps2keyboard.X.a        -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	${MP_CC_DIR}/xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/machikania_jap.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
