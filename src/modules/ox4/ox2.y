%hna


ox :
   oxignore
   oxbody
   oxignore
   END
   {
      new_dir($$);
   }
 ;

oxignore :
   %empty
 | blank_and_indented_ignored
 ;

blank_and_indented_ignored
 : BLANKLINE

 | INDENTED_IGNORE

 | blank_and_indented_ignored
   BLANKLINE

 | blank_and_indented_ignored
   INDENTED_IGNORE
 ;

oxbody:
   oxaddr
 | oxbody
   oxignore
   oxaddr
 ;

oxaddr
 : outline_body
 ;

outline
 : outline_head

 | outline_head
   OUTLINE_BODY_START
   outline_body
   OUTLINE_BODY_END

   {
      new_dir($$);
      new_dirent($$);
   }
 ;

outline_head
 : text EOL
 ;

outline_body
 : outline

 | outline_body
   STRIP_INDENT outline
 ;




text :
   NONBLANK NONEOL*
 ;


INDENT :
   %( ^[ \t]+ )%
 ;

OUTLINE_BODY_START :
   INDENT
   {
      if( len(INDENT) > cur_indent )
         cur_indent = len(INDENT);
      else
         %fail
   }
 ;

OUTLINE_BODY_END :
   INDENT
   {
      if( len(INDENT) < cur_indent )
         cur_indent = len(INDENT);
      else
         %fail
   }
 |
   BLANKLINE
 ;

STRIP_INDENT :
   INDENT
   {
      if(len(INDENT) == cur_indent)
   }
 ;

