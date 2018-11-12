



fudge language - fluent piping
------------------------------
(rev 4/24/2018)


fudge language

  <name>.<mod_id>
  <name>.<mod_id>.<mod_id>
  <name>.<mod_id>/<name>  //child
  <name>.<mod_id>:<name>  //prop
s
ie.

  myfile.ox
  myfile.ox.json
  myfile.ox/some_element
  myfile.ox:ctime
  myfile.ox.div.html
  myfile.ox.div/some_element.html


the actual way fudge works is a pipeline of production instructions.

eg.
(where "pi" is "production instruction"):

  <pi><pi><pi><pi><pi><pi>...


(reminder, prod instr types:
source, map, find, bind, transform)


modules implement functions for the production types.


deciding which function to trigger:

the first function in a lookup should be a map function of the parent "directory".

    map <par mod> <par>

the next function is a 'find'

    find-child <par> <str>
    - or -
    find-prop <par> <str>

the following functions can be 'map' or 'transform' until the next path segment.

deciding to map or transform.

    a map can be transformed into a stream.

    a map can be over-mapped

    a stream can be mapped


  'file::///dir.ox' should generate a stream from a dir map.

  'file::///file.ox' should generate a map from a stream.


   maybe the rule of thumb:
      
      1) try mapper
      2) try transformer
 


fudge implementation
--------------------

fudge-segment() takes a dcel and a string, generates a production instruction, executes the instruction, returns a dcel.

fudge-loop takes a dcel and a string, parses the string into segments, passes each segment to fudge-segment, returns a dcel.

fudge_parse() takes a string, cosmos_db and a cosmos_ino (parent directory) and parses the string into a production instruction chain.



fudge with snafu
----------------

the snafu file system takes a url, a mountpoint, a lookup module; generates a source production instruction, executes it, uses the resulting dcel as file system root, stores root dcel in aframe database, mounts the file system to mountpoint.

takes lookup request as ino and lookup string; retrieves dcel from inode, passes dcel and string to lookup module, stores resultant dcel in inode database.

(fudge conforms to lookup module interface and is loaded by snafu)

implements file ops (stat, open, opendir, etc.) as functions on a dcel.  each takes an ino, retrieves dcel from inode database, performs op on dcel.

(the ops interface is declared by hiena_svc and defined by dcel_svc.)




module connector maps for auto fudge
------------------------------------

fudge tries to complete a path of transformations between incompatable formats.

this table describes possible transformations:
 
    ox  | divine
    ox  | dir
    dir | ox
    dir | yaml
    txt | ox
    txt | html
    txt | yaml
    txt | c
    yaml | dir
    divine | html


a request:

    dir.html


would complete by:

    dir.ox.divine.html




fudge grammar
-------------
(10/12/2017)


  <identifier> : <find child>

  '/' <identifier> : <find child>

  '.' <identifier> : <grind scan>
                   | <grind exec>

  ':' <identifier> : <find prop>

  '.==' <identifier> : <bind equiv>

  '.->' <identifier> : <bind flow R>

  '.<-' <identifier> : <bind flow L>

  ':==' <identifier> : <bind prop equiv>

  ':->' <identifier> : <bind prop flow R>

  ':<-' <identifier> : <bind prop flow L>

  '.=' <identifier> : <bind assign>

  '.+>' <identifier> : <bind copy R>

  '.<+' <identifier> : <bind copy L>

  '.==' <url> : <source equiv>




boneyard
--------

lazy evaluation lookup
----------------------
9/24/2018
10/07/2018 unnecessary and inefficient - omit


fudge compiles a fudge url into a dcel chain.  the validity of the chain is unknown.

the contents of the leaf of the chain are evaluated at file system access, such as a stat() call, at which point, the chain is evaluated.

this lazy evaluation is the same mechanism as the normal sync'ing of the distributed file system.

the evaluation mechanism is implemented by production instructions in the dcel chain.


