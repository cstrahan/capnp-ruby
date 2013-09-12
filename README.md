[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/cstrahan/capnp-ruby/trend.png)](https://bitdeli.com/free "Bitdeli Badge")

![Cap'n Proto][logo]

# Ruby Edition

This here is a [Ruby][ruby] wrapper for the official C++ implementation of [Cap'n Proto][capnp].

[![Build Status](https://travis-ci.org/cstrahan/capnp-ruby.png?branch=master)](https://travis-ci.org/cstrahan/capnp-ruby)

# Installing

First [install libcapnp][libcapnp-install], then install the gem:

```bash
gem install capn_proto --pre
```

The native extension for this gem requires a C++ compiler with C++11 features, so use the same C++ compiler and flags that you used to compile libcapnp (e.g. `CXX` and `CXXFLAGS`).

Note: this gem will attempt to automatically discover any necessary compiler flags for C++11 features (e.g. -std=c++11 -stdlib=libc++), so setting `CXXFLAGS` isn't strictly necessary.

As an OSX user, having followed the [instructions for installing libcapnp on OSX][libcapnp-install], the correct incantation is as follows:

```bash
CXX=$HOME/clang-3.2/bin/clang++ gem install capn_proto --pre
```

# Example

```ruby
require 'capn_proto'

module AddressBook extend CapnProto::SchemaLoader
  load_schema("addressbook.capnp")
end

def print_address_book(file)
  addresses = AddressBook::AddressBook.read_from(file)

  addresses.people.each do |person|
    puts "#{person.name} : #{person.email}"

    person.phones.each do |phone|
      puts "#{phone.type} : #{phone.number}"
    end

    which = person.employment.which

    if which == "unemployed"
      puts "unemployed"
    elsif which == 'employer'
      puts "employer: #{person.employment.employer}"
    elsif which == "school"
      puts "student at: #{person.employment.school}"
    elsif which == "selfEmployed"
      puts "self employed"
    end
  end
end

file = File.open("addressbook.bin", "rb")
print_address_book(file)
```

# Status

What's implemented:
- Schema parsing/loading
- Message reading

What's to come:
- Message writing

Proper support for [JRuby][jruby] will come after I implement support for Java.

[logo]: https://raw.github.com/cstrahan/capnp-ruby/master/media/captain_proto_small.png "Cap'n Proto"
[ruby]: http://www.ruby-lang.org/ "Ruby"
[capnp]: http://kentonv.github.io/capnproto/ "Cap'n Proto"
[jruby]: http://jruby.org/ "JRuby"
[libcapnp-install]: http://kentonv.github.io/capnproto/install.html "Installing Cap'n Proto"
[mit-license]: http://opensource.org/licenses/MIT "MIT License"
