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
ifeq "$(wildcard nbproject/Makefile-local-Todd.mk)" "nbproject/Makefile-local-Todd.mk"
include nbproject/Makefile-local-Todd.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=Todd
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Quiver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Quiver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=--mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=configuration_bits.c interrupts.c main.c system.c user.c memory.c LEDs.c tactiles.c state_manager.c SwitchBypass.c SwitchTap.c preset_programming.c expressTap.c usart_pic16.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/configuration_bits.p1 ${OBJECTDIR}/interrupts.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/system.p1 ${OBJECTDIR}/user.p1 ${OBJECTDIR}/memory.p1 ${OBJECTDIR}/LEDs.p1 ${OBJECTDIR}/tactiles.p1 ${OBJECTDIR}/state_manager.p1 ${OBJECTDIR}/SwitchBypass.p1 ${OBJECTDIR}/SwitchTap.p1 ${OBJECTDIR}/preset_programming.p1 ${OBJECTDIR}/expressTap.p1 ${OBJECTDIR}/usart_pic16.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/configuration_bits.p1.d ${OBJECTDIR}/interrupts.p1.d ${OBJECTDIR}/main.p1.d ${OBJECTDIR}/system.p1.d ${OBJECTDIR}/user.p1.d ${OBJECTDIR}/memory.p1.d ${OBJECTDIR}/LEDs.p1.d ${OBJECTDIR}/tactiles.p1.d ${OBJECTDIR}/state_manager.p1.d ${OBJECTDIR}/SwitchBypass.p1.d ${OBJECTDIR}/SwitchTap.p1.d ${OBJECTDIR}/preset_programming.p1.d ${OBJECTDIR}/expressTap.p1.d ${OBJECTDIR}/usart_pic16.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/configuration_bits.p1 ${OBJECTDIR}/interrupts.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/system.p1 ${OBJECTDIR}/user.p1 ${OBJECTDIR}/memory.p1 ${OBJECTDIR}/LEDs.p1 ${OBJECTDIR}/tactiles.p1 ${OBJECTDIR}/state_manager.p1 ${OBJECTDIR}/SwitchBypass.p1 ${OBJECTDIR}/SwitchTap.p1 ${OBJECTDIR}/preset_programming.p1 ${OBJECTDIR}/expressTap.p1 ${OBJECTDIR}/usart_pic16.p1

