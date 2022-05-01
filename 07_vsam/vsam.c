#include "vsam.h"
#include "../08_fss/svc.h"

typedef struct List
{
    Uint8 mode;
    Uint8 acb[3];
} __attribute__((packed)) List;

Uint32 to24(Uint32 from)
{
    C32to24 tmp;
    tmp.u32 = from;
    tmp.u24[0] = 0;
    return tmp.u32;
}

void v_el(ExitList *el,
          void (*p_eodad)(void),
          void (*p_synad)(void),
          void (*p_lerad)(void))
{
    el->id = EXLSTID;
    el->subtype = 0; /* EXLSVSAM? */
    el->len = EXLLEN;
    el->flags = 0;
    el->eodad = (EXIT_SPECIFIED | EXIT_ACTIVE);
    el->p_eodad = p_eodad;
    el->synad = (EXIT_SPECIFIED | EXIT_ACTIVE);
    el->p_synad = p_synad;
    el->lerad = (EXIT_SPECIFIED | EXIT_ACTIVE);
    el->p_lerad = p_lerad;
}

void v_acb(AccessMethodControlBlock *acb,
           ExitList *p_exitls)
{
    acb->id = ACBIDVAL;
    acb->subtype = ACBSVSAM;
    acb->len = VSAMLEN;
    acb->p_amblst = 0;
    acb->p_interf = 0;
    acb->macrf1 = (ACBKEY | ACBIN | ACBSEQ);
    acb->macrf2 = 0;
    acb->num_conc = 0;
    acb->num_str = 1;
    acb->num_dat = 0;
    acb->num_index = 0;
    acb->macrf3 = 0;
    acb->macrf4 = 0;
    acb->jes_pool = 0;
    acb->recfm = 80;
    acb->cct = 0;
    acb->dsorg = ACBDORGA;
    acb->p_filler = 0;
    acb->p_passwd = 0;
    acb->p_exitls = p_exitls;
    strncpy(acb->ddname, "VSIN    ", DDNAME_LEN);
    acb->oflgs = ACBEXFG;
    acb->erflgs = 0;
    acb->inflgs1 = 0;
    acb->inflgs2 = 0;
    acb->p_ojfcb = 0;
    acb->bufspace = 0;
    acb->blksize = 0;
    acb->recsize = 0;
    acb->p_usrwka = 0;
    acb->p_cblkm = 0;
    acb->p_appnam = 0;
}

void v_rpl(RequestParameterList *rpl,
           AccessMethodControlBlock *acb,
           void *inrec,
           void *userkey)
{
    rpl->id = RPLIDD;
    rpl->subtype = RPLSVSAM;
    rpl->reqtype = 0;
    rpl->len = RPLLEN;
    rpl->p_plhold = 0;
    rpl->ecb = 0;
    rpl->status = 0;
    rpl->retcode = 0;
    rpl->condition = 0;
    rpl->errcode = 0;
    rpl->keylen = 6;
    rpl->transid = 0;
    rpl->p_chrctr = 0;
    rpl->p_acb = acb;
    rpl->p_tcb = 0;
    rpl->p_recare = inrec;
    rpl->p_arg = userkey;
    /* RPLSAF PTR(16), SOURCE ADDRESS FIELD */
    /* RPLDAF PTR(16), DESTINATION ADDRESS */
    rpl->optcd[0] = RPLSEQ; /* RPLOPT1 */
    rpl->optcd[1] = RPLKEY; /* RPLOPT2 */
    rpl->optcd[2] = 0;      /* RPLOPT3 */
    rpl->optcd[3] = 0;      /* RPLOPT4 */
    rpl->p_nxtrpl = 0;
    rpl->logrecl = 0;
    rpl->buflen = 118;
    rpl->byte5 = 0;
    rpl->byte6 = 0;
    rpl->byte7 = 0;
    rpl->byte8 = 0;
    rpl->rba[0] = 0;
    rpl->rba[1] = 0;
    rpl->rba[2] = 0;
    rpl->rba[3] = 0;
    rpl->rba[4] = 0;
    rpl->rba[5] = 0;
    rpl->rba[6] = 0;
    rpl->rba[7] = 0;
    rpl->exitdef = RPLNEXIT;
    rpl->actind = 0;
    rpl->mxerrlen = 0;
    rpl->p_msgare = 0;
}

int v_open(AccessMethodControlBlock *acb, int mode)
{
    C32to24 tmp;
    List lista;
    REGS regs;

    lista.mode = mode;
    tmp.u32 = (Uint32)acb;
    lista.acb[0] = tmp.u24[1];
    lista.acb[1] = tmp.u24[2];
    lista.acb[2] = tmp.u24[3];

    regs.R0 = 0;
    regs.R1 = (Uint32)&lista;
    regs.R15 = 0;
    EXSVC(19, &regs);
    return regs.R15;
}

int v_close(AccessMethodControlBlock *acb, int mode)
{
    C32to24 tmp;
    List lista;
    REGS regs;

    tmp.u32 = (Uint32)acb;
    lista.acb[0] = tmp.u24[1];
    lista.acb[1] = tmp.u24[2];
    lista.acb[2] = tmp.u24[3];
    lista.mode = mode;

    regs.R0 = 0;
    regs.R1 = (Uint32)&lista;
    regs.R15 = 0;
    EXSVC(20, &regs);
    return regs.R15;
}

int v_get(RequestParameterList *rpl)
{
    C32to24 tmp;
    REGS regs;

    tmp.u32 = rpl->p_acb->p_interf;
    tmp.u24[0] = 0;
    regs.R1 = (Uint32)rpl;
    regs.R0 = 0;
    regs.R15 = (Uint32)tmp.u32;
    EXEC(&regs);

    return regs.R15;
}
