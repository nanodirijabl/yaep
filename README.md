# YÆP(b)

**Not for production use, raw AF**

Yet another Erlang-PHP bridge, Erlang cnode implementation for PHP.

With this extension one can start a hidden node in PHP and connect to regular Erlang node, send and receive messages using erlang types in "object oriented way". Pun intended.

Originally this project was concieved to support communication between PHP child processes and Erlang balancer/manager. That madness was inspired by [Roadrunner](https://github.com/roadrunner-server/roadrunner).

## Build

    phpize
    ./configure --with-erlang-interface=<path to>/erlang/lib/erl_interface-5.3
    make

### Docker

    docker build -t yaep:0.0.1 .

## Example

* Start erlang node in `./elixir`

        cd example/elixir
        elixir --sname 'srv' --cookie 'secretcookie' --no-halt -S mix

* Run PHP script with built extension

        php -dextension=$(pwd)/.libs/yaep.so example/php/example1.php

## TODO

- [ ] Add PHP stub docs

- [ ] Extend README

- [ ] Add PHP extension tests

- [ ] Review C code

- [ ] Clean up node name and PID checks on receive

- [ ] Add support persistent connections

- [ ] Add support of multiple nodes connections
