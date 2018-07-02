/*
 * Copyright (C) 2015 Marek Vasut <marex@denx.de>
 *
 * SPDX-License-Identifier:    GPL-2.0+
 */

#include <common.h>
#include <errno.h>
#include <asm/arch/sdram.h>

/* Board-specific header. */
#include <qts/sdram_config.h>

static const struct socfpga_sdram_config sdram_config = {
	.ctrl_cfg =
		(CONFIG_HPS_SDR_CTRLCFG_CTRLCFG_MEMTYPE <<
			SDR_CTRLGRP_CTRLCFG_MEMTYPE_LSB)		|
		(CONFIG_HPS_SDR_CTRLCFG_CTRLCFG_MEMBL <<
			SDR_CTRLGRP_CTRLCFG_MEMBL_LSB)			|
		(CONFIG_HPS_SDR_CTRLCFG_CTRLCFG_ADDRORDER <<
			SDR_CTRLGRP_CTRLCFG_ADDRORDER_LSB)		|
		(CONFIG_HPS_SDR_CTRLCFG_CTRLCFG_ECCEN <<
			SDR_CTRLGRP_CTRLCFG_ECCEN_LSB)			|
		(CONFIG_HPS_SDR_CTRLCFG_CTRLCFG_ECCCORREN <<
			SDR_CTRLGRP_CTRLCFG_ECCCORREN_LSB)		|
		(CONFIG_HPS_SDR_CTRLCFG_CTRLCFG_REORDEREN <<
			SDR_CTRLGRP_CTRLCFG_REORDEREN_LSB)		|
		(CONFIG_HPS_SDR_CTRLCFG_CTRLCFG_STARVELIMIT <<
			SDR_CTRLGRP_CTRLCFG_STARVELIMIT_LSB)		|
		(CONFIG_HPS_SDR_CTRLCFG_CTRLCFG_DQSTRKEN <<
			SDR_CTRLGRP_CTRLCFG_DQSTRKEN_LSB)		|
		(CONFIG_HPS_SDR_CTRLCFG_CTRLCFG_NODMPINS <<
			SDR_CTRLGRP_CTRLCFG_NODMPINS_LSB),
	.dram_timing1 =
		(CONFIG_HPS_SDR_CTRLCFG_DRAMTIMING1_TCWL <<
			SDR_CTRLGRP_DRAMTIMING1_TCWL_LSB)		|
		(CONFIG_HPS_SDR_CTRLCFG_DRAMTIMING1_AL <<
			SDR_CTRLGRP_DRAMTIMING1_TAL_LSB)		|
		(CONFIG_HPS_SDR_CTRLCFG_DRAMTIMING1_TCL <<
			SDR_CTRLGRP_DRAMTIMING1_TCL_LSB)		|
		(CONFIG_HPS_SDR_CTRLCFG_DRAMTIMING1_TRRD <<
			SDR_CTRLGRP_DRAMTIMING1_TRRD_LSB)		|
		(CONFIG_HPS_SDR_CTRLCFG_DRAMTIMING1_TFAW <<
			SDR_CTRLGRP_DRAMTIMING1_TFAW_LSB)		|
		(CONFIG_HPS_SDR_CTRLCFG_DRAMTIMING1_TRFC <<
			SDR_CTRLGRP_DRAMTIMING1_TRFC_LSB),
	.dram_timing2 =
		(CONFIG_HPS_SDR_CTRLCFG_DRAMTIMING2_IF_TREFI <<
			SDR_CTRLGRP_DRAMTIMING2_TREFI_LSB)		|
		(CONFIG_HPS_SDR_CTRLCFG_DRAMTIMING2_IF_TRCD <<
			SDR_CTRLGRP_DRAMTIMING2_TRCD_LSB)		|
		(CONFIG_HPS_SDR_CTRLCFG_DRAMTIMING2_IF_TRP <<
			SDR_CTRLGRP_DRAMTIMING2_TRP_LSB)		|
		(CONFIG_HPS_SDR_CTRLCFG_DRAMTIMING2_IF_TWR <<
			SDR_CTRLGRP_DRAMTIMING2_TWR_LSB)		|
		(CONFIG_HPS_SDR_CTRLCFG_DRAMTIMING2_IF_TWTR <<
			SDR_CTRLGRP_DRAMTIMING2_TWTR_LSB),
	.dram_timing3 =
		(CONFIG_HPS_SDR_CTRLCFG_DRAMTIMING3_TRTP <<
			SDR_CTRLGRP_DRAMTIMING3_TRTP_LSB)		|
		(CONFIG_HPS_SDR_CTRLCFG_DRAMTIMING3_TRAS <<
			SDR_CTRLGRP_DRAMTIMING3_TRAS_LSB)		|
		(CONFIG_HPS_SDR_CTRLCFG_DRAMTIMING3_TRC <<
			SDR_CTRLGRP_DRAMTIMING3_TRC_LSB)		|
		(CONFIG_HPS_SDR_CTRLCFG_DRAMTIMING3_TMRD <<
			SDR_CTRLGRP_DRAMTIMING3_TMRD_LSB)		|
		(CONFIG_HPS_SDR_CTRLCFG_DRAMTIMING3_TCCD <<
			SDR_CTRLGRP_DRAMTIMING3_TCCD_LSB),
	.dram_timing4 =
		(CONFIG_HPS_SDR_CTRLCFG_DRAMTIMING4_SELFRFSHEXIT <<
			SDR_CTRLGRP_DRAMTIMING4_SELFRFSHEXIT_LSB)	|
		(CONFIG_HPS_SDR_CTRLCFG_DRAMTIMING4_PWRDOWNEXIT <<
			SDR_CTRLGRP_DRAMTIMING4_PWRDOWNEXIT_LSB),
	.lowpwr_timing =
		(CONFIG_HPS_SDR_CTRLCFG_LOWPWRTIMING_AUTOPDCYCLES <<
			SDR_CTRLGRP_LOWPWRTIMING_AUTOPDCYCLES_LSB)	|
		(CONFIG_HPS_SDR_CTRLCFG_LOWPWRTIMING_CLKDISABLECYCLES <<
			SDR_CTRLGRP_LOWPWRTIMING_CLKDISABLECYCLES_LSB),
	.dram_odt =
		(CONFIG_HPS_SDR_CTRLCFG_DRAMODT_READ <<
			SDR_CTRLGRP_DRAMODT_READ_LSB)			|
		(CONFIG_HPS_SDR_CTRLCFG_DRAMODT_WRITE <<
			SDR_CTRLGRP_DRAMODT_WRITE_LSB),
	.dram_addrw =
		(CONFIG_HPS_SDR_CTRLCFG_DRAMADDRW_COLBITS <<
			SDR_CTRLGRP_DRAMADDRW_COLBITS_LSB)		|
		(CONFIG_HPS_SDR_CTRLCFG_DRAMADDRW_ROWBITS <<
			SDR_CTRLGRP_DRAMADDRW_ROWBITS_LSB)		|
		(CONFIG_HPS_SDR_CTRLCFG_DRAMADDRW_BANKBITS <<
			SDR_CTRLGRP_DRAMADDRW_BANKBITS_LSB)		|
		((CONFIG_HPS_SDR_CTRLCFG_DRAMADDRW_CSBITS - 1) <<
			SDR_CTRLGRP_DRAMADDRW_CSBITS_LSB),
	.dram_if_width =
		(CONFIG_HPS_SDR_CTRLCFG_DRAMIFWIDTH_IFWIDTH <<
			SDR_CTRLGRP_DRAMIFWIDTH_IFWIDTH_LSB),
	.dram_dev_width =
		(CONFIG_HPS_SDR_CTRLCFG_DRAMDEVWIDTH_DEVWIDTH <<
			SDR_CTRLGRP_DRAMDEVWIDTH_DEVWIDTH_LSB),
	.dram_intr =
		(CONFIG_HPS_SDR_CTRLCFG_DRAMINTR_INTREN <<
			SDR_CTRLGRP_DRAMINTR_INTREN_LSB),
	.lowpwr_eq =
		(CONFIG_HPS_SDR_CTRLCFG_LOWPWREQ_SELFRFSHMASK <<
			SDR_CTRLGRP_LOWPWREQ_SELFRFSHMASK_LSB),
	.static_cfg =
		(CONFIG_HPS_SDR_CTRLCFG_STATICCFG_MEMBL <<
			SDR_CTRLGRP_STATICCFG_MEMBL_LSB)		|
		(CONFIG_HPS_SDR_CTRLCFG_STATICCFG_USEECCASDATA <<
			SDR_CTRLGRP_STATICCFG_USEECCASDATA_LSB),
	.ctrl_width =
		(CONFIG_HPS_SDR_CTRLCFG_CTRLWIDTH_CTRLWIDTH <<
			SDR_CTRLGRP_CTRLWIDTH_CTRLWIDTH_LSB),
	.cport_width =
		(CONFIG_HPS_SDR_CTRLCFG_CPORTWIDTH_CPORTWIDTH <<
			SDR_CTRLGRP_CPORTWIDTH_CMDPORTWIDTH_LSB),
	.cport_wmap =
		(CONFIG_HPS_SDR_CTRLCFG_CPORTWMAP_CPORTWMAP <<
			SDR_CTRLGRP_CPORTWMAP_CPORTWFIFOMAP_LSB),
	.cport_rmap =
		(CONFIG_HPS_SDR_CTRLCFG_CPORTRMAP_CPORTRMAP <<
			SDR_CTRLGRP_CPORTRMAP_CPORTRFIFOMAP_LSB),
	.rfifo_cmap =
		(CONFIG_HPS_SDR_CTRLCFG_RFIFOCMAP_RFIFOCMAP <<
			SDR_CTRLGRP_RFIFOCMAP_RFIFOCPORTMAP_LSB),
	.wfifo_cmap =
		(CONFIG_HPS_SDR_CTRLCFG_WFIFOCMAP_WFIFOCMAP <<
			SDR_CTRLGRP_WFIFOCMAP_WFIFOCPORTMAP_LSB),
	.cport_rdwr =
		(CONFIG_HPS_SDR_CTRLCFG_CPORTRDWR_CPORTRDWR <<
			SDR_CTRLGRP_CPORTRDWR_CPORTRDWR_LSB),
	.port_cfg =
		(CONFIG_HPS_SDR_CTRLCFG_PORTCFG_AUTOPCHEN <<
			SDR_CTRLGRP_PORTCFG_AUTOPCHEN_LSB),
	.fpgaport_rst = CONFIG_HPS_SDR_CTRLCFG_FPGAPORTRST,
	.fifo_cfg =
		(CONFIG_HPS_SDR_CTRLCFG_FIFOCFG_SYNCMODE <<
			SDR_CTRLGRP_FIFOCFG_SYNCMODE_LSB)		|
		(CONFIG_HPS_SDR_CTRLCFG_FIFOCFG_INCSYNC <<
			SDR_CTRLGRP_FIFOCFG_INCSYNC_LSB),
	.mp_priority =
		(CONFIG_HPS_SDR_CTRLCFG_MPPRIORITY_USERPRIORITY <<
			SDR_CTRLGRP_MPPRIORITY_USERPRIORITY_LSB),
	.mp_weight0 =
		(CONFIG_HPS_SDR_CTRLCFG_MPWIEIGHT_0_STATICWEIGHT_31_0 <<
			SDR_CTRLGRP_MPWEIGHT_MPWEIGHT_0_STATICWEIGHT_31_0_LSB),
	.mp_weight1 =
		(CONFIG_HPS_SDR_CTRLCFG_MPWIEIGHT_1_STATICWEIGHT_49_32 <<
			SDR_CTRLGRP_MPWEIGHT_MPWEIGHT_1_STATICWEIGHT_49_32_LSB) |
		(CONFIG_HPS_SDR_CTRLCFG_MPWIEIGHT_1_SUMOFWEIGHT_13_0 <<
			SDR_CTRLGRP_MPWEIGHT_MPWEIGHT_1_SUMOFWEIGHTS_13_0_LSB),
	.mp_weight2 =
		(CONFIG_HPS_SDR_CTRLCFG_MPWIEIGHT_2_SUMOFWEIGHT_45_14 <<
			SDR_CTRLGRP_MPWEIGHT_MPWEIGHT_2_SUMOFWEIGHTS_45_14_LSB),
	.mp_weight3 =
		(CONFIG_HPS_SDR_CTRLCFG_MPWIEIGHT_3_SUMOFWEIGHT_63_46 <<
			SDR_CTRLGRP_MPWEIGHT_MPWEIGHT_3_SUMOFWEIGHTS_63_46_LSB),
	.mp_pacing0 =
		(CONFIG_HPS_SDR_CTRLCFG_MPPACING_0_THRESHOLD1_31_0 <<
			SDR_CTRLGRP_MPPACING_MPPACING_0_THRESHOLD1_31_0_LSB),
	.mp_pacing1 =
		(CONFIG_HPS_SDR_CTRLCFG_MPPACING_1_THRESHOLD1_59_32 <<
			SDR_CTRLGRP_MPPACING_MPPACING_1_THRESHOLD1_59_32_LSB) |
		(CONFIG_HPS_SDR_CTRLCFG_MPPACING_1_THRESHOLD2_3_0 <<
			SDR_CTRLGRP_MPPACING_MPPACING_1_THRESHOLD2_3_0_LSB),
	.mp_pacing2 =
		(CONFIG_HPS_SDR_CTRLCFG_MPPACING_2_THRESHOLD2_35_4 <<
			SDR_CTRLGRP_MPPACING_MPPACING_2_THRESHOLD2_35_4_LSB),
	.mp_pacing3 =
		(CONFIG_HPS_SDR_CTRLCFG_MPPACING_3_THRESHOLD2_59_36 <<
			SDR_CTRLGRP_MPPACING_MPPACING_3_THRESHOLD2_59_36_LSB),
	.mp_threshold0 =
		(CONFIG_HPS_SDR_CTRLCFG_MPTHRESHOLDRST_0_THRESHOLDRSTCYCLES_31_0 <<
			SDR_CTRLGRP_MPTHRESHOLDRST_0_THRESHOLDRSTCYCLES_31_0_LSB),
	.mp_threshold1 =
		(CONFIG_HPS_SDR_CTRLCFG_MPTHRESHOLDRST_1_THRESHOLDRSTCYCLES_63_32 <<
			SDR_CTRLGRP_MPTHRESHOLDRST_1_THRESHOLDRSTCYCLES_63_32_LSB),
	.mp_threshold2 =
		(CONFIG_HPS_SDR_CTRLCFG_MPTHRESHOLDRST_2_THRESHOLDRSTCYCLES_79_64 <<
			SDR_CTRLGRP_MPTHRESHOLDRST_2_THRESHOLDRSTCYCLES_79_64_LSB),
	.phy_ctrl0 = CONFIG_HPS_SDR_CTRLCFG_PHYCTRL_PHYCTRL_0,
};

