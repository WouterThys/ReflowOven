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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/LMP90080.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/LMP90080.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=Controllers/Utils.c Controllers/LMP_Controller.c Drivers/SYSTEM_Driver.c Drivers/SPI_Driver.c Drivers/INT_Driver.c Drivers/UART_Driver.c Drivers/PORT_Driver.c Drivers/LMP_Driver.c configuration.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Controllers/Utils.o ${OBJECTDIR}/Controllers/LMP_Controller.o ${OBJECTDIR}/Drivers/SYSTEM_Driver.o ${OBJECTDIR}/Drivers/SPI_Driver.o ${OBJECTDIR}/Drivers/INT_Driver.o ${OBJECTDIR}/Drivers/UART_Driver.o ${OBJECTDIR}/Drivers/PORT_Driver.o ${OBJECTDIR}/Drivers/LMP_Driver.o ${OBJECTDIR}/configuration.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Controllers/Utils.o.d ${OBJECTDIR}/Controllers/LMP_Controller.o.d ${OBJECTDIR}/Drivers/SYSTEM_Driver.o.d ${OBJECTDIR}/Drivers/SPI_Driver.o.d ${OBJECTDIR}/Drivers/INT_Driver.o.d ${OBJECTDIR}/Drivers/UART_Driver.o.d ${OBJECTDIR}/Drivers/PORT_Driver.o.d ${OBJECTDIR}/Drivers/LMP_Driver.o.d ${OBJECTDIR}/configuration.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Controllers/Utils.o ${OBJECTDIR}/Controllers/LMP_Controller.o ${OBJECTDIR}/Drivers/SYSTEM_Driver.o ${OBJECTDIR}/Drivers/SPI_Driver.o ${OBJECTDIR}/Drivers/INT_Driver.o ${OBJECTDIR}/Drivers/UART_Driver.o ${OBJECTDIR}/Drivers/PORT_Driver.o ${OBJECTDIR}/Drivers/LMP_Driver.o ${OBJECTDIR}/configuration.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=Controllers/Utils.c Controllers/LMP_Controller.c Drivers/SYSTEM_Driver.c Drivers/SPI_Driver.c Drivers/INT_Driver.c Drivers/UART_Driver.c Drivers/PORT_Driver.c Drivers/LMP_Driver.c configuration.c main.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/LMP90080.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP32GP502
MP_LINKER_FILE_OPTION=,--script=p33EP32GP502.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Controllers/Utils.o: Controllers/Utils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Controllers" 
	@${RM} ${OBJECTDIR}/Controllers/Utils.o.d 
	@${RM} ${OBJECTDIR}/Controllers/Utils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Controllers/Utils.c  -o ${OBJECTDIR}/Controllers/Utils.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Controllers/Utils.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Controllers/Utils.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Controllers/LMP_Controller.o: Controllers/LMP_Controller.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Controllers" 
	@${RM} ${OBJECTDIR}/Controllers/LMP_Controller.o.d 
	@${RM} ${OBJECTDIR}/Controllers/LMP_Controller.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Controllers/LMP_Controller.c  -o ${OBJECTDIR}/Controllers/LMP_Controller.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Controllers/LMP_Controller.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Controllers/LMP_Controller.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Drivers/SYSTEM_Driver.o: Drivers/SYSTEM_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Drivers" 
	@${RM} ${OBJECTDIR}/Drivers/SYSTEM_Driver.o.d 
	@${RM} ${OBJECTDIR}/Drivers/SYSTEM_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Drivers/SYSTEM_Driver.c  -o ${OBJECTDIR}/Drivers/SYSTEM_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Drivers/SYSTEM_Driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Drivers/SYSTEM_Driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Drivers/SPI_Driver.o: Drivers/SPI_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Drivers" 
	@${RM} ${OBJECTDIR}/Drivers/SPI_Driver.o.d 
	@${RM} ${OBJECTDIR}/Drivers/SPI_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Drivers/SPI_Driver.c  -o ${OBJECTDIR}/Drivers/SPI_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Drivers/SPI_Driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Drivers/SPI_Driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Drivers/INT_Driver.o: Drivers/INT_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Drivers" 
	@${RM} ${OBJECTDIR}/Drivers/INT_Driver.o.d 
	@${RM} ${OBJECTDIR}/Drivers/INT_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Drivers/INT_Driver.c  -o ${OBJECTDIR}/Drivers/INT_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Drivers/INT_Driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Drivers/INT_Driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Drivers/UART_Driver.o: Drivers/UART_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Drivers" 
	@${RM} ${OBJECTDIR}/Drivers/UART_Driver.o.d 
	@${RM} ${OBJECTDIR}/Drivers/UART_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Drivers/UART_Driver.c  -o ${OBJECTDIR}/Drivers/UART_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Drivers/UART_Driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Drivers/UART_Driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Drivers/PORT_Driver.o: Drivers/PORT_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Drivers" 
	@${RM} ${OBJECTDIR}/Drivers/PORT_Driver.o.d 
	@${RM} ${OBJECTDIR}/Drivers/PORT_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Drivers/PORT_Driver.c  -o ${OBJECTDIR}/Drivers/PORT_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Drivers/PORT_Driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Drivers/PORT_Driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Drivers/LMP_Driver.o: Drivers/LMP_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Drivers" 
	@${RM} ${OBJECTDIR}/Drivers/LMP_Driver.o.d 
	@${RM} ${OBJECTDIR}/Drivers/LMP_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Drivers/LMP_Driver.c  -o ${OBJECTDIR}/Drivers/LMP_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Drivers/LMP_Driver.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Drivers/LMP_Driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/configuration.o: configuration.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/configuration.o.d 
	@${RM} ${OBJECTDIR}/configuration.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  configuration.c  -o ${OBJECTDIR}/configuration.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/configuration.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/configuration.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/Controllers/Utils.o: Controllers/Utils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Controllers" 
	@${RM} ${OBJECTDIR}/Controllers/Utils.o.d 
	@${RM} ${OBJECTDIR}/Controllers/Utils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Controllers/Utils.c  -o ${OBJECTDIR}/Controllers/Utils.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Controllers/Utils.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Controllers/Utils.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Controllers/LMP_Controller.o: Controllers/LMP_Controller.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Controllers" 
	@${RM} ${OBJECTDIR}/Controllers/LMP_Controller.o.d 
	@${RM} ${OBJECTDIR}/Controllers/LMP_Controller.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Controllers/LMP_Controller.c  -o ${OBJECTDIR}/Controllers/LMP_Controller.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Controllers/LMP_Controller.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Controllers/LMP_Controller.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Drivers/SYSTEM_Driver.o: Drivers/SYSTEM_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Drivers" 
	@${RM} ${OBJECTDIR}/Drivers/SYSTEM_Driver.o.d 
	@${RM} ${OBJECTDIR}/Drivers/SYSTEM_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Drivers/SYSTEM_Driver.c  -o ${OBJECTDIR}/Drivers/SYSTEM_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Drivers/SYSTEM_Driver.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Drivers/SYSTEM_Driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Drivers/SPI_Driver.o: Drivers/SPI_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Drivers" 
	@${RM} ${OBJECTDIR}/Drivers/SPI_Driver.o.d 
	@${RM} ${OBJECTDIR}/Drivers/SPI_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Drivers/SPI_Driver.c  -o ${OBJECTDIR}/Drivers/SPI_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Drivers/SPI_Driver.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Drivers/SPI_Driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Drivers/INT_Driver.o: Drivers/INT_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Drivers" 
	@${RM} ${OBJECTDIR}/Drivers/INT_Driver.o.d 
	@${RM} ${OBJECTDIR}/Drivers/INT_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Drivers/INT_Driver.c  -o ${OBJECTDIR}/Drivers/INT_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Drivers/INT_Driver.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Drivers/INT_Driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Drivers/UART_Driver.o: Drivers/UART_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Drivers" 
	@${RM} ${OBJECTDIR}/Drivers/UART_Driver.o.d 
	@${RM} ${OBJECTDIR}/Drivers/UART_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Drivers/UART_Driver.c  -o ${OBJECTDIR}/Drivers/UART_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Drivers/UART_Driver.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Drivers/UART_Driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Drivers/PORT_Driver.o: Drivers/PORT_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Drivers" 
	@${RM} ${OBJECTDIR}/Drivers/PORT_Driver.o.d 
	@${RM} ${OBJECTDIR}/Drivers/PORT_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Drivers/PORT_Driver.c  -o ${OBJECTDIR}/Drivers/PORT_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Drivers/PORT_Driver.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Drivers/PORT_Driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Drivers/LMP_Driver.o: Drivers/LMP_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Drivers" 
	@${RM} ${OBJECTDIR}/Drivers/LMP_Driver.o.d 
	@${RM} ${OBJECTDIR}/Drivers/LMP_Driver.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Drivers/LMP_Driver.c  -o ${OBJECTDIR}/Drivers/LMP_Driver.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Drivers/LMP_Driver.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/Drivers/LMP_Driver.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/configuration.o: configuration.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/configuration.o.d 
	@${RM} ${OBJECTDIR}/configuration.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  configuration.c  -o ${OBJECTDIR}/configuration.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/configuration.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/configuration.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/LMP90080.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/LMP90080.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x1000:0x101B -mreserve=data@0x101C:0x101D -mreserve=data@0x101E:0x101F -mreserve=data@0x1020:0x1021 -mreserve=data@0x1022:0x1023 -mreserve=data@0x1024:0x1027 -mreserve=data@0x1028:0x104F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/LMP90080.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/LMP90080.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/LMP90080.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
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
