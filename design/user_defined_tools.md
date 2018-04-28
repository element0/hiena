

user defined tools
---

examples:
  transformers:
  - byte encoder
  - image scaler
  - encryption
  - compressor
  - checksum
  scanners:
  - xml
  - json
  translators:
  - json to xml
  - less to css
  builders:
  - divine to html
  - html,css to pdf
  - multiple imgs to mov
  - multiple pdf to single pdf


byte tools, invoked in filepath
--------------------------------

below, the keyword alias is a derivative of the bash keyword except the line is parsed for {substitutions} kind of like a macro function in c.

  pathto/img.s50.png

  alias s{num} scale -percent {num}

the above tool wouldn't require any mapping to dcels.  it uses stdin, stdout and argv.

  pathto/pdf[1-10].combine.pdf

  alias {file+}.combine pdf-combine {file+} -stdout

the above doesn't require mapping.  but it requires the lookup language to place filepaths to the children of the cell `pdf[1-10]` on the argv of pdf-combine.

  pathto/a.div.html

  alias {file}.div map {file} ox; map {file} div
  alias {x}.html if {x}==div div-to-html {file}

the above takes a filepath {file} to 'a' and maps it twice.  the sequence of the mapping is important.  technically the div scanner should initiate prescanning with the 
ox scanner - since divinity uses an ox structure.

the map is managed in the cosmosd database.  so each reference to {file} can be used to query the map via libcosmos or cosmos tools.  {file} will not be a user exposed filepath.  it will function to serve the file and can also be used as an is to reference the dcel.

  pathto/img.svg.s5x7.png

  alias {x}.svg format {x} -as svg
  alias s{h}x{w} scale -inch -h5 -w7
  alias {x}.png format {x} -as png


alias keyword (fudge lang)
--------------------------

  alias {x+}.word{y} substitution args {x+} -args {y}

the brackets capture substrings from the lookup expression and use them in the substitution

a '.' is allowed to indicate the capture of the previous lookup segment before the dot.

a '+' indicates an expansion of the members of a capture into a list of separate items in the substitution.

aliases are kept in the environment of an access frame.  they may be defined in a file (on a per directory basis) akin to bashrc meets htaccess.

their use is lookup language dependent.  in this case fudge will look for them in ".cosm/config/fudgerc".


running the tools from snafufs
------------------------------

when the cosmosd runs an external tool from within the snafu mount, it uses standard system calls to run it from the command line.

in the case of "fudge" lookup running a command, 

  pathto/info.div.html

the lookup might load

  pathto/.cosm/types/div.so
  pathto/.cosm/types/html.so

which makes 2 more file requests on the same snafufs mount.  needs multithreading.

can work bc type object paths are not the same as the branch being looked up.

the sections of a file name represent individual dcels which can be accessed as files.

  pathto/info
  pathto/info.div
  pathto/info.div.html

the output of 'div' could be passed to the input of 'html'.  the following uses shell scripts and transforms info into info.div.html 

  ./pathto/.cosm/types/div.sh \
      pathto/info \
  | ./pathto/.cosm/types/html.sh \
      pathto/info.div

the cosmosd captures the stdout.  the scripts might use the cosmos cli tools to map 'info'.  cosmosd will be invoked by such cli tools.