static const struct socfpga_sdram_rw_mgr_config rw_mgr_config = {
	.activate_0_and_1		= RW_MGR_ACTIVATE_0_AND_1,
	.activate_0_and_1_wait1		= RW_MGR_ACTIVATE_0_AND_1_WAIT1,
	.activate_0_and_1_wait2		= RW_MGR_ACTIVATE_0_AND_1_WAIT2,
	.activate_1			= RW_MGR_ACTIVATE_1,
	.clear_dqs_enable		= RW_MGR_CLEAR_DQS_ENABLE,
	.guaranteed_read		= RW_MGR_GUARANTEED_READ,
	.guaranteed_read_cont		= RW_MGR_GUARANTEED_READ_CONT,
	.guaranteed_write		= RW_MGR_GUARANTEED_WRITE,
	.guaranteed_write_wait0		= RW_MGR_GUARANTEED_WRITE_WAIT0,
	.guaranteed_write_wait1		= RW_MGR_GUARANTEED_WRITE_WAIT1,
	.guaranteed_write_wait2		= RW_MGR_GUARANTEED_WRITE_WAIT2,
	.guaranteed_write_wait3		= RW_MGR_GUARANTEED_WRITE_WAIT3,
	.idle				= RW_MGR_IDLE,
	.idle_loop1			= RW_MGR_IDLE_LOOP1,
	.idle_loop2			= RW_MGR_IDLE_LOOP2,
	.init_reset_0_cke_0		= RW_MGR_INIT_RESET_0_CKE_0,
	.init_reset_1_cke_0		= RW_MGR_INIT_RESET_1_CKE_0,
	.lfsr_wr_rd_bank_0		= RW_MGR_LFSR_WR_RD_BANK_0,
	.lfsr_wr_rd_bank_0_data		= RW_MGR_LFSR_WR_RD_BANK_0_DATA,
	.lfsr_wr_rd_bank_0_dqs		= RW_MGR_LFSR_WR_RD_BANK_0_DQS,
	.lfsr_wr_rd_bank_0_nop		= RW_MGR_LFSR_WR_RD_BANK_0_NOP,
	.lfsr_wr_rd_bank_0_wait		= RW_MGR_LFSR_WR_RD_BANK_0_WAIT,
	.lfsr_wr_rd_bank_0_wl_1		= RW_MGR_LFSR_WR_RD_BANK_0_WL_1,
	.lfsr_wr_rd_dm_bank_0		= RW_MGR_LFSR_WR_RD_DM_BANK_0,
	.lfsr_wr_rd_dm_bank_0_data	= RW_MGR_LFSR_WR_RD_DM_BANK_0_DATA,
	.lfsr_wr_rd_dm_bank_0_dqs	= RW_MGR_LFSR_WR_RD_DM_BANK_0_DQS,
	.lfsr_wr_rd_dm_bank_0_nop	= RW_MGR_LFSR_WR_RD_DM_BANK_0_NOP,
	.lfsr_wr_rd_dm_bank_0_wait	= RW_MGR_LFSR_WR_RD_DM_BANK_0_WAIT,
	.lfsr_wr_rd_dm_bank_0_wl_1	= RW_MGR_LFSR_WR_RD_DM_BANK_0_WL_1,
	.mrs0_dll_reset			= RW_MGR_MRS0_DLL_RESET,
	.mrs0_dll_reset_mirr		= RW_MGR_MRS0_DLL_RESET_MIRR,
	.mrs0_user			= RW_MGR_MRS0_USER,
	.mrs0_user_mirr			= RW_MGR_MRS0_USER_MIRR,
	.mrs1				= RW_MGR_MRS1,
	.mrs1_mirr			= RW_MGR_MRS1_MIRR,
	.mrs2				= RW_MGR_MRS2,
	.mrs2_mirr			= RW_MGR_MRS2_MIRR,
	.mrs3				= RW_MGR_MRS3,
	.mrs3_mirr			= RW_MGR_MRS3_MIRR,
	.precharge_all			= RW_MGR_PRECHARGE_ALL,
	.read_b2b			= RW_MGR_READ_B2B,
	.read_b2b_wait1			= RW_MGR_READ_B2B_WAIT1,
	.read_b2b_wait2			= RW_MGR_READ_B2B_WAIT2,
	.refresh_all			= RW_MGR_REFRESH_ALL,
	.rreturn			= RW_MGR_RETURN,
	.sgle_read			= RW_MGR_SGLE_READ,
	.zqcl				= RW_MGR_ZQCL,

	.true_mem_data_mask_width	= RW_MGR_TRUE_MEM_DATA_MASK_WIDTH,
	.mem_address_mirroring		= RW_MGR_MEM_ADDRESS_MIRRORING,
	.mem_data_mask_width		= RW_MGR_MEM_DATA_MASK_WIDTH,
	.mem_data_width			= RW_MGR_MEM_DATA_WIDTH,
	.mem_dq_per_read_dqs		= RW_MGR_MEM_DQ_PER_READ_DQS,
	.mem_dq_per_write_dqs		= RW_MGR_MEM_DQ_PER_WRITE_DQS,
	.mem_if_read_dqs_width		= RW_MGR_MEM_IF_READ_DQS_WIDTH,
	.mem_if_write_dqs_width		= RW_MGR_MEM_IF_WRITE_DQS_WIDTH,
	.mem_number_of_cs_per_dimm	= RW_MGR_MEM_NUMBER_OF_CS_PER_DIMM,
	.mem_number_of_ranks		= RW_MGR_MEM_NUMBER_OF_RANKS,
	.mem_virtual_groups_per_read_dqs =
		RW_MGR_MEM_VIRTUAL_GROUPS_PER_READ_DQS,
	.mem_virtual_groups_per_write_dqs =
		RW_MGR_MEM_VIRTUAL_GROUPS_PER_WRITE_DQS,
};

