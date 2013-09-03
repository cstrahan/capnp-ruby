[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/cstrahan/capnp-ruby/trend.png)](https://bitdeli.com/free "Bitdeli Badge")

![Cap'n Proto][logo]

# Ruby Edition

This here is a [Ruby][ruby] wrapper for the official C++ implementation of [Cap'n Proto][capnp].

[![Build Status](https://api.travis-ci.org/cstrahan/capnp-ruby.png)](https://travis-ci.org/cstrahan/capnp-ruby)

# Installing

First [install libcapnp][libcapnp-install], then install the gem:

```bash
gem install capn_proto --pre
```

Remember to set the `CXX` and `CXXFLAGS` environment variables as necessary. As an OSX user, having followed the [instructions for installing libcapnp on OSX][libcapnp-install], the correct incantation is as follows:

```bash
export CXX=$HOME/clang-3.2/bin/clang++
export CXXFLAGS="-std=c++11 -stdlib=libc++"
gem install capn_proto --pre
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
