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
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/PE_GarageDoorLocal.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/PE_GarageDoorLocal.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=main.c timer.c glcd.c door_system.c utils.c touch.c adc.c uart.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/timer.o ${OBJECTDIR}/glcd.o ${OBJECTDIR}/door_system.o ${OBJECTDIR}/utils.o ${OBJECTDIR}/touch.o ${OBJECTDIR}/adc.o ${OBJECTDIR}/uart.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/timer.o.d ${OBJECTDIR}/glcd.o.d ${OBJECTDIR}/door_system.o.d ${OBJECTDIR}/utils.o.d ${OBJECTDIR}/touch.o.d ${OBJECTDIR}/adc.o.d ${OBJECTDIR}/uart.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/timer.o ${OBJECTDIR}/glcd.o ${OBJECTDIR}/door_system.o ${OBJECTDIR}/utils.o ${OBJECTDIR}/touch.o ${OBJECTDIR}/adc.o ${OBJECTDIR}/uart.o

# Source Files
SOURCEFILES=main.c timer.c glcd.c door_system.c utils.c touch.c adc.c uart.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/PE_GarageDoorLocal.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=30F4013
MP_LINKER_FILE_OPTION=,--script=p30F4013.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/bae040e5e196c96b7aca11287168bc45a8407aaf .generated_files/flags/default/74b34707da22605293d6311696ae0a4a34fb9101
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/timer.o: timer.c  .generated_files/flags/default/d2acceaed9b6d901bb174f068a62c6a57de3f433 .generated_files/flags/default/74b34707da22605293d6311696ae0a4a34fb9101
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timer.o.d 
	@${RM} ${OBJECTDIR}/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  timer.c  -o ${OBJECTDIR}/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/timer.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/glcd.o: glcd.c  .generated_files/flags/default/8b6e7b59d2853af56ad2c35d8ef3c6a53ce1c4b .generated_files/flags/default/74b34707da22605293d6311696ae0a4a34fb9101
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/glcd.o.d 
	@${RM} ${OBJECTDIR}/glcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  glcd.c  -o ${OBJECTDIR}/glcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/glcd.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/door_system.o: door_system.c  .generated_files/flags/default/ceefb632d4f6f5794e3e44cfd60f5969dd7547da .generated_files/flags/default/74b34707da22605293d6311696ae0a4a34fb9101
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/door_system.o.d 
	@${RM} ${OBJECTDIR}/door_system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  door_system.c  -o ${OBJECTDIR}/door_system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/door_system.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/utils.o: utils.c  .generated_files/flags/default/67ca69b989c6b0e1d391305b0a3a2c34f91d900a .generated_files/flags/default/74b34707da22605293d6311696ae0a4a34fb9101
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/utils.o.d 
	@${RM} ${OBJECTDIR}/utils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  utils.c  -o ${OBJECTDIR}/utils.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/utils.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/touch.o: touch.c  .generated_files/flags/default/f8afad0e51ed4d12e805dc8ea8782c167362cfcb .generated_files/flags/default/74b34707da22605293d6311696ae0a4a34fb9101
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/touch.o.d 
	@${RM} ${OBJECTDIR}/touch.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  touch.c  -o ${OBJECTDIR}/touch.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/touch.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/adc.o: adc.c  .generated_files/flags/default/1709b35068cb6666e6c7c21b995144c84ee1eb60 .generated_files/flags/default/74b34707da22605293d6311696ae0a4a34fb9101
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/adc.o.d 
	@${RM} ${OBJECTDIR}/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  adc.c  -o ${OBJECTDIR}/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/adc.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/uart.o: uart.c  .generated_files/flags/default/5f0706230837d5184753b163d3226c50704a5a2f .generated_files/flags/default/74b34707da22605293d6311696ae0a4a34fb9101
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uart.o.d 
	@${RM} ${OBJECTDIR}/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uart.c  -o ${OBJECTDIR}/uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/uart.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
else
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/2c3c9f596b1105ecd61f94709b038bc215c5ddb8 .generated_files/flags/default/74b34707da22605293d6311696ae0a4a34fb9101
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/timer.o: timer.c  .generated_files/flags/default/fe47d3c4facc0f636a2752ad243eac3f0ae3176d .generated_files/flags/default/74b34707da22605293d6311696ae0a4a34fb9101
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timer.o.d 
	@${RM} ${OBJECTDIR}/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  timer.c  -o ${OBJECTDIR}/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/timer.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/glcd.o: glcd.c  .generated_files/flags/default/7ecaf6a6a96dfa7639368a8ed657f28729ce52db .generated_files/flags/default/74b34707da22605293d6311696ae0a4a34fb9101
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/glcd.o.d 
	@${RM} ${OBJECTDIR}/glcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  glcd.c  -o ${OBJECTDIR}/glcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/glcd.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/door_system.o: door_system.c  .generated_files/flags/default/94ff825a20d3cb3fed489cbf34cb30796812c74b .generated_files/flags/default/74b34707da22605293d6311696ae0a4a34fb9101
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/door_system.o.d 
	@${RM} ${OBJECTDIR}/door_system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  door_system.c  -o ${OBJECTDIR}/door_system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/door_system.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/utils.o: utils.c  .generated_files/flags/default/e2169b18b04828f295c14a22c5eda1018245df .generated_files/flags/default/74b34707da22605293d6311696ae0a4a34fb9101
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/utils.o.d 
	@${RM} ${OBJECTDIR}/utils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  utils.c  -o ${OBJECTDIR}/utils.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/utils.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/touch.o: touch.c  .generated_files/flags/default/b23fd6d3285570e06e7a4485bb9a8c5013dc0c43 .generated_files/flags/default/74b34707da22605293d6311696ae0a4a34fb9101
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/touch.o.d 
	@${RM} ${OBJECTDIR}/touch.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  touch.c  -o ${OBJECTDIR}/touch.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/touch.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/adc.o: adc.c  .generated_files/flags/default/bddf857d055338fb2c068b94fc6f556d36c2c767 .generated_files/flags/default/74b34707da22605293d6311696ae0a4a34fb9101
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/adc.o.d 
	@${RM} ${OBJECTDIR}/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  adc.c  -o ${OBJECTDIR}/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/adc.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/uart.o: uart.c  .generated_files/flags/default/367c037cac7c316ba071bf66cdf668c0ebde3bd5 .generated_files/flags/default/74b34707da22605293d6311696ae0a4a34fb9101
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uart.o.d 
	@${RM} ${OBJECTDIR}/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uart.c  -o ${OBJECTDIR}/uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/uart.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
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
${DISTDIR}/PE_GarageDoorLocal.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/PE_GarageDoorLocal.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)      -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST)  
	
else
${DISTDIR}/PE_GarageDoorLocal.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/PE_GarageDoorLocal.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST)  
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/PE_GarageDoorLocal.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
