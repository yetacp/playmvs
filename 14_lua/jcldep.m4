jcl/01.done: lapi.s
	@echo "Preparing EBCDIC for lapi..."
	@$(RDRPREP) jcl/01.jcl tmp.jcl_E
	@echo "Installing lapi..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/01.done
	sleep 2

jcl/02.done: lauxlib.s
	@echo "Preparing EBCDIC for lauxlib..."
	@$(RDRPREP) jcl/02.jcl tmp.jcl_E
	@echo "Installing lauxlib..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/02.done
	sleep 2

jcl/03.done: lbaselib.s
	@echo "Preparing EBCDIC for lbaselib..."
	@$(RDRPREP) jcl/03.jcl tmp.jcl_E
	@echo "Installing lbaselib..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/03.done
	sleep 2

jcl/04.done: lcode.s
	@echo "Preparing EBCDIC for lcode..."
	@$(RDRPREP) jcl/04.jcl tmp.jcl_E
	@echo "Installing lcode..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/04.done
	sleep 2

jcl/05.done: lcorolib.s
	@echo "Preparing EBCDIC for lcorolib..."
	@$(RDRPREP) jcl/05.jcl tmp.jcl_E
	@echo "Installing lcorolib..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/05.done
	sleep 2

jcl/06.done: lctype.s
	@echo "Preparing EBCDIC for lctype..."
	@$(RDRPREP) jcl/06.jcl tmp.jcl_E
	@echo "Installing lctype..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/06.done
	sleep 2

jcl/07.done: ldebug.s
	@echo "Preparing EBCDIC for ldebug..."
	@$(RDRPREP) jcl/07.jcl tmp.jcl_E
	@echo "Installing ldebug..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/07.done
	sleep 2

jcl/08.done: ldo.s
	@echo "Preparing EBCDIC for ldo..."
	@$(RDRPREP) jcl/08.jcl tmp.jcl_E
	@echo "Installing ldo..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/08.done
	sleep 2

jcl/09.done: ldump.s
	@echo "Preparing EBCDIC for ldump..."
	@$(RDRPREP) jcl/09.jcl tmp.jcl_E
	@echo "Installing ldump..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/09.done
	sleep 2

jcl/10.done: lfunc.s
	@echo "Preparing EBCDIC for lfunc..."
	@$(RDRPREP) jcl/10.jcl tmp.jcl_E
	@echo "Installing lfunc..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/10.done
	sleep 2

jcl/11.done: lgc.s
	@echo "Preparing EBCDIC for lgc..."
	@$(RDRPREP) jcl/11.jcl tmp.jcl_E
	@echo "Installing lgc..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/11.done
	sleep 2

jcl/12.done: linit.s
	@echo "Preparing EBCDIC for linit..."
	@$(RDRPREP) jcl/12.jcl tmp.jcl_E
	@echo "Installing linit..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/12.done
	sleep 2

jcl/13.done: liolib.s
	@echo "Preparing EBCDIC for liolib..."
	@$(RDRPREP) jcl/13.jcl tmp.jcl_E
	@echo "Installing liolib..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/13.done
	sleep 2

jcl/14.done: llex.s
	@echo "Preparing EBCDIC for llex..."
	@$(RDRPREP) jcl/14.jcl tmp.jcl_E
	@echo "Installing llex..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/14.done
	sleep 2

jcl/15.done: lmathlib.s
	@echo "Preparing EBCDIC for lmathlib..."
	@$(RDRPREP) jcl/15.jcl tmp.jcl_E
	@echo "Installing lmathlib..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/15.done
	sleep 2

jcl/16.done: lmem.s
	@echo "Preparing EBCDIC for lmem..."
	@$(RDRPREP) jcl/16.jcl tmp.jcl_E
	@echo "Installing lmem..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/16.done
	sleep 2

jcl/17.done: loadlib.s
	@echo "Preparing EBCDIC for loadlib..."
	@$(RDRPREP) jcl/17.jcl tmp.jcl_E
	@echo "Installing loadlib..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/17.done
	sleep 2

jcl/18.done: lobject.s
	@echo "Preparing EBCDIC for lobject..."
	@$(RDRPREP) jcl/18.jcl tmp.jcl_E
	@echo "Installing lobject..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/18.done
	sleep 2

jcl/19.done: lopcodes.s
	@echo "Preparing EBCDIC for lopcodes..."
	@$(RDRPREP) jcl/19.jcl tmp.jcl_E
	@echo "Installing lopcodes..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/19.done
	sleep 2

jcl/20.done: loslib.s
	@echo "Preparing EBCDIC for loslib..."
	@$(RDRPREP) jcl/20.jcl tmp.jcl_E
	@echo "Installing loslib..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/20.done
	sleep 2

jcl/21.done: lparser.s
	@echo "Preparing EBCDIC for lparser..."
	@$(RDRPREP) jcl/21.jcl tmp.jcl_E
	@echo "Installing lparser..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/21.done
	sleep 2

jcl/22.done: lstate.s
	@echo "Preparing EBCDIC for lstate..."
	@$(RDRPREP) jcl/22.jcl tmp.jcl_E
	@echo "Installing lstate..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/22.done
	sleep 2

jcl/23.done: lstring.s
	@echo "Preparing EBCDIC for lstring..."
	@$(RDRPREP) jcl/23.jcl tmp.jcl_E
	@echo "Installing lstring..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/23.done
	sleep 2

jcl/24.done: lstrlib.s
	@echo "Preparing EBCDIC for lstrlib..."
	@$(RDRPREP) jcl/24.jcl tmp.jcl_E
	@echo "Installing lstrlib..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/24.done
	sleep 2

jcl/25.done: ltable.s
	@echo "Preparing EBCDIC for ltable..."
	@$(RDRPREP) jcl/25.jcl tmp.jcl_E
	@echo "Installing ltable..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/25.done
	sleep 2

jcl/26.done: ltablib.s
	@echo "Preparing EBCDIC for ltablib..."
	@$(RDRPREP) jcl/26.jcl tmp.jcl_E
	@echo "Installing ltablib..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/26.done
	sleep 2

jcl/27.done: ltm.s
	@echo "Preparing EBCDIC for ltm..."
	@$(RDRPREP) jcl/27.jcl tmp.jcl_E
	@echo "Installing ltm..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/27.done
	sleep 2

jcl/28.done: lundump.s
	@echo "Preparing EBCDIC for lundump..."
	@$(RDRPREP) jcl/28.jcl tmp.jcl_E
	@echo "Installing lundump..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/28.done
	sleep 2

jcl/29.done: lvm.s
	@echo "Preparing EBCDIC for lvm..."
	@$(RDRPREP) jcl/29.jcl tmp.jcl_E
	@echo "Installing lvm..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/29.done
	sleep 2

jcl/30.done: lzio.s
	@echo "Preparing EBCDIC for lzio..."
	@$(RDRPREP) jcl/30.jcl tmp.jcl_E
	@echo "Installing lzio..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/30.done
	sleep 2

jcl/31.done: lua.s
	@echo "Preparing EBCDIC for lua..."
	@$(RDRPREP) jcl/31.jcl tmp.jcl_E
	@echo "Installing lua..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
	touch jcl/31.done
	sleep 2

