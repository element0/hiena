



fudge language - fluent piping
------------------------------
(10/12/2017)


fudge language's use of this

  <dcel>.<scanner_id>
  <dcel>.<scanner_id>.<formatter_id>
  <dcel>.<scanner_id>/<child_name>
  <dcel>.<scanner_id>:<prop_name>

ie.

  myfile.ox
  myfile.ox.json
  myfile.ox/some_element
  myfile.ox:outline
  myfile.ox.div.html
  myfile.ox.div/some_element.html

the actual way fudge works is a pipeline of production instructions.

eg.
(where "pi" is "production instruction"):

  <pi><pi><pi><pi><pi><pi>...


(reminder, four prod instr types: source, find, bind, grind)



fudge implementation
--------------------

fudge-segment takes a dcel and a string, generates a production instruction, executes the instruction, returns a dcel.

fudge-loop takes a dcel and a string, parses the string into segments, passes each segment to fudge-segment, returns a dcel.



fudge with snafu
----------------

the snafu file system takes a url, a mountpoint, a lookup module; generates a source production instruction, executes it, uses the resulting dcel as file system root, stores root dcel in inode database, mounts the file system to mountpoint.

takes lookup request as inode and lookup string; retrieves dcel from inode, passes dcel and string to lookup module, stores resultant dcel in inode database.

(fudge conforms to lookup module interface and is loaded by snafu)

implements file ops (stat, open, opendir, etc.) as functions on a dcel.  each takes an ino, retrieves dcel from inode database, performs op on dcel.

(the ops interface is declared by hiena_svc and defined by dcel_svc.)


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



