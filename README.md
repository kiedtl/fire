![](https://github.com/lptstr/lptstr-images/blob/master/proj/fire/scrot.jpg?raw=true)

# fire

> The ancient DOOM fire animation in the terminal!

## what?
`fire` is a remake of the PSX DOOM fire animation in the terminal,
as seen in the [ly](https://github.com/cylgom/ly) display manager.
It's described nicely by Fabien Sanglard on his
[blog](https://fabiensanglard.net/doom_fire_psx/index.html).

## where?
### supported platforms
- Linux (musl/glibc) (*tested and supported*)
- Windows (*should work, but not tested*)
- (Dragonfly|Net|Free|Open)BSD: (*not tested, might work*)

### building from source
You will need:
- `git` or `wget`
- a c99 compiler (gcc or clang)
- GNU Make (unknown if other `make`s will work)

Retrieve the source:
```
$ # via git:
$ git --recurse clone https://github.com/lptstr/fire
$
$ # via wget:
$ wget https://github.com/lptstr/fire/archive/master.tar.gz
$ tar xvf master.tar.gz
```

Build:
```
$ make
```

and install:
```
# make install
```

Uninstall, if you wish:
```
# make uninstall
```

## how?
simply run `./fire` (or `fire`, if you installed) and enjoy.
```
$ fire
```

### why?
I'm bored

## credits
- Thanks to @cylgom, for inspiring me to make this project.
- More thanks to @cylgom, from whose repositories I sto^Hborrowed a lot
of stuff :)

## license
This project is licensed under the MIT license. View the LICENSE.md file
for more information.
