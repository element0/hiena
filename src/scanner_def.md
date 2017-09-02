


scanner definition language
---------------------------

%%    section start

production_name ':'
   production_body
  ';'


flex_name ':'
"%(" flex_regex ")%"

-->

   flex_name  flex_regex
   %%
   {flex_name}  return flex_name;


production_name ':'
   flex_name
   '{' if_clause '}'

production_name_n ':'
   same_flex_name
   '{' if_clause '}'

-->

   {flex_name}   {
        if_clause
           return production_name;
        if_clause_n
           return production_name_n;
        ...
      }