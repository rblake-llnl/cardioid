#ifdef BGQ
#include <bgpm/include/bgpm.h>
/*====================================================*/
/* routine to set labels for each of the BGQ counters */
/*====================================================*/
const int MAX_EVENTS = 420; // number of counter events in BGQ
const int MAX_THREADS = 64; // maximum number of threads in BGQ
const int MAX_A2_COUNTERS = 24; // maximum number of events collected by A2
// predefined counter events; limited to 6 A2 events for now
unsigned int counterSet[] = { PEVT_LSU_COMMIT_LD_MISSES, PEVT_LSU_COMMIT_CACHEABLE_LDS, PEVT_L1P_BAS_MISS, PEVT_INST_QFPU_FMA, PEVT_INST_QFPU_QMA, PEVT_INST_QFPU_FPGRP1};         
//int nCounters_ = sizeof(counterSet)/sizeof(unsigned); 
int nCounters_=8; 
const char *counterNames_[] = {"#Calls" , "Time","LD_MISSES",  "CACHEABLE_LDS", "L1P_BAS_MISS", "QFPU_FMA", "QFPU_QMA", "QFPU_FPGR1"};
static unsigned int counterHandle[MAX_THREADS]; // store the event set handler for each thread
static char label[MAX_EVENTS][80]; // store the event name
void set_labels(void)
{
   strcpy(label[PEVT_UNDEF], " undefined");
   strcpy(label[PEVT_AXU_INSTR_COMMIT], " AXU Instruction Committed");
   strcpy(label[PEVT_AXU_CR_COMMIT], " AXU CR Instruction Committed");
   strcpy(label[PEVT_AXU_IDLE], " AXU Idle");
   strcpy(label[PEVT_AXU_FP_DS_ACTIVE], " AXU FP Divide or Square root in progress");
   strcpy(label[PEVT_AXU_FP_DS_ACTIVE_CYC], " AXU FP Divide or Square root in progress cycles");
   strcpy(label[PEVT_AXU_DENORM_FLUSH], " AXU Denormal Operand flush");
   strcpy(label[PEVT_AXU_UCODE_OPS_COMMIT], " AXU uCode Operations Committed");
   strcpy(label[PEVT_AXU_FP_EXCEPT], " AXU Floating Point Exception");
   strcpy(label[PEVT_AXU_FP_ENAB_EXCEPT], " AXU Floating Point Enabled Exception");
   strcpy(label[PEVT_IU_IL1_MISS], " IL1 Miss");
   strcpy(label[PEVT_IU_IL1_MISS_CYC], " IL1 Miss cycles");
   strcpy(label[PEVT_IU_IL1_RELOADS_DROPPED], " IL1 Reloads Dropped");
   strcpy(label[PEVT_IU_RELOAD_COLLISIONS], " Reload Collisions");
   strcpy(label[PEVT_IU_RELOAD_COLLISIONS_CYC], " Reload Collisions cycles");
   strcpy(label[PEVT_IU_IU0_REDIR_CYC], " IU0 Redirected cycles");
   strcpy(label[PEVT_IU_IERAT_MISS], " IERAT Miss");
   strcpy(label[PEVT_IU_IERAT_MISS_CYC], " IERAT Miss cycles");
   strcpy(label[PEVT_IU_ICACHE_FETCH], " ICache Fetch");
   strcpy(label[PEVT_IU_ICACHE_FETCH_CYC], " ICache Fetch cycles");
   strcpy(label[PEVT_IU_INSTR_FETCHED], " Instructions Fetched");
   strcpy(label[PEVT_IU_INSTR_FETCHED_CYC], " Instructions Fetched cycles");
   strcpy(label[PEVT_IU_RSV_ANY_L2_BACK_INV], " reserved any L2 Back Invalidates");
   strcpy(label[PEVT_IU_RSV_ANY_L2_BACK_INV_CYC], " reserved any L2 Back Invalidates cycles");
   strcpy(label[PEVT_IU_L2_BACK_INV_HITS], " L2 Back Invalidates - Hits");
   strcpy(label[PEVT_IU_L2_BACK_INV_HITS_CYC], " L2 Back Invalidates - Hits cycles");
   strcpy(label[PEVT_IU_IBUFF_EMPTY], " IBuff Empty");
   strcpy(label[PEVT_IU_IBUFF_EMPTY_CYC], " IBuff Empty cycles");
   strcpy(label[PEVT_IU_IBUFF_FLUSH], " IBuff Flush");
   strcpy(label[PEVT_IU_IBUFF_FLUSH_CYC], " IBuff Flush cycles");
   strcpy(label[PEVT_IU_IS1_STALL_CYC], " IU5 Stage Register Dependency Stall");
   strcpy(label[PEVT_IU_IS2_STALL_CYC], " IU6 Instruction Issue Stall");
   strcpy(label[PEVT_IU_BARRIER_OP_STALL_CYC], " Barrier Op Stall");
   strcpy(label[PEVT_IU_SLOW_SPR_ACCESS_CYC], " Slow SPR Access");
   strcpy(label[PEVT_IU_RAW_DEP_HIT_CYC], " RAW Dep Hit");
   strcpy(label[PEVT_IU_WAW_DEP_HIT_CYC], " WAW Dep Hit");
   strcpy(label[PEVT_IU_SYNC_DEP_HIT_CYC], " Sync Dep Hit");
   strcpy(label[PEVT_IU_SPR_DEP_HIT_CYC], " SPR Dep Hit");
   strcpy(label[PEVT_IU_AXU_DEP_HIT_CYC], " AXU Dep Hit");
   strcpy(label[PEVT_IU_FXU_DEP_HIT_CYC], " FXU Dep Hit");
   strcpy(label[PEVT_IU_AXU_FXU_DEP_HIT_CYC], " AXU CR Instruction Committed");
   strcpy(label[PEVT_IU_AXU_ISSUE_PRI_LOSS_CYC], " AXU Issue Priority Loss");
   strcpy(label[PEVT_IU_FXU_ISSUE_PRI_LOSS_CYC], " FXU Issue Priority Loss");
   strcpy(label[PEVT_IU_FXU_ISSUE_COUNT], " FXU Issue Count");
   strcpy(label[PEVT_IU_TOT_ISSUE_COUNT], " Total Issue Count");
   //strcpy(label[PEVT_IU_INSTR_MATCH_COUNT], " Instruction Match Count");
   strcpy(label[PEVT_XU_PROC_BUSY], " Processor Busy");
   strcpy(label[PEVT_XU_BR_COMMIT_CORE], " Branch Commit");
   strcpy(label[PEVT_XU_BR_MISPRED_COMMIT_CORE], " Branch Mispredict Commit");
   strcpy(label[PEVT_XU_BR_TARG_ADDR_MISPRED_COMMIT_CORE], " Branch Target Address Mispredict Commit");
   strcpy(label[PEVT_XU_THRD_RUNNING], " Thread Running");
   strcpy(label[PEVT_XU_TIMEBASE_TICK], " Timebase Tick");
   strcpy(label[PEVT_XU_SPR_READ_COMMIT], " SPR Read Commit");
   strcpy(label[PEVT_XU_SPR_WRITE_COMMIT], " SPR Write Commit");
   strcpy(label[PEVT_XU_STALLED_ON_WAITRSV], " Cycles stalled on waitrsv");
   strcpy(label[PEVT_XU_STALLED_ON_WAITRSV_CYC], " Cycles stalled on waitrsv cycles");
   strcpy(label[PEVT_XU_EXT_INT_ASSERT], " External Interrupt Asserted");
   strcpy(label[PEVT_XU_CRIT_EXT_INT_ASSERT], " Critical External Interrupt Asserted");
   strcpy(label[PEVT_XU_PERF_MON_INT_ASSERT], " Performance Monitor Interrupt Asserted");
   strcpy(label[PEVT_XU_PPC_COMMIT], " PPC Commit");
   strcpy(label[PEVT_XU_COMMIT], " XU Operations Committed");
   strcpy(label[PEVT_XU_UCODE_COMMIT], " uCode Sequence Commit");
   strcpy(label[PEVT_XU_ANY_FLUSH], " Any Flush");
   strcpy(label[PEVT_XU_BR_COMMIT], " Branch Commit");
   strcpy(label[PEVT_XU_BR_MISPRED_COMMIT], " Branch Mispredict Commit");
   strcpy(label[PEVT_XU_BR_TAKEN_COMMIT], " Branch Taken Commit");
   strcpy(label[PEVT_XU_BR_TARG_ADDR_MISPRED_COMMIT], " Branch Target Address Mispredict Commit");
   strcpy(label[PEVT_XU_MULT_DIV_COLLISION], " Mult/Div Collision");
   strcpy(label[PEVT_XU_EXT_INT_PEND], " External Interrupt Pending");
   strcpy(label[PEVT_XU_CRIT_EXT_INT_PEND], " Critical External Interrupt Pending");
   strcpy(label[PEVT_XU_PERF_MON_INT_PEND], " Performance Monitor Interrupt Pending");
   //strcpy(label[PEVT_XU_OPCODE_MATCH], " Opcode Match");
   strcpy(label[PEVT_XU_RUN_INSTR], " Run Instructions");
   strcpy(label[PEVT_XU_INTS_TAKEN], " Interrupts Taken");
   strcpy(label[PEVT_XU_EXT_INT_TAKEN], " External Interrupt Taken");
   strcpy(label[PEVT_XU_CRIT_EXT_INT_TAKEN], " Critical External Interrupt Taken");
   strcpy(label[PEVT_XU_PERF_MON_INT_TAKEN], " Performance Monitor Interrupt Taken");
   strcpy(label[PEVT_XU_DOORBELL_INT_TAKEN], " Doorbell Interrupt Taken");
   strcpy(label[PEVT_XU_STCX_FAIL], " stcx fail");
   strcpy(label[PEVT_XU_ICSWX_FAILED], " icswx failed");
   strcpy(label[PEVT_XU_ICSWX_COMMIT], " icswx commit");
   strcpy(label[PEVT_XU_MULT_DIV_BUSY], " Mult/Div Busy");
   strcpy(label[PEVT_LSU_COMMIT_STS], " Committed Stores");
   strcpy(label[PEVT_LSU_COMMIT_ST_MISSES], " Committed Store Misses");
   strcpy(label[PEVT_LSU_COMMIT_LD_MISSES], " Committed Load Misses");
   strcpy(label[PEVT_LSU_COMMIT_CACHE_INHIB_LD_MISSES], " Committed Cache-Inhibited Load Misses");
   strcpy(label[PEVT_LSU_COMMIT_CACHEABLE_LDS], " Committed Cacheable Loads");
   strcpy(label[PEVT_LSU_COMMIT_DCBT_MISSES], " Committed DCBT Misses");
   strcpy(label[PEVT_LSU_COMMIT_DCBT_HITS], " Committed DCBT Hits");
   strcpy(label[PEVT_LSU_COMMIT_AXU_LDS], " Committed AXU Loads");
   strcpy(label[PEVT_LSU_COMMIT_AXU_STS], " Committed AXU Stores");
   strcpy(label[PEVT_LSU_COMMIT_STCX], " Committed STCX");
   strcpy(label[PEVT_LSU_COMMIT_WCLR], " Committed WCLR");
   strcpy(label[PEVT_LSU_COMMIT_WCLR_WL], " Committed WCLR Watchlost");
   strcpy(label[PEVT_LSU_COMMIT_LDAWX], " Committed LDAWX");
   strcpy(label[PEVT_LSU_UNSUPPORTED_ALIGNMENT_FLUSH], " Unsupported Alignment Flush");
   strcpy(label[PEVT_LSU_RELOAD_RESRC_CONFLICT_FLUSH], " Reload Resource Conflict Flush");
   strcpy(label[PEVT_LSU_COMMIT_DUPLICATE_LDAWX], " Committed Duplicate LDAWX");
   strcpy(label[PEVT_LSU_INTER_THRD_DIR_ACCESS_FLUSH], " Inter-Thread Directory Access Flush");
   strcpy(label[PEVT_LSU_LMQ_DEPENDENCY_FLUSH], " Load Miss Queue Dependency Flush");
   strcpy(label[PEVT_LSU_COMMIT_WCHKALL], " Committed WCHKALL");
   strcpy(label[PEVT_LSU_COMMIT_SUCC_WCHKALL], " Committed Successful WCHKALL");
   strcpy(label[PEVT_LSU_LD_MISS_Q_FULL_FLUSH], " Load Miss Queue Full Flush");
   strcpy(label[PEVT_LSU_ST_Q_FULL_FLUSH], " Store Queue Full Flush");
   strcpy(label[PEVT_LSU_HIT_LD_FLUSH], " Hit Against Outstanding Load Flush");
   strcpy(label[PEVT_LSU_HIT_IG1_REQ_FLUSH], " Hit Against Outstanding I=G=1 Request Flush");
   strcpy(label[PEVT_LSU_LARX_FINISHED], " LARX Finished");
   strcpy(label[PEVT_LSU_INTER_THRD_ST_WATCH_LOST], " Inter-Thread Store Set Watch Lost Indicator");
   strcpy(label[PEVT_LSU_RELOAD_WATCH_LOST], " Reload Set Watch Lost Indicator");
   strcpy(label[PEVT_LSU_BACK_INV_WATCH_LOST], " Back-Invalidate Set Watch Lost Indicator");
   strcpy(label[PEVT_LSU_L1_DCACHE_BACK_INVAL], " L1 Data Cache Back-Invalidate");
   strcpy(label[PEVT_LSU_L1_DCACHE_BACK_INVAL_HITS], " L1 Data Cache Back-Invalidate Hits");
   strcpy(label[PEVT_LSU_L1_CACHE_PTYERR_DETECTED], " L1 Cache Parity Error Detected");
   strcpy(label[PEVT_LSU_LD_LAT_MEM_SUBSYS_CYC], " Load Latency Memory Subsystem");
   strcpy(label[PEVT_MMU_TLB_HIT_DIRECT_IERAT], " TLB hit direct after ierat miss");
   strcpy(label[PEVT_MMU_TLB_MISS_DIRECT_IERAT], " TLB miss direct after ierat miss");
   strcpy(label[PEVT_MMU_TLB_MISS_INDIR_IERAT], " TLB miss indirect after ierat miss");
   strcpy(label[PEVT_MMU_HTW_HIT_IERAT], " Hardware Table walk hit after ierat miss");
   strcpy(label[PEVT_MMU_HTW_MISS_IERAT], " Hardware Table walk miss after ierat miss");
   strcpy(label[PEVT_MMU_TLB_HIT_DIRECT_DERAT], " TLB hit direct after derat miss");
   strcpy(label[PEVT_MMU_TLB_MISS_DIRECT_DERAT], " TLB miss direct after derat miss");
   strcpy(label[PEVT_MMU_TLB_MISS_INDIR_DERAT], " TLB miss indirect after derat miss");
   strcpy(label[PEVT_MMU_HTW_HIT_DERAT], " Hardware Table walk hit after derat miss");
   strcpy(label[PEVT_MMU_HTW_MISS_DERAT], " Hardware Table walk miss after derat miss");
   strcpy(label[PEVT_MMU_IERAT_MISS], " Ierat miss");
   strcpy(label[PEVT_MMU_IERAT_MISS_CYC], " Ierat miss cycles");
   strcpy(label[PEVT_MMU_DERAT_MISS], " Derat miss");
   strcpy(label[PEVT_MMU_DERAT_MISS_CYC], " Derat miss cycles");
   strcpy(label[PEVT_MMU_IERAT_MISS_TOT], " Ierat miss total");
   strcpy(label[PEVT_MMU_DERAT_MISS_TOT], " derat miss total");
   strcpy(label[PEVT_MMU_TLB_MISS_DIRECT_TOT], " tlb miss direct total");
   strcpy(label[PEVT_MMU_TLB_HIT_FIRSTSIZE_TOT], " tlb hit firstsize total");
   strcpy(label[PEVT_MMU_TLB_HIT_INDIR_TOT], " tlb hit indirect total");
   strcpy(label[PEVT_MMU_HTW_PTERELOAD_TOT], " htw ptereload total");
   strcpy(label[PEVT_MMU_LRAT_TRANS_TOT], " lrat translation total");
   strcpy(label[PEVT_MMU_LRAT_MISS_TOT], " lrat miss total");
   strcpy(label[PEVT_MMU_PT_FAULT_TOT], " pt fault total");
   strcpy(label[PEVT_MMU_PT_INELIG_TOT], " pt inelig total");
   strcpy(label[PEVT_MMU_TLBWEC_FAIL_TOT], " tlbwec fail total");
   strcpy(label[PEVT_MMU_TLBWEC_SUCC_TOT], " tlbwec success total");
   strcpy(label[PEVT_MMU_TLBILX_SRC_TOT], " tlbilx local source total");
   strcpy(label[PEVT_MMU_TLBIVAX_SRC_TOT], " tlbivax local source total");
   strcpy(label[PEVT_MMU_TLBIVAX_SNOOP_TOT], " tlbivax snoop total");
   strcpy(label[PEVT_MMU_TLB_FLUSH_REQ_TOT], " tlb flush req total");
   strcpy(label[PEVT_MMU_TLB_FLUSH_REQ_TOT_CYC], " tlb flush req total cycles");
   strcpy(label[PEVT_L1P_BAS_STRM_LINE_ESTB], " L1p stream line establish");
   strcpy(label[PEVT_L1P_BAS_HIT], " L1p hit ");
   strcpy(label[PEVT_L1P_BAS_PF2DFC], " L1p pf2dfc");
   strcpy(label[PEVT_L1P_BAS_MISS], " L1p miss");
   strcpy(label[PEVT_L1P_BAS_LU_DRAIN], " L1p LU drain");
   strcpy(label[PEVT_L1P_BAS_LU_DRAIN_CYC], " L1p LU drain Cyc");
   strcpy(label[PEVT_L1P_BAS_LD], " L1p Load");
   strcpy(label[PEVT_L1P_BAS_ST_WC], " L1p Store-WC");
   strcpy(label[PEVT_L1P_BAS_ST_32BYTE], " L1p Store 32byte");
   strcpy(label[PEVT_L1P_BAS_ST_CRACKED], " L1p Store-cracked");
   strcpy(label[PEVT_L1P_BAS_LU_STALL_SRT], " L1p LU stall-SRT");
   strcpy(label[PEVT_L1P_BAS_LU_STALL_SRT_CYC], " L1p LU stall-SRT Cyc");
   strcpy(label[PEVT_L1P_BAS_LU_STALL_MMIO_DCR], " L1p LU stall-MMIO/DCR");
   strcpy(label[PEVT_L1P_BAS_LU_STALL_MMIO_DCR_CYC], " L1p LU stall-MMIO/DCR Cyc");
   strcpy(label[PEVT_L1P_BAS_LU_STALL_STRM_DET], " L1p LU stall-stream detect");
   strcpy(label[PEVT_L1P_BAS_LU_STALL_STRM_DET_CYC], " L1p LU stall-stream detect Cyc");
   strcpy(label[PEVT_L1P_BAS_LU_STALL_LIST_RD], " L1p LU stall-list read");
   strcpy(label[PEVT_L1P_BAS_LU_STALL_LIST_RD_CYC], " L1p LU stall-list read Cyc");
   strcpy(label[PEVT_L1P_BAS_ST], " L1p Store");
   strcpy(label[PEVT_L1P_BAS_LU_STALL_LIST_WRT], " L1p LU stall-list write");
   strcpy(label[PEVT_L1P_BAS_LU_STALL_LIST_WRT_CYC], " L1p LU stall-list write Cyc");
   strcpy(label[PEVT_L1P_SW_MAS_SW_REQ_VAL], " L1p switch master sw req valid");
   strcpy(label[PEVT_L1P_SW_MAS_SW_REQ_GATE], " L1p switch master sw req gate");
   strcpy(label[PEVT_L1P_SW_MAS_SW_DATA_GATE], " L1p switch master sw data gate");
   strcpy(label[PEVT_L1P_SW_SR_MAS_RD_VAL_2], " L1p switch sr master rd valid 2 ");
   strcpy(label[PEVT_L1P_SW_SI_MAS_REQ_VAL_2], " L1p switch si master req valid 2");
   strcpy(label[PEVT_L1P_SW_SW_MAS_SKED_VAL_2], " L1p switch sw master sked valid 2");
   strcpy(label[PEVT_L1P_SW_SW_MAS_EAGER_VAL_2], " L1p switch sw master eager valid 2");
   strcpy(label[PEVT_L1P_SW_TLB_FILL], " L1p switch tlb fill");
   strcpy(label[PEVT_L1P_SW_STWCX_FAIL], " L1p switch stwcx fail");
   strcpy(label[PEVT_L1P_SW_STWCX], " L1p switch stwcx");
   strcpy(label[PEVT_L1P_SW_I_FETCH], " L1p switch I-fetch");
   strcpy(label[PEVT_L1P_SW_MSYNC], " L1p switch Msync");
   strcpy(label[PEVT_L1P_SW_LWARX], " L1p switch Lwarx");
   strcpy(label[PEVT_L1P_SW_KILL_L2_RSV], " L1p switch L1p killed L2 slice reserve");
   strcpy(label[PEVT_L1P_SW_L2_CANCEL_A2_RSV], " L1p switch L2 slice cancelled A2 reserve");
   strcpy(label[PEVT_L1P_SW_L1_INVAL], " L1p switch L1 inval");
   strcpy(label[PEVT_L1P_SW_WC_EVICT_ADDR], " L1p switch WC evict by nearby address");
   strcpy(label[PEVT_L1P_STRM_LINE_ESTB], " L1p stream L1p single line established");
   strcpy(label[PEVT_L1P_STRM_HIT_FWD], " L1p stream L1p hit forwarded");
   strcpy(label[PEVT_L1P_STRM_L1_HIT_FWD], " L1p stream L1 hit forwarded");
   strcpy(label[PEVT_L1P_STRM_EVICT_UNUSED], " L1p stream L1p evict unused");
   strcpy(label[PEVT_L1P_STRM_EVICT_PART_USED], " L1p stream L1p evict partially used");
   strcpy(label[PEVT_L1P_STRM_REMOTE_INVAL_MATCH], " L1p stream L1p Remote Invalidate match");
   strcpy(label[PEVT_L1P_STRM_DONT_CACHE], " L1p stream L1p don't cache");
   strcpy(label[PEVT_L1P_STRM_STRM_DEPTH_STEAL], " L1p stream L1p Stream depth steal");
   strcpy(label[PEVT_L1P_STRM_STRM_ESTB], " L1p stream L1p streams established");
   strcpy(label[PEVT_L1P_STRM_WRT_INVAL], " L1p stream L1p Write Invalidate");
   strcpy(label[PEVT_L1P_STRM_LINE_ESTB_ALL_LIST], " L1p stream L1p line establish (all list)");
   strcpy(label[PEVT_L1P_STRM_HIT_LIST], " L1p stream L1p hit (list)");
   strcpy(label[PEVT_L1P_STRM_PF2DFC_LIST], " L1p stream L1p pf2dfc (list)");
   strcpy(label[PEVT_L1P_STRM_PART_INVAL_REFCH], " L1p stream L1p partial invalid refetched");
   strcpy(label[PEVT_L1P_LIST_SKIP_1], " L1p list skip by 1");
   strcpy(label[PEVT_L1P_LIST_SKIP_2], " L1p list skip by 2");
   strcpy(label[PEVT_L1P_LIST_SKIP_3], " L1p list skip by 3");
   strcpy(label[PEVT_L1P_LIST_SKIP_4], " L1p list skip by 4");
   strcpy(label[PEVT_L1P_LIST_SKIP_5], " L1p list skip by 5");
   strcpy(label[PEVT_L1P_LIST_SKIP_6], " L1p list skip by 6");
   strcpy(label[PEVT_L1P_LIST_SKIP_7], " L1p list skip by 7");
   strcpy(label[PEVT_L1P_LIST_ABANDON], " L1p list abandoned");
   strcpy(label[PEVT_L1P_LIST_CMP], " L1p list comparison");
   strcpy(label[PEVT_L1P_LIST_SKIP], " L1p list skip");
   strcpy(label[PEVT_L1P_LIST_MISMATCH], " L1p list mismatch ");
   strcpy(label[PEVT_L1P_LIST_STARTED], " L1p list started.");
   strcpy(label[PEVT_L1P_LIST_OVF_MEM], " L1p list overflow mem");
   strcpy(label[PEVT_L1P_LIST_CMP_OVRUN_PREFCH], " L1p list cmp overrun prefetch");
   strcpy(label[PEVT_WAKE_HIT_10], " Wakeup hit 10");
   strcpy(label[PEVT_WAKE_HIT_11], " Wakeup hit 11");
   strcpy(label[PEVT_CYCLES], " x1 cycles");
   strcpy(label[PEVT_INST_XU_MATCH], " Match XU OpCode");
   strcpy(label[PEVT_INST_XU_GRP_MASK], " XU OpCode Mask Multiple Groups");
   strcpy(label[PEVT_INST_XU_FLD], " Floating Point Load Instr Compl");
   strcpy(label[PEVT_INST_XU_FST], " Floating Point Store Instr Compl");
   strcpy(label[PEVT_INST_XU_QLD], " Quad Floating Point Load Instr Compl");
   strcpy(label[PEVT_INST_XU_QST], " Quad Floating Point Store Instr Compl");
   strcpy(label[PEVT_INST_XU_BITS], " Bit manipulation Instr Compl");
   strcpy(label[PEVT_INST_XU_BRC], " Branch Conditional Instr Compl");
   strcpy(label[PEVT_INST_XU_BRU], " Branch Unconditional Instr Compl");
   strcpy(label[PEVT_INST_XU_CINV], " Cache Invalidate Instr Compl");
   strcpy(label[PEVT_INST_XU_CSTO], " Cache Store Instr Compl");
   strcpy(label[PEVT_INST_XU_CTCH], " Cache Touch Instr Compl");
   strcpy(label[PEVT_INST_XU_IADD], " Integer Arithmetic Instr Compl");
   strcpy(label[PEVT_INST_XU_ICMP], " Compare Instr Compl");
   strcpy(label[PEVT_INST_XU_ICSW], " Coprocessor Instr Compl");
   strcpy(label[PEVT_INST_XU_IDIV], " integer divide Instr Compl");
   strcpy(label[PEVT_INST_XU_ILOG], " Logical Instr Compl");
   strcpy(label[PEVT_INST_XU_IMOV], " Quick Register move Instr Compl");
   strcpy(label[PEVT_INST_XU_IMUL], " integer multiply Instr Compl");
   strcpy(label[PEVT_INST_XU_INT], " Interrupt/system call Instr Compl");
   strcpy(label[PEVT_INST_XU_LD], " Load Instr Compl");
   strcpy(label[PEVT_INST_XU_LSCX], " Load & Store reserve conditional Instr Compl");
   strcpy(label[PEVT_INST_XU_ST], " Store Instr Compl");
   strcpy(label[PEVT_INST_XU_SYNC], " Context Sync Instr Compl");
   strcpy(label[PEVT_INST_XU_TLB], " TLB other Instr Compl");
   strcpy(label[PEVT_INST_XU_TLBI], " TLB Invalidate Instr Compl");
   strcpy(label[PEVT_INST_XU_WCH], " Watch Instr Compl");
   strcpy(label[PEVT_INST_XU_ALL], " All XU Instruction Completions");
   strcpy(label[PEVT_INST_QFPU_MATCH], " AXU Opcode Match");
   strcpy(label[PEVT_INST_QFPU_GRP_MASK], " AXU Opcode Mask Multiple Groups");
   strcpy(label[PEVT_INST_QFPU_FOTH], " Floating Point Other Instr Compl");
   strcpy(label[PEVT_INST_QFPU_FRES], " Floating Point Reciprocal Estimate Instr Compl");
   strcpy(label[PEVT_INST_QFPU_FADD], " Floating Point Add Instr Compl");
   strcpy(label[PEVT_INST_QFPU_FCVT], " Floating Point Convert Instr Compl");
   strcpy(label[PEVT_INST_QFPU_FCMP], " Floating Point Compare Instr Compl");
   strcpy(label[PEVT_INST_QFPU_FDIV], " Floating Point Divide Instr Compl");
   strcpy(label[PEVT_INST_QFPU_FMOV], " Floating Point Move Instr Compl");
   strcpy(label[PEVT_INST_QFPU_FMA], " Floating Point Multiply-Add Instr Compl");
   strcpy(label[PEVT_INST_QFPU_FMUL], " Floating Point Multiply Instr Compl");
   strcpy(label[PEVT_INST_QFPU_FRND], " Floating Point Round Instr Compl");
   strcpy(label[PEVT_INST_QFPU_FSQE], " Floating Point Square Root Estimate Instr Compl");
   strcpy(label[PEVT_INST_QFPU_FSQ], " Floating Point Square Root Instr Compl");
   strcpy(label[PEVT_INST_QFPU_QMOV], " Quad Floating Point Move Instr Compl");
   strcpy(label[PEVT_INST_QFPU_QOTH], " Quad Floating Point Other Instr Compl");
   strcpy(label[PEVT_INST_QFPU_QADD], " Quad Floating Point Add Instr Compl");
   strcpy(label[PEVT_INST_QFPU_QMUL], " Quad Floating Point Multiply Instr Compl");
   strcpy(label[PEVT_INST_QFPU_QRES], " Quad Floating Point Reciprocal Estimate Instr Compl");
   strcpy(label[PEVT_INST_QFPU_QMA], " Quad Floating Point Multiply-Add Instr Compl");
   strcpy(label[PEVT_INST_QFPU_QRND], " Quad Floating Point Round Instr Compl");
   strcpy(label[PEVT_INST_QFPU_QCVT], " Quad Floating Point Convert Instr Compl");
   strcpy(label[PEVT_INST_QFPU_QCMP], " Quad Floating Point Compare Instr Compl");
   strcpy(label[PEVT_INST_QFPU_UCODE], " Floating Point microcoded instructions");
   strcpy(label[PEVT_INST_QFPU_ALL], " All AXU Instruction Completions");
   strcpy(label[PEVT_INST_QFPU_FPGRP1], " FP Operations Group 1 ");
   strcpy(label[PEVT_INST_QFPU_FPGRP2], " FP Operations Group 2 ");
   strcpy(label[PEVT_INST_ALL], " All Instruction Completions");
   strcpy(label[PEVT_L2_HITS], " L2 Hits");
   strcpy(label[PEVT_L2_MISSES], " L2 Misses");
   strcpy(label[PEVT_L2_PREFETCH], " L2 prefetch ahead of L1P prefetch");
   strcpy(label[PEVT_L2_FETCH_LINE], " L2 fetch 128 byte line from main memory");
   strcpy(label[PEVT_L2_STORE_LINE], " L2 store 128 byte line to main memory");
   strcpy(label[PEVT_L2_STORE_PARTIAL_LINE], " L2 store partial line to main memory");
   strcpy(label[PEVT_L2_REQ_REJECT], " L2 Req Reject");
   strcpy(label[PEVT_L2_REQ_RETIRE], " L2 Req Retire");
   strcpy(label[PEVT_L2_REQ_MISS_AND_EVICT], " L2 Req Miss and Evict");
   strcpy(label[PEVT_L2_REQ_MISS_AND_EVICT_SPEC], " L2 Req Miss and Evict Spec");
   strcpy(label[PEVT_L2_MISS_AND_EVICT], " L2 Miss and Evict");
   strcpy(label[PEVT_L2_MISS_AND_EVICT_SPEC], " L2 Miss and Evict Spec");
   strcpy(label[PEVT_L2_REQ_SPEC_ADDR_CLEANUP], " L2 Req Spec Addr Cleanup");
   strcpy(label[PEVT_L2_SPEC_ADDR_CLEANUP], " L2 Spec Addr Cleanup");
   strcpy(label[PEVT_L2_SPEC_SET_CLEANUP], " L2 Spec Set Cleanup");
   strcpy(label[PEVT_L2_SPEC_RETRY], " L2 Spec Retry");
   strcpy(label[PEVT_L2_HITS_SLICE], " L2 Cache Slice Hits ");
   strcpy(label[PEVT_L2_MISSES_SLICE], " L2 Cache Slice Misses");
   strcpy(label[PEVT_L2_PREFETCH_SLICE], " L2 Cache Slice prefetch ahead of L1P prefetch");
   strcpy(label[PEVT_L2_FETCH_LINE_SLICE], " L2 Cache Slice fetch 128 byte line from main memory");
   strcpy(label[PEVT_L2_STORE_LINE_SLICE], " L2 Cache Slice store 128 byte line to main memory");
   strcpy(label[PEVT_L2_STORE_PARTIAL_LINE_SLICE], " L2 Cache Slice store partial line to main memory");
   strcpy(label[PEVT_L2_REQ_REJECT_SLICE], " L2 Cache Slice Req Reject");
   strcpy(label[PEVT_L2_REQ_RETIRE_SLICE], " L2 Cache Slice Req Retire");
   strcpy(label[PEVT_L2_REQ_MISS_AND_EVICT_SLICE], " L2 Cache Slice Req Miss and Evict");
   strcpy(label[PEVT_L2_REQ_MISS_AND_EVICT_SPEC_SLICE], " L2 Cache Slice Req Miss and Evict Spec");
   strcpy(label[PEVT_L2_MISS_AND_EVICT_SLICE], " L2 Cache Slice Miss and Evict");
   strcpy(label[PEVT_L2_MISS_AND_EVICT_SPEC_SLICE], " L2 Cache Slice Miss and Evict Spec");
   strcpy(label[PEVT_L2_REQ_SPEC_ADDR_CLEANUP_SLICE], " L2 Cache Slice Req Spec Addr Cleanup");
   strcpy(label[PEVT_L2_SPEC_ADDR_CLEANUP_SLICE], " L2 Cache Slice Spec Addr Cleanup");
   strcpy(label[PEVT_L2_SPEC_SET_CLEANUP_SLICE], " L2 Cache Slice Spec Set Cleanup");
   strcpy(label[PEVT_L2_SPEC_RETRY_SLICE], " L2 Cache Slice Spec Retry");
   strcpy(label[PEVT_MU_PKT_INJ], " Mu packet injected");
   strcpy(label[PEVT_MU_MSG_INJ], " Mu message injected");
   strcpy(label[PEVT_MU_FIFO_PKT_RCV], " Mu FIFO packet received");
   strcpy(label[PEVT_MU_RGET_PKT_RCV], " Mu RGET packet received");
   strcpy(label[PEVT_MU_PUT_PKT_RCV], " Mu PUT packet received");
   strcpy(label[PEVT_MU_PORT0_16B_WRT], " Mu port 0 16B write");
   strcpy(label[PEVT_MU_PORT0_32B_RD], " Mu port 0 32B read");
   strcpy(label[PEVT_MU_PORT0_64B_RD], " Mu port 0 64B read");
   strcpy(label[PEVT_MU_PORT0_128B_RD], " Mu port 0 128B read");
   strcpy(label[PEVT_MU_PORT1_16B_WRT], " Mu port 1 16B write");
   strcpy(label[PEVT_MU_PORT1_32B_RD], " Mu port 1 32B read");
   strcpy(label[PEVT_MU_PORT1_64B_RD], " Mu port 1 64B read");
   strcpy(label[PEVT_MU_PORT1_128B_RD], " Mu port 1 128B read");
   strcpy(label[PEVT_MU_PORT2_16B_WRT], " Mu port 2 16B write");
   strcpy(label[PEVT_MU_PORT2_32B_RD], " Mu port 2 32B read");
   strcpy(label[PEVT_MU_PORT2_64B_RD], " Mu port 2 64B read");
   strcpy(label[PEVT_MU_PORT2_128B_RD], " Mu port 2 128B read");
   strcpy(label[PEVT_MU_SLV_PORT_RD], " Mu Slave port read");
   strcpy(label[PEVT_MU_SLV_PORT_WRT], " Mu Slave port write");
   strcpy(label[PEVT_MU_PORT0_PEND_WRT], " Mu port 0 pending write requests");
   strcpy(label[PEVT_MU_PORT0_PEND_RD], " Mu port 0 pending read requests");
   strcpy(label[PEVT_MU_PORT1_PEND_WRT], " Mu port 1 pending write requests");
   strcpy(label[PEVT_MU_PORT1_PEND_RD], " Mu port 1 pending read requests");
   strcpy(label[PEVT_MU_PORT2_PEND_WRT], " Mu port 2 pending write requests");
   strcpy(label[PEVT_MU_PORT2_PEND_RD], " Mu port 2 pending read requests");
   strcpy(label[PEVT_PCIE_INB_RD_BYTES], " Pcie Inbound Read Bytes");
   strcpy(label[PEVT_PCIE_INB_RDS], " Pcie Inbound Read Requests");
   strcpy(label[PEVT_PCIE_INB_RD_CMPLT], " Pcie Inbound Read Completions");
   strcpy(label[PEVT_PCIE_OUTB_WRT_BYTES], " Pcie outbound memory write bytes");
   strcpy(label[PEVT_PCIE_OUTB_CFG_X], " Pcie Outbound CFG transactions");
   strcpy(label[PEVT_PCIE_OUTB_IO_X], " Pcie Outbound IO transactions");
   strcpy(label[PEVT_PCIE_RX_DLLP], " Pcie RX DLLP Count");
   strcpy(label[PEVT_PCIE_RX_TLP], " Pcie RX TLP Count");
   strcpy(label[PEVT_PCIE_RX_TLP_SIZE], " Pcie RX TLP Size in DWORDS");
   strcpy(label[PEVT_PCIE_TX_DLLP], " Pcie TX DLLP Count");
   strcpy(label[PEVT_PCIE_TX_TLP], " Pcie TX TLP Count");
   strcpy(label[PEVT_PCIE_TX_TLP_SIZE], " Pcie TX TLP Size in DWORDS");
   strcpy(label[PEVT_DB_PCIE_INB_WRT_BYTES], " Devbus PCIe inbound write bytes written");
   strcpy(label[PEVT_DB_PCIE_OUTB_RD_BYTES], " Devbus PCIe outbound read bytes requested");
   strcpy(label[PEVT_DB_PCIE_OUTB_RDS], " Devbus PCIe outbound read requests");
   strcpy(label[PEVT_DB_PCIE_OUTB_RD_CMPLT], " Devbus PCIe outbound read completions");
   strcpy(label[PEVT_DB_BOOT_EDRAM_WRT_BYTES], " Devbus Boot eDRAM bytes written");
   strcpy(label[PEVT_DB_BOOT_EDRAM_RD_BYTES], " Devbus Boot eDRAM bytes read");
   strcpy(label[PEVT_DB_MSG_SIG_INTS], " Devbus Message-Signaled Interrupts (MSIs)");
   strcpy(label[PEVT_NW_USER_PP_SENT], " User pt-pt 32B packet chunks sent ");
   strcpy(label[PEVT_NW_USER_DYN_PP_SENT], " User dynamic pt-pt 32B packet chunks sent ");
   strcpy(label[PEVT_NW_USER_ESC_PP_SENT], " User escape pt-pt 32B packet chunks sent ");
   strcpy(label[PEVT_NW_USER_PRI_PP_SENT], " User priority pt-pt 32B packet chunks sent ");
   strcpy(label[PEVT_NW_SYS_PP_SENT], " System pt-pt 32B packet chunks sent ");
   strcpy(label[PEVT_NW_USER_WORLD_COL_SENT], " User world collective 32B packet chunks sent ");
   strcpy(label[PEVT_NW_USER_SUBC_COL_SENT], " User sub-comm collective 32B packet chunks sent ");
   strcpy(label[PEVT_NW_SYS_COL_SENT], " System collective 32B packet chunks sent ");
   strcpy(label[PEVT_NW_COMMWORLD_COL_SENT], " Comm-world collective 32B packet chunks sent ");
   strcpy(label[PEVT_NW_USER_PP_RECV], " User pt-pt packets received ");
   strcpy(label[PEVT_NW_USER_DYN_PP_RECV], " User dynamic pt-pt packets received ");
   strcpy(label[PEVT_NW_USER_ESC_PP_RECV], " User escape pt-pt packets received ");
   strcpy(label[PEVT_NW_USER_PRI_PP_RECV], " User priority pt-pt packets received ");
   strcpy(label[PEVT_NW_SYS_PP_RECV], " System pt-pt packets received ");
   strcpy(label[PEVT_NW_USER_WORLD_COL_RECV], " User world collective packets received ");
   strcpy(label[PEVT_NW_USER_SUBC_COL_RECV], " User sub-comm collective packets received ");
   strcpy(label[PEVT_NW_SYS_COL_RECV], " System collective packets received ");
   strcpy(label[PEVT_NW_COMMWORLD_COL_RECV], " Comm-world collective packets received ");
   strcpy(label[PEVT_NW_USER_PP_RECV_FIFO], " User pt-pt packets in receive fifo ");
   strcpy(label[PEVT_NW_USER_DYN_PP_RECV_FIFO], " User dynamic pt-pt packets in receive fifo ");
   strcpy(label[PEVT_NW_USER_ESC_PP_RECV_FIFO], " User escape pt-pt packets in receive fifo ");
   strcpy(label[PEVT_NW_USER_PRI_PP_RECV_FIFO], " User priority pt-pt packets in receive fifo ");
   strcpy(label[PEVT_NW_SYS_PP_RECV_FIFO], " System pt-pt packets in receive fifo ");
   strcpy(label[PEVT_NW_USER_WORLD_COL_RECV_FIFO], " User world collective packets in receive fifo ");
   strcpy(label[PEVT_NW_USER_SUBC_COL_RECV_FIFO], " User subcomm collective packets in receive fifo ");
   strcpy(label[PEVT_NW_SYS_COL_RECV_FIFO], " System collective packets in receive fifo ");
   strcpy(label[PEVT_NW_COMMWORLD_COL_RECV_FIFO], " Comm-world collective packets in receive fifo ");
   strcpy(label[PEVT_NW_SENT], " Set attribute to filter 32B packet chunks sent ");
   strcpy(label[PEVT_NW_RECV], " Set attribute to filter packets received");
   strcpy(label[PEVT_NW_RECV_FIFO], " Set attribute to filter packets in receive fifo");
   strcpy(label[PEVT_NW_CYCLES], " Network cycles since reset");
/*
   strcpy(label[PEVT_CNK_NODE_TBD], " CNK Node events are not yet defined");
   strcpy(label[PEVT_CNK_PROC_TBD], " CNK Process events are not yet defined");
*/
   strcpy(label[PEVT_CNKHWT_SYSCALL], " System Calls");
   strcpy(label[PEVT_CNKHWT_STANDARD], " External Input Interrupts");
   strcpy(label[PEVT_CNKHWT_CRITICAL], " Critical Input Interrupts");
   strcpy(label[PEVT_CNKHWT_DECREMENTER], " Decrementer Interrupts");
   strcpy(label[PEVT_CNKHWT_FIT], " Fixed Interval Timer Interrupts");
   strcpy(label[PEVT_CNKHWT_WATCHDOG], " Watchdog Timer Interrupts");
   strcpy(label[PEVT_CNKHWT_UDEC], " User Decrementer Interrupts");
   strcpy(label[PEVT_CNKHWT_PERFMON], " Performance Monitor interrupts");
   strcpy(label[PEVT_CNKHWT_UNKDEBUG], " Unknown/Invalid Interrupts");
   strcpy(label[PEVT_CNKHWT_DEBUG], " Debug Interrupts");
   strcpy(label[PEVT_CNKHWT_DSI], " Data Storage Interrupts");
   strcpy(label[PEVT_CNKHWT_ISI], " Instruction Storage Interrupts");
   strcpy(label[PEVT_CNKHWT_ALIGNMENT], " Alignment Interrupts");
   strcpy(label[PEVT_CNKHWT_PROGRAM], " Program Interrupts");
   strcpy(label[PEVT_CNKHWT_FPU], " FPU Unavailable Interrupts");
   strcpy(label[PEVT_CNKHWT_APU], " APU Unavailable Interrupts");
   strcpy(label[PEVT_CNKHWT_DTLB], " Data TLB Interrupts");
   strcpy(label[PEVT_CNKHWT_ITLB], " Instruction TLB Interrupts");
   strcpy(label[PEVT_CNKHWT_VECTOR], " Vector Unavailable Interrupts");
   strcpy(label[PEVT_CNKHWT_UNDEF], " Undefined Interrupts");
   strcpy(label[PEVT_CNKHWT_PDBI], " Processor Doorbell Interrupts");
   strcpy(label[PEVT_CNKHWT_PDBCI], " Processor Doorbell Critical Ints");
   strcpy(label[PEVT_CNKHWT_GDBI], " Guest Doorbell Interrupts");
   strcpy(label[PEVT_CNKHWT_GDBCI], " Guest Doorbell Crit or MChk Ints");
   strcpy(label[PEVT_CNKHWT_EHVSC], " Embedded Hypervisor System Calls");
   strcpy(label[PEVT_CNKHWT_EHVPRIV], " Embedded Hypervisor Privileged");
   strcpy(label[PEVT_CNKHWT_LRATE], " LRAT exception");
}
/*=================================================================*/
/* Initialize the counters                                         */
/*=================================================================*/
inline uint64_t getTime()
{
   return GetTimeBase();
}
double getTick()
{
   double seconds_per_cycle = 0.625e-9; /* 1600 MHz default */
   return seconds_per_cycle; 
}
void profileInitBGQ(void)
{
#ifdef HPM
   nCounters_ = 2;
#else
   #pragma omp parallel
   {
      int tid = omp_get_thread_num() ;
      Bgpm_Init(BGPM_MODE_SWDISTRIB);
      counterHandle[tid] = Bgpm_CreateEventSet();
      Bgpm_AddEventList(counterHandle[tid], counterSet, sizeof(counterSet)/sizeof(unsigned) );
      Bgpm_Apply(counterHandle[tid]);
      
      Bgpm_Start(counterHandle[tid]);
      
      set_labels();
   }
#endif
}
int getNCores() { return 16;} 
void  (*readCounter)(unsigned int, int,  uint64_t*)=(void (*)(unsigned, int, uint64_t*))Bgpm_ReadEvent;
void (*machineSpecficInit)() = profileInitBGQ; 
#define MACHINE BGQ
#endif

