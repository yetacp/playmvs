include ../common.m4

asm : vsam.s main.s 

00_define_catalog:
	@echo "Preparing EBCDIC..."
	@$(RDRPREP) db/00_define_catalog.jcl tmp.jcl_E
	@echo "00_define_catalog..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E

03_create_dataset:
	@echo "Preparing EBCDIC..."
	@$(RDRPREP) db/03_create_dataset.jcl tmp.jcl_E
	@echo "03_create_dataset..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E

04_define_cluster_esds:
	@echo "Preparing EBCDIC..."
	@$(RDRPREP) db/04_define_cluster_esds.jcl tmp.jcl_E
	@echo "04_define_cluster_esds..."
	nc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
