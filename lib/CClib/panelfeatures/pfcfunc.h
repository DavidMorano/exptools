
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

/* PFCLOWIO.C */
extern void pfsetup_term();
extern void pfreset_term();
extern void pfsetup_pipe(int in,int out);
extern int pfkeychar();
extern int pfhostchar();

/* PFCKEYS.C */
extern void keyconfig();
extern void keyhelp(char nodetype);
extern void keycmd(struct node*, int);

/* PFCDRAW.C */
extern void pfscr_init_com();
extern void pfscr_logo_draw();
extern void pfscr_node_draw();

/* PFCMSG.C */
extern void warn(char *msg);
extern void inform(char *msg);

/* PFCSHORTS.C */
extern void logo(char *);
extern int xtoi(char);

/* PFCHCMD.C */
extern void sendhost(char *);
extern void hostcmd(struct node**, char);
extern void clearnode(struct node*);

/* PFCMAIN.C */
void pfc_exit( struct node *);
