

prod_exec
---------

  struct access_frame *
  prod_exec( pcmd_t, cosmos_id_t, char * );

  struct access_frame *a;
  a = prod_exec(PCMD_FND,par,name);

  a = prod_exec(PCMD_MAP,a,"ox");

  a = prod_exec(PCMD_XFM,a,"dir");

  a = prod_exec(PCMD_MRG,a,NULL);

  return a;


some cmds dont want a merge...


same prefix filenames...


   pacman.ox
   pacman.txt
   pacman.png
   pacman.svg

if you

   a = prod_exec(PCMD_FNDPFX,par,"pacman");

a->dcel->child_list will contain all.

then if you

  a = prod_exec(PCMD_XFM,a,"ox");

it will try to interpret each in the list. 


  