# Source Files
SOURCEFILES=configuration_bits.c interrupts.c main.c system.c user.c memory.c LEDs.c tactiles.c state_manager.c SwitchBypass.c SwitchTap.c preset_programming.c expressTap.c usart_pic16.c


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
	${MAKE}  -f nbproject/Makefile-Todd.mk dist/${CND_CONF}/${IMAGE_TYPE}/Quiver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=16F1527
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/configuration_bits.p1: configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/configuration_bits.p1.d 
	@${RM} ${OBJECTDIR}/configuration_bits.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/configuration_bits.p1  configuration_bits.c 
	@-${MV} ${OBJECTDIR}/configuration_bits.d ${OBJECTDIR}/configuration_bits.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/configuration_bits.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/interrupts.p1: interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupts.p1.d 
	@${RM} ${OBJECTDIR}/interrupts.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/interrupts.p1  interrupts.c 
	@-${MV} ${OBJECTDIR}/interrupts.d ${OBJECTDIR}/interrupts.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/interrupts.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/main.p1  main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/system.p1: system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/system.p1.d 
	@${RM} ${OBJECTDIR}/system.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/system.p1  system.c 
	@-${MV} ${OBJECTDIR}/system.d ${OBJECTDIR}/system.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/system.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/user.p1: user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/user.p1.d 
	@${RM} ${OBJECTDIR}/user.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/user.p1  user.c 
	@-${MV} ${OBJECTDIR}/user.d ${OBJECTDIR}/user.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/user.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/memory.p1: memory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/memory.p1.d 
	@${RM} ${OBJECTDIR}/memory.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/memory.p1  memory.c 
	@-${MV} ${OBJECTDIR}/memory.d ${OBJECTDIR}/memory.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/memory.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LEDs.p1: LEDs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LEDs.p1.d 
	@${RM} ${OBJECTDIR}/LEDs.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LEDs.p1  LEDs.c 
	@-${MV} ${OBJECTDIR}/LEDs.d ${OBJECTDIR}/LEDs.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LEDs.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/tactiles.p1: tactiles.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tactiles.p1.d 
	@${RM} ${OBJECTDIR}/tactiles.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/tactiles.p1  tactiles.c 
	@-${MV} ${OBJECTDIR}/tactiles.d ${OBJECTDIR}/tactiles.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/tactiles.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/state_manager.p1: state_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/state_manager.p1.d 
	@${RM} ${OBJECTDIR}/state_manager.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/state_manager.p1  state_manager.c 
	@-${MV} ${OBJECTDIR}/state_manager.d ${OBJECTDIR}/state_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/state_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SwitchBypass.p1: SwitchBypass.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SwitchBypass.p1.d 
	@${RM} ${OBJECTDIR}/SwitchBypass.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SwitchBypass.p1  SwitchBypass.c 
	@-${MV} ${OBJECTDIR}/SwitchBypass.d ${OBJECTDIR}/SwitchBypass.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SwitchBypass.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SwitchTap.p1: SwitchTap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SwitchTap.p1.d 
	@${RM} ${OBJECTDIR}/SwitchTap.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SwitchTap.p1  SwitchTap.c 
	@-${MV} ${OBJECTDIR}/SwitchTap.d ${OBJECTDIR}/SwitchTap.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SwitchTap.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/preset_programming.p1: preset_programming.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/preset_programming.p1.d 
	@${RM} ${OBJECTDIR}/preset_programming.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/preset_programming.p1  preset_programming.c 
	@-${MV} ${OBJECTDIR}/preset_programming.d ${OBJECTDIR}/preset_programming.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/preset_programming.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/expressTap.p1: expressTap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/expressTap.p1.d 
	@${RM} ${OBJECTDIR}/expressTap.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/expressTap.p1  expressTap.c 
	@-${MV} ${OBJECTDIR}/expressTap.d ${OBJECTDIR}/expressTap.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/expressTap.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usart_pic16.p1: usart_pic16.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usart_pic16.p1.d 
	@${RM} ${OBJECTDIR}/usart_pic16.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/usart_pic16.p1  usart_pic16.c 
	@-${MV} ${OBJECTDIR}/usart_pic16.d ${OBJECTDIR}/usart_pic16.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usart_pic16.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/configuration_bits.p1: configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/configuration_bits.p1.d 
	@${RM} ${OBJECTDIR}/configuration_bits.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/configuration_bits.p1  configuration_bits.c 
	@-${MV} ${OBJECTDIR}/configuration_bits.d ${OBJECTDIR}/configuration_bits.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/configuration_bits.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/interrupts.p1: interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupts.p1.d 
	@${RM} ${OBJECTDIR}/interrupts.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/interrupts.p1  interrupts.c 
	@-${MV} ${OBJECTDIR}/interrupts.d ${OBJECTDIR}/interrupts.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/interrupts.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/main.p1  main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/system.p1: system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/system.p1.d 
	@${RM} ${OBJECTDIR}/system.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/system.p1  system.c 
	@-${MV} ${OBJECTDIR}/system.d ${OBJECTDIR}/system.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/system.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/user.p1: user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/user.p1.d 
	@${RM} ${OBJECTDIR}/user.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/user.p1  user.c 
	@-${MV} ${OBJECTDIR}/user.d ${OBJECTDIR}/user.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/user.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/memory.p1: memory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/memory.p1.d 
	@${RM} ${OBJECTDIR}/memory.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/memory.p1  memory.c 
	@-${MV} ${OBJECTDIR}/memory.d ${OBJECTDIR}/memory.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/memory.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/LEDs.p1: LEDs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LEDs.p1.d 
	@${RM} ${OBJECTDIR}/LEDs.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/LEDs.p1  LEDs.c 
	@-${MV} ${OBJECTDIR}/LEDs.d ${OBJECTDIR}/LEDs.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/LEDs.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/tactiles.p1: tactiles.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tactiles.p1.d 
	@${RM} ${OBJECTDIR}/tactiles.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/tactiles.p1  tactiles.c 
	@-${MV} ${OBJECTDIR}/tactiles.d ${OBJECTDIR}/tactiles.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/tactiles.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/state_manager.p1: state_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/state_manager.p1.d 
	@${RM} ${OBJECTDIR}/state_manager.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/state_manager.p1  state_manager.c 
	@-${MV} ${OBJECTDIR}/state_manager.d ${OBJECTDIR}/state_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/state_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SwitchBypass.p1: SwitchBypass.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SwitchBypass.p1.d 
	@${RM} ${OBJECTDIR}/SwitchBypass.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SwitchBypass.p1  SwitchBypass.c 
	@-${MV} ${OBJECTDIR}/SwitchBypass.d ${OBJECTDIR}/SwitchBypass.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SwitchBypass.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SwitchTap.p1: SwitchTap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SwitchTap.p1.d 
	@${RM} ${OBJECTDIR}/SwitchTap.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SwitchTap.p1  SwitchTap.c 
	@-${MV} ${OBJECTDIR}/SwitchTap.d ${OBJECTDIR}/SwitchTap.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SwitchTap.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/preset_programming.p1: preset_programming.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/preset_programming.p1.d 
	@${RM} ${OBJECTDIR}/preset_programming.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/preset_programming.p1  preset_programming.c 
	@-${MV} ${OBJECTDIR}/preset_programming.d ${OBJECTDIR}/preset_programming.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/preset_programming.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/expressTap.p1: expressTap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/expressTap.p1.d 
	@${RM} ${OBJECTDIR}/expressTap.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/expressTap.p1  expressTap.c 
	@-${MV} ${OBJECTDIR}/expressTap.d ${OBJECTDIR}/expressTap.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/expressTap.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usart_pic16.p1: usart_pic16.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usart_pic16.p1.d 
	@${RM} ${OBJECTDIR}/usart_pic16.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/usart_pic16.p1  usart_pic16.c 
	@-${MV} ${OBJECTDIR}/usart_pic16.d ${OBJECTDIR}/usart_pic16.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usart_pic16.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Quiver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/Quiver.X.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"        $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/Quiver.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/Quiver.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Quiver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/Quiver.X.${IMAGE_TYPE}.map  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=16000000 -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/Quiver.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Todd
	${RM} -r dist/Todd

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