struct socfpga_sdram_io_config io_config = {
	.delay_per_dchain_tap		= IO_DELAY_PER_DCHAIN_TAP,
	.delay_per_dqs_en_dchain_tap	= IO_DELAY_PER_DQS_EN_DCHAIN_TAP,
	.delay_per_opa_tap		= IO_DELAY_PER_OPA_TAP,
	.dll_chain_length		= IO_DLL_CHAIN_LENGTH,
	.dqdqs_out_phase_max		= IO_DQDQS_OUT_PHASE_MAX,
	.dqs_en_delay_max		= IO_DQS_EN_DELAY_MAX,
	.dqs_en_delay_offset		= IO_DQS_EN_DELAY_OFFSET,
	.dqs_en_phase_max		= IO_DQS_EN_PHASE_MAX,
	.dqs_in_delay_max		= IO_DQS_IN_DELAY_MAX,
	.dqs_in_reserve			= IO_DQS_IN_RESERVE,
	.dqs_out_reserve		= IO_DQS_OUT_RESERVE,
	.io_in_delay_max		= IO_IO_IN_DELAY_MAX,
	.io_out1_delay_max		= IO_IO_OUT1_DELAY_MAX,
	.io_out2_delay_max		= IO_IO_OUT2_DELAY_MAX,
	.shift_dqs_en_when_shift_dqs	= IO_SHIFT_DQS_EN_WHEN_SHIFT_DQS,
};

