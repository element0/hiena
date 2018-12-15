cosmos_dlopen design
--------------------


return 


procedure
---------

START

locate library file

ascertain requirements profile

match requirements profile to a vm capabilities profile
(cache result)

open vm handle
   load/open vm
   rcv function pointer block



ascertain requirements profile
------------------------------

case Package Manager installed
case User installed
case local directory installed
case local script
  embed profile in header comments


available metadata

   utils
      file
      ldd
      pax-utils.deb

arch-type:
kernel-type:
lib-depend:
pkg-depend:
interp-depend:
distro-type:


