#SPDX-License-Identifier: GPL-2.0-only
# tools/power/acpi/Makefile - ACPI tool Makefile
#
# Copyright (c) 2013, Intel Corporation
#   Author: Lv Zheng <lv.zheng@intel.com>
#

# 다른 Makefile의 일부를 가져온다
include ../../scripts/Makefile.include

# 모든 target에 대하여 acpidbg, acpidump, ec를 dependency로 한다.
all: acpidbg acpidump ec
# clean하는 경우엔 acpidbg_clean, acpidump_clean, ec_clean를 dependency로 한다.
clean: acpidbg_clean acpidump_clean ec_clean
# install하는 경우엔 acpidbg_install, acpidump_install, ec_install을 dependency로 한다.
install: acpidbg_install acpidump_install ec_install
# uninstall하는 경우엔 acpidbg_uninstall, acpidump_uninstall, ec_uninstall을 dependency로 한다.
uninstall: acpidbg_uninstall acpidump_uninstall ec_uninstall

# .PHONY에 의해 acpidbg acpidump ec의 파일의 존재여부와는 관계없이 해당 command를 실행한다.
acpidbg acpidump ec: FORCE
# Makefile.include의 call descend를 한다. directory는 tools/$@, target은 all
	$(call descend,tools/$@,all)
# target이 acpidbg_clean acpidump_clean ec_clean일 경우
acpidbg_clean acpidump_clean ec_clean:
# Makefile.include의 call descend를 한다. directory는 tools/$(@:_clean=), target은 clean
	$(call descend,tools/$(@:_clean=),clean)
# target이 acpidbg_install acpidump_install ec_install인 경우
acpidbg_install acpidump_install ec_install:
# Makefile.include의 call descend를 한다. directory는 tools/$(@:_install=), target은 install
	$(call descend,tools/$(@:_install=),install)
# target이 acpidbg_uninsttall acpidump_uninstall ec_uninstall인 경우
acpidbg_uninstall acpidump_uninstall ec_uninstall:
# Makefile.include의 call descend를 한다. directory는 tools/$(@:_uninstall=), target은 uninstall
	$(call descend,tools/$(@:_uninstall=),uninstall)

# acpidbg acpidump ec라는 파일의 존재여부와 관계 없이 FORCE가 dependency로 붙으면 실행한다.
.PHONY: FORCE