struct socfpga_sdram_misc_config misc_config = {
	.afi_rate_ratio			= AFI_RATE_RATIO,
	.calib_lfifo_offset		= CALIB_LFIFO_OFFSET,
	.calib_vfifo_offset		= CALIB_VFIFO_OFFSET,
	.enable_super_quick_calibration	= ENABLE_SUPER_QUICK_CALIBRATION,
	.max_latency_count_width	= MAX_LATENCY_COUNT_WIDTH,
	.read_valid_fifo_size		= READ_VALID_FIFO_SIZE,
	.reg_file_init_seq_signature	= REG_FILE_INIT_SEQ_SIGNATURE,
	.tinit_cntr0_val		= TINIT_CNTR0_VAL,
	.tinit_cntr1_val		= TINIT_CNTR1_VAL,
	.tinit_cntr2_val		= TINIT_CNTR2_VAL,
	.treset_cntr0_val		= TRESET_CNTR0_VAL,
	.treset_cntr1_val		= TRESET_CNTR1_VAL,
	.treset_cntr2_val		= TRESET_CNTR2_VAL,
};

const struct socfpga_sdram_config *socfpga_get_sdram_config(void)
{
	return &sdram_config;
}

void socfpga_get_seq_ac_init(const u32 **init, unsigned int *nelem)
{
	*init = ac_rom_init;
	*nelem = ARRAY_SIZE(ac_rom_init);
}

void socfpga_get_seq_inst_init(const u32 **init, unsigned int *nelem)
{
	*init = inst_rom_init;
	*nelem = ARRAY_SIZE(inst_rom_init);
}

const struct socfpga_sdram_rw_mgr_config *socfpga_get_sdram_rwmgr_config(void)
{
	return &rw_mgr_config;
}

const struct socfpga_sdram_io_config *socfpga_get_sdram_io_config(void)
{
	return &io_config;
}

const struct socfpga_sdram_misc_config *socfpga_get_sdram_misc_config(void)
{
	return &misc_config;
}
