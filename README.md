![](https://github.com/lptstr/lptstr-images/blob/master/proj/fire/scrot.jpg?raw=true)

# fire

> The ancient DOOM fire animation in the terminal!

## what?
`fire` is a remake of the PSX DOOM fire animation in the terminal,
as seen in the [ly](https://github.com/nullgemm/ly) display manager.
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
- `gmake` (`bmake` is untested, but might work.)

Retrieve the source:
```
$ # via git:
$ git clone https://github.com/lptstr/fire --recurse
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
```
$ fire                     # no args for default animation
$ fire -h                  # help message
$ fire -Rw0 -f100          # matrix effect
$ fire -l2 -w2             # small fire with wind blowing east
$ fire -Rw0 -f1000000      # california animation
$ fire -t -l2 -f3          # truecolor!
```

### why?
I'm bored

## credits
This code was originally based on [`ly`](https://github.com/nullgemm/ly)'s
animation code.

## license
This project is licensed under the MIT license. View the [COPYING](COPYING)
file for more information.
