
cosmos wire format
------------------

cosmos_msg := head DATA

head := 'cosmomsg' INTSIZE length

length := INT32 | INT64 

