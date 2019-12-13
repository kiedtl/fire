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
- `git`
- a c99 compiler (gcc or clang)
- GNU Make (unknown if other `make`s will work)

Clone the source via `git`:
```
$ git --recurse clone https://github.com/lptstr/fire
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
# rm -f /usr/bin/fire
```

## how?
simply run `./fire` (or `fire`, if you installed) and enjoy.
```
$ fire
```

### why?
I'm bored

## credits
Thanks to @cylgom, for inspiring me to make this project.
More thanks to @cylgom, from whose repositories I sto^Hborrowed a lot
of stuff :)

## license
This project is licensed under the MIT license. View the LICENSE.md file
for more information.
