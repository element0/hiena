
dcel producer: bind-cascade
---------------------------


inputs
------
dcels[2]


output
------
dcel3


procedure
---------
copy all of dcel[0] to dcel3 (children, properties, etc)

copy-replace all of dcel[1] to dcel3



side effects
------------

write behavior:

when users write to dcel3, they actually intend to write to dcel2.  dcel2 is the local data of the casacade.

read behavior:

users intend to read from dcel3.



bind-cascade module
-------------------
bind producer
write function
read function
