[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/cstrahan/capnp-ruby/trend.png)](https://bitdeli.com/free "Bitdeli Badge")

![Cap'n Proto][logo]

# Ruby Edition

This here is a [Ruby][ruby] wrapper for the official C++ implementation of [Cap'n Proto][capnp].

# Installing

First [install libcapnp][libcapnp-install], then install the gem:

```bash
gem install capn_proto
```

Remember to set the CXX and CXXFLAGS environment variables as necessary. As an OSX user, having followed the [instructions for installing libcapnp on OSX][libcapnp-install], the correct incantation is as follows:

```bash
export CXX=$HOME/clang-3.2/bin/clang++
export CXXFLAGS="-std=c++11 -stdlib=libc++"
gem install capn_proto
```

# Status

- [x] Schema parsing (and recursive Module definition)
- [x] Message reading
- [ ] Message writing

Proper support for [JRuby][jruby] will come after I implement support for Java.

[logo]: https://raw.github.com/cstrahan/capnp-ruby/master/media/captain_proto_small.png "Cap'n Proto"
[ruby]: http://www.ruby-lang.org/ "Ruby"
[capnp]: http://kentonv.github.io/capnproto/ "Cap'n Proto"
[jruby]: http://jruby.org/ "JRuby"
[libcapnp-install]: [http://kentonv.github.io/capnproto/install.html]
