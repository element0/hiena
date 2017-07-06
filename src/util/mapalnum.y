




mapalnum:
     alnum EOF
    { end }
  ;


alnum:
     alstr
    { new $0
      add $0 $1 }
  |  numstr
    { new $0
      add $0 $1 }
  |  alnum alstr
    { add $0 $1 }
  |  alnum numstr
    { add $0 $1 }
  ;

alstr:
  |  ALPHA
    { new $1 }
  |  alstr ALPHA
    { grow $1 $2 }
  ;

numstr
  |  NUM
    { new $1 }
  |  numstr NUM
    { grow $1 $2 }
  ;