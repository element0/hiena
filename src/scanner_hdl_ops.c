
Hspops *hsp_ops_create() {
    Hspops *ops = malloc(sizeof(Hspops));
    memset(ops,0,sizeof(Hspops));

    return ops;
}

Hspops *hsp_ops_init() {
    Hspops *ops = hsp_ops_create();

/*
    ops->make_ob    = ppak_make_ob;
    ops->set_bounds = ppak_set_bounds;
    ops->set_buf    = ppak_set_map_buf;

    ops->add_prop   = ppak_add_prop_hsp;
    ops->add_child  = ppak_add_child_hsp;
*/


    /* RETIRING... */
/*
    ops->putob  = hiena_map_putob;
    ops->gettok = NULL;
    ops->fopen  = dcel_svc->open;
*/
    /* ...RETIRING */

    /* CONTEXT FUNCTIONS */
    ops->getenv = hsp_getenv;


    /* REQUEST BUILDER FUNCTIONS */
    ops->set_rqtarg = set_rqtarg;
    ops->set_rqdest = set_rqdest;
    ops->set_rqsrc  = set_rqsrc;
    ops->set_rqmap  = set_rqmap;
    ops->set_rqop   = set_rqop;

    return ops;
}

int hsp_ops_cleanup(Hspops *ho)
{
    free(ho);
    return 0;
}